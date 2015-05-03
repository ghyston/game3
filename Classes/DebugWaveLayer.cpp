//
//  DebugWaveLayer.cpp
//  Game3
//
//  Created by Stepanov Ilia on 03/05/15.
//
//

#include "DebugWaveLayer.h"

DebugWaveLayer::DebugWaveLayer()
{
	
}

DebugWaveLayer::~DebugWaveLayer()
{
	
}

void DebugWaveLayer::init (Vec2 mapSize, Size tileSize)
{
	_mapSize = mapSize;
	
	float height = mapSize.y * tileSize.height;
	
	setContentSize(Size(mapSize.x * tileSize.width, height));

	for(int iY = 0; iY < mapSize.y; iY++)
	{
		for(int iX = 0; iX < mapSize.x; iX++)
		{
			Label * lbl = Label::Label::createWithTTF("x", "fonts/Marker Felt.ttf", 16);
			lbl->setColor(Color3B(255, 0, 0));
			lbl->setPosition((iX + 0.5) * tileSize.width, height - (iY + 0.5) * tileSize.height);
			addChild(lbl);
			_labels.pushBack(lbl);
		}
	}
	
}

void DebugWaveLayer::updateValues(const int * values)
{
	int cellsCount = _mapSize.x * _mapSize.y;
	
	for(int i = 0; i < cellsCount; i++)
	{
		_labels.at(i)->setString(String::createWithFormat("%i", values[i])->getCString());
	}
}