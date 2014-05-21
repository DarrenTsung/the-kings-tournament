// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "app.h"

// Constants
const unsigned SCREEN_WIDTH = 1280;
const unsigned SCREEN_HEIGHT = 800;

// Globals
Application app(SCREEN_WIDTH, SCREEN_HEIGHT);

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

// ============================================================================
// [Entry-Point]
// ============================================================================

int main(int argc, char* argv[])
{
    app.initialize();
    app.run();
    
    return EXIT_SUCCESS;
}