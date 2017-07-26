#pragma once
#include "Component.h"
#include <typeindex>
#include <vector>

// TODO: Will I need to ever return other combinations of types?
class SystemControllerComponent 
	: public Component<SystemControllerComponent> {
public:
	SystemControllerComponent();
	~SystemControllerComponent();

	const std::vector<std::type_index>& systemTypes() const { return mSystemTypes; }

private:
	std::vector<std::type_index> mSystemTypes;
};

