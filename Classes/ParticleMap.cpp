//
//  ParticleMap.cpp
//  Game3
//
//  Created by Stepanov Ilia on 18/05/15.
//
//

#include "ParticleMap.h"

ParticleMap::ParticleMap()
{
	
}

ParticleMap::~ParticleMap()
{
	delete [] _heatmap;
	delete [] _vecMap;
}

bool ParticleMap::initWithParams(GameMap * gameMap)
{
	_gameMap = gameMap;
	_mapSizeX = gameMap->_mapSizeX;
	_mapSizeY = gameMap->_mapSizeY; //@todo: use anchors?
	_heatmap	= new int[_mapSizeX * _mapSizeY];
	_vecMap		= new Vec2[_mapSizeX * _mapSizeY];
	clearGrids();
	return true;
}

void ParticleMap::clearGrids()
{
	memset(_heatmap, -1, (size_t)(_mapSizeX * _mapSizeY * sizeof(int)));
	memset(_vecMap, 0, (size_t)(_mapSizeX * _mapSizeY * sizeof(Vec2)));
}

bool ParticleMap::recalculateGoal(Vec2 goal)
{
	clearGrids();
	
	if(_gameMap->isCollidable(goal))
		return false;
	
	calculateHeatGrid(_gameMap->getIdByCoords(goal));
	calculateVecGrid();
	return true;
}

void ParticleMap::calculateHeatGrid(int goalCellId)
{
	// recalculate heat values
	int currentValue = 0;
	bool canWaveBeIncreased = true;
	_heatmap[goalCellId] = currentValue;
	while (canWaveBeIncreased)
	{
		bool isCalculated = false;
		
		for(int iX = 0; iX < _mapSizeX; iX++)
		{
			for(int iY = 0; iY < _mapSizeY; iY++)
			{
				int id = _gameMap->getIdByCoords(Vec2(iX, iY));
				
				if(_heatmap[id] != currentValue)
					continue;
				
				isCalculated |= calculteHeatMapAtCell(Vec2(iX, iY + 1), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX, iY - 1), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX + 1, iY), currentValue + 1);
				isCalculated |= calculteHeatMapAtCell(Vec2(iX - 1, iY), currentValue + 1);
				
			}
		}
		
		canWaveBeIncreased &= isCalculated;
		currentValue++;
	}
}

void ParticleMap::calculateVecGrid()
{
	int xL, xR, yT, yB; // x: Left, Right; y: Top, Bottom
	
	// fill out vector map
	for(int iX = 0; iX < _mapSizeX; iX++)
	{
		for(int iY = 0; iY < _mapSizeY; iY++)
		{
			xL = (iX == 0) ? iX : (iX - 1);
			xR = (iX == _mapSizeX - 1) ? iX : iX + 1;
			yT = (iY == _mapSizeY - 1) ? iY : iY + 1;
			yB = (iY == 0) ? iY : (iY - 1);
			
			int id = _gameMap->getIdByCoords(Vec2(iX, iY));
			int idL = _gameMap->getIdByCoords(Vec2(xL, iY));
			int idR = _gameMap->getIdByCoords(Vec2(xR, iY));
			int idT = _gameMap->getIdByCoords(Vec2(iX, yT));
			int idB = _gameMap->getIdByCoords(Vec2(iX, yB));
			
			if(_gameMap->isCollidable(idL) == 1) idL = id;
			if(_gameMap->isCollidable(idR) == 1) idR = id;
			if(_gameMap->isCollidable(idT) == 1) idT = id;
			if(_gameMap->isCollidable(idB) == 1) idB = id;
			
			if(_gameMap->isCollidable(id) == 1)
			{
				_vecMap[id].x = 0;
				_vecMap[id].y = 0;
			}
			else
			{
				_vecMap[id].x = _heatmap[idL] - _heatmap[idR];
				_vecMap[id].y = _heatmap[idT] - _heatmap[idB];
			}
			
			_vecMap[id].normalize();
			//float length = _vecMap[id].length();
			//_vecMap[id] *= 100;
		}
	}
}

bool ParticleMap::calculteHeatMapAtCell(Vec2 cell, int value)
{
	int id = _gameMap->getIdByCoords(cell);
	
	if((cell.x < 0) ||
	   (cell.x >= _mapSizeX) ||
	   (cell.y < 0) ||
	   (cell.y >= _mapSizeY))
		return false;
	
	if(_gameMap->isCollidable(id) == 1)
		return false;
	
	if((_heatmap[id] <= value) &&
	   (_heatmap[id] != -1))
		return false;
	
	_heatmap[id] = value;
	
	//log("x: %i y: %i wave: %i", (int)cell.x, (int)cell.y, (int)value);
	return  true;
}

Vec2 ParticleMap::getVecByTileID(int tileID)
{
	return _vecMap[tileID];
}
