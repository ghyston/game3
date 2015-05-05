//
//  DebugVecLayer.cpp
//  Game3
//
//  Created by Stepanov Ilia on 04/05/15.
//
//

#include "DebugVecLayer.h"

DebugVecLayer::DebugVecLayer()
{
	
}

DebugVecLayer::~DebugVecLayer()
{
	
}

void DebugVecLayer::init (Vec2 mapSize, Size tileSize)
{
	_mapSize = mapSize;
	
	float height = mapSize.y * tileSize.height;
	
	setContentSize(Size(mapSize.x * tileSize.width, height));
	
	for(int iY = 0; iY < mapSize.y; iY++)
	{
		for(int iX = 0; iX < mapSize.x; iX++)
		{
			Label * lbl = Label::Label::createWithTTF("x", "fonts/arial.ttf", 10);
			lbl->setColor(Color3B(0, 0, 0));
			lbl->setPosition((iX + 0.5) * tileSize.width, height - (iY + 0.9) * tileSize.height);
			addChild(lbl);
			_labels.pushBack(lbl);
		}
	}
	
}

void DebugVecLayer::updateValues(const Vec2 * values)
{
	int cellsCount = _mapSize.x * _mapSize.y;
	
	for(int i = 0; i < cellsCount; i++)
	{
		Vec2 v = values[i];
		String * vecStr = String::createWithFormat("%2.2f,\n%2.2f", values[i].x, values[i].y);
		//log(vecStr->getCString());
		_labels.at(i)->setString(vecStr->getCString());
	}
}