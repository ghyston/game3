//
//  CommonMap.h
//  Game3
//
//  Created by Stepanov Ilia on 01/06/15.
//
//

#ifndef __Game3__CommonMap__
#define __Game3__CommonMap__

using namespace cocos2d;

class BaseMap : public Ref
{
public:
	
	void initWithSize(int sizeX, int sizeY, Size tileSize);
	void initWithMap(const BaseMap * otherMap);
	
	virtual int getIdByTileCoords(int tileCoordsX, int tileCoordsY) const;
	virtual int getIdByTileCoords(const Vec2& tileCoords) const;
	virtual Vec2 getTileCoordsByPos(const Vec2& globalPosition) const;
	
protected:
	
	CC_SYNTHESIZE_READONLY(int, _mapSizeX, MapSizeX);
	CC_SYNTHESIZE_READONLY(int, _mapSizeY, MapSizeY);
	CC_SYNTHESIZE_READONLY(Size, _tileSize, TileSize);
	
	BaseMap();
	virtual ~BaseMap();
};

#endif /* defined(__Game3__CommonMap__) */
