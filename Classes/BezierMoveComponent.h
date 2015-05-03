//
//  BezierMoveComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 19/04/15.
//
//

#ifndef __Game3__BezierMoveComponent__
#define __Game3__BezierMoveComponent__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class BezierMoveComponent : public artemis::Component
{
public:
	
	cocos2d::Vec2 _P0;
	cocos2d::Vec2 _P1;
	cocos2d::Vec2 _P2;
	
	float _duration;
	float _timeLeft;
};

#endif /* defined(__Game3__BezierMoveComponent__) */
