//
//  EnergyStorageComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef Game3_EnergyStorageComponent_h
#define Game3_EnergyStorageComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class EnergyStorageComponent : public artemis::Component
{
public:
	
	unsigned int _currentValue;
	unsigned int _maxValue;
};

#endif
