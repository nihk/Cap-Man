#pragma once
#include "Component.h"

class LifeCollisionComponent 
	: public Component<LifeCollisionComponent> {
public:
	// Holder: The entity has life, e.g. Cap-Man
	// Taker: The entity takes life away from a holder
	enum class Type { HOLDER, TAKER };

	LifeCollisionComponent(Type type);
	~LifeCollisionComponent();

	Type type() const { return mType; }

private:
	Type mType;
};

