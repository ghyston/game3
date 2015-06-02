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
	//_gameMap = NULL;
};

MoveSystem::~MoveSystem()
{
	
}

void MoveSystem::initialize()
{
	movementMapper.init(*world);
	positionMapper.init(*world);
};

void MoveSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	MovementComponent * movCmp = movementMapper.get(e);
	
	float speed = movCmp->_speed.length();
	const float MAX_SPEED = 150.0f;
	if(speed >= MAX_SPEED)
	{
		movCmp->_speed.scale(MAX_SPEED / speed);
	}
	
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
