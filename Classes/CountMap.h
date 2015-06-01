//
//  CountMap.h
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#ifndef __Game3__CountMap__
#define __Game3__CountMap__

#include <Artemis/Artemis.h>
#include "CommonMap.h"

using namespace artemis;
using namespace cocos2d;

class CountMap : public BaseMap
{
public:
	
	static CountMap * create(Size size, float tileSideSize)
	{
		CountMap * instance = new CountMap();
		instance->init(size, tileSideSize);
		instance->autorelease();
		return instance;
	}
	
	void clean();
	const GLubyte * getData();
	void incCount(Vec2 point, int channel);
	void resetAlpha();
		
private:
	
	void init(Size size, float tileSideSize);
	
	int getIdByTileCoordsAndChannel(Vec2 coords, int channel);
	
	GLubyte * _countData; //@todo: use MemoryGrid
	
	CountMap();
	virtual ~CountMap();
	
};




#endif /* defined(__Game3__CountMap__) */
