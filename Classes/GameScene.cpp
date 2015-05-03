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
}

GameScene::~GameScene()
{
	setTiledMap(NULL);
	setDebugLayer(NULL);
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
	ed->addCustomEventListener("DEBUG_MAP_LOADED", CC_CALLBACK_1(GameScene::onDebugMapLoaded, this));
	
	_battle.init(0, 0);
	
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
	_battle.startShipMoving(loc);
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
	Sprite * ship = (Sprite*)(event->getUserData());
	if(ship == NULL)
		return;
	
	addChild(ship);
}

void GameScene::onMapLoaded(EventCustom * event)
{
	TMXTiledMap * tiledMap = (TMXTiledMap *)(event->getUserData());
	if(tiledMap == NULL)
		return;
	
	setTiledMap(tiledMap);
	addChild(tiledMap);
}

void GameScene::onDebugMapLoaded(EventCustom * event)
{
	DebugWaveLayer * dwl = (DebugWaveLayer *)(event->getUserData());
	if(dwl == NULL)
		return;
	
	getTiledMap()->
	
	addChild(dwl);
}

void GameScene::update(float delta)
{
	Scene::update(delta);
	
	_battle.update(delta);
}