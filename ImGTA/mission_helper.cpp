/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "mission_helper.h"
#include "utils.h"
#include <stdexcept>
#include <map>
#include "global_id.h"



MissionHelper::MissionHelper(eGameVersion ver) : m_version(ver)
{
	if (!IsVersionSupportedForGlobals(ver))
		throw new std::logic_error("Unsupported version supplied for MissionHelper");
}

void MissionHelper::Fail()
{
	*getGlobalPtr(GlobalID::_89962) = 0;
}

void MissionHelper::Skip()
{
	*getGlobalPtr(GlobalID::_84544) = 1;
	*getGlobalPtr(GlobalID::_54748) = 1;
	*getGlobalPtr(GlobalID::_89962) = 9;
}