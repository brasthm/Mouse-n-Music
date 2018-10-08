#include "SongSelection.h"

std::string SongSelection::getSongInfo(std::string file)
{
	std::string res = "";
	std::ifstream fichier(MUSIC_PATH + file + "/" + file + ".mnm");

	std::string buffer;
	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back() + " - ";

	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back() + " (BPM : ";

	std::getline(fichier, buffer);

	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back() + " / Length : ";

	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back() + ")";

	fichier.close();
	return res;
}

SongSelection::SongSelection()
{

}

void SongSelection::play(std::string & choice)
{
	int choix = -1;
	std::vector<std::string> path;

	std::cout << "    ---  Mouse n Music  ---" << std::endl << std::endl;

	while (choix == -1)
	{
		std::cout << "Select a song : " << std::endl;
		int nbSong = 0;
		for (auto & p : std::filesystem::directory_iterator(MUSIC_PATH))
		{
			path.emplace_back(Utils::splitString(p.path().string(), '/').back());
			std::cout << "  " << nbSong + 1 << " - " << getSongInfo(path.back()) << std::endl;
			nbSong++;
		}
			
		std::cout << "Your choice : ";
		std::cin >> choix;

		if (choix <= 0 || choix > nbSong)
			choix = -1;
	}

	choice = path[choix - 1];
}
