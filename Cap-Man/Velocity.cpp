#include "Velocity.h"

Velocity::Velocity()
	: Velocity(0.0f, 0.0f) {
}

Velocity::Velocity(int vx, int vy) 
	: Velocity(static_cast<float>(vx), static_cast<float>(vy)) {
}

Velocity::Velocity(float vx, float vy)
	: mVelocityX(vx)
	, mVelocityY(vy) {
}

Velocity::Velocity(const Velocity& other)
	: Velocity(other.mVelocityX, other.mVelocityY) {
}

Velocity::~Velocity() {
}

Velocity& Velocity::operator=(const Velocity& other) {
	this->mVelocityX = other.mVelocityX;
	this->mVelocityY = other.mVelocityY;
	return *this;
}

Velocity Velocity::operator+(const Velocity& other) const {
	return Velocity(this->mVelocityX + other.mVelocityX, this->mVelocityY + other.mVelocityY);
}

Velocity Velocity::operator-(const Velocity& other) const {
	return Velocity(this->mVelocityX - other.mVelocityX, this->mVelocityY - other.mVelocityY);
}

Velocity Velocity::operator*(const float& scalar) const {
	return Velocity(this->mVelocityX * scalar, this->mVelocityY * scalar);
}

Velocity& Velocity::operator+=(const Velocity& other) {
	this->mVelocityX += other.mVelocityX;
	this->mVelocityY += other.mVelocityY;
	return *this;
}

Velocity& Velocity::operator-=(const Velocity& other) {
	this->mVelocityX -= other.mVelocityX;
	this->mVelocityY -= other.mVelocityY;
	return *this;
}

bool Velocity::operator==(const Velocity& other) const {
	return this->mVelocityX == other.mVelocityX && this->mVelocityY == other.mVelocityY;
}