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
	
}

Battle::~Battle()
{
//	delete _isCollidable;
}

bool Battle::init(int mapCellsX, int mapCellsY)
{
	// init ECS
	SystemManager * sysManager =  _world.getSystemManager();
	MoveSystem * ms = new MoveSystem();
	sysManager->setSystem(ms);
	sysManager->setSystem(new BezierMoveSystem());
	sysManager->initializeAll();
	
	// create map @todo: move to another function or class!
	
	_tiledMap = TMXTiledMap::create("second.tmx");
	
	_mapSizeX = _tiledMap->getMapSize().width;
	_mapSizeY = _tiledMap->getMapSize().height;
	_isCollidable = new int[_mapSizeX * _mapSizeY];
	_heatmap = new int[_mapSizeX * _mapSizeY];
	_vecMap = new Vec2[_mapSizeX * _mapSizeY];
	
	memset(_isCollidable, 0, (size_t)(_mapSizeX * _mapSizeY * sizeof(int)));
	
	TMXLayer * layer1 = _tiledMap->getLayer("Layer1");
	
	// fill out _isCollidable array
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			int tileGid = layer1->getTileGIDAt(Vec2(iX, iY) );
			if (tileGid == 0)
				continue;
			
			int isCollidableID = getIdByCoords(Vec2(iX, iY));
			
			Value properties = _tiledMap->getPropertiesForGID(tileGid);
			ValueMap& valMap = properties.asValueMap();
			
			_isCollidable[isCollidableID] = (valMap["collidable"].asString().compare("0")) ? 1 : 0;
			//log("x: %i y: %i isCollideble: %s", iX, iY, _isCollidable[isCollidableID] ? "True" : "False");
		}
	}
	
	
	EventCustom * event = new EventCustom("MAP_LOADED");
	event->autorelease();
	event->setUserData(_tiledMap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
	
	//add tower for test
	//_touchedShipId = EntityFabric::createShip(_world);
	EntityFabric::createParticle(_world);
	
	 //@todo: very dirty hack!
	ms->mapSize = Vec2(_mapSizeX, _mapSizeY);
	ms->tileSize = Vec2(_tiledMap->getTileSize().width, _tiledMap->getTileSize().height);
	
	return true;
}

int Battle::getIdByCoords(Vec2 coords)
{
	return coords.y * _mapSizeX + coords.x;
}

void Battle::recalculateMapVectors(Vec2 goal)
{
	memset(_heatmap, -1, (size_t)(_mapSizeX * _mapSizeY * sizeof(int)));
	memset(_vecMap, 0, (size_t)(_mapSizeX * _mapSizeY * sizeof(Vec2)));
	
	int goalCellId = getIdByCoords(goal);
	
	if(_isCollidable[goalCellId] == 1)
		return;
	
	// recalculate heat values
	int currentValue = 0;
	bool canWaveBeIncreased = true;
	_heatmap[goalCellId] = currentValue;
	while (canWaveBeIncreased)
	{
		bool isCalculated = false;
		
		for(int iX = 0; iX < _mapSizeX; iX++)
		{
			for(int iY = 0; iY < _mapSizeY; iY++)
			{
				int id = getIdByCoords(Vec2(iX, iY));
				
				if(_heatmap[id] != currentValue)
					continue;
				
				isCalculated |= calculteHeatMapAtCell(Vec2(iX, iY + 1), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX, iY - 1), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX + 1, iY), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX - 1, iY), currentValue + 1);
				
			}
		}
		
		canWaveBeIncreased &= isCalculated;
		currentValue++;
	}
	
	// Upd debug layer
	EventCustom * testEvent = new EventCustom("DEBUG_MAP_UPDATED");
	testEvent->autorelease();
	testEvent->setUserData(_heatmap);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(testEvent);
	
	int xL, xR, yT, yB; // x: Left, Right; y: Top, Bottom
	
	// fill out vector map
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			xL = (iX == 0) ? iX : (iX - 1);
			xR = (iX == _mapSizeX - 1) ? iX : iX + 1;
			yT = (iY == _mapSizeY - 1) ? iY : iY + 1;
			yB = (iY == 0) ? iY : (iY - 1);
		
			int id = getIdByCoords(Vec2(iX, iY));
			int idL = getIdByCoords(Vec2(xL, iY));
			int idR = getIdByCoords(Vec2(xR, iY));
			int idT = getIdByCoords(Vec2(iX, yT));
			int idB = getIdByCoords(Vec2(iX, yB));
			
			if(_isCollidable[idL] == 1) idL = id;
			if(_isCollidable[idR] == 1) idR = id;
			if(_isCollidable[idT] == 1) idT = id;
			if(_isCollidable[idB] == 1) idB = id;
			
			_vecMap[id].x = _heatmap[idL] - _heatmap[idR];
			_vecMap[id].y = _heatmap[idT] - _heatmap[idB];
			
			_vecMap[id].normalize();
			float length = _vecMap[id].length();
			_vecMap[id] *= 1000;
		}
	}
}

bool Battle::calculteHeatMapAtCell(Vec2 cell, int value)
{
	int id = getIdByCoords(cell);
	
	if((cell.x < 0) ||
	   (cell.x >= _mapSizeX) ||
	   (cell.y < 0) ||
	   (cell.y >= _mapSizeY))
		return false;
	
	if(_isCollidable[id] == 1)
		return false;
	
	if((_heatmap[id] <= value) &&
	   (_heatmap[id] != -1))
		return false;
	
	_heatmap[id] = value;
	
	//log("x: %i y: %i wave: %i", (int)cell.x, (int)cell.y, (int)value);
	return  true;
}

void Battle::update(float delta)
{
	_world.setDelta(delta);
	_world.loopStart();
	
	SystemManager * sysManager =  _world.getSystemManager();
	
	MoveSystem* ms = (MoveSystem*)sysManager->getSystem<MoveSystem>();
	ms->vecMap = _vecMap;
	ms->process();
	
	BezierMoveSystem* bms = (BezierMoveSystem*)sysManager->getSystem<BezierMoveSystem>();
	bms->process();
}

void Battle::updateGoal(Vec2 coords)
{
	//@todo: check!!!
	Vec2 goalPos = getTileCoordsForPosition(coords);
	recalculateMapVectors(goalPos);
}

Vec2 Battle::getTileCoordsForPosition(Vec2 pos)
{
	int x = pos.x / _tiledMap->getTileSize().width;
	int y = ((_tiledMap->getMapSize().height * _tiledMap->getTileSize().height) - pos.y) / _tiledMap->getTileSize().height;
	return Vec2(x, y);
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
















