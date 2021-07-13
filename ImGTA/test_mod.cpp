/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 * Copyright (c) 2021, Rayope
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "test_mod.h"

#include "script.h"

#include "natives.h"


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
		if (ImGui::BeginMenu("Menu 1"))
		{

			if (ImGui::MenuItem("Item 1"))
			{
			}

			if (ImGui::MenuItem("Item 2"))
			{
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

bool TestMod::Draw()
{
	DrawMenuBar();

	ImGui::Text("Text sample");

	return true;
}