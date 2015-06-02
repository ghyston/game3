//
//  ParticleHandlingSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "ParticleHandlingSystem.h"

ParticleHandlingSystem::ParticleHandlingSystem()
{
	addComponentType<PositionComponent>();
	_countMap = NULL;
	_gradientMap = NULL;
}

ParticleHandlingSystem::~ParticleHandlingSystem()
{
	
}

void ParticleHandlingSystem::initialize()
{
	positionMapper.init(*world);
};

void ParticleHandlingSystem::preProcess()
{
	_countMap->clean();
	_gradientMap->clearGrids();
}

void ParticleHandlingSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	
	Vec2 tileCoords =  _countMap->getTileCoordsByPos(posCmpt->_pos);
	_countMap->incCountR(tileCoords);
}

void ParticleHandlingSystem::postProcess()
{
	_countMap->resetAlpha();
	_gradientMap->recalculateGradient();
}