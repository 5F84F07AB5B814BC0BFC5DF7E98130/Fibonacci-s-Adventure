#include "Button.h"

Button::Button(const sf::Vector2f& size)
	: Label{ size }
{
}

sf::FloatRect Button::getGlobalBounds() const
{
	return DynamicObject::getGlobalBounds();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Label::draw(target, states);   
}