#include "stdafx.h"
#include "Core/Game.h"

void wrapper();

int main()
{
	wrapper();

	// Assert that the function returns zero indicating no memory leaks from
	// the debug CRT libraries.
	if (_CrtDumpMemoryLeaks())
	{
		std::cout << "Memory leaks detected!\n";
	}

	return 0;
}

void wrapper()
{
	// Create the game and initialize the window
	Game game;

	// Run the window
	game.run();
}
