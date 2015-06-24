//
//  Battle.cpp
//  Game3
//
//  Created by Stepanov Ilia on 12/04/15.
//
//

#include "Battle.h"

#include "time.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "NodeComponent.h"
#include "RenderComponent.h"
#include "NodeComponent.h"
#include "EnergyStorageComponent.h"
#include "EnergyGeneratorComponent.h"
#include "ArmyComponent.h"

#include "MoveSystem.h"
#include "BezierMoveSystem.h"
#include "ParticleCountSystem.h"
#include "ParticleMoveSystem.h"
#include "GradientCalcSystem.h"

#include "EntityFabric.h"

#include "DebugWaveLayer.h"

Battle::Battle()
{
	_touchedShipId = -1;
	_currentArmyChoosenId = ArmyIdEnum::RED;
	_gameMap = NULL;
	_particleMap1 = NULL;
	_particleMap2 = NULL;
	_countMap = NULL;
	_gradientMap = NULL;
}

Battle::~Battle()
{
	setGameMap(NULL);
	setParticleMap1(NULL);
	setParticleMap2(NULL);
	setCountMap(NULL);
	setGradientMap(NULL);
}

bool Battle::init()
{
	// init ECS
	SystemManager * sysManager =  _world.getSystemManager();
	ParticleMoveSystem * pms = new ParticleMoveSystem();
	ParticleCountSystem * phs = new ParticleCountSystem();
	GradientCalcSystem * gcs = new GradientCalcSystem();
	sysManager->setSystem(new MoveSystem());
	sysManager->setSystem(pms);
	sysManager->setSystem(new BezierMoveSystem());
	sysManager->setSystem(phs);
	sysManager->setSystem(gcs);
	sysManager->initializeAll();

	createMaps();
	
	for (int i = 0; i < 5000; i++)
		EntityFabric::createParticle(_world, ArmyIdEnum::RED, getParticleMap1());
	
	for (int i = 0; i < 5000; i++)
		EntityFabric::createParticle(_world, ArmyIdEnum::GREEN, getParticleMap2());
	
	pms->_gameMap = getGameMap();
	pms->_gradientMap = getGradientMap();
	pms->_countMap = getCountMap();
	phs->_countMap = getCountMap();
	gcs->_gradientMap = getGradientMap();
		
	return true;
}

void Battle::createMaps()
{
	TMXTiledMap * tmxMap = TMXTiledMap::create("second.tmx");
	
	GameMap * gameMap = GameMap::createWithTmxMap(tmxMap);
	setGameMap(gameMap);
	
	ParticleMap * particleMap = ParticleMap::createWithParams(gameMap);
	setParticleMap1(particleMap);
	
	particleMap = ParticleMap::createWithParams(gameMap);
	setParticleMap2(particleMap);
	
	EventCustom * event = new EventCustom("MAP_LOADED");
	event->autorelease();
	event->setUserData(tmxMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
	
	const float arraySpritePixelsPerTile = 10; //very hard to explain this constant meaning
	Size countMapSize;
	countMapSize.width = gameMap->getMapSizeX() * arraySpritePixelsPerTile;
	countMapSize.height = gameMap->getMapSizeY() * arraySpritePixelsPerTile;
	
	Size tileSize (gameMap->getTileSize().width / arraySpritePixelsPerTile,
				   gameMap->getTileSize().height / arraySpritePixelsPerTile);
	CountMap * countMap = CountMap::create(countMapSize, tileSize);
	setCountMap(countMap);
	
	GradientMap * gradientsMap = GradientMap::createWithParams(countMap);
	setGradientMap(gradientsMap);
	
	EventCustom * event2 = new EventCustom("COUNT_MAP_LOADED");
	event2->autorelease();
	event2->setUserData(countMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event2);
}

void Battle::update(float delta)
{
	delta = MIN(0.03, delta);
	
	_world.setDelta(delta);
	_world.loopStart();
	
	SystemManager * sysManager =  _world.getSystemManager();
	
	ParticleMoveSystem * pms = (ParticleMoveSystem*)sysManager->getSystem<ParticleMoveSystem>();
	pms->process();
	
	MoveSystem* ms = (MoveSystem*)sysManager->getSystem<MoveSystem>();
	ms->process();
	
	BezierMoveSystem* bms = (BezierMoveSystem*)sysManager->getSystem<BezierMoveSystem>();
	bms->process();
	
	ParticleCountSystem * phs = (ParticleCountSystem*)sysManager->getSystem<ParticleCountSystem>();
	phs->process();
	
	GradientCalcSystem * gcs = (GradientCalcSystem*)sysManager->getSystem<GradientCalcSystem>();
	gcs->process();
	
	//auto t50 = std::chrono::high_resolution_clock::now();
	
	/*long long int pmsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t10 - t0).count();
	long long int msTS = std::chrono::duration_cast<std::chrono::milliseconds>(t20 - t10).count();
	long long int bmsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t30 - t20).count();
	long long int gcsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t40 - t30).count();
	long long int phsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t50 - t40).count();
	
	long long int pre_phsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t41 - t40).count();
	long long int proc_phsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t42 - t41).count();
	long long int post_phsTS = std::chrono::duration_cast<std::chrono::milliseconds>(t50 - t42).count();*/
	
	//printf("pre: %lld proc: %lld post: %lld \n", pre_phsTS, proc_phsTS, post_phsTS);
	
	//printf("pms: %lld ms: %lld bms: %lld gcs: %lld phs: %lld\n", pmsTS, msTS, bmsTS, gcsTS, phsTS);
	
}

void Battle::updateGoal(Vec2 coords)
{
	Vec2 goalPos = _gameMap->getTileCoordsByPos(coords);
	
	if(_currentArmyChoosenId == ArmyIdEnum::RED)
		getParticleMap1()->recalculateGoal(goalPos);
	else if (_currentArmyChoosenId == ArmyIdEnum::GREEN)
		getParticleMap2()->recalculateGoal(goalPos);
	
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

void Battle::chooseArmy(int armyId)
{
	_currentArmyChoosenId = armyId;
}

//@todo: ship?? Bezier movement?! We have different game here now!!!
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
















