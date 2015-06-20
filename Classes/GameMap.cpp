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

}

GameMap::~GameMap()
{
	//delete [] _isCollidable;
	//delete [] _collisionVecMap;
}

bool GameMap::initWithTmxMap(TMXTiledMap * tmxMap)
{
	BaseMap::initWithSize(tmxMap->getMapSize().width,
						  tmxMap->getMapSize().height,
						  tmxMap->getTileSize());
	
	initMemoryVariables(tmxMap);
	initIsCollidableGrid(tmxMap);
	//initCollisionVecGrid();
	return true;
}

void GameMap::initMemoryVariables(TMXTiledMap * tmxMap)
{
	_isCollidable.create(this);
	_collisionVecMap.create(this);
	
	_isCollidable.clear();
	_collisionVecMap.clear();
}

void GameMap::initIsCollidableGrid(TMXTiledMap * tmxMap)
{
	TMXLayer * layer1 = tmxMap->getLayer("Layer1");
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			int tileGid = layer1->getTileGIDAt(Vec2(iX, iY) );
			if (tileGid == 0)
				continue;
			
			int isCollidableID = getIdByTileCoords(Vec2(iX, iY));
			
			Value properties = tmxMap->getPropertiesForGID(tileGid);
			ValueMap& valMap = properties.asValueMap();
			
			int val = (valMap["collidable"].asString().compare("0")) ? 1 : 0;
			_isCollidable.set(isCollidableID, val);
			
			// Init collision vec grid
			Vec2 collision(0, 0);
			if(val == 1)
			{
				collision.x = valMap["borderX"].asFloat();
				collision.y = valMap["borderY"].asFloat();
			}
			_collisionVecMap.set(isCollidableID, collision);
		}
	}
}
/*
void GameMap::initCollisionVecGrid()
{
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			int id = getIdByTileCoords(Vec2(iX, iY));
			
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
			if(!leftBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX - 1, iY))] == 0))
			{
				resultX--;
			}
			
			// left top
			if(!leftBlocked && !topBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX - 1, iY + 1))] == 0))
			{
				resultX--;
				resultY--;
			}
			
			// top
			if(!topBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX, iY + 1))] == 0))
			{
				resultY--;
			}
			
			// top right
			if(!topBlocked && !rightBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX + 1, iY + 1))] == 0))
			{
				resultY--;
				resultX++;
			}
			
			// right
			if(!rightBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX + 1, iY))] == 0))
			{
				resultX++;
			}
			
			// right bottom
			if(!rightBlocked && !bottomBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX + 1, iY - 1))] == 0))
			{
				resultX++;
				resultY++;
			}
			
			// bottom
			if(!bottomBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX, iY - 1))] == 0))
			{
				resultY++;
			}
			
			// bottom left
			if(!leftBlocked && !bottomBlocked && (_isCollidable[getIdByTileCoords(Vec2(iX - 1, iY - 1))] == 0))
			{
				resultX--;
				resultY++;
			}
			
			_collisionVecMap[id] = Vec2(resultX, resultY);
			_collisionVecMap[id].normalize();
		}
	}
}*/

//@todo: test, would it be faster, if all this functions will be inlined!
Vec2 GameMap::getCollisionVecByTileID(int tileID) const
{
	return _collisionVecMap[tileID];
}

bool GameMap::isCollidable(const Vec2& coords) const
{
	return isCollidable(getIdByTileCoords(coords));
}

bool GameMap::isCollidable(int tileID) const
{
	return _isCollidable[tileID];
}
