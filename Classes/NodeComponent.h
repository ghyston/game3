//
//  NodeComponent.h
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#ifndef Game3_NodeComponent_h
#define Game3_NodeComponent_h

#include <Artemis/Artemis.h>
#include "cocos2d.h"

class NodeComponent : public artemis::Component
{
public:
	
	cocos2d::Vector<int> _neighbors;
};

#endif
