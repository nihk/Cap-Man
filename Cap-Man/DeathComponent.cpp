#include "DeathComponent.h"

DeathComponent::DeathComponent()
	: DeathComponent(false) {
}

DeathComponent::DeathComponent(bool isDead)
	: mIsDead(isDead) {
}

DeathComponent::~DeathComponent() {
}
