#ifndef SHAPE_NOTE_H
#define SHAPE_NOTE_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"

class NoteShape
{
	private:
		size_t section_;
		float thickness_;
		float distance_;

		float angle1_, angle2_;

		std::vector<sf::ConvexShape> triangles_;

		void update();

	public :
		NoteShape();
		NoteShape(const float distance, const float thickness, const size_t section);
		void init(const float distance, const float thickness, const size_t section);
		void setDistance(const float distance);
		void addDistance(const float delta);
		void setThickness(const float thick);
		void draw(sf::RenderWindow &window);
		
};


#endif // !SHAPE_NOTE_H
