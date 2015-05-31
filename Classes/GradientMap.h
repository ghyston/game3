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

#include <Artemis/Artemis.h>

using namespace artemis;
using namespace cocos2d;

class GradientMap : public Ref
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
	
	bool recalculateGradient();
	Vec2 getVecByTileID(int tileID);
	int getIdByCoords(Vec2 coords);
	void clearGrids();
	
private:
	
	bool initWithParams(CountMap * countMap);
	
	
	GradientMap();
	virtual ~GradientMap();
	
	int _mapSizeX;
	int _mapSizeY;
	Vec2 * _vecMap;
	
	const GLubyte * _countMapData;
	
};

#endif /* defined(__Game3__GradientMap__) */
