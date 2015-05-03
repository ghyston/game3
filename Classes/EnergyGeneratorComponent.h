//
//  EnergyGeneratorComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef Game3_EnergyGeneratorComponent_h
#define Game3_EnergyGeneratorComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class EnergyGeneratorComponent : public artemis::Component
{
public:
	
	float radius;
	float intensivity;
	bool activated;
	
	//@todo: list of towers id?
};

#endif
