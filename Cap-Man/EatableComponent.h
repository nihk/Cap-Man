#pragma once
#include "Component.h"

class EatableComponent 
	: public Component<EatableComponent> {
public:
	EatableComponent(int eaterEntity);
	~EatableComponent();

	int eaterEntity() const { return mEaterEntity; }

private:
	int mEaterEntity;
};

