#include "test_mod.h"
#include "natives.h"
#include "script.h"


void TestMod::Load()
{

}

void TestMod::Unload()
{

}

void TestMod::Think()
{

}

void TestMod::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Watch"))
		{

			if (ImGui::MenuItem("Load all debug"))
			{
			}

			if (ImGui::MenuItem("Clear"))
			{
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool TestMod::Draw()
{
	ImGui::SetWindowFontScale(m_menuFontSize);
	DrawMenuBar();

	ImGui::SetWindowFontScale(m_contentFontSize);
	ImGui::Text("RAS_maybe_loading_screen_tests");

	return true;
}