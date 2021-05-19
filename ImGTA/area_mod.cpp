#include "area_mod.h"
#include "natives.h"
#include "script.h"
#include "anim_dict.h"
#include "utils.h"
#include "imgui_extras.h"


void AreaMod::Load()
{

}

void AreaMod::Unload()
{

}

void AreaMod::Think()
{
	if ((m_constantUpdate || m_wantsUpdate))
	{
		Ped ped = PLAYER::PLAYER_PED_ID();
		if (ENTITY::DOES_ENTITY_EXIST(ped))
		{
			m_currentPos = ENTITY::GET_ENTITY_COORDS(ped, false);

			m_isInAngledArea = ENTITY::IS_ENTITY_IN_ANGLED_AREA(ped,
				m_angledAreaStartPoint.x, m_angledAreaStartPoint.y, m_angledAreaStartPoint.z,
				m_angledAreaEndPoint.x, m_angledAreaEndPoint.x, m_angledAreaEndPoint.x,
				m_angledAreaWidth, FALSE, m_angledAreaIncludeZ, 0);

			m_isInArea = ENTITY::IS_ENTITY_IN_AREA(ped,
				m_areaStartPoint.x, m_areaStartPoint.y, m_areaStartPoint.z,
				m_areaEndPoint.x, m_areaEndPoint.x, m_areaEndPoint.x,
				m_areaUnk0, m_areaUnk1, (Any)m_areaUnk2);

			m_isAtCoord = ENTITY::IS_ENTITY_AT_COORD(ped,
				m_coordPoint.x, m_coordPoint.y, m_coordPoint.z,
				m_coordSize.x, m_coordSize.y, m_coordSize.z,
				m_coordUnk0, m_coordUnk1, m_coordUnk2);
		}

		if (m_drawBox)
		{
			GRAPHICS::DRAW_BOX(m_startBoxPoint.x, m_startBoxPoint.y, m_startBoxPoint.z,
				m_endBoxPoint.x, m_endBoxPoint.y, m_endBoxPoint.z,
				220, 50, 50, 125);

			// Marker types: https://docs.fivem.net/docs/game-references/markers/
			GRAPHICS::DRAW_MARKER(0, m_startBoxPoint.x, m_startBoxPoint.y, m_startBoxPoint.z,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f,
				50, 220, 50, 125,
				TRUE, TRUE, 2, TRUE,
				NULL, NULL, FALSE);

			GRAPHICS::DRAW_MARKER(0, m_endBoxPoint.x, m_endBoxPoint.y, m_endBoxPoint.z,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f,
				50, 220, 50, 125,
				TRUE, TRUE, 2, TRUE,
				NULL, NULL, FALSE);

			if (m_areaSameBox)
			{
				m_areaStartPoint = m_startBoxPoint;
				m_areaEndPoint = m_endBoxPoint;
			}

			if (m_angledAreaSameBox)
			{
				m_angledAreaStartPoint = m_startBoxPoint;
				m_angledAreaEndPoint = m_endBoxPoint;
			}
		}

		if (m_drawInGame && m_showInGame)
		{
			float screenX, screenY;
			HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(m_currentPos.x, m_currentPos.y, m_currentPos.z + m_drawOffsetZ,
				&screenX, &screenY);

			char buf[256] = "";
			sprintf_s(buf, "Angled area: %s\nArea: %s\nCoord: %s",
				BoolToStr(m_isInAngledArea), BoolToStr(m_isInArea), BoolToStr(m_isAtCoord));
			DrawTextToScreen(buf, screenX, screenY, m_inGameFontSize, eFont::FontChaletLondon);
		}

		m_wantsUpdate = false;
	}
}

void AreaMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("HUD"))
		{
			ImGui::MenuItem("Show on HUD", NULL, &m_drawInGame);

			if (ImGui::BeginMenu("Misc"))
			{
				ImGui::InputFloat("Z offset", &m_drawOffsetZ, 0.1f);
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool AreaMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);

	ImGui::Checkbox("Constant Updates?", &m_constantUpdate);
	if (!m_constantUpdate)
		if (ImGui::Button("Update"))
			m_wantsUpdate = true;

	if (ImGui::TreeNodeEx("Draw Box", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGuiExtras::InputVector3("Start point", &m_startBoxPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current Start"))
			m_startBoxPoint = m_currentPos;

		ImGuiExtras::InputVector3("End point", &m_endBoxPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current End"))
			m_endBoxPoint = m_currentPos;

		if (ImGui::Button("Draw"))
			m_drawBox = true;
		if (ImGui::Button("Erase"))
			m_drawBox = false;
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Angled Area"))
	{
		ImGui::Checkbox("Same as box", &m_angledAreaSameBox);
		ImGuiExtras::InputVector3("Start point", &m_angledAreaStartPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current Start"))
			m_angledAreaStartPoint = m_currentPos;

		ImGuiExtras::InputVector3("End point", &m_angledAreaEndPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current End"))
			m_angledAreaEndPoint = m_currentPos;

		ImGui::InputFloat("Width", &m_angledAreaWidth);
		ImGui::Checkbox("Debug", &m_angledAreaDebug);
		ImGui::Checkbox("Include Z", &m_angledAreaIncludeZ);
		ImGui::InputInt("Unk0", &m_angledAreaUnk0);
		ImGui::Separator();
		ImGui::Text("Is player in angled area: %s", BoolToStr(m_isInAngledArea));
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Area"))
	{
		ImGui::Checkbox("Same as box", &m_areaSameBox);
		ImGuiExtras::InputVector3("Start point", &m_areaStartPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current Start"))
			m_areaStartPoint = m_currentPos;

		ImGuiExtras::InputVector3("End point", &m_areaEndPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current End"))
			m_areaEndPoint = m_currentPos;

		ImGui::Checkbox("Unk", &m_areaUnk0);
		ImGui::Checkbox("Unk1", &m_areaUnk1);
		ImGui::InputInt("Unk2", &m_areaUnk2);
		ImGui::Separator();
		ImGui::Text("Is player in area: %s", BoolToStr(m_isInArea));
		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNode("Coord"))
	{
		ImGuiExtras::InputVector3("Coord point", &m_coordPoint);
		ImGui::SameLine();
		if (ImGui::Button("Current"))
			m_coordPoint = m_currentPos;

		ImGuiExtras::InputVector3("Size", &m_coordSize);

		ImGui::Checkbox("Unk", &m_coordUnk0);
		ImGui::Checkbox("Unk1", &m_coordUnk1);
		ImGui::InputInt("Unk2", &m_coordUnk2);
		ImGui::Separator();
		ImGui::Text("Is player at coord: %s", BoolToStr(m_isAtCoord));
		ImGui::TreePop();
	}


	return true;
}