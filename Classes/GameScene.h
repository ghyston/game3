//
//  GameScene.h
//  Game3
//
//  Created by Stepanov Ilia on 09/04/15.
//
//

#ifndef __Game3__GameScene__
#define __Game3__GameScene__

#include "cocos2d.h"

#include "Battle.h"

using namespace cocos2d;

class GameScene : public Scene
{
public:
	
	CREATE_FUNC(GameScene);
	
	virtual void update(float delta);
	
	void onNewShip(EventCustom * event);
	
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	
private:
	
	bool init();
	
	Battle _battle;
};

#endif /* defined(__Game3__GameScene__) */
