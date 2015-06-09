//
//  ParticleCountSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "ParticleCountSystem.h"

ParticleCountSystem::ParticleCountSystem()
{
	addComponentType<PositionComponent>();
	_countMap = NULL;
}

ParticleCountSystem::~ParticleCountSystem()
{
	
}

void ParticleCountSystem::initialize()
{
	positionMapper.init(*world);
};

void ParticleCountSystem::begin()
{
	_countMap->clean();
}

void ParticleCountSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	
	Vec2 tileCoords =  _countMap->getTileCoordsByPos(posCmpt->_pos);
	_countMap->incCountR(tileCoords);
}

void ParticleCountSystem::end()
{
	_countMap->resetAlpha();
}