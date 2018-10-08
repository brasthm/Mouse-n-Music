#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <fmod.hpp>

#include "Constantes.h"
#include "Note.h"
#include "PopUp.h"


class Game
{
	private:
		sf::Font neig_;
		sf::Text scoreText_;

		std::vector<sf::Texture> textSections_;
		sf::Texture textBackground_;
		sf::Texture textCursor_;

		sf::Sprite background_;
		std::vector<sf::Sprite> sections_;
		sf::Sprite cursor_;
		
		std::vector<PopUp> popups_;

		FMOD::Sound *song_;
		FMOD::Channel *channel_ = 0;

		bool isPlaying_ = false;

		int section_ = -1;
		int score_ = 0;
		sf::Vector2f mousePosition_;

		sf::Clock clock_;
		sf::Time songTime_, elapsedTime_;

		int current_ = 0;

		std::vector<Note> notes_;

		float getAngle();
		float getDistance();
		void drawCursor(sf::RenderWindow &window);
		void drawSection(sf::RenderWindow & window);
		void update(sf::RenderWindow &window, FMOD::System *soundSystem);
		void draw(sf::RenderWindow &window);
		void generateNotes();


	public:
		Game();
		void play(sf::RenderWindow &window, FMOD::System *soundSystem);
		~Game();
		
};

#endif // !GAME_H
