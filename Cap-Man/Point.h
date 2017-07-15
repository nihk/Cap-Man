#pragma once
#include <SDL.h>
#include "Wrapper.h"

// TODO: Wrap floats, too?
class Point 
	: public Wrapper<SDL_Point> {
public:
	Point();
	Point(int x, int y);
	~Point();

	bool				operator==(const Point& other) const;

	int					x() const				{ return mSdlPoint.x; }
	int					y() const				{ return mSdlPoint.y; }
	void				setX(int x)				{ mSdlPoint.x = x; }
	void				setY(int y)				{ mSdlPoint.y = y; }

	double				distance(const Point& other) const;
	const SDL_Point*	data() const override	{ return &mSdlPoint; }
	SDL_Point*			mutableData() override	{ return &mSdlPoint; }

private:
	SDL_Point	mSdlPoint;
};

