#include "Score.h"

Score::Score()
{
}

void Score::computeRank()
{
	if (accuracy_ < 50)
		rank_ = "D";
	else if (accuracy_ < 70)
		rank_ = "C";
	else if (accuracy_ < 80)
		rank_ = "B";
	else if (accuracy_ < 90)
		rank_ = "A";
	else if (accuracy_ < 100)
		rank_ = "S";
	else
		rank_ = "SS";
}

void Score::drawConsole(std::string path)
{
	computeRank();

	std::cout << std::endl;
	std::cout << " -------------------------------- " << std::endl;
	std::cout << "   Results  " << std::endl;
	std::cout << "      " << Utils::getSongInfo(path, true) << std::endl;
	std::cout << " -------------------------------- " << std::endl;
	

	std::cout << "Score : " << score_ << std::endl;
	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << "Accuracy : " << accuracy_ << " %" << std::endl;
	std::cout << "Rank : " << rank_ << std::endl;

	std::cout << " -------------------------------- " << std::endl;
	std::cout << "Perfect : " << nbPerfect_ << std::endl;
	std::cout << "Good : " << nbGood_ << std::endl;
	std::cout << "Ok : " << nbOk_ << std::endl;
	std::cout << "Bad : " << nbBad_ << std::endl;
	std::cout << "Miss : " << nbMiss_ << std::endl << std::endl;

	std::cout << "Press Enter to continue ... ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Score::operator+=(int const & a)
{
	score_ += a;
	maxScore_ += 100;

	accuracy_ = score_ / (float)maxScore_ * 100.f;
}
