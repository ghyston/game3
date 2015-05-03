//
//  EntityFabric.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef __Game3__EntityFabric__
#define __Game3__EntityFabric__

#include <Artemis/Artemis.h>
using namespace artemis;

class EntityFabric
{
public:
	
	static void createTower(World& world);
	static int createShip(World& world);
	static int createParticle(World& world);
	
private:
	
	EntityFabric();
};

#endif /* defined(__Game3__EntityFabric__) */
