//
//  ParticleHandlingSystem.h
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#ifndef __Game3__ParticleHandlingSystem__
#define __Game3__ParticleHandlingSystem__

#include <Artemis/Artemis.h>
#include "cocos2d.h"

#include "PositionComponent.h"
#include "CountMap.h"
#include "GradientMap.h"


using namespace cocos2d;

class ParticleHandlingSystem : public artemis::EntityProcessingSystem
{
public:
	ParticleHandlingSystem();
	virtual ~ParticleHandlingSystem();
	
	virtual void initialize();
	
	void preProcess(); //@todo: chenge it to begin/end!
	void postProcess();
	
	virtual void processEntity(artemis::Entity &e);
	
	CountMap * _countMap;
	GradientMap * _gradientMap;
	
private:
	
	artemis::ComponentMapper<PositionComponent> positionMapper;
	
};


#endif /* defined(__Game3__ParticleHandlingSystem__) */
