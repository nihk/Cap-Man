#pragma once
#include "Component.h"
#include "Velocity.h"

class VelocityComponent
	: public Component<VelocityComponent> {
public:
	VelocityComponent(float vx, float vy, float speed);
	VelocityComponent(Velocity velocity, float speed);
	~VelocityComponent();

	Velocity	velocity() const					{ return mVelocity; }
	void		setVelocity(float vx, float vy)		{ mVelocity.setVx(vx); mVelocity.setVy(vy); }
	float		speed() const						{ return mSpeed; }
	void		setSpeed(float speed)				{ mSpeed = speed; }
	bool		isMoving() const					{ return mVelocity.isMoving(); }

private:
	Velocity	mVelocity;
	float		mSpeed;
};

