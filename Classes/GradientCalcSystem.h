//
//  GradientCalcSystem.h
//  Game3
//
//  Created by Stepanov Ilia on 03/06/15.
//
//

#ifndef __Game3__GradientCalcSystem__
#define __Game3__GradientCalcSystem__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

#include "ParticleComponent.h"
#include "PositionComponent.h"

#include "GradientMap.h"

using namespace cocos2d;

class GradientCalcSystem : public artemis::EntityProcessingSystem
{
public:
	
	GradientCalcSystem();
	virtual ~GradientCalcSystem();
	
	virtual void begin();
	
	virtual void initialize();
	
	virtual void processEntity(artemis::Entity &e);
	
	GradientMap * _gradientMap;
	
private:
	
	artemis::ComponentMapper<ParticleComponent> particleMapper;
	artemis::ComponentMapper<PositionComponent> positionMapper;
	
};


#endif /* defined(__Game3__GradientCalcSystem__) */
