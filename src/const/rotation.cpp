#include "rotation.h"

float ReverseRotation(float rotation) {
    if (rotation == UP_ROTATION) {
        return DOWN_ROTATION;
    }
    if (rotation == RIGHT_ROTATION) {
        return LEFT_ROTATION;
    }
    if (rotation == DOWN_ROTATION) {
        return UP_ROTATION;
    }
    return RIGHT_ROTATION;
}
