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
	
};

#endif /* defined(__Game3__Battle__) */
