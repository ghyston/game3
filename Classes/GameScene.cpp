//
//  GameScene.cpp
//  Game3
//
//  Created by Stepanov Ilia on 09/04/15.
//
//

#include "GameScene.h"

using namespace cocos2d;

bool GameScene::init()
{
	if(!Scene::init())
		return false;
	
	this->scheduleUpdate();
	
	//CCNotificationCenter
	
	//EventListenerCustom * elc = EventListenerCustom::create("NEW_TOWER_SPRITE", GameScene::onNewShip);
	
	Director * d = Director::getInstance();
	EventDispatcher * ed = d->getEventDispatcher();
	ed->addCustomEventListener("NEW_TOWER_SPRITE", CC_CALLBACK_1(GameScene::onNewShip, this));
	
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
	return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* t, cocos2d::Event* e)
{
	Vec2 loc = t->getLocation();
	_battle.startShipMoving(loc);
}

void GameScene::onTouchMoved(cocos2d::Touch*, cocos2d::Event*)
{
	
}

void GameScene::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*)
{
	
}

void GameScene::onNewShip(EventCustom * event)
{
	Sprite * ship = (Sprite*)(event->getUserData());
	if(ship == NULL)
		return;
	
	addChild(ship);
}

void GameScene::update(float delta)
{
	Scene::update(delta);
	
	_battle.update(delta);
}