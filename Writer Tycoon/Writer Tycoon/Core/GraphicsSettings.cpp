#include "../stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "Writer Tycoon";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{
}

void GraphicsSettings::saveToFile(const std::string path)
{
	// Open the config ini
	std::ofstream ofs(path);

	// Check if the file is open
	if (ofs.is_open())
	{
		// Write data
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;		// Load window size settings
		ofs << this->fullscreen;										// Load fullscreen settings
		ofs << this->frameRateLimit;									// Load framerate limit settings
		ofs << this->verticalSync;										// Load VSync settings
		ofs << this->contextSettings.antialiasingLevel;					// Load antialiasing settings
	}

	// Close the file
	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	// Open the config ini
	std::ifstream ifs(path);

	// Check if the file is open
	if (ifs.is_open())
	{
		// Read data
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;		// Load window size settings
		ifs >> this->fullscreen;										// Load fullscreen settings
		ifs >> this->frameRateLimit;									// Load framerate limit settings
		ifs >> this->verticalSync;										// Load VSync settings
		ifs >> this->contextSettings.antialiasingLevel;					// Load antialiasing settings
	}

	// Close the file
	ifs.close();
}
