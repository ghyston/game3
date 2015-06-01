//
//  GradientMap.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "GradientMap.h"

GradientMap::GradientMap()
{
	_countMapData = NULL;
}

GradientMap::~GradientMap()
{

}

bool GradientMap::initWithParams(CountMap * countMap)
{
	initWithMap(countMap);
	_countMapData = countMap->getData();
	
	_vecMap.create(this);
	clearGrids();
	return true;
}

void GradientMap::clearGrids()
{
	_vecMap.clear();
}

bool GradientMap::recalculateGradient()
{
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			int xL = MAX(iX - 1, 0);
			int xR = MIN(iX + 1, _mapSizeX - 1);
			int yB = MAX(iY - 1, 0);
			int yT = MIN(iY + 1, _mapSizeY - 1);
			
			int idL = getIdByTileCoords(Vec2(xL, iY));
			int idR = getIdByTileCoords(Vec2(xR, iY));
			int idT = getIdByTileCoords(Vec2(iX, yT));
			int idB = getIdByTileCoords(Vec2(iX, yB));
			int id = getIdByTileCoords(Vec2(iX, iY));
			
			int dencityL = _countMapData[idL];
			int dencityR = _countMapData[idR];
			int dencityT = _countMapData[idT];
			int dencityB = _countMapData[idB];
			int dencityC = _countMapData[id];
			
			int resultX = dencityL - dencityR;
			int resultY = dencityT - dencityB;
			
			if((resultX == 0) && (dencityC != 0))
				resultX = (rand() % 10 < 5) ? (dencityL - dencityC) : (dencityC - dencityR);
			
			if((resultY == 0) && (dencityC != 0))
				resultY = (rand() % 10 < 5) ? (dencityB - dencityC) : (dencityC - dencityT);
					
			
			_vecMap[id] = Vec2(resultX, resultY);
		}
	}
	return true;
}

Vec2 GradientMap::getVecByTileID(int tileID)
{
	return _vecMap[tileID];
}