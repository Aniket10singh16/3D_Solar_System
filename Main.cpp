#include "Application.h"

int main()
{
	try
	{
		// Create the engine application with window settings
		Application app(1280, 720, "Celestial Engine - Phase 2");

		// Run the main loop (blocks until exit)
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return EXIT_FAILURE;

	}

    return EXIT_SUCCESS;
}
