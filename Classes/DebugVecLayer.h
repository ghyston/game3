//
//  DebugVecLayer.h
//  Game3
//
//  Created by Stepanov Ilia on 04/05/15.
//
//

#ifndef __Game3__DebugVecLayer__
#define __Game3__DebugVecLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DebugVecLayer : public Layer
{
public:
	
	~DebugVecLayer();
	
	static DebugVecLayer * create(Vec2 mapSize, Size tileSize)
	{
		DebugVecLayer * instance = new DebugVecLayer();
		instance->init(mapSize, tileSize);
		instance->autorelease();
		return instance;
	}
	
	void updateValues(const Vec2 * values);
	
private:
	
	void init (Vec2 mapSize, Size tileSize);
	
	DebugVecLayer();
	
	Vec2 _mapSize;
	
	Vector<Label*> _labels;
	
};

#endif /* defined(__Game3__DebugVecLayer__) */
