#pragma once

template<class T>
class Wrapper {
public:
    virtual ~Wrapper() = default;

    // These method should only be used when it's necessary to work with a C library's
    // functions, e.g. SDL for this game.
    virtual const T* data() const = 0;
    virtual T* mutableData() = 0;
};