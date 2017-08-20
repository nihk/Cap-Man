#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent() 
    : GraphicsComponent(true) {
}

GraphicsComponent::GraphicsComponent(bool shouldDraw)
    : mShouldDraw(shouldDraw) {
}

GraphicsComponent::~GraphicsComponent() {
}
