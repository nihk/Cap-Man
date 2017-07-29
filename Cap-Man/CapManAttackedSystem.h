#pragma once
#include "System.h"
#include <vector>
#include <unordered_set>

class CapManAttackedSystem 
	: public System {
public:
	CapManAttackedSystem(Manager& manager, int& state, std::vector<int>& lifeEntities, std::unordered_set<int>& consumedEntities);
	~CapManAttackedSystem();

	void updateEntity(float delta, int entity) override;

private:
	int& mGameState;
	std::vector<int>& mLifeEntities;
	std::unordered_set<int>& mConsumedEntities;
};

