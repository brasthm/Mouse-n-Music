#include "Utils.h"

std::vector<std::string> Utils::splitString(std::string str, char sep)
{
	std::vector<std::string> res;
	int debut = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == sep || i == str.size() - 1)
		{
			i += i == str.size() - 1 ? 1 : 0;
			std::string section = "";
			for (int j = debut; j < i; j++)
				section += str[j];
			debut = i + 1;
			res.emplace_back(section);
		}
	}

	return res;
}

std::string Utils::getSongInfo(std::string file, bool shrt)
{
	std::string res = "";
	std::ifstream fichier(MUSIC_PATH + file + "/" + file + ".mnm");

	std::string buffer;
	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back() + " - ";

	std::getline(fichier, buffer);
	res += Utils::splitString(buffer, '=').back();

	if (!shrt)
	{
		std::getline(fichier, buffer);
		std::getline(fichier, buffer);

		std::getline(fichier, buffer);
		res += " (BPM : " + Utils::splitString(buffer, '=').back() + " / Length : ";

		std::getline(fichier, buffer);
		res += Utils::splitString(buffer, '=').back() + ")";
	}
	

	fichier.close();
	return res;
}
