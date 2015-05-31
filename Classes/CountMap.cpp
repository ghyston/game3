//
//  CountMap.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "CountMap.h"

CountMap::CountMap()
{
	_mapSizeX = 0;
	_mapSizeY = 0;
	_countData = NULL;
	_tileSideSize = 0;
}

CountMap::~CountMap()
{
	delete [] _countData;
}

void CountMap::init(Size size, float tileSideSize)
{
	_mapSizeX = size.width;
	_mapSizeY = size.height;
	_countData = new GLubyte[4 * _mapSizeX * _mapSizeY];
	clean();
	_tileSideSize = tileSideSize;
}

void CountMap::clean()
{
	memset(_countData, 0, (size_t)(4 * _mapSizeX * _mapSizeY * sizeof(GLbyte)));
}

const GLubyte * CountMap::getData()
{
	return _countData;
}

int CountMap::getIdByCoords(Vec2 coords, int channel)
{
	return 4 * (coords.y * _mapSizeX + coords.x) + channel;
}

void CountMap::incCount(Vec2 point, int channel)
{
	int id = getIdByCoords(point, channel);
	if (_countData[id] < 15) {
		_countData[id]++;
	}
}

void CountMap::resetAlpha()
{
	for (int i = 0; i < _mapSizeX * _mapSizeY; i++)
	{
		_countData[4 * i] = _countData[4 * i] * 17;
		if(_countData[4 * i] > 0)
			_countData[4 * i  + 3] = _countData[4 * i]; //set alpha
	}
}

Vec2 CountMap::getTileCoordsForPosition(Vec2 pos)
{
	int x = pos.x / _tileSideSize;
	int y = ((_mapSizeY * _tileSideSize) - pos.y) / _tileSideSize;
	return Vec2(x, y);
}