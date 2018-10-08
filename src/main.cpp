#include "Game.h"
#include "SongSelection.h"
#include <iostream>

int main()
{
	FMOD::System *system;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	void*extradriverdata = 0;

	SongSelection songSelection;
	Game game;

	std::string choice;
	songSelection.play(choice);

	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Mouse n Music", sf::Style::Default, settings);
	
	window.setMouseCursorVisible(false);


	game.play(window, system, choice);

	system->close();
	system->release();

	return 0;
}