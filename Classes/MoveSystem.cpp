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
	Vec2 tileCoords = getTileCoordsForPosition(posCmpt->_pos);
	int tileID = getIdByCoords(tileCoords);
	Vec2 tileVelocity = vecMap[tileID];
	
	movCmp->_speed.x = 10 * tileVelocity.x * world->getDelta();
	movCmp->_speed.y = 10 * tileVelocity.y * world->getDelta();
	
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
int MoveSystem::getIdByCoords(Vec2 coords)
{
	return coords.y * mapSize.x + coords.x;
}

Vec2 MoveSystem::getTileCoordsForPosition(Vec2 pos)
{
	int x = pos.x / tileSize.x;
	int y = ((mapSize.y * tileSize.y) - pos.y) / tileSize.y;
	return Vec2(x, y);
}