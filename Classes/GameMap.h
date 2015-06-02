//
//  Map.h
//  Game3
//
//  Created by Stepanov Ilia on 10/05/15.
//
//

#ifndef __Game3__Map__
#define __Game3__Map__

#include <Artemis/Artemis.h>
#include "CommonMap.h"
#include "MemoryGrid.h"
#include "MyMacroses.h"

using namespace artemis;
using namespace cocos2d;

class GameMap : public BaseMap
{
public:
	
	static GameMap * createWithTmxMap(TMXTiledMap * tmxMap)
	{
		GameMap * instance = new GameMap();
		if(instance->initWithTmxMap(tmxMap))
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
	
	Vec2 getCollisionVecByTileID(int tileID) const;
	bool isCollidable(Vec2 coords) const;
	bool isCollidable(int tileID) const;
	
private:
	
	bool initWithTmxMap(TMXTiledMap * tmxMap);
	void initMemoryVariables(TMXTiledMap * tmxMap);
	void initIsCollidableGrid(TMXTiledMap * tmxMap);
	void initCollisionVecGrid();
	
	GameMap();
	virtual ~GameMap();
	
	MemoryGrid<int> _isCollidable;
	MemoryGrid<Vec2> _collisionVecMap;
	
};

#endif /* defined(__Game3__Map__) */
