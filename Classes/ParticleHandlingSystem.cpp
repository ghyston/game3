//
//  ParticleHandlingSystem.cpp
//  Game3
//
//  Created by Stepanov Ilia on 31/05/15.
//
//

#include "ParticleHandlingSystem.h"

ParticleHandlingSystem::ParticleHandlingSystem()
{
	addComponentType<PositionComponent>();
	_countMap = NULL;
	_gradientMap = NULL;
}

ParticleHandlingSystem::~ParticleHandlingSystem()
{
	
}

void ParticleHandlingSystem::initialize()
{
	positionMapper.init(*world);
};

void ParticleHandlingSystem::preProcess()
{
	_countMap->clean();
	_gradientMap->clearGrids(); //@todo: move to gradientCalcSystem
}

void ParticleHandlingSystem::processEntity(artemis::Entity &e)
{
	PositionComponent * posCmpt = positionMapper.get(e);
	
	Vec2 tileCoords =  _countMap->getTileCoordsByPos(posCmpt->_pos);
	_countMap->incCountR(tileCoords);
}

void ParticleHandlingSystem::postProcess()
{
//	auto t0 = std::chrono::high_resolution_clock::now();
	
	_countMap->resetAlpha();
	
//	auto t10 = std::chrono::high_resolution_clock::now();
	
	//_gradientMap->recalculateGradient();
	
	/*auto t20 = std::chrono::high_resolution_clock::now();
	
	long long int alphaTS = std::chrono::duration_cast<std::chrono::milliseconds>(t10 - t0).count();
	long long int gradientTS = std::chrono::duration_cast<std::chrono::milliseconds>(t20 - t10).count();
	
	printf("alphaTS: %lld gradientTS: %lld \n", alphaTS, gradientTS);*/

}