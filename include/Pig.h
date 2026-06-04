#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicObject.h"

class Pig : public virtual DynamicObject {
private:

public:
	Pig(const std::string& textureFile, float x, float y) {		// Constructor.

		if (!sf_tex.loadFromFile("../assets/pig.png")) {	// Only triggers if "pig.png" fails to load from assets.
			std::cout << "Failed to load texture: " << "../assets/pig.png" << std::endl;	// Prints error message to console.
			b_spriteRendered = false;	// Changes defined boolean to false, used for testing purposes.
		}

		sp_rendered.setTexture(sf_tex);		// Assigns texture file to sprite for rendering.
		sp_rendered.setPosition(x, y);		// Sets position to the inputted X and Y float values.
		sp_rendered.setScale(0.2f, 0.2f);	// Sets scale to appropiate value. This could be changed into a modifiable value like the x and y co-ordinates.
	}

	sf::Vector2f getSpriteCoordinates() {
		return sp_rendered.getPosition();	// Gets the SFML co-ordinates of the sprite.
	}
};