#include "src/core/core.h"

int main() {
    try {
        Game* g = new Game();
        g->start();
    } catch (...) {
        return 1;
    }

    return 0;
}