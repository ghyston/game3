//
//  ParticleMap.h
//  Game3
//
//  Created by Stepanov Ilia on 18/05/15.
//
//

#ifndef __Game3__ParticleMap__
#define __Game3__ParticleMap__

#include "GameMap.h"

#include <Artemis/Artemis.h>

using namespace artemis;
using namespace cocos2d;

class ParticleMap : public Ref
{
public:
	
	virtual ~ParticleMap();
	
	static ParticleMap * createWithParams(GameMap * gameMap)
	{
		ParticleMap * instance = new ParticleMap();
		if(instance->initWithParams(gameMap))
		{
			instance->autorelease();
			return instance;
		}
		else
		{
			delete instance;
			instance = NULL;
			return  NULL;
		}
	}
	
	bool recalculateGoal(Vec2 goal);
	Vec2 getVecByTileID(int tileID);
	
private:
	
	bool initWithParams(GameMap * gameMap);
	void clearGrids();
	void calculateHeatGrid(int goalCellId);
	void calculateVecGrid();
	bool calculteHeatMapAtCell(Vec2 cell, int value);
	
	ParticleMap();
		
	int _mapSizeX;
	int _mapSizeY;
	int * _heatmap;
	Vec2 * _vecMap;
	
	GameMap * _gameMap;
	
};

#endif /* defined(__Game3__ParticleMap__) */
