#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Bird : public virtual DynamicObject {
private:
	sf::Sprite sp_rendered;
	sf::Texture sf_tex;

	float mx = 0, my = 0;
public:
	Bird(const std::string& textureFile, float x, float y) {

		if (!sf_tex.loadFromFile("../assets/bird.png")) {
			std::cout << "Failed to load texture: " << "../assets/bird.png" << std::endl;
		}

		sp_rendered.setTexture(sf_tex);
		sp_rendered.setPosition(x, y);
		sp_rendered.setScale(0.2f, 0.2f);

		mx = x, my = y;

	}
	~Bird()
	{
		destructorLog.push_back("Bird");
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sp_rendered);
	}
	void moveSpriteBy(float moveX, float moveY) {
		sp_rendered.move(moveX, moveY);
	}

	sf::Sprite getSprite() const {
		return sp_rendered;
	}
	sf::Vector2f getSpriteCoordinates() const {
		return sp_rendered.getPosition();
	}

	float getXPosition() const {
		return mx;
	}
	float getYPosition() const {
		return my;
	}
};