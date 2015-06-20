//
//  ParticleMoveSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 02/06/15.
//
//

#include "ParticleMoveSystem.h"

ParticleMoveSystem::ParticleMoveSystem()
{
	addComponentType<MovementComponent>();
	addComponentType<ParticleComponent>();
	addComponentType<PositionComponent>();
};

ParticleMoveSystem::~ParticleMoveSystem()
{
	
}

void ParticleMoveSystem::initialize()
{
	movementMapper.init(*world);
	particleMapper.init(*world);
	positionMapper.init(*world);
};

void ParticleMoveSystem::processEntity(artemis::Entity &e)
{
	ParticleComponent * particleCmp = particleMapper.get(e);
	PositionComponent * posCmpt = positionMapper.get(e);
	MovementComponent * movCmp = movementMapper.get(e);
	
	// update speed by potential map
	Vec2 tileCoords = _gameMap->getTileCoordsByPos(posCmpt->_pos);
	int tileID = _gameMap->getIdByTileCoords(tileCoords);
	
	//Calculate collision
	{
		Vec2 collisionVelocity = _gameMap->getCollisionVecByTileID(tileID);
		if((movCmp->_speed.x * collisionVelocity.x) < 0)
		{
			movCmp->_speed.x *= -1;
		}
		
		if((movCmp->_speed.y * collisionVelocity.y) < 0)
		{
			movCmp->_speed.y *= -1;
		}
	}
	
	
	Vec2 tileVelocity = 100 * particleCmp->_map->getVecByTileID(tileID);
	//Vec2 collisionVelocity = 100 * _gameMap->getCollisionVecByTileID(tileID);
	
	Vec2 steeringForce = tileVelocity;// + collisionVelocity;
	float steerLength = steeringForce.length();
	
	const float MAX_FORCE = 50.0f;
	if(steerLength >= MAX_FORCE)
	{
		steeringForce.scale(MAX_FORCE / steerLength);
	}
	
	Vec2 countTileCoords = _countMap->getTileCoordsByPos(posCmpt->_pos);
	int countTileId = _gradientMap->getIdByTileCoords(countTileCoords);
	Vec2 gradForce = _gradientMap->getVecByTileID(countTileId);
	float gradLength = gradForce.length();
	if(gradLength >= MAX_FORCE * 2)
	{
		gradForce.scale(MAX_FORCE * 2 / gradLength);
	}
	
	movCmp->_speed = movCmp->_speed + steeringForce + gradForce;
};