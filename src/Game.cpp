#include "Game.h"

Game::Game()
{
	// Load Background
	textBackground_.loadFromFile(IMG_PATH + "bg.png");
	background_.setTexture(textBackground_);

	// Load Cursor
	textCursor_.loadFromFile(IMG_PATH + "cursor.png");
	cursor_.setTexture(textCursor_);
	cursor_.setOrigin(32, 32);

	// Load Sections
	textSections_.resize(NB_SECTIONS);
	sections_.resize(NB_SECTIONS);

	for (int i = 0; i < NB_SECTIONS; i++)
	{
		textSections_[i].loadFromFile(IMG_PATH + "section" + std::to_string(i + 1) + ".png");
		sections_[i].setTexture(textSections_[i]);
	}

	// Load Font
	neig_.loadFromFile(FONT_PATH + "neig.otf");

	scoreText_.setFont(neig_);
	scoreText_.setOutlineThickness(5);
	scoreText_.setOutlineColor(sf::Color::Black);
	scoreText_.setFillColor(sf::Color::White);
	scoreText_.setCharacterSize(50);

	// Start Clock
	clock_.restart();
	songTime_ = sf::Time::Zero;
}

float Game::getAngle()
{
	sf::Vector2f reference(REFERENCE_X, REFERENCE_Y);
	sf::Vector2f hyp = mousePosition_ - reference;

	return atan2(hyp.y, hyp.x) * 180 / PI + 180;
}

float Game::getDistance()
{
	sf::Vector2f reference(REFERENCE_X, REFERENCE_Y);
	sf::Vector2f hyp = mousePosition_ - reference;


	return sqrt(hyp.x*hyp.x + hyp.y*hyp.y);
}

void Game::drawCursor(sf::RenderWindow & window)
{
	cursor_.setPosition(mousePosition_);
	window.draw(cursor_);
}

void Game::drawSection(sf::RenderWindow & window)
{
	if (section_ != -1)
		window.draw(sections_[section_]);
}

void Game::update(sf::RenderWindow &window)
{
	elapsedTime_ = clock_.getElapsedTime();
	songTime_ += elapsedTime_;
	clock_.restart();

	section_ = -1;
	mousePosition_ = sf::Vector2f(sf::Mouse::getPosition(window));

	if (getDistance() >= REFERENCE_MARGIN)
	{
		float angle = getAngle();

		for (int i = 0; i <= NB_SECTIONS; i++)
		{
			if (angle < i * 180 / NB_SECTIONS)
			{
				section_ = i - 1;
				break;
			}
		}
	}

	for (int i = current_; i < notes_.size(); i++)
	{
		int status = notes_[i].update(songTime_, elapsedTime_, section_);
		if (status == 1)
		{
			int s = notes_[i].getScore();
			current_++;
			score_ += s;
			if (s == 0)
				popups_.emplace_back(neig_, "Miss", sf::Color(244, 101, 101), notes_[i].getSection());
			else if(s <= 40)
				popups_.emplace_back(neig_, "Bad", sf::Color(244, 146, 101), notes_[i].getSection());
			else if (s <= 70)
				popups_.emplace_back(neig_, "Ok", sf::Color(101, 144, 226), notes_[i].getSection());
			else if (s <= 90)
				popups_.emplace_back(neig_, "Good", sf::Color(155, 244, 101), notes_[i].getSection());
			else
				popups_.emplace_back(neig_, "Perfect", sf::Color(217, 101, 244), notes_[i].getSection());
		}
	}

	for (int i = 0; i < popups_.size(); i++)
	{
		if (popups_[i].isDead())
		{
			popups_[i] = popups_.back();
			popups_.pop_back();
		}
	}
		
	scoreText_.setString(std::to_string(score_));
}

void Game::draw(sf::RenderWindow & window)
{
	window.clear();

	window.draw(background_);
	drawSection(window);

	for (int i = 0; i < notes_.size(); i++)
		notes_[i].draw(window);


	scoreText_.setPosition((WINDOW_W - scoreText_.getGlobalBounds().width) / 2, REFERENCE_Y - 100);
	window.draw(scoreText_);

	for (int i = 0; i < popups_.size(); i++)
		popups_[i].draw(window, elapsedTime_);

	drawCursor(window);

	window.display();
}

void Game::generateNotes()
{
	for (int i = 0; i < 700; i++)
		notes_.emplace_back(sf::seconds(5 + 60/168.f * i), sf::seconds(5 + 60 / 168.f * (i+0.5)), 500, rand() % NB_SECTIONS);
}


void Game::play(sf::RenderWindow & window)
{
	srand(time(NULL));
	generateNotes();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		update(window);
		draw(window);
		
		sf::sleep(sf::milliseconds(1));
	}
}

