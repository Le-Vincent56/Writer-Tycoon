#pragma once

class GraphicsSettings
{
public:
	// Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned int frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	// Constructor/Destructor
	GraphicsSettings();
	virtual ~GraphicsSettings();

	// Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
