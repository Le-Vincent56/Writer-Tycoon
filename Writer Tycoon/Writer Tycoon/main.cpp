#include "Game.h"
#include <cassert>

void OnExit();

int main()
{
    // Enable memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    // Signal this function to execute on exit
    atexit(OnExit);

	// Create the game and initialize the window
	Game game;

	// Run the window
	game.run();

	return 0;
}

void OnExit()
{
    // Assert that the function returns zero indicating no memory leaks from
    // the debug CRT libraries.
    assert(!_CrtDumpMemoryLeaks() && "Memory leak detected!");
}
