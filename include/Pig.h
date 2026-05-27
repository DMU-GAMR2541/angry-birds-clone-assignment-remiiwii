#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicObject.h"

class Pig : public virtual DynamicObject {
private:
	sf::Sprite sp_rendered;
	sf::Texture sf_tex;

	float i = 0, mx = 0, my = 0, movement = 0;
	bool b_spriteRendered = true;

public:
	Pig(const std::string& textureFile, float x, float y) {

		if (!sf_tex.loadFromFile("../assets/pig.png")) {
			std::cout << "Failed to load texture: " << "../assets/pig.png" << std::endl;
			b_spriteRendered = false;
		}

		sp_rendered.setTexture(sf_tex);
		sp_rendered.setPosition(x, y);
		sp_rendered.setScale(0.2f, 0.2f);

		mx = x, my = y;
		
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sp_rendered);
	}

	float getXPosition() const {
		return mx;
	}
	float getYPosition() const {
		return my;
	}

	bool checkSpriteRendered() const {
		return b_spriteRendered;	}		
};