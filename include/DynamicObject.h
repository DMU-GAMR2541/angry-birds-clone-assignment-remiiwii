#pragma once
#include <iostream>
#include "GameObject.h"

class DynamicObject : public virtual GameObject {
protected:
    sf::Sprite sp_rendered;
    sf::Texture sf_tex;

    bool b_spriteRendered = true;	// Default value is true, only assigned false if sprite fails to render.
public:
    ~DynamicObject()    // Destructor for testing purposes.
    {
        destructorLog.push_back("DynamicObject");   // Upon triggering, adds itself to the destructorLog vector.
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sp_rendered);	// Draws the sprite to the SFML window.
    }

    sf::Sprite getSprite() const {
        return sp_rendered;		// Function to return the sprite variable as an SFML sprite.		
    }

    bool checkSpriteRendered() const {
        return b_spriteRendered;	// Simply returns the boolean.
    }
};