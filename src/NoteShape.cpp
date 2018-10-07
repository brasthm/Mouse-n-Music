#include "NoteShape.h"

void NoteShape::update()
{
	triangles_.clear(); 

	float delta = 2.*(angle2_ - angle1_) / (float)NOTE_NB_POINTS;

	for (int i = 0; i < NOTE_NB_POINTS / 2; i++)
	{

		// Triangle 1
		triangles_.emplace_back(3);

		triangles_.back().setPoint(0, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f(distance_*cos(angle1_ + delta*i), distance_*sin(angle1_ + delta*i)));
		triangles_.back().setPoint(1, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f(distance_*cos(angle1_ + delta*(i + 1)), distance_*sin(angle1_ + delta*(i + 1))));
		triangles_.back().setPoint(2, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*i), (thickness_ + distance_)*sin(angle1_ + delta*i)));
		triangles_.back().setFillColor(sf::Color(101, 137, 244));

		// Triangle 2
		triangles_.emplace_back(3);

		triangles_.back().setPoint(0, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f(distance_*cos(angle1_ + delta*(i + 1)), distance_*sin(angle1_ + delta*(i + 1))));
		triangles_.back().setPoint(1, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*(i)), (thickness_ + distance_)*sin(angle1_ + delta*(i))));
		triangles_.back().setPoint(2, sf::Vector2f(REFERENCE_X, REFERENCE_Y) + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*(i + 1)), (thickness_ + distance_)*sin(angle1_ + delta*(i + 1))));
		triangles_.back().setFillColor(sf::Color(101, 137, 244));

	}
}

NoteShape::NoteShape()
{
}

NoteShape::NoteShape(const float distance, const float thickness, const size_t section)
{
	init(distance, thickness, section);
}

void NoteShape::init(const float distance, const float thickness, const size_t section)
{
	distance_ = distance;;
	thickness_ = thickness; 
	section_ = section;
	angle1_ = PI + section_ * PI / NB_SECTIONS;
	angle2_ = angle1_ + PI / NB_SECTIONS;

	update();
}

void NoteShape::setDistance(const float distance)
{
	distance_ = distance;
	update();
}

void NoteShape::addDistance(const float delta)
{
	distance_ += delta;
	update();
}

void NoteShape::setThickness(const float thick)
{
	thickness_ = thick;
}

void NoteShape::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < triangles_.size(); i++)
		window.draw(triangles_[i]);
}
