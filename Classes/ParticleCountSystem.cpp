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
	addComponentType<ArmyComponent>();
	_countMap = NULL;
}

ParticleCountSystem::~ParticleCountSystem()
{
	
}

void ParticleCountSystem::initialize()
{
	positionMapper.init(*world);
	armyMapper.init(*world);
};

void ParticleCountSystem::begin()
{
	_countMap->clean();
}

void ParticleCountSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	ArmyComponent * armyCmpt = armyMapper.get(e);
	
	Vec2 tileCoords =  _countMap->getTileCoordsByPos(posCmpt->_pos);
	
	if(armyCmpt->_armyId == ArmyIdEnum::RED)
		_countMap->incCountR(tileCoords);
	else if(armyCmpt->_armyId == ArmyIdEnum::GREEN)
		_countMap->incCountG(tileCoords);
	
	//@todo: all other types, or (better!) include by memory offset!
}

void ParticleCountSystem::end()
{
	_countMap->resetAlpha();
}