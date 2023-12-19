#pragma once

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class AnimationComponent
{
private:
	class Animation
	{
	public:
		// Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;

		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		// Constructor
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, 
			float animationTimer, 
			int startFrameX, int startFrameY, int endFrameX, int endFrameY, int width, int height)
			: sprite(sprite), textureSheet(textureSheet), 
			animationTimer(animationTimer), 
			width(width), height(height)
		{
			this->timer = 0.0f;

			// Estabish rects
			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(endFrameX * width, endFrameY * height, width, height);

			// Set start rect texture
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		// Functions
		void play(const float& dt)
		{
			// Update timer
			this->timer += 10.0f * dt;

			// Check if the timer should be reset
			if (this->timer >= this->animationTimer)
			{
				// Reset timer
				this->timer = 0.0f;

				// Check if the current rect is at the end
				if (this->currentRect != this->endRect)
				{
					// Move the rect over by its width to get to the next sprite
					this->currentRect.left += this->width;
				}
				else
				{
					// Reset the current rect back to the start
					this->currentRect.left = this->startRect.left;
				}

				// Set the sprite at the current rect
				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset()
		{
			this->timer = 0.0f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;

public:
	// Constructor/Destructor
	AnimationComponent(sf::Sprite&, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	// Functions
	void addAnimation(const std::string key, 
		float animationTimer,
		int startFrameX, int startFrameY, int endFrameX, int endFrameY, int width, int height);

	void play(const std::string key, const float& dt);
};

