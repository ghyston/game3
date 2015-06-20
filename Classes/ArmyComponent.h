//
//  ArmyComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 20/06/15.
//
//

#ifndef Game3_ArmyComponent_h
#define Game3_ArmyComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"
#include "ParticleMap.h"

struct ArmyIdEnum
{
	enum
	{
		RED,
		GREEN,
		BLUE,
		ALPHA
	};
};

class ArmyComponent : public artemis::Component
{
public:
	
	ArmyComponent(int armyId) : _armyId(armyId)
	{ }
	
	const int _armyId;
};

#endif
