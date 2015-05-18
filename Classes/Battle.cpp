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

#include "DebugWaveLayer.h"

Battle::Battle()
{
	_touchedShipId = -1;
	_gameMap = NULL;
}

Battle::~Battle()
{
	setGameMap(NULL);
}

bool Battle::init()
{
	// init ECS
	SystemManager * sysManager =  _world.getSystemManager();
	MoveSystem * ms = new MoveSystem();
	sysManager->setSystem(ms);
	sysManager->setSystem(new BezierMoveSystem());
	sysManager->initializeAll();
	
	GameMap * gameMap = GameMap::createWithFileName("second.tmx");
	setGameMap(gameMap);
	
	ParticleMap * particleMap = ParticleMap::createWithParams(gameMap);
	setParticleMap(particleMap);
	
	EventCustom * event = new EventCustom("MAP_LOADED");
	event->autorelease();
	event->setUserData(gameMap->getTiledMap());
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
	
	//add tower for test
	EntityFabric::createParticle(_world);
	

	ms->_gameMap = gameMap;
	ms->_particleMap = particleMap;
		
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

void Battle::updateGoal(Vec2 coords)
{
	Vec2 goalPos = _gameMap->getTileCoordsForPosition(coords);
	getParticleMap()->recalculateGoal(goalPos);
	
	//@todo: think, how to update
	// Upd debug layer
	/*
	 EventCustom * testEvent = new EventCustom("DEBUG_MAP_UPDATED");
	testEvent->autorelease();
	testEvent->setUserData(_heatmap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(testEvent);
	
	// Upd debug layer
	EventCustom * testEvent2 = new EventCustom("DEBUG_VEC_MAP_UPDATED");
	testEvent2->autorelease();
	testEvent2->setUserData(_collisionVecMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(testEvent2);*/

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
















