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

class ParticleCountSystem : public artemis::EntityProcessingSystem
{
public:
	ParticleCountSystem();
	virtual ~ParticleCountSystem();
	
	virtual void initialize();
	
	virtual void begin();
	virtual void end();
		
	virtual void processEntity(artemis::Entity &e);
	
	CountMap * _countMap;
	
private:
	
	artemis::ComponentMapper<PositionComponent> positionMapper;
	
};


#endif /* defined(__Game3__ParticleHandlingSystem__) */
