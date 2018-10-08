#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <vector>

#include "Constantes.h"

class Utils
{
	public :
		static std::vector<std::string> splitString(std::string str, char sep);
		static std::string getSongInfo(std::string fileName, bool shrt = false);
};


#endif // !UTILS_H
