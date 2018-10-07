#include "Note.h"
#include <iostream>

Note::Note(sf::Time start, sf::Time end, float speed, int section) : start_(start), end_(end), speed_(speed), section_(section)
{
	triggered_ = false;
	dead_ = false;
	active_ = false;
	distance_ = NOTE_START_DISTANCE;
	thickness_ = speed_ * (end_ - start_).asSeconds();
	hovered_ = sf::Time::Zero;
}


int Note::update(sf::Time songTime, sf::Time elapsedTime, int section)
{
	int status = 0;

	if (triggered_ && !dead_)
	{
		distance_ -= speed_ * elapsedTime.asSeconds();
		shape_.setDistance(distance_);

		if(active_ && section == section_)
			hovered_ += elapsedTime;

		if (distance_ < REFERENCE_MARGIN)
		{
			active_ = true;
			distance_ = REFERENCE_MARGIN;
			thickness_ -= speed_ * elapsedTime.asSeconds();
			shape_.setThickness(thickness_);
			shape_.setDistance(REFERENCE_MARGIN);
		}
		if (thickness_ < 0)
		{
			status = 1;
			dead_ = true;
			active_ = false;
		}
			
	}
	else if(!dead_ && songTime > start_ - sf::seconds((NOTE_START_DISTANCE - REFERENCE_MARGIN) / speed_))
	{
		shape_.init(distance_, thickness_, section_);
		triggered_ = true;
	}

	return status;
}

void Note::draw(sf::RenderWindow & window)
{
	if (triggered_ && !dead_)
		shape_.draw(window);
}

int Note::getScore()
{
	return 10*(int)(10.f * (hovered_ / (end_ - start_)) + 0.5);
}
