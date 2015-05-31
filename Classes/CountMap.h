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

using namespace artemis;
using namespace cocos2d;

class CountMap : public Ref
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
	
	int getWidth() { return _mapSizeX; }
	int getHeight() {return _mapSizeY; }
	
	Vec2 getTileCoordsForPosition(Vec2 pos);
	
private:
	
	void init(Size size, float tileSideSize);
	
	int getIdByCoords(Vec2 coords, int channel);
	
	float _tileSideSize;
	int _mapSizeX;
	int _mapSizeY;
	
	GLubyte * _countData;
	
	CountMap();
	virtual ~CountMap();
	
};




#endif /* defined(__Game3__CountMap__) */
