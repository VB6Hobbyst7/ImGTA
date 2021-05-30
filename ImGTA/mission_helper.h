/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once
#include "main.h"

// TOOD: actually support other versions
class MissionHelper
{
public:
	MissionHelper(eGameVersion ver);

	void Fail();
	void Skip();

private:
	eGameVersion m_version;
};