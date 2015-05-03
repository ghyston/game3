//
//  MoveSystem.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef __Game3__MoveSystem__
#define __Game3__MoveSystem__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "RenderComponent.h"

class MoveSystem : public artemis::EntityProcessingSystem
{
public:
	
	MoveSystem();
	virtual ~MoveSystem();
	
	virtual void initialize();
	
	virtual void processEntity(artemis::Entity &e);
	
private:
	
	artemis::ComponentMapper<MovementComponent> movementMapper;
	artemis::ComponentMapper<PositionComponent> positionMapper;
	
};

#endif /* defined(__Game3__MoveSystem__) */
