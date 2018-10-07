#ifndef POP_UP_H
#define POP_UP_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"

class PopUp
{
	private :
		float speed_;
		float opacity_ = 255;
		sf::Text text_;
		sf::Color color_;
		bool dead_ = false;
	public:
		PopUp(sf::Font &font, const char* str, sf::Color c, int section);
		void draw(sf::RenderWindow &window, sf::Time elapsedTime);
		inline bool isDead() const { return dead_; }

};


#endif // !POP_UP_H
