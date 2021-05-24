#include "core/game.h"

int main() {
    try {
        Game* g = new Game();
        g->Start();
    } catch (...) {
        return 1;
    }

    return 0;
}