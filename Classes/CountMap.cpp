//
//  CountMap.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "CountMap.h"

const int CountMap::MAX_COUNT_PER_CELL = 5;

CountMap::CountMap()
{
}

CountMap::~CountMap()
{
}

void CountMap::init(Size mapSize, Size tileSize)
{
	initWithSize(mapSize.width, mapSize.height, tileSize);
	_countData.create(this);
	clean();
}

void CountMap::clean()
{
	_countData.clear();
}

const GLubyte * CountMap::getDataAsGLubyte()
{
	return (GLubyte*)_countData.getData();
}

const PixelRGBA * CountMap::getDataAsPixels()
{
	return _countData.getData();
}

void CountMap::incCountR(Vec2& point)
{
	int id = getIdByTileCoords(point);
	if (_countData[id].r < MAX_COUNT_PER_CELL) {
		_countData[id].r++;
	}
}

void CountMap::resetAlpha()
{
	static float multiplyer = 255.0 / MAX_COUNT_PER_CELL;
	
	for (int i = 0; i < _mapSizeX * _mapSizeY; i++)
	{
		_countData[i].r = _countData[i].r * multiplyer;
		if(_countData[i].r > 0)
			_countData[i].a = _countData[i].r; //set alpha equal to red (should be on shader)
	}
}
