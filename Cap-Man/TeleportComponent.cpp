#include "TeleportComponent.h"

TeleportComponent::TeleportComponent(Rect portPadA, Directions::Direction emergantSideA, Rect portPadB, Directions::Direction emergantSideB) 
	: mPortPadA(portPadA)
	, mPortPadB(portPadB)
	, mEmergantSideA(emergantSideA)
	, mEmergantSideB(emergantSideB) {
}

TeleportComponent::~TeleportComponent() {
}
