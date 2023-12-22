#include "../stdafx.h"
#include "AnimationComponent.h"

// Constructor/Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	// Delete all animations
	for (auto& it : this->animations)
	{
		delete it.second;
	}
}

// Accessor
const bool& AnimationComponent::isAnimationComplete(const std::string key)
{
	return this->animations[key]->getAnimationComplete();
}

// Functions
void AnimationComponent::addAnimation(const std::string key, 
	float animationTimer,
	int startFrameX, int startFrameY, int endFrameX, int endFrameY, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, 
		animationTimer, 
		startFrameX, startFrameY, endFrameX, endFrameY, 
		width, height);
}

void AnimationComponent::checkLastAnimation(Animation* currentAnimation)
{
	// Check if we have switched animations
	if (this->lastAnimation != currentAnimation)
	{
		// Check if the last animation exists
		if (this->lastAnimation != nullptr)
		{
			// Reset the last animation
			this->lastAnimation->reset();
		}

		// Set the new last animation
		this->lastAnimation = currentAnimation;
	}
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	// Check if the animation is a priority over other ones
	if (priority)
	{
		priorityAnimation = this->animations[key];
	}

	// Check if running a priority animation
	if (this->priorityAnimation)
	{
		// Check for/update last animation
		if (this->priorityAnimation == this->animations[key])
		{
			checkLastAnimation(this->animations[key]);

			// Play and the animation and check if finished
			if (this->priorityAnimation->play(dt))
			{
				// Reset priority animation
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		// Check for/update last animation
		checkLastAnimation(this->animations[key]);

		// Play the animation
		this->animations[key]->play(dt);
	}

	// Return whether the animation is complete
	return this->animations[key]->getAnimationComplete();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority)
{
	// Check if the animation is a priority over other ones
	if (priority)
	{
		this->priorityAnimation = this->animations[key];
	}

	// Check if running a priority animation
	if (this->priorityAnimation)
	{
		// Check for/update last animation
		if (this->priorityAnimation == this->animations[key])
		{
			checkLastAnimation(this->animations[key]);

			// Play and the animation and check if finished
			if (this->priorityAnimation->play(dt, (modifier / modifierMax)))
			{
				// Reset priority animation
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		// Check for/update last animation
		checkLastAnimation(this->animations[key]);

		// Play the animation
		this->animations[key]->play(dt, (modifier / modifierMax));
	}

	// Return whether the animation is complete
	return this->animations[key]->getAnimationComplete();
}
