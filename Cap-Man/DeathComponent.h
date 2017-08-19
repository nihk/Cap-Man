#pragma once
#include "Component.h"

class DeathComponent 
	: public Component<DeathComponent> {
public:
	DeathComponent();
	DeathComponent(bool isDead);
	~DeathComponent();

	bool isDead() const { return mIsDead; }
	void setDead(bool isDead) { mIsDead = isDead; }

private:
	bool mIsDead;
};

