//
//  Map.cpp
//  Game3
//
//  Created by Stepanov Ilia on 10/05/15.
//
//

#include "GameMap.h"

GameMap::GameMap()
{
	_tiledMap = NULL;
}

GameMap::~GameMap()
{
	setTiledMap(NULL);
	delete [] _isCollidable;
	delete [] _collisionVecMap;
}

bool GameMap::initWithFileName(const std::string& filename)
{
	setTiledMap(TMXTiledMap::create("second.tmx"));
	
	initMemoryVariables();
	initIsCollidableGrid();
	initCollisionVecGrid();
	return true;
}

void GameMap::initMemoryVariables()
{
	_mapSizeX = getTiledMap()->getMapSize().width;
	_mapSizeY = getTiledMap()->getMapSize().height;
	_isCollidable		= new int[_mapSizeX * _mapSizeY];
	_collisionVecMap	= new Vec2[_mapSizeX * _mapSizeY];
	memset(_isCollidable, 0, (size_t)(_mapSizeX * _mapSizeY * sizeof(int)));
	memset(_collisionVecMap, 0, (size_t)(_mapSizeX * _mapSizeY * sizeof(Vec2)));
}

void GameMap::initIsCollidableGrid()
{
	TMXLayer * layer1 = getTiledMap()->getLayer("Layer1");
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
}

void GameMap::initCollisionVecGrid()
{
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			int id = getIdByCoords(Vec2(iX, iY));
			
			if(_isCollidable[id] == 0)
			{
				_collisionVecMap[id] = Vec2(0, 0);
				continue;
			}
			
			
			int resultX = 0;
			int resultY = 0;
			
			bool leftBlocked = (iX == 0);
			bool rightBlocked = (iX == (_mapSizeX - 1));
			bool topBlocked = (iY == (_mapSizeY - 1));
			bool bottomBlocked = (iY == 0);
			
			// For all blocked cells on border calculate push force (by unblocked neighbors)
			
			// left
			if(!leftBlocked && (_isCollidable[getIdByCoords(Vec2(iX - 1, iY))] == 0))
			{
				resultX--;
			}
			
			// left top
			if(!leftBlocked && !topBlocked && (_isCollidable[getIdByCoords(Vec2(iX - 1, iY + 1))] == 0))
			{
				resultX--;
				resultY--;
			}
			
			// top
			if(!topBlocked && (_isCollidable[getIdByCoords(Vec2(iX, iY + 1))] == 0))
			{
				resultY--;
			}
			
			// top right
			if(!topBlocked && !rightBlocked && (_isCollidable[getIdByCoords(Vec2(iX + 1, iY + 1))] == 0))
			{
				resultY--;
				resultX++;
			}
			
			// right
			if(!rightBlocked && (_isCollidable[getIdByCoords(Vec2(iX + 1, iY))] == 0))
			{
				resultX++;
			}
			
			// right bottom
			if(!rightBlocked && !bottomBlocked && (_isCollidable[getIdByCoords(Vec2(iX + 1, iY - 1))] == 0))
			{
				resultX++;
				resultY++;
			}
			
			// bottom
			if(!bottomBlocked && (_isCollidable[getIdByCoords(Vec2(iX, iY - 1))] == 0))
			{
				resultY++;
			}
			
			// bottom left
			if(!leftBlocked && !bottomBlocked && (_isCollidable[getIdByCoords(Vec2(iX - 1, iY - 1))] == 0))
			{
				resultX--;
				resultY++;
			}
			
			_collisionVecMap[id] = Vec2(resultX, resultY);
			_collisionVecMap[id].normalize();
		}
	}
}

//@todo: test, would it be faster, if all this functions will be inlined!
Vec2 GameMap::getCollisionVecByTileID(int tileID)
{
	return _collisionVecMap[tileID];
}

bool GameMap::isCollidable(Vec2 coords)
{
	return isCollidable(getIdByCoords(coords));
}

bool GameMap::isCollidable(int tileID)
{
	return _isCollidable[tileID];
}

int GameMap::getIdByCoords(Vec2 coords)
{
	return coords.y * _mapSizeX + coords.x;
}

Vec2 GameMap::getTileCoordsForPosition(Vec2 pos)
{
	int x = pos.x / _tiledMap->getTileSize().width;
	int y = ((_tiledMap->getMapSize().height * _tiledMap->getTileSize().height) - pos.y) / _tiledMap->getTileSize().height;
	return Vec2(x, y);
}

