//
//  ParticleComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 02/06/15.
//
//

#ifndef Game3_ParticleComponent_h
#define Game3_ParticleComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"
#include "ParticleMap.h"

class ParticleComponent : public artemis::Component
{
public:
	
	ParticleComponent(const ParticleMap * map) : _map(map)
	{ }
	
	const ParticleMap * _map;
};

#endif
