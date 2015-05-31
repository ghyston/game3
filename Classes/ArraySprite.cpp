//
//  ArraySprite.cpp
//  Game3
//
//  Created by Stepanov Ilia on 07/05/15.
//
//

#include "ArraySprite.h"

ArraySprite::ArraySprite()
{
	_texture = NULL;
}

ArraySprite::~ArraySprite()
{
	
}

bool ArraySprite::init(Size size, const GLubyte * data)
{
	Sprite::init();
	_textureSize = size;
	setContentSize(size);
	
	//update(data);
	_texture = new Texture2D();
	
	//@todo: check possible memory leaks here!
	_texture->initWithData(data, _textureSize.width * _textureSize.height * 4, Texture2D::PixelFormat::RGBA8888, _textureSize.width, _textureSize.height, _textureSize);
	setTexture(_texture);
	initWithTexture(_texture);
	
	return false;
}

void ArraySprite::update(const GLubyte * data)
{
	_texture->updateWithData(data, 0, 0, _textureSize.width, _textureSize.height);
	
	/*if(_texture == NULL)
		_texture = new Texture2D();
	
	//@todo: check possible memory leaks here!
	_texture->initWithData(data, _textureSize.width * _textureSize.height * 4, Texture2D::PixelFormat::RGBA8888, _textureSize.width, _textureSize.height, _textureSize);
	setTexture(_texture);
	initWithTexture(_texture);*/
}