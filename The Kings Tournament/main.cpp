// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "app.h"

// Constants
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;

// Globals
Application app(SCREEN_WIDTH, SCREEN_HEIGHT);

// ============================================================================
// [Entry-Point]
// ============================================================================

int main(int argc, char* argv[])
{
    app.initialize();
    app.run();
    
    return EXIT_SUCCESS;
}