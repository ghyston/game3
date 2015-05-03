//
//  PositionComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef __Game3__PositionComponent__
#define __Game3__PositionComponent__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class PositionComponent : public artemis::Component
{
public:
	
	PositionComponent(float x = 0.0f, float y = 0.0f, float angle = 0.0f)
	{
		_pos.x = x;
		_pos.y = y;
		_angle = angle;
	}
	
	cocos2d::Vec2 _pos;
	float _angle;
};

#endif /* defined(__Game3__PositionComponent__) */
