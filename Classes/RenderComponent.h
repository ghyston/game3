//
//  RenderComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef Game3_RenderComponent_h
#define Game3_RenderComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class RenderComponent : public artemis::Component
{
public:
	
	cocos2d::Sprite * _sprite; //@todo: keep it as cocos object?
};

#endif
