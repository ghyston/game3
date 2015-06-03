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

void GradientMap::recalculateGradientAt(Vec2 coords)
{
	static int xL, xR, yB, yT, idL, idR, idT, idB, id, dencityL, dencityR, dencityT, dencityB, dencityC, resultX, resultY;
	
	int iX = coords.x;
	int iY = coords.y;
	
	id = getIdByTileCoords(Vec2(iX, iY));
	
	if((_vecMap[id].x > 0) || (_vecMap[id].y > 0))
		return;
	
	xL = MAX(iX - 1, 0);
	xR = MIN(iX + 1, _mapSizeX - 1);
	yB = MAX(iY - 1, 0);
	yT = MIN(iY + 1, _mapSizeY - 1);
	
	idL = getIdByTileCoords(Vec2(xL, iY));
	idR = getIdByTileCoords(Vec2(xR, iY));
	idT = getIdByTileCoords(Vec2(iX, yT));
	idB = getIdByTileCoords(Vec2(iX, yB));
	
	dencityL = _countMapData[idL];
	dencityR = _countMapData[idR];
	dencityT = _countMapData[idT];
	dencityB = _countMapData[idB];
	dencityC = _countMapData[id];
	
	resultX = dencityL - dencityR;
	resultY = dencityT - dencityB;
	
	if((resultX == 0) && (dencityC != 0))
		resultX = (rand() % 10 < 5) ? (dencityL - dencityC) : (dencityC - dencityR);
	
	if((resultY == 0) && (dencityC != 0))
		resultY = (rand() % 10 < 5) ? (dencityB - dencityC) : (dencityC - dencityT);
	
	
	_vecMap[id] = Vec2(resultX, resultY);
}

bool GradientMap::recalculateGradient()
{
	static int xL, xR, yB, yT, idL, idR, idT, idB, id, dencityL, dencityR, dencityT, dencityB, dencityC, resultX, resultY;
	
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			xL = MAX(iX - 1, 0);
			xR = MIN(iX + 1, _mapSizeX - 1);
			yB = MAX(iY - 1, 0);
			yT = MIN(iY + 1, _mapSizeY - 1);
			
			idL = getIdByTileCoords(Vec2(xL, iY));
			idR = getIdByTileCoords(Vec2(xR, iY));
			idT = getIdByTileCoords(Vec2(iX, yT));
			idB = getIdByTileCoords(Vec2(iX, yB));
			id = getIdByTileCoords(Vec2(iX, iY));
			
			dencityL = _countMapData[idL];
			dencityR = _countMapData[idR];
			dencityT = _countMapData[idT];
			dencityB = _countMapData[idB];
			dencityC = _countMapData[id];
			
			resultX = dencityL - dencityR;
			resultY = dencityT - dencityB;
			
			if((resultX == 0) && (dencityC != 0))
				resultX = (rand() % 10 < 5) ? (dencityL - dencityC) : (dencityC - dencityR);
			
			if((resultY == 0) && (dencityC != 0))
				resultY = (rand() % 10 < 5) ? (dencityB - dencityC) : (dencityC - dencityT);
					
			
			_vecMap[id] = Vec2(resultX, resultY);
		}
	}
	return true;
}

Vec2 GradientMap::getVecByTileID(int tileID) const
{
	return _vecMap[tileID];
}