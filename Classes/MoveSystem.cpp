//
//  MoveSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#include "MoveSystem.h"

MoveSystem::MoveSystem()
{
	addComponentType<MovementComponent>();
	addComponentType<PositionComponent>();
	_gameMap = NULL;
};

MoveSystem::~MoveSystem()
{
	
}

void MoveSystem::initialize()
{
	movementMapper.init(*world);
	positionMapper.init(*world);
};

// @todo: this system operates potentional system, separate to two systems:
// basic movement and potentional movement!
void MoveSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	MovementComponent * movCmp = movementMapper.get(e);
	
	// update speed by potential map
	Vec2 tileCoords = _gameMap->getTileCoordsForPosition(posCmpt->_pos);
	int tileID = _gameMap->getIdByCoords(tileCoords);
	
	
	Vec2 tileVelocity = 100 * _particleMap->getVecByTileID(tileID);
	Vec2 collisionVelocity = 100 * _gameMap->getCollisionVecByTileID(tileID);
	
	Vec2 steering = tileVelocity + collisionVelocity;
	float steerLength = steering.length();
	
	const float MAX_FORCE = 50.0f;
	if(steerLength >= MAX_FORCE)
	{
		steering.scale(MAX_FORCE / steerLength);
	}
	
	
	movCmp->_speed = movCmp->_speed + steering;
	float speed = movCmp->_speed.length();
	const float MAX_SPEED = 150.0f;
	if(speed >= MAX_SPEED)
	{
		movCmp->_speed.scale(MAX_SPEED / speed);
	}
	
	//movCmp->_speed.x += tileVelocity.x * world->getDelta();
	//movCmp->_speed.y += tileVelocity.y * world->getDelta();
	//movCmp->_speed.normalize();
	//movCmp->_speed *= 100;
	
	// update position
	posCmpt->_pos.x += movCmp->_speed.x * world->getDelta();
	posCmpt->_pos.y += movCmp->_speed.y * world->getDelta();
	
	// update render component
	RenderComponent * rc = dynamic_cast<RenderComponent *>(e.getComponent<RenderComponent>());
	if(rc == NULL)
		return;
	
	if(rc->_sprite == NULL)
		return;
		
	rc->_sprite->setPosition(positionMapper.get(e)->_pos);
};

//@todo: duplicated at battle, move map stuff to other class!
/*int MoveSystem::getIdByCoords(Vec2 coords)
{
	return coords.y * mapSize.x + coords.x;
}

Vec2 MoveSystem::getTileCoordsForPosition(Vec2 pos)
{
	int x = pos.x / tileSize.x;
	int y = ((mapSize.y * tileSize.y) - pos.y) / tileSize.y;
	return Vec2(x, y);
}*/