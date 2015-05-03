//
//  BezierMoveSystem.h
//  Game3
//
//  Created by Stepanov Ilia on 19/04/15.
//
//

#ifndef __Game3__BezierMoveSystem__
#define __Game3__BezierMoveSystem__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

#include "PositionComponent.h"
#include "BezierMoveComponent.h"
#include "RenderComponent.h"

using namespace cocos2d;

class BezierMoveSystem : public artemis::EntityProcessingSystem
{
public:
	
	BezierMoveSystem();
	virtual ~BezierMoveSystem();
	
	virtual void initialize();
	
	virtual void processEntity(artemis::Entity &e);
	
private:
	
	artemis::ComponentMapper<BezierMoveComponent> bezMovementMapper;
	artemis::ComponentMapper<PositionComponent> positionMapper;
	
	Vec2 calculateCurrentPos(BezierMoveComponent * bmc);
	float calculateCurrentAngle(BezierMoveComponent * bmc);
	
	void moveCoordsFromPosCMptToSprite(PositionComponent * posCmpt, RenderComponent * rendCmpt);
	
};

#endif /* defined(__Game3__BezierMoveSystem__) */
