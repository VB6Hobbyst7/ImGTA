#include "lua_console_mod.h"
#include "imgui_internal.h"
#include "script.h"
#include "lua_engine.h"
#include "lua.h"
#include <algorithm>

void LuaConsoleMod::Load()
{

}

void LuaConsoleMod::Unload()
{

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
				LoadLuaNatives();

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

bool LuaConsoleMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

	ImGui::TextColored(ImVec4(255, 0, 0, 255), "Needs testing, can crash your game.");
	ImGui::TextColored(ImVec4(0, 25, 0, 255), "Look at natives.lua for function names. Examples:");
	ImGui::TextColored(ImVec4(0, 25, 0, 255), "val = entity.get_entity_health(2)");
	ImGui::TextColored(ImVec4(0, 25, 0, 255), "print(val)");
	ImGui::TextColored(ImVec4(0, 25, 0, 255), "entity.set_entity_health(2, 150)");

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // thanks omar
	if (ImGui::BeginChild("ConsoleText", ImVec2(0.0f, -footer_height_to_reserve)))
	{
		ImGui::TextUnformatted(lua_stream.str().c_str());
		ImGui::SetScrollHereY(0.999f);
		ImGui::EndChild(); // legacy dont-care-about-return-value end.

	}
	
	ImGui::Separator();
	ImGui::SetNextItemWidth(ImGui::GetCurrentWindow()->Size.x - 75.0f);

	//bool uparrow = ImGui::IsKeyPressedMap( ImGuiKey_UpArrow, false );
	//bool downarrow = ImGui::IsKeyPressedMap( ImGuiKey_DownArrow, false );

	//if ( uparrow )
	//    m_iCurrentHistory = std::min( m_iCurrentHistory + 1, ( int )m_commandHistory.size() - 1 );
	//else if ( downarrow )
	//    m_iCurrentHistory = std::max( m_iCurrentHistory - 1, 0 );

	//if ( m_commandHistory.size() > 0 && ( uparrow || downarrow ) )
	//    strcpy_s( m_szInput, m_commandHistory[m_commandHistory.size() - m_iCurrentHistory].c_str() );

	if (ImGui::InputText("Input", m_input, sizeof(m_input), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		strcpy_s(m_luaInput, m_input);
		strcpy_s(m_input, "");
		m_commandHistory.push_back(m_luaInput);
		m_currentHistory = 0;
		ImGui::SetKeyboardFocusHere();

		lua_stream << "> " << m_luaInput << std::endl;
		RunOnNativeThread([=]
		{
			if (DoLuaString(m_luaInput) != LUA_OK)
				lua_stream << GetLastLuaError() << std::endl;
		});
	}

	return true;
}
