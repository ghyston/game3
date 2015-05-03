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

void DebugWaveLayer::init (Vec2 mapSize, Size tileSize, int * values)
{
	float height = mapSize.y * tileSize.height;
	
	setContentSize(Size(mapSize.x * tileSize.width, height));

	for(int iX = 0; iX < mapSize.x; iX++)
	{
		for(int iY = 0; iY < mapSize.y; iY++)
		{
			int id = iY * mapSize.x + iX;
			int val = values[id];
			
			String * strVal = String::createWithFormat("%i", val);
			Label * lbl = Label::Label::createWithTTF(strVal->getCString(), "fonts/Marker Felt.ttf", 16);
			lbl->setColor(Color3B(255, 0, 0));
			lbl->setPosition((iX + 0.5) * tileSize.width, height - (iY + 0.5) * tileSize.height);
			addChild(lbl);
		}
	}
	
}