#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Bird : public virtual DynamicObject {
private:

public:
	Bird(const std::string& textureFile, float x, float y) {

		if (!sf_tex.loadFromFile("../assets/bird.png")) {	// Only triggers if "bird.png" fails to load from assets.
			std::cout << "Failed to load texture: " << "../assets/bird.png" << std::endl;	// Prints error message to console.
			b_spriteRendered = false;	// Changes defined boolean to false, used for testing purposes.
		}

		sp_rendered.setTexture(sf_tex);		// Assigns texture file to sprite for rendering.
		sp_rendered.setPosition(x, y);		// Sets position to the inputted X and Y float values.
		sp_rendered.setScale(0.2f, 0.2f);	// Sets scale to appropiate value. This could be changed into a modifiable value like the x and y co-ordinates.
	}

	~Bird()
	{
		destructorLog.push_back("Bird");	// Appends itself to destructorLog.
	}

	sf::Vector2f getSpriteCoordinates() {
		return sp_rendered.getPosition();	// Gets the SFML co-ordinates of the sprite.
	}

	void moveSpriteBy(float moveX, float moveY) {
		sp_rendered.move(moveX, moveY);
	}
};