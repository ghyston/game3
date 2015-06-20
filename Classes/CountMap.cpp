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

void CountMap::incCountG(Vec2& point)
{
	int id = getIdByTileCoords(point);
	if (_countData[id].g < MAX_COUNT_PER_CELL) {
		_countData[id].g++;
	}
}

void CountMap::resetAlpha()
{
	static float multiplyer = 255.0 / MAX_COUNT_PER_CELL;
	
	for (int i = 0; i < _mapSizeX * _mapSizeY; i++)
	{
		if(_countData[i].r > 0)
		{
			_countData[i].a = 255;
			_countData[i].r = 255;
		}
		
		if(_countData[i].g > 0)
		{
			_countData[i].a = 255;
			_countData[i].g = 255;
		}
		
		/*_countData[i].r = _countData[i].r * multiplyer;
		_countData[i].g = _countData[i].g * multiplyer;
		if((_countData[i].r > 0) || (_countData[i].g > 0)) //@todo: improve this check!
		_countData[i].a = _countData[i].r + _countData[i].g; //set alpha equal to red (should be on shader)*/
	}
}
