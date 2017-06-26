#pragma once
#include <cstdint>
#include "Constants.h"

// Not a wrapper of an SDL struct per se, but does initialize
// it's mKeys member via an SDL function
class Keyboard {
public:
	Keyboard();
	~Keyboard();

	bool initialize();
	bool isKeyBeingPressed(Keys::Key key) const;
	int getRecentKeyDown() const { return mRecentKeyDown; }
	void setRecentKeyDown(int key) { mRecentKeyDown = key; }

private:
	int mRecentKeyDown;
	const uint8_t* mKeys;
};

