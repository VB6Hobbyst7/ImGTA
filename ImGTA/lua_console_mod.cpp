/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "lua_console_mod.h"

#include "lua_engine.h"
#include "script.h"

#include "imgui_internal.h"

#include <algorithm>

LuaConsoleMod::LuaConsoleMod(DLLObject & dllObject, bool supportGlobals, LuaEngine & luaEngine) : Mod(dllObject, "Lua Console", true, supportGlobals), m_luaEngine(luaEngine)
{
	m_windowFlags = ImGuiWindowFlags_MenuBar;
	m_commandHistory.reserve(commandHistorySize);
	m_commands.reserve(commandCount);
	luaEngine.ListAllCommands(m_commands);
	m_commands.shrink_to_fit();
}

void LuaConsoleMod::Load()
{
	m_settings = m_dllObject.GetUserSettings().luaConsole;
}

void LuaConsoleMod::Unload()
{
	m_dllObject.GetUserSettings().luaConsole = m_settings;
}

void LuaConsoleMod::Think()
{

}

void LuaConsoleMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Lua"))
		{
			if (ImGui::MenuItem("Reload natives.lua"))
				m_luaEngine.LoadLuaNatives();

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Misc"))
		{
			ImGui::MenuItem("Show information", NULL, &m_settings.showInfo);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

bool LuaConsoleMod::Draw()
{
	ImGui::SetWindowFontScale(m_settings.common.menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_settings.common.contentFontSize);

	if (m_settings.showInfo)
	{
		ImGui::TextColored(ImVec4(255, 0, 0, 255), "If trying out random functions,\n"
						   "be aware that some listed in your 'natives.lua' may not be available\n"
						   "in ScriptHookV and it will crash.");
		ImGui::TextColored(ImVec4(0, 25, 0, 255), "Look at natives.lua for function names or tab for autocompletion. Examples:");
		ImGui::TextColored(ImVec4(0, 25, 0, 255), "val = entity.get_entity_health(2)");
		ImGui::TextColored(ImVec4(0, 25, 0, 255), "print(val)");
		ImGui::TextColored(ImVec4(0, 25, 0, 255), "entity.set_entity_health(2, 150)");
	}

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // thanks omar
	if (ImGui::BeginChild("ConsoleText", ImVec2(0.0f, -footer_height_to_reserve)))
	{
		ImGui::TextUnformatted(LuaEngine::luaStream.str().c_str());
		if (m_scrollDown)
		{
			ImGui::SetScrollHereY(1.0f);
			m_scrollDown = false;
		}
		ImGui::EndChild(); // legacy dont-care-about-return-value end.
	}
	
	ImGui::Separator();
	ImGui::SetNextItemWidth(ImGui::GetCurrentWindow()->Size.x - 75.0f);
	
	if (ImGui::InputText("Input", m_input, sizeof(m_input),
		ImGuiInputTextFlags_EnterReturnsTrue
		| ImGuiInputTextFlags_CallbackHistory
		| ImGuiInputTextFlags_CallbackCompletion
		| ImGuiInputTextFlags_CallbackEdit,
		&InputTextCallbackStub, (void*)this))
	{
		strcpy_s(m_luaInput, m_input);
		strcpy_s(m_input, "");
		if (m_commandHistory.size() < commandHistorySize)
			m_commandHistory.emplace_back(m_luaInput);
		else
			m_commandHistory.at(m_currentHistoryId) = m_luaInput;
		m_currentHistoryId = m_lastInputHistoryId;
		IncrementCurrentHistoryId();
		m_lastInputHistoryId = m_currentHistoryId;
		m_inHistory = false;
		ImGui::SetKeyboardFocusHere();

		LuaEngine::luaStream << "> " << m_luaInput << std::endl;
		m_dllObject.RunOnNativeThread([=]
		{
			if (m_luaEngine.DoLuaString(m_luaInput) != LUA_OK)
				LuaEngine::luaStream << m_luaEngine.GetLastLuaError() << std::endl;
		});
		m_scrollDown = true;
	}

	return true;
}


int LuaConsoleMod::InputTextCallback(ImGuiInputTextCallbackData * data)
{
	if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
	{
		m_tabbingCandidates = false;
	}
	else if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
	{
		const char* word_end = data->Buf + data->CursorPos;
		const char* word_start = word_end;

		// If not currently tabbing candidates or the input hasn't changed
		if (!m_tabbingCandidates)
		{
			// Completion algo taken from imgui_demo.cpp
			// Locate beginning of current word
			while (word_start > data->Buf)
			{
				const char c = word_start[-1];
				if (c == ' ' || c == '\t' || c == ',' || c == ';'
					|| c == '(' || c == '{' || c == '['
					|| c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
					|| c == '!' || c == '|' || c == '&' || c == '~' || c == '^')
					break;
				word_start--;
			}
			int word_size = (int)(word_end - word_start);
			std::string word{ word_start };
			m_lastInputBuffer = word;

			// Build a list of candidates
			std::vector<std::string> candidates;
			for (const auto & command : m_commands)
			{
				if (command.substr(0, word_size) == word.substr(0, word_size))
					candidates.push_back(command);
			}

			if (candidates.size() == 1)
			{
				// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
				data->DeleteChars((int)(word_start - data->Buf), word_size);
				data->InsertChars(data->CursorPos, candidates.at(0).c_str());
			}
			else if (!candidates.empty())
			{
				// Keep the candidates for extended tabbing (another tab after this one)
				m_lastCandidates = candidates;
				m_lastCandidates.push_back(m_lastInputBuffer);
				m_tabbingCandidates = true;
				m_lastCandidatesId = -1; // ID will be incremented before accessing the first candidate

				// Multiple matches. Complete as much as we can..
				// So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
				int match_len = word_size;
				for (;;)
				{
					int c = 0;
					bool all_candidates_matches = true;
					for (int i = 0; i < candidates.size() && all_candidates_matches; i++)
						if (i == 0)
							c = toupper(candidates[i][match_len]);
						else if (c == 0 || c != toupper(candidates[i][match_len]))
							all_candidates_matches = false;
					if (!all_candidates_matches)
						break;
					match_len++;
				}

				if (match_len > 0)
				{
					data->DeleteChars((int)(word_start - data->Buf), word_size);
					data->InsertChars(data->CursorPos, candidates.at(0).c_str(), candidates.at(0).c_str() + match_len);
				}
			}
		}
		else
		{
			// Rotate the candidates ID
			if (data->EventFlag == ImGuiKeyModFlags_Shift)
				m_lastCandidatesId = (m_lastCandidatesId - 1) % m_lastCandidates.size();
			else
				m_lastCandidatesId = (m_lastCandidatesId + 1) % m_lastCandidates.size();

			const std::string currentCandidate = m_lastCandidates.at(m_lastCandidatesId);
			// Completion algo taken from imgui_demo.cpp
			// Locate beginning of current word
			while (word_start > data->Buf)
			{
				const char c = word_start[-1];
				if (c == ' ' || c == '\t' || c == ',' || c == ';'
					|| c == '(' || c == '{' || c == '['
					|| c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
					|| c == '!' || c == '|' || c == '&' || c == '~' || c == '^')
					break;
				word_start--;
			}
			int word_size = (int)(word_end - word_start);
			std::string word{ word_start };

			// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
			data->DeleteChars((int)(word_start - data->Buf), word_size);
			data->InsertChars(data->CursorPos, currentCandidate.c_str());

		}
	}
	else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
	{
		if (data->EventKey == ImGuiKey_UpArrow)
		{
			if (m_inHistory)
				DecrementCurrentHistoryId();
			else
			{
				m_inHistory = true;
				m_lastInputHistoryId = m_currentHistoryId;
				m_savedCommand = std::string(data->Buf);
			}
		}
		else if (data->EventKey == ImGuiKey_DownArrow)
		{
			if (m_inHistory)
			{
				if (m_currentHistoryId == m_lastInputHistoryId)
					m_inHistory = false;
				else
					IncrementCurrentHistoryId();
			}
			else
				m_confirmedOutOfHistory = true;
		}

		if (m_inHistory)
		{
			if (m_commandHistory.size() > 0
				&& m_currentHistoryId < m_commandHistory.size())
			{
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, m_commandHistory.at(m_currentHistoryId).c_str());
			}
		}
		else
		{
			data->DeleteChars(0, data->BufTextLen);
			data->InsertChars(0, m_savedCommand.c_str());
			m_confirmedOutOfHistory = false;
		}
	}
	return 0;
}
void LuaConsoleMod::IncrementCurrentHistoryId()
{
	if (m_currentHistoryId < (int)m_commandHistory.size())
		m_currentHistoryId = (m_currentHistoryId + 1) % commandHistorySize;
}
void LuaConsoleMod::DecrementCurrentHistoryId()
{
	if (m_currentHistoryId > 0 || m_commandHistory.size() == commandHistorySize)
		m_currentHistoryId = (m_currentHistoryId - 1) % commandHistorySize;
}