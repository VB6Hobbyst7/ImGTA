/*
 * Copyright (c) 2021, James Puleo <james@jame.xyz>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "model.h"

#include "natives.h"

Model::Model(const char *model, bool block) : Model(MISC::GET_HASH_KEY((char *)model), block) {}

Model::Model(Hash modelHash, bool block) : m_hash(modelHash)
{
	m_isValid = STREAMING::IS_MODEL_IN_CDIMAGE(m_hash);

	if (IsValid())
	{
		STREAMING::REQUEST_MODEL(m_hash);
		if (block)
			WaitForLoad();
	}
}

Model::~Model()
{
	if (!m_marked)
		Unload();
}

void Model::WaitForLoad()
{
	while (!STREAMING::HAS_MODEL_LOADED(m_hash))
		WAIT(0);
}

bool Model::IsValid()
{
	return m_isValid;
}

void Model::Unload()
{
	if (m_isValid)
	{
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(m_hash);
		m_marked = true;
	}
}

Hash Model::GetHash()
{
	return m_hash;
}

bool Model::IsVehicle()
{
	return STREAMING::IS_MODEL_A_VEHICLE(m_hash);
}