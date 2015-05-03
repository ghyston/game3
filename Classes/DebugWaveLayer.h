//
//  DebugWaveLayer.h
//  Game3
//
//  Created by Stepanov Ilia on 03/05/15.
//
//

#ifndef __Game3__DebugWaveLayer__
#define __Game3__DebugWaveLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DebugWaveLayer : public Layer
{
public:
	
	~DebugWaveLayer();
	
	static DebugWaveLayer * create(Vec2 mapSize, Size tileSize, int * values)
	{
		DebugWaveLayer * instance = new DebugWaveLayer();
		instance->init(mapSize, tileSize, values);
		instance->autorelease();
		return instance;
	}
	
private:
	
	void init (Vec2 mapSize, Size tileSize, int * values);
	
	DebugWaveLayer();
	
};

#endif /* defined(__Game3__DebugWaveLayer__) */
