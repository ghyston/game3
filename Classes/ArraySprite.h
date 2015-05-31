//
//  ArraySprite.h
//  Game3
//
//  Created by Stepanov Ilia on 07/05/15.
//
//

#ifndef __Game3__ArraySprite__
#define __Game3__ArraySprite__

#include "cocos2d.h"

using namespace cocos2d;

class ArraySprite : public Sprite
{
public:
	
	~ArraySprite();
	
	static ArraySprite * create(Size size, const GLubyte * data)
	{
		ArraySprite * instance = new ArraySprite();
		instance->init(size, data);
		instance->autorelease();
		return instance;
	}
	
	void update(const GLubyte * data);
	
private:
	
	ArraySprite();
	
	bool init(Size size, const GLubyte * data);
	Size _textureSize;
	Texture2D *_texture; //@todo: release it safety!
	
};


#endif /* defined(__Game3__ArraySprite__) */
