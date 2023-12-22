#pragma once

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
		bool animationComplete;

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
			width(width), height(height), timer(0.0f), animationComplete(false)
		{
			// Estabish rects
			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(endFrameX * width, endFrameY * height, width, height);

			// Set start rect texture
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		// Accessors
		const bool& getAnimationComplete() const
		{
			return this->animationComplete;
		}

		// Functions
		const bool& play(const float& dt)
		{
			// Set animation complete to false
			this->animationComplete = false;

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
					this->animationComplete = true;
				}

				// Set the sprite at the current rect
				this->sprite.setTextureRect(this->currentRect);
			}

			return this->animationComplete;
		}

		const bool& play(const float& dt, float modifierPercentage)
		{
			// Set animation complete to false
			this->animationComplete = false;

			// Calculate the modifier for the percentage
			float absPercentage = std::abs(modifierPercentage);

			// Set a minimum percentage
			if (absPercentage < 0.5f)
				absPercentage = 0.5f;


			// Update timer
			this->timer += absPercentage * 100.0f * dt;

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
					this->animationComplete = true;
				}

				// Set the sprite at the current rect
				this->sprite.setTextureRect(this->currentRect);
			}

			return this->animationComplete;
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	// Constructor/Destructor
	AnimationComponent(sf::Sprite&, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	// Accessor
	const bool& isAnimationComplete(std::string key);

	// Functions
	void addAnimation(const std::string key, 
		float animationTimer,
		int startFrameX, int startFrameY, int endFrameX, int endFrameY, int width, int height);

	void checkLastAnimation(Animation* animation);
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority = false);
};

