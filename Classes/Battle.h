//
//  Battle.h
//  Game3
//
//  Created by Stepanov Ilia on 12/04/15.
//
//

#ifndef __Game3__Battle__
#define __Game3__Battle__

#include <Artemis/Artemis.h>

using namespace artemis;
using namespace cocos2d;

/*
 
 */
class Battle
{
public:
	
	Battle();
	~Battle();
	
	bool init(int mapCellsX, int mapCellsY); //@todo: here should be all data about current game: players, map
	
	void update(float delta);
	
	void startShipMoving(Vec2 newCoords);
	
private:
	
	World _world;
	
	int _touchedShipId;
	
	//@todo: move it to separate class!
	TMXTiledMap * _tiledMap;
	int _mapSizeX;
	int _mapSizeY;
	int * _isCollidable;
	int * _heatmap;
	
	void recalculateMapVectors(Vec2 goal);
	bool calculteHeatMapAtCell(Vec2 cell, int value);
	int getIdByCoords(Vec2 coords);
	
};

#endif /* defined(__Game3__Battle__) */
