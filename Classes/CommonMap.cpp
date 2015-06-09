//
//  CommonMap.cpp
//  Game3
//
//  Created by Stepanov Ilia on 01/06/15.
//
//

#include "CommonMap.h"

BaseMap::BaseMap()
{
	_mapSizeX = 0;
	_mapSizeY = 0;
	_tileSize.width = 0;
	_tileSize.height = 0;
}

BaseMap::~BaseMap()
{
	
}

void BaseMap::initWithSize(int sizeX, int sizeY, Size tileSize)
{
	_mapSizeX = sizeX;
	_mapSizeY = sizeY;
	_tileSize = tileSize;
}

void BaseMap::initWithMap(const BaseMap * otherMap)
{
	initWithSize(otherMap->getMapSizeX(),
				 otherMap->getMapSizeY(),
				 otherMap->getTileSize());
}

int BaseMap::getIdByTileCoords(int tileCoordsX, int tileCoordsY) const
{
	return tileCoordsY * _mapSizeX + tileCoordsX;
}

int BaseMap::getIdByTileCoords(Vec2 tileCoords) const
{
	return tileCoords.y * _mapSizeX + tileCoords.x;
}

Vec2 BaseMap::getTileCoordsByPos(Vec2 globalPosition) const
{
	int x = globalPosition.x / _tileSize.width;
	int y = ((_mapSizeY * _tileSize.height) - globalPosition.y) / _tileSize.height;
	return Vec2(x, y);
}