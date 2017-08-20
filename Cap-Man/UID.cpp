#include "UID.h"

int UID::sLastKnownId = -1;

int UID::generate() {
    return ++sLastKnownId;
}