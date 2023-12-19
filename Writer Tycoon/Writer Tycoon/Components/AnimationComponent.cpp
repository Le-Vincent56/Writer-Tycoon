#include "AnimationComponent.h"

// Constructor/Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet)
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

void AnimationComponent::play(const std::string key, const float& dt)
{
	this->animations[key]->play(dt);
}
