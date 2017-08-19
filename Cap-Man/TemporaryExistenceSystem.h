#pragma once
#include "System.h"

class TemporaryExistenceSystem 
	: public System {
public:
	TemporaryExistenceSystem(Manager& manager);
	~TemporaryExistenceSystem();

	void updateEntity(float delta, int entity) override;
};

