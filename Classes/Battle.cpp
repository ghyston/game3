//
//  Battle.cpp
//  Game3
//
//  Created by Stepanov Ilia on 12/04/15.
//
//

#include "Battle.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "NodeComponent.h"
#include "RenderComponent.h"
#include "NodeComponent.h"
#include "EnergyStorageComponent.h"
#include "EnergyGeneratorComponent.h"

#include "MoveSystem.h"
#include "BezierMoveSystem.h"

#include "EntityFabric.h"

Battle::Battle()
{
	_touchedShipId = -1;
	
}

Battle::~Battle()
{
	
}

bool Battle::init(int mapCellsX, int mapCellsY)
{
	// init ECS
	SystemManager * sysManager =  _world.getSystemManager();
	sysManager->setSystem(new MoveSystem());
	sysManager->setSystem(new BezierMoveSystem());
	sysManager->initializeAll();
	
	//add tower for test
	_touchedShipId = EntityFabric::createShip(_world);
	
	return true;
}

void Battle::update(float delta)
{
	_world.setDelta(delta);
	_world.loopStart();
	
	SystemManager * sysManager =  _world.getSystemManager();
	
	MoveSystem* ms = (MoveSystem*)sysManager->getSystem<MoveSystem>();
	ms->process();
	
	BezierMoveSystem* bms = (BezierMoveSystem*)sysManager->getSystem<BezierMoveSystem>();
	bms->process();
}

void Battle::startShipMoving(Vec2 newCoords)
{
	if(_touchedShipId == -1)
		return;
	
	Entity& ship = _world.getEntity(_touchedShipId);
	BezierMoveComponent * bmc = dynamic_cast<BezierMoveComponent *>(ship.getComponent<BezierMoveComponent>());
	PositionComponent * pc = dynamic_cast<PositionComponent *>(ship.getComponent<PositionComponent>());
	
	if(bmc != NULL)
	{
		ship.removeComponent<BezierMoveComponent>();
	}
	bmc = new BezierMoveComponent();
	
	bmc->_P0 = pc->_pos;
	float radius = 350.0f;
	//@todo: all this part can be implemented much clearly and/or moved to some math module!
	const float PI = 3.14159265;
	Vec2 diff = Vec2(-sinf(pc->_angle*PI/180.0), -cosf(pc->_angle*PI/180));
	
	bmc->_P1 = Vec2(pc->_pos.x + radius * diff.x, pc->_pos.y + radius * diff.y);
	bmc->_P2 = newCoords;
	bmc->_timeLeft = 5;
	bmc->_duration = 5;
	
	ship.addComponent(bmc);
	ship.refresh();
}
















