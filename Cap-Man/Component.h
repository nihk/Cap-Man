#pragma once
#include "UID.h"

class ComponentBase {
public:
	virtual ~ComponentBase() = default;
};

// CRTP to ensure that immediate derived classes of ComponentBase will have their own 
// unique static IDs, but children of those will retain the parent ID. E.g. this is useful for a 
// component class PositionComponent with child PlayerPositionComponent. Both
// Position components will have the same ID, but something like InputComponent, not derived from
// PositionComponent, will have a different ID. This facilitates polymorphism.
// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
template<class Derived>
class Component
	: public ComponentBase {
public:
	static const int ID;
};

template<class Derived>
const int Component<Derived>::ID = UID::generate();