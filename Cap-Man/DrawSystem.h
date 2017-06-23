#pragma once
#include "System.h"

class Renderer;

class DrawSystem
	: public System {
public:
	DrawSystem(Manager& manager, Renderer& renderer);
	~DrawSystem();

	void updateEntity(float delta, int entity) override;

private:
	Renderer& mRenderer;
};

