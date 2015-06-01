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
	_countData = NULL;
}

CountMap::~CountMap()
{
	delete [] _countData;
}

void CountMap::init(Size size, float tileSideSize)
{
	initWithSize(size.width, size.height, Size(tileSideSize, tileSideSize));
	_countData = new GLubyte[4 * _mapSizeX * _mapSizeY];
	clean();
}

void CountMap::clean()
{
	memset(_countData, 0, (size_t)(4 * _mapSizeX * _mapSizeY * sizeof(GLbyte)));
}

const GLubyte * CountMap::getData()
{
	return _countData;
}

int CountMap::getIdByTileCoordsAndChannel(Vec2 coords, int channel)
{
	return 4 * getIdByTileCoords(coords) + channel;
}

void CountMap::incCount(Vec2 point, int channel)
{
	int id = getIdByTileCoordsAndChannel(point, channel);
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
