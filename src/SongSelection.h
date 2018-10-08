#ifndef SONG_SELECTION_H
#define SONG_SELECTION_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "Constantes.h"
#include "Utils.h"

class SongSelection
{
	private:
		std::string getSongInfo(std::string file);
	public:
		SongSelection();
		void play(std::string &choice);

};


#endif // !SONG_SELECTION_H
