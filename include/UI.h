#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"

class UI : public virtual StaticObject, public virtual GameObject {
private:
	sf::Sprite sp_rendered;
	sf::Texture sf_tex;
public:

};