#pragma once

enum button_states {
	BTN_IDLE = 0,
	BTN_ACTIVE = 1,
	BTN_ACTIVE_FUNCTION = 2,
	BTN_DISABLED = 3
};

class Button
{
private:
	// Variables
	short unsigned int id;

	float clickBufferMax;
	float clickBuffer;

	short unsigned int buttonState;

	sf::RectangleShape shape;

	sf::Font& font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Texture& buttonIdleTexture;
	sf::Color buttonIdleColor;
	sf::Color buttonHoverColor;
	sf::Texture& buttonActiveTexture;

	bool textureOverriden;
	bool hovering;

public:
	// Constructor/Destructor
	Button(float x, float y, float width, float height,
		sf::Font& font, std::string text, unsigned int textSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture,
		short unsigned int id = 0);
	~Button();

	// Accessors
	const short unsigned int& getID() const;
	const bool isPressed();
	const std::string getText() const;
	const bool getClickBuffer();

	// Modifiers
	void setEnabled(const bool enabled);
	void setID(const short unsigned int id);
	void setText(const std::string text);
	void setButtonTexture(const sf::Texture& texture);
	void setTextureOverride(const bool isOverriding);

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2i& mousePosWindow);
	void updateClickBuffer(const float& dt);
	void update(const float& dt, const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

