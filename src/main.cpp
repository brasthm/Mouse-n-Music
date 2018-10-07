#include "Game.h"

int main()
{
	FMOD::System *system;
	FMOD::Sound *sound;
	FMOD::Channel *channel = 0;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	void*extradriverdata = 0;

	Game game;


	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Mouse n Music", sf::Style::Default, settings);
	std::string path = MUSIC_PATH + "Yorushika.ogg";
	system->createStream(path.c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
	system->playSound(sound, 0, false, &channel);

	window.setMouseCursorVisible(false);

	game.play(window);


	sound->release();
	system->close();
	system->release();

	return 0;
}