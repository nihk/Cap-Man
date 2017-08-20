#include "TeleportSystem.h"
#include "PhysicsComponent.h"
#include "TeleportComponent.h"
#include "Map.h"
#include "Manager.h"
#include <iostream>

TeleportSystem::TeleportSystem(Manager& manager)
        : System(manager) {
    insertRequiredComponent(TeleportComponent::ID);
    insertRequiredComponent(PhysicsComponent::ID);
}

TeleportSystem::~TeleportSystem() {
}

void TeleportSystem::updateEntity(float delta, int entity) {
    TeleportComponent& teleportComponent = mManager.getComponent<TeleportComponent>(entity);
    PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);

    Rect rect = physicsComponent.rect();
    Point center = rect.center();

    Rect portPadA = teleportComponent.portPadA();
    Rect portPadB = teleportComponent.portPadB();
    Directions::Direction emergantSideA = teleportComponent.emergantSideA();
    Directions::Direction emergantSideB = teleportComponent.emergantSideB();

    if (portPadA.containsPoint(center)) {
        emerge(rect, center, portPadB, emergantSideB);
        physicsComponent.setRect(rect);
    } else if (portPadB.containsPoint(center)) {
        emerge(rect, center, portPadA, emergantSideA);
        physicsComponent.setRect(rect);
    }
}

void TeleportSystem::emerge(Rect& rect /* out */, const Point& center, const Rect& emergantPortPad, Directions::Direction emergingSide) {
    switch (emergingSide) {
        case Directions::UP: {
            rect.setCenter(center.x(), emergantPortPad.top());
            break;
        }
        case Directions::RIGHT: {
            rect.setCenter(emergantPortPad.right(), center.y());
            break;
        }
        case Directions::DOWN: {
            rect.setCenter(center.x(), emergantPortPad.bottom());
            break;
        }
        case Directions::LEFT: {
            rect.setCenter(emergantPortPad.left(), center.y());
            break;
        }
        default: {
            std::cout << "Error: attempting to emerge from an invalid direction" << std::endl;
            break;
        }
    }
}
