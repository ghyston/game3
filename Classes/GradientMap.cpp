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
	_countMapData = countMap->getDataAsPixels();
	
	_vecMap.create(this);
	clearGrids();
	return true;
}

void GradientMap::clearGrids()
{
	_vecMap.clear();
}

//@todo: most trickest part of calculation!
void GradientMap::recalculateGradientAt(const Vec2& coords)
{
	static int xL, xR, yB, yT, idL, idR, idT, idB, id, dencityL, dencityR, dencityT, dencityB, dencityC, resultX, resultY;
	
	int iX = coords.x;
	int iY = coords.y;
	
	id = getIdByTileCoords(iX, iY);
	
	if((_vecMap[id].x > 0) || (_vecMap[id].y > 0))
		return;
	
	xL = MAX(iX - 1, 0);
	xR = MIN(iX + 1, _mapSizeX - 1);
	yB = MAX(iY - 1, 0);
	yT = MIN(iY + 1, _mapSizeY - 1);
	
	idL = getIdByTileCoords(xL, iY);
	idR = getIdByTileCoords(xR, iY);
	idT = getIdByTileCoords(iX, yT);
	idB = getIdByTileCoords(iX, yB);
	
	dencityL = _countMapData[idL].r + _countMapData[idL].g;
	dencityR = _countMapData[idR].r + _countMapData[idR].g;
	dencityT = _countMapData[idT].r + _countMapData[idT].g;
	dencityB = _countMapData[idB].r + _countMapData[idB].g;
	dencityC = _countMapData[id].r	+ _countMapData[id].g;
	
	resultX = dencityL - dencityR;
	resultY = dencityT - dencityB;
	
	if((resultX == 0) && (dencityC != 0))
		resultX = (rand() % 10 < 5) ? (dencityL - dencityC) : (dencityC - dencityR);
	
	if((resultY == 0) && (dencityC != 0))
		resultY = (rand() % 10 < 5) ? (dencityB - dencityC) : (dencityC - dencityT);
	
	
	_vecMap[id] = Vec2(resultX, resultY);
}

/*bool GradientMap::recalculateGradient()
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
}*/

Vec2 GradientMap::getVecByTileID(int tileID) const
{
	return _vecMap[tileID];
}