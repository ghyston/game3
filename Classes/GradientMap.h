//
//  GradientMap.h
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#ifndef __Game3__GradientMap__
#define __Game3__GradientMap__

#include "CountMap.h"
#include "MemoryGrid.h"

#include <Artemis/Artemis.h>

using namespace artemis;
using namespace cocos2d;

class GradientMap : public BaseMap
{
public:
	
	static GradientMap * createWithParams(CountMap * countMap)
	{
		GradientMap * instance = new GradientMap();
		if(instance->initWithParams(countMap))
		{
			instance->autorelease();
			return instance;
		}
		else
		{
			delete instance;
			instance = NULL;
			return  NULL;
		}
	}
	
	void recalculateGradientAt(Vec2& coords);
	//bool recalculateGradient();
	Vec2 getVecByTileID(int tileID) const;
	void clearGrids();
	
private:
	
	bool initWithParams(CountMap * countMap);
	
	
	GradientMap();
	virtual ~GradientMap();

	MemoryGrid<Vec2> _vecMap;
	
	const PixelRGBA * _countMapData;
	
};

#endif /* defined(__Game3__GradientMap__) */
