#pragma once

template<class T>
class Wrapper {
public:
	virtual ~Wrapper() = default;

	virtual const T* data() const = 0;
	virtual T* mutableData() = 0;
};