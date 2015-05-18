//
//  GameScene.cpp
//  Game3
//
//  Created by Stepanov Ilia on 09/04/15.
//
//

#include "GameScene.h"

using namespace cocos2d;

GameScene::GameScene()
{
	_tiledMap = NULL;
	_debugLayer = NULL;
	_debugVecLayer = NULL;
	_arraySprite = NULL;
}

GameScene::~GameScene()
{
	setTiledMap(NULL);
	setDebugLayer(NULL);
	setDebugVecLayer(NULL);
	setArraySprite(NULL);
}

bool GameScene::init()
{
	if(!Scene::init())
		return false;
	
	_touched = false;
	
	this->scheduleUpdate();
	
	//CCNotificationCenter
	
	//EventListenerCustom * elc = EventListenerCustom::create("NEW_TOWER_SPRITE", GameScene::onNewShip);
	
	Director * d = Director::getInstance();
	EventDispatcher * ed = d->getEventDispatcher();
	ed->addCustomEventListener("NEW_TOWER_SPRITE", CC_CALLBACK_1(GameScene::onNewShip, this));
	ed->addCustomEventListener("MAP_LOADED", CC_CALLBACK_1(GameScene::onMapLoaded, this));
	ed->addCustomEventListener("DEBUG_MAP_UPDATED", CC_CALLBACK_1(GameScene::onDebugMapUpdated, this));
	ed->addCustomEventListener("DEBUG_VEC_MAP_UPDATED", CC_CALLBACK_1(GameScene::onDebugVecMapUpdated, this));
	
	_battle.init();
	
	auto touchListener = EventListenerTouchOneByOne::create();
	
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	
	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch*, cocos2d::Event*)
{
	_touched = true;
	return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* t, cocos2d::Event* e)
{
	_touched = false;
	Vec2 loc = t->getLocation();
	
	Vec2 startLoc = t->getStartLocation();
	
	if((std::abs(startLoc.x - loc.x) < 10) && (std::abs(startLoc.y - loc.y) < 10))
	   _battle.updateGoal(loc - getTiledMap()->getPosition());
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event*)
{
	if(!_touched)
		return;
	
	Vec2 prevLoc = touch->getPreviousLocation();
	Vec2 currLoc = touch->getLocation();
	
	
	getTiledMap()->setPositionX(getTiledMap()->getPositionX() + (currLoc.x - prevLoc.x));
	getTiledMap()->setPositionY(getTiledMap()->getPositionY() + (currLoc.y - prevLoc.y));
}

void GameScene::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*)
{
	_touched = false;
}

void GameScene::onNewShip(EventCustom * event)
{
	if(getTiledMap() == NULL)
		return;
	
	Sprite * ship = (Sprite*)(event->getUserData());
	if(ship == NULL)
		return;
	
	getTiledMap()->addChild(ship);
}

void GameScene::onMapLoaded(EventCustom * event)
{
	TMXTiledMap * tiledMap = (TMXTiledMap *)(event->getUserData());
	if(tiledMap == NULL)
		return;
	
	setTiledMap(tiledMap);
	addChild(tiledMap);
	
	DebugWaveLayer * dwl = DebugWaveLayer::create(tiledMap->getMapSize(),
												  tiledMap->getTileSize());
	setDebugLayer(dwl);
	//getTiledMap()->addChild(dwl);
	
	
	DebugVecLayer * dvl = DebugVecLayer::create(tiledMap->getMapSize(),
												tiledMap->getTileSize());
	setDebugVecLayer(dvl);
	//getTiledMap()->addChild(dvl);
	
	const float arraySpritePixelsPerTile = 5; //very hard to explain this constant meaning, jft, 25 pixels per tile
	float scaleFactor = tiledMap->getTileSize().width / arraySpritePixelsPerTile; //@note: for simply, lets say, that tile width == height
	Size arrayMapSize = Size(tiledMap->getMapSize().width * arraySpritePixelsPerTile, tiledMap->getMapSize().height * arraySpritePixelsPerTile);
	_assResolution = arrayMapSize.width * arrayMapSize.height;
	
	_tempSpriteData = new GLbyte[4 * _assResolution];
	genRandomTexture();
	
	ArraySprite * as = ArraySprite::create(arrayMapSize, _tempSpriteData);
	setArraySprite(as);
	as->setAnchorPoint(Vec2(0, 0));
	as->setScale(scaleFactor);
	getTiledMap()->addChild(as);
	
}

void GameScene::genRandomTexture()
{
	for(size_t i = 0; i <= _assResolution; i++)
	{
		_tempSpriteData[i * 4 + 1]=0;
		_tempSpriteData[i * 4 + 2]=0;
		
		if(rand() % 10 < 1)
		{
			_tempSpriteData[i * 4 + 0]=255;
			_tempSpriteData[i * 4 + 3]=128;
		}
		else
		{
			_tempSpriteData[i * 4 + 0]=0;
			_tempSpriteData[i * 4 + 3]=0;
		}
	}
}

void GameScene::onDebugMapUpdated(EventCustom * event)
{
	if(getDebugLayer() == NULL)
		return;
	
	int * values = (int *)(event->getUserData());
	getDebugLayer()->updateValues(values);
}

void GameScene::onDebugVecMapUpdated(EventCustom * event)
{
	if(getDebugLayer() == NULL)
		return;
	
	Vec2 * values = (Vec2 *)(event->getUserData());
	getDebugVecLayer()->updateValues(values);
}

void GameScene::update(float delta)
{
	Scene::update(delta);
	
	_battle.update(delta);
	
	if(getArraySprite() != NULL)
	{
		genRandomTexture();
		getArraySprite()->update(_tempSpriteData);
	}
}