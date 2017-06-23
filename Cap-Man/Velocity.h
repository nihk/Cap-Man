#pragma once
class Velocity {
public:
	Velocity();
	Velocity(float vx, float vy);
	Velocity(const Velocity& vec);
	~Velocity();

	Velocity&	operator=(const Velocity& other);
	Velocity	operator+(const Velocity& other) const;
	Velocity	operator-(const Velocity& other) const;
	Velocity	operator*(const float& scalar) const;
	Velocity&	operator+=(const Velocity& other);
	Velocity&	operator-=(const Velocity& other);
	bool		operator==(const Velocity& other) const;

	float		vx() const { return mVelocityX; }
	float		vy() const { return mVelocityY; }
	void		setVx(float vx) { mVelocityX = vx; }
	void		setVy(float vy) { mVelocityY = vy; }

	bool		isMoving() const { return mVelocityX != 0.0f || mVelocityY != 0.0f; }
	int			calcDeltaX(float delta) const { return static_cast<int>(mVelocityX * delta); }
	int			calcDeltaY(float delta) const { return static_cast<int>(mVelocityY * delta); }

private:
	float		mVelocityX;
	float		mVelocityY;
};

