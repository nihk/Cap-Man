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

	const std::vector<std::string>& systemTypes() const { return mSystemTypes; }

private:
	std::vector<std::string> mSystemTypes;
};

