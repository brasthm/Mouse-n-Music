#include "PopUp.h"

PopUp::PopUp(sf::Font &font, const char* str, sf::Color c, int section)
{
	speed_ = 255;

	text_.setFont(font);
	text_.setOutlineThickness(5);
	text_.setOutlineColor(sf::Color::Black);
	color_ = c;
	text_.setFillColor(color_);
	text_.setCharacterSize(50);
	text_.setString(str);

	float x = REFERENCE_X + POP_UP_DISTANCE * cos(PI + (section + 0.5f) * PI / NB_SECTIONS);
	float y = REFERENCE_Y + POP_UP_DISTANCE * sin(PI + (section + 0.5f) * PI / NB_SECTIONS);

	text_.setPosition(x - text_.getGlobalBounds().width / 2, y - text_.getGlobalBounds().height / 2);
}

void PopUp::draw(sf::RenderWindow & window, sf::Time elapsedTime)
{
	opacity_ -= speed_ * elapsedTime.asSeconds();
	color_.a = opacity_;
	text_.setOutlineColor({0, 0, 0, (sf::Uint8)opacity_});
	text_.setFillColor(color_);

	if (opacity_ < 0)
		dead_ = true;

	window.draw(text_);
}
