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
#include "MemoryGrid.h"

using namespace artemis;
using namespace cocos2d;

struct PixelRGBA
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

class CountMap : public BaseMap
{
public:
	
	static CountMap * create(Size mapSize, Size tileSize)
	{
		CountMap * instance = new CountMap();
		instance->init(mapSize, tileSize);
		instance->autorelease();
		return instance;
	}
	
	void clean();
	const GLubyte * getDataAsGLubyte();
	const PixelRGBA * getDataAsPixels();
	void incCountR(Vec2& point);
	void incCountG(Vec2& point);
	void resetAlpha();
		
private:
	
	static const int MAX_COUNT_PER_CELL;
	
	void init(Size mapSize, Size tileSize);
	
	MemoryGrid<PixelRGBA> _countData;
	//GLubyte * _countData; //@todo: use MemoryGrid
	
	CountMap();
	virtual ~CountMap();
	
};




#endif /* defined(__Game3__CountMap__) */
