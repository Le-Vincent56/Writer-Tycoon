#include "SettingsState.h"

// Initialize Functions
void SettingsState::initVariables()
{
	// Load video modes
	this->modes = sf::VideoMode::getFullscreenModes();
	this->changesMade = false;
}

void SettingsState::initBackground()
{
	// Set backgorund size to the window size
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	// Attempt to load the background texture
	if (!this->backgroundTexture.loadFromFile("Assets/Images/main_menu_background.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	// Set the background texture;
	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initTextures()
{
	// Load button sprites
	if (!this->buttonIdle.loadFromFile("Assets/Sprites/UI/button_long_idle.png"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED_TO_LOAD_BUTTON_LONG_IDLE_TEXTURE";
	}

	if (!this->buttonPressed.loadFromFile("Assets/Sprites/UI/button_long_active.png"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED_TO_LOAD_BUTTON_LONG_ACTIVE_TEXTURE";
	}

	// Load dropdown sprites
	if (!this->dropdownIdle.loadFromFile("Assets/Sprites/UI/dropdown_idle.png"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED_TO_LOAD_DROPDOWN_IDLE_TEXTURE";
	}

	if (!this->dropdownActive.loadFromFile("Assets/Sprites/UI/dropdown_active.png"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED_TO_LOAD_DROPDOWN_ACTIVE_TEXTURE";
	}
}

void SettingsState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/monogram-extended.ttf"))
	{
		throw("ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT_MONOGRAM_EXTENDED");
	}
}

void SettingsState::initKeybinds()
{
	// Open the control scheme
	std::ifstream ifs("Config/settingsstate_keybinds.ini");

	// Add keys to the control scheme through the text file
	if (ifs.is_open())
	{
		std::string bindKey = "";
		std::string controlKey = "";

		while (ifs >> bindKey >> controlKey)
		{
			this->keybinds[bindKey] = this->supportedKeys->at(controlKey);
		}
	}

	// Close the ilfe stream
	ifs.close();
}


void SettingsState::initGUI()
{
	// Button Params
	float windowThreeFourthsX = this->window->getSize().x - (this->window->getSize().x / 3.0f);
	float buttonWidth = 200.0f;
	float buttonCenterX = windowThreeFourthsX - (buttonWidth / 2.0f);

	float windowCenterY = this->window->getSize().y / 2.0f;
	float buttonHeight = 75.0f;

	// Save Button
	this->buttons["SAVE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 5.0),
		buttonWidth, buttonHeight,
		this->font, "SAVE", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);

	// Disable the save button at first
	this->buttons["SAVE"]->setEnabled(false);

	// Back Button
	this->buttons["BACK"] = new Button(
		buttonCenterX + buttonWidth, windowCenterY + (buttonHeight * 5.0f),
		buttonWidth, buttonHeight,
		this->font, "BACK", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);

	float windowCenterX = this->window->getSize().x / 2.0f;
	float dropdownWidth = 300.0f;
	float dropdownCenterX = windowCenterX - (dropdownWidth / 2.0f);

	float dropdownCenterY = this->window->getSize().y / 5.0f;
	float dropdownHeight = 40.0f;

	std::vector<std::string> modesStrings;
	for (auto& i : this->modes)
	{
		modesStrings.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}

	this->dropdowns["RESOLUTION"] = new DropDown(
		dropdownCenterX, dropdownCenterY, dropdownWidth , dropdownHeight,
		this->font, 
		this->dropdownIdle, this->dropdownActive,
		modesStrings.data(),
		modesStrings.size(), 0
	);

	this->initText(dropdownCenterX, dropdownWidth, dropdownCenterY);
}

void SettingsState::initText(const float& dropdownCenterX, const float& dropdownWidth,
	const float& dropdownCenterY)
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(dropdownCenterX - (dropdownWidth / 2.0f) -  50, dropdownCenterY));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution\nFullscreen\nVsync\nAntialising"
	);
}

// Constructor/Destructor
SettingsState::SettingsState(sf::RenderWindow* window, 
	std::map<std::string, int>* supportedKeys, 
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	// Initialize variables
	this->initVariables();
	this->initBackground();
	this->initTextures();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
}

SettingsState::~SettingsState()
{
	auto itButtons = this->buttons.begin();
	for (itButtons = this->buttons.begin(); itButtons != this->buttons.end(); ++itButtons)
	{
		delete itButtons->second;
	}

	auto itDropDowns = this->dropdowns.begin();
	for (itDropDowns = this->dropdowns.begin(); itDropDowns != this->dropdowns.end(); ++itDropDowns)
	{
		delete itDropDowns->second;
	}
}

// Functions
void SettingsState::updateEvents(sf::Event& sfEvent)
{
	// Update button events
	for (auto& it : this->buttons)
	{
		it.second->updateEvents(sfEvent, this->mousePosView);
	}

	// Update button events
	for (auto& it : this->dropdowns)
	{
		it.second->updateEvents(sfEvent, this->mousePosView);
	}
}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateGUI(const float& dt)
{
	// Update the buttons
	for (auto& it : this->buttons)
	{
		it.second->update(dt, this->mousePosView);
	}

	// Update dropdown
	for (auto& it : this->dropdowns)
	{
		// Check if settings have been changed
		if (it.second->getLastCurrentElementID() != it.second->getCurrentElementID())
		{
			this->changesMade = true;
		}

		// Update
		it.second->update(dt, this->mousePosView);
	}

	// Save changes
	if (this->buttons["SAVE"]->isPressed())
	{
		// Save changes
		this->window->create(
			this->modes[this->dropdowns["RESOLUTION"]->getCurrentElementID()],
			"Test", sf::Style::Default
		);

		// Reset changes made
		this->changesMade = false;
	}

	// Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// Enable the save button if changes made, disable if not
	if (changesMade)
	{
		this->buttons["SAVE"]->setEnabled(true);
	}
	else
	{
		this->buttons["SAVE"]->setEnabled(false);
	}
}

void SettingsState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update input
	this->updateInput(dt);

	// Update buttons
	this->updateGUI(dt);
}

void SettingsState::renderGUI(sf::RenderTarget& target)
{
	// Draw the buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	// Draw dropdowns
	for (auto& it : this->dropdowns)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw the background
	target->draw(this->background);

	this->renderGUI(*target);

	target->draw(this->optionsText);
}