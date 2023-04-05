#include "Label.h"

Label::Label(const sf::Vector2f& size, const std::string& text)
    : DynamicObject{ size }
    , relativeCharacterSize{ 50.f }
{
    setTextSize(relativeCharacterSize);
    setTextString(text);
}

void Label::setSize(const sf::Vector2f& size)
{
    DynamicObject::setSize(size);
    setTextSize(relativeCharacterSize);
}

void Label::setTextString(const sf::String& string)
{
    text.setString(string);
    centerText();
}

void Label::setTextFont(const std::string& fontPath)
{
    font.loadFromFile(fontPath);
    text.setFont(font);
    centerText();
}

void Label::setTextSize(float percentage)
{
    text.setCharacterSize(static_cast<unsigned int>(getLocalBounds().height * (percentage / 100.f)));
    relativeCharacterSize = percentage;
    centerText();
}

void Label::setTextFillColor(const sf::Color& color)
{
    text.setFillColor(color);
}

void Label::setTextOutlineColor(const sf::Color& color)
{
    text.setOutlineColor(color);
}

void Label::setTextOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);
}

void Label::setTextStyle(sf::Text::Style style)
{
    text.setStyle(style);
    centerText();
}

const sf::String& Label::getTextString() const
{
    return text.getString();
}

const sf::Font* Label::getTextFont() const
{
    return &font;
}

float Label::getTextSize() const
{
    return relativeCharacterSize;
}

const sf::Color& Label::getTextFillColor() const
{
    return text.getFillColor();
}

const sf::Color& Label::getTextOutlineColor() const
{
    return text.getOutlineColor();
}

float Label::getTextOutlineThickness() const
{
    return text.getOutlineThickness();
}

sf::Text::Style Label::getTextStyle() const
{
    return (sf::Text::Style)text.getStyle();
}

sf::FloatRect Label::getTextLocalBounds() const
{
    return text.getLocalBounds();
}

sf::FloatRect Label::getTextGlobalBounds() const
{
    return getTransform().transformRect(getTextLocalBounds());
}

void Label::centerText()
{
    text.setOrigin(text.getLocalBounds().left, text.getLocalBounds().top);

    float offsetX{ (getLocalBounds().width - text.getLocalBounds().width) / 2.f };
    float offsetY{ (getLocalBounds().height - text.getLocalBounds().height) / 2.f };
    text.setPosition(getLocalBounds().left + offsetX, getLocalBounds().top + offsetY);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform combinedTransform{ states.transform * sf::Transformable::getTransform() };
    applyChanges(combinedTransform);

    Shape::draw(target, combinedTransform);
    if (text.getFont()) target.draw(text, combinedTransform);
}