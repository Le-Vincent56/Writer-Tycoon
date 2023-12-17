#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	// Variables
	sf::RenderTarget* window;
	std::vector<sf::Texture*> textures;
	bool quit;

public:
	// Constructor/Destructor
	State(sf::RenderWindow* window);
	virtual ~State();

	// Functions
	const bool& getQuit() const;
	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

