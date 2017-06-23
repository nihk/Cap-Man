#pragma once

// A generator of application-wide unique IDs
class UID {
public:
	static int generate();
	static int getLastKnownId() { return sLastKnownId; }

private:
	static int sLastKnownId;

	// Prevent instantiation
	UID() = default;
};

