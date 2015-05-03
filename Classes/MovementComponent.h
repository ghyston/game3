//
//  Header.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef Game3_Header_h
#define Game3_Header_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class MovementComponent : public artemis::Component
{
public:
	
	cocos2d::Vec2 _speed;
	cocos2d::Vec2 _velocity;
};

#endif
