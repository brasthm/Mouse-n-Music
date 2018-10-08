#ifndef NOTE_H
#define NOTE_H

#include "NoteShape.h"

class Note
{
	private:
		NoteShape shape_;
		float speed_;
		sf::Time start_, end_, hovered_;
		int section_;
		bool triggered_, dead_, active_;
		float distance_;
		float thickness_;

	public:
		Note(sf::Time start, sf::Time end, float speed, int section);
		int update(sf::Time songTime, sf::Time elapsed, int section);
		void draw(sf::RenderWindow & window);

		inline bool isDead() const { return dead_; }
		inline bool isActive() const { return active_; }
		inline int getSection() const { return section_; }
		inline float getSpeed() const { return speed_; }
		inline sf::Time getStartTime() const { return start_; }

		int getScore();

};


#endif // !NOTE_H
