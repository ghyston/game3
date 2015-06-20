//
//  EntityFabric.cpp
//  Game3
//
//  Created by Stepanov Ilia on 13/04/15.
//
//

#include "EntityFabric.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "BezierMoveComponent.h"
#include "NodeComponent.h"
#include "RenderComponent.h"
#include "NodeComponent.h"
#include "EnergyStorageComponent.h"
#include "EnergyGeneratorComponent.h"
#include "ParticleComponent.h"

using namespace cocos2d;

void EntityFabric::createTower(World& world)
{
	EntityManager * em = world.getEntityManager();
	
	Entity & tower = em->create();
	
	MovementComponent * moveCmp = new MovementComponent();
	PositionComponent * posCmp = new PositionComponent();
	RenderComponent * renderCmp = new RenderComponent();
	
	//@todo: finish here!
	
	tower.addComponent(renderCmp);
	tower.addComponent(moveCmp);
	tower.addComponent(posCmp);
	tower.refresh();
}

int EntityFabric::createShip(World& world)
{
	EntityManager * em = world.getEntityManager();
	
	Entity & ship = em->create();
	
	//BezierMoveComponent * bMoveCmp = new BezierMoveComponent();
	PositionComponent * posCmp = new PositionComponent();
	RenderComponent * renderCmp = new RenderComponent();
	
	Sprite * shipSprite = Sprite::create("ship_s.png");
	renderCmp->_sprite = shipSprite;
	
	posCmp->_pos = Vec2(300, 300);
	
	/*bMoveCmp->_duration = 10;
	bMoveCmp->_timeLeft = 10;
	bMoveCmp->_P0 = Vec2(0,0);
	bMoveCmp->_P1 = Vec2(100,200);
	bMoveCmp->_P2 = Vec2(500,500);*/
	
	EventCustom * event = new EventCustom("NEW_TOWER_SPRITE");
	event->autorelease();
	event->setUserData(shipSprite);
	
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
	
	ship.addComponent(renderCmp);
	//ship.addComponent(bMoveCmp);
	ship.addComponent(posCmp);
	ship.refresh();
	
	return ship.getId();
}

int EntityFabric::createParticle(World& world, ParticleMap * map)
{
	EntityManager * em = world.getEntityManager();
	Entity & particle = em->create();
	
	MovementComponent * movCmp = new MovementComponent();
	PositionComponent * posCmp = new PositionComponent();
	
	ParticleComponent * particleCmp = new ParticleComponent(map);
	
//	RenderComponent * renderCmp = new RenderComponent();
	
//	Sprite * sprite = Sprite::create("energy_sprite.png");
//	renderCmp->_sprite = sprite;
	
	posCmp->_pos = Vec2(100 + rand() % 300, 110 + rand() % 330);
	
/*	EventCustom * event = new EventCustom("NEW_TOWER_SPRITE");
	event->autorelease();
	event->setUserData(sprite);
	
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(event);*/
	
	particle.addComponent(movCmp);
//	particle.addComponent(renderCmp);
	particle.addComponent(particleCmp);
	particle.addComponent(posCmp);
	particle.refresh();
	
	return particle.getId();
}