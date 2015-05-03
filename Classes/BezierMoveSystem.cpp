//
//  BezierMoveSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 19/04/15.
//
//

#include "BezierMoveSystem.h"

BezierMoveSystem::BezierMoveSystem()
{
	addComponentType<BezierMoveComponent>();
	addComponentType<PositionComponent>();
};

BezierMoveSystem::~BezierMoveSystem()
{
	
}

void BezierMoveSystem::initialize()
{
	bezMovementMapper.init(*world);
	positionMapper.init(*world);
};

void BezierMoveSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	BezierMoveComponent * bmc = bezMovementMapper.get(e);
	
	Vec2 newPos = calculateCurrentPos(bmc);
	posCmpt->_pos = newPos;
	
	float newAngle = calculateCurrentAngle(bmc);
	posCmpt->_angle = newAngle;
	
	if(bmc->_timeLeft == 0)
	{
		e.removeComponent<BezierMoveComponent>();
		e.refresh();
	}
	else
	{
		bmc->_timeLeft -= world->getDelta();
		
		if(bmc->_timeLeft < 0)
			bmc->_timeLeft = 0;
	}
	
	RenderComponent * rc = dynamic_cast<RenderComponent *>(e.getComponent<RenderComponent>());
	moveCoordsFromPosCMptToSprite(posCmpt, rc);	
};

void BezierMoveSystem::moveCoordsFromPosCMptToSprite(PositionComponent * posCmpt, RenderComponent * rendCmpt)
{
	if(rendCmpt == NULL)
		return;
	
	if(rendCmpt->_sprite == NULL)
		return;
	
	rendCmpt->_sprite->setPosition(posCmpt->_pos);
	rendCmpt->_sprite->setRotation(posCmpt->_angle);
}

Vec2 BezierMoveSystem::calculateCurrentPos(BezierMoveComponent * bmc)
{
	float t = (bmc->_duration - bmc->_timeLeft) / bmc->_duration;
	float omt = 1 - t; //one minus t
	
	float x = omt * omt * bmc->_P0.x + 2 * t * omt * bmc->_P1.x + t * t * bmc->_P2.x;
	float y = omt * omt * bmc->_P0.y + 2 * t * omt * bmc->_P1.y + t * t * bmc->_P2.y;
	return Vec2(x, y);
}

float BezierMoveSystem::calculateCurrentAngle(BezierMoveComponent * bmc)
{
	float t = (bmc->_duration - bmc->_timeLeft) / bmc->_duration;
	
	// derivative from bezie function
	float x = (bmc->_P0.x - 2 * bmc->_P1.x + bmc->_P2.x) * t * 2 - 2 * (bmc->_P0.x  - bmc->_P1.x);
	float y = (bmc->_P0.y - 2 * bmc->_P1.y + bmc->_P2.y) * t * 2 - 2 * (bmc->_P0.y  - bmc->_P1.y);
	
	//@todo: all this part can be implemented much clearly and/or moved to some math module!
	const float PI = 3.14159265;
	
	float angle = 0.0f;
	
	if(x < 0)
	{
		if(y < 0)
		{
			angle = atanf(x / y);
		}
		else
		{
			angle = PI / 2 + atanf(y / -x);
		}
	}
	else
	{
		if(y < 0)
		{
			angle = - atanf(x / -y);
		}
		else
		{
			angle = - PI / 2 - atanf(y / x);
		}
	}
	
	return angle * 180.0 / PI; //move to degrees
}



