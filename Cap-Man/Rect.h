#pragma once
#include <SDL.h>
#include "Point.h"

class Rect 
	: public Wrapper<SDL_Rect> {
public:
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(const Rect& other);
	Rect&				operator=(const Rect& other);
	bool				operator==(const Rect& other) const;

	int					x() const							{ return mSdlRect.x; }
	int					y() const							{ return mSdlRect.y; }
	int					width() const						{ return mSdlRect.w; }
	int					height() const						{ return mSdlRect.h; }

	void				setWidth(int w)						{ mSdlRect.w = w; }
	void				setHeight(int h)					{ mSdlRect.h = h; }

	int					left() const						{ return mSdlRect.x; }
	int					top() const							{ return mSdlRect.y; }
	int					right() const						{ return mSdlRect.x + mSdlRect.w; }
	int					bottom() const						{ return mSdlRect.y + mSdlRect.h; }

	Point				center() const;
	Point				topLeft() const;
	Point				topRight() const;
	Point				bottomRight() const;
	Point				bottomLeft() const;
	float				area() const;

	void				setLeft(int x)						{ mSdlRect.x = x; }
	void				setRight(int x)						{ mSdlRect.x = x - mSdlRect.w; }
	void				setTop(int y)						{ mSdlRect.y = y; }
	void				setBottom(int y)					{ mSdlRect.y = y - mSdlRect.h; }

	void				setCenter(int x, int y);
	void				setCenter(const Point& point);
	void				setRect(Rect rect)					{ mSdlRect = rect.mSdlRect; }
	void				setRect(int x, int y, int w, int h) { mSdlRect.x = x; mSdlRect.y = y; mSdlRect.w = w; mSdlRect.h = h; }

	bool				isWithinScreenBounds(int sw, int sh) const;
	bool				containsPoint(const Point& point) const;
	bool				containsRect(const Rect& rect) const;

	bool				isEmpty() const						{ return SDL_RectEmpty(&mSdlRect) == SDL_TRUE; }

	const SDL_Rect*		data() const override				{ return &mSdlRect; }
	SDL_Rect*			mutableData() override				{ return &mSdlRect; }

private:
	SDL_Rect			mSdlRect;
};
