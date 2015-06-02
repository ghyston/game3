//
//  ParticleMoveSystem.h
//  Game3
//
//  Created by Stepanov Ilia on 02/06/15.
//
//

#ifndef __Game3__ParticleMoveSystem__
#define __Game3__ParticleMoveSystem__

#include <Artemis/Artemis.h>
#include "cocos2d.h"


#include "MovementComponent.h"
#include "ParticleComponent.h"
#include "PositionComponent.h"

#include "GameMap.h"
#include "ParticleMap.h"
#include "CountMap.h"
#include "GradientMap.h"

using namespace cocos2d;

class ParticleMoveSystem : public artemis::EntityProcessingSystem
{
public:
	
	ParticleMoveSystem();
	virtual ~ParticleMoveSystem();
	
	virtual void initialize();
	
	virtual void processEntity(artemis::Entity &e);
	
	const GameMap * _gameMap;
	//const ParticleMap * _particleMap;
	const GradientMap * _gradientMap;
	const CountMap * _countMap;
	
private:
	
	artemis::ComponentMapper<MovementComponent> movementMapper;
	artemis::ComponentMapper<PositionComponent> positionMapper;
	artemis::ComponentMapper<ParticleComponent> particleMapper;
	
};


#endif /* defined(__Game3__ParticleMoveSystem__) */
