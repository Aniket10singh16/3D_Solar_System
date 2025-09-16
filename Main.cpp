#include "Application.h"

int main()
{
    // Create the engine application with window settings
    Application app(800, 600, "Celestial Engine - Phase 1");

    // Run the main loop (blocks until exit)
    app.Run();

    // Exit cleanly
    return 0;
}
