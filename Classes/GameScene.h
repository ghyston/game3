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
#include "DebugWaveLayer.h"
#include "DebugVecLayer.h"
#include "ArraySprite.h"

using namespace cocos2d;

class GameScene : public Scene
{
public:
	
	CREATE_FUNC(GameScene);
	
	~GameScene();
	
	virtual void update(float delta);
	
	void onNewShip(EventCustom * event);
	void onMapLoaded(EventCustom * event);
	void onCountMapLoaded(EventCustom * event);
	void onDebugMapUpdated(EventCustom * event);
	void onDebugVecMapUpdated(EventCustom * event);
	
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	
private:
	
	GameScene();
	
	bool init();
	
	Battle _battle;
	bool _touched;
	
	void createArmySwitcher();
	void onSwitchArmy(Ref * pObj);
	
	CC_SYNTHESIZE_RETAIN(TMXTiledMap *, _tiledMap, TiledMap);
	CC_SYNTHESIZE_RETAIN(DebugWaveLayer *, _debugLayer, DebugLayer);
	CC_SYNTHESIZE_RETAIN(DebugVecLayer *, _debugVecLayer, DebugVecLayer);
	CC_SYNTHESIZE_RETAIN(ArraySprite *, _arraySprite, ArraySprite);
	
	CC_SYNTHESIZE_RETAIN(Menu *, _armySwitcher, ArmySwitcher);
	
	const GLubyte * _spriteData;
	//@todo: jft, remove!
	/*GLbyte * _tempSpriteData;
	void genRandomTexture();
	uint _assResolution;*/
	
};

#endif /* defined(__Game3__GameScene__) */
