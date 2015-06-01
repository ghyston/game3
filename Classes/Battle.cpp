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
#include "ParticleHandlingSystem.h"

#include "EntityFabric.h"

#include "DebugWaveLayer.h"

Battle::Battle()
{
	_touchedShipId = -1;
	_gameMap = NULL;
	_particleMap = NULL;
	_countMap = NULL;
	_gradientMap = NULL;
}

Battle::~Battle()
{
	setGameMap(NULL);
	setParticleMap(NULL);
	setCountMap(NULL);
	setGradientMap(NULL);
}

bool Battle::init()
{
	// init ECS
	SystemManager * sysManager =  _world.getSystemManager();
	MoveSystem * ms = new MoveSystem();
	ParticleHandlingSystem * phs = new ParticleHandlingSystem();
	sysManager->setSystem(ms);
	sysManager->setSystem(new BezierMoveSystem());
	sysManager->setSystem(phs);
	sysManager->initializeAll();
	
	TMXTiledMap * tmxMap = TMXTiledMap::create("second.tmx");
	
	GameMap * gameMap = GameMap::createWithTmxMap(tmxMap);
	setGameMap(gameMap);
	
	ParticleMap * particleMap = ParticleMap::createWithParams(gameMap);
	setParticleMap(particleMap);
	
	EventCustom * event = new EventCustom("MAP_LOADED");
	event->autorelease();
	event->setUserData(tmxMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
	
	const float arraySpritePixelsPerTile = 10; //very hard to explain this constant meaning
	Size countMapSize;
	countMapSize.width = gameMap->getMapSizeX() * arraySpritePixelsPerTile;
	countMapSize.height = gameMap->getMapSizeY() * arraySpritePixelsPerTile;
	
	float tileSize = gameMap->getTileSize().width / arraySpritePixelsPerTile; //@todo: omly width?
	CountMap * countMap = CountMap::create(countMapSize, tileSize);
	setCountMap(countMap);
	
	GradientMap * gradientsMap = GradientMap::createWithParams(countMap);
	setGradientMap(gradientsMap);
	
	EventCustom * event2 = new EventCustom("COUNT_MAP_LOADED");
	event2->autorelease();
	event2->setUserData(countMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event2);

	for (int i = 0; i < 10000; i++)
		EntityFabric::createParticle(_world);
	
	ms->_gameMap = gameMap;
	ms->_particleMap = particleMap;
	ms->_gradientMap = gradientsMap;
	ms->_countMap = countMap;
	phs->_countMap = countMap;
	phs->_gradientMap = gradientsMap;
		
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
	
	ParticleHandlingSystem * phs = (ParticleHandlingSystem*)sysManager->getSystem<ParticleHandlingSystem>();
	phs->preProcess();
	phs->process();
	phs->postProcess();
}

void Battle::updateGoal(Vec2 coords)
{
	Vec2 goalPos = _gameMap->getTileCoordsByPos(coords);
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
















