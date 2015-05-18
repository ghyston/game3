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

using namespace artemis;
using namespace cocos2d;

class GameMap : public Ref
{
public:
	
	static GameMap * createWithFileName(const std::string& filename)
	{
		GameMap * instance = new GameMap();
		if(instance->initWithFileName(filename))
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
	
	virtual ~GameMap();
	
	Vec2 getCollisionVecByTileID(int tileID);
	int getIdByCoords(Vec2 coords);
	Vec2 getTileCoordsForPosition(Vec2 pos);
	bool isCollidable(Vec2 coords);
	bool isCollidable(int tileID);
	
private:
	
	bool initWithFileName(const std::string& filename);
	void initMemoryVariables();
	void initIsCollidableGrid();
	void initCollisionVecGrid();
	
	GameMap();
	
	CC_SYNTHESIZE_RETAIN(TMXTiledMap *, _tiledMap, TiledMap);
	
	int _mapSizeX;
	int _mapSizeY;
	int * _isCollidable;
	Vec2 * _collisionVecMap;
	
};

#endif /* defined(__Game3__Map__) */
