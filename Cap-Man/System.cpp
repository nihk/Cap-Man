#include "System.h"

System::System(Manager& manager)
    : mManager(manager)
    , mIsUpdatable(true) {
}

size_t System::updateEntities(float delta) {
    size_t numUpdatedEntities = 0;

    if (mIsUpdatable) {
        // Derived classes can use their own logic to impose order
        for (auto& entity : mMatchingEntities) {
            updateEntity(delta, entity);
            ++numUpdatedEntities;
        }
    }

    return numUpdatedEntities;
}
