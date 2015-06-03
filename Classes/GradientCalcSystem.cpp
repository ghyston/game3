//
//  GradientCalcSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 03/06/15.
//
//

#include "GradientCalcSystem.h"

GradientCalcSystem::GradientCalcSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<ParticleComponent>();
	_gradientMap = NULL;
}

GradientCalcSystem::~GradientCalcSystem()
{
	
}

void GradientCalcSystem::initialize()
{
	positionMapper.init(*world);
	particleMapper.init(*world);
}

void GradientCalcSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	Vec2 tileCoords =  _gradientMap->getTileCoordsByPos(posCmpt->_pos);
	_gradientMap->recalculateGradientAt(tileCoords);
}