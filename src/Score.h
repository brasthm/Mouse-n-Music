#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <iostream>
#include <limits>

#include "Utils.h"

class Score
{
	private:
		int score_ = 0;
		int maxScore_ = 0;
		float accuracy_;
		std::string rank_;
		int nbMiss_ = 0;
		int nbBad_ = 0;
		int nbOk_ = 0;
		int nbGood_ = 0;
		int nbPerfect_ = 0;

	public:
		Score();
		inline void setMaxScore(const int maxi) { maxScore_ = maxi; }
		inline void incMiss() { nbMiss_++; }
		inline void incBad() { nbBad_++; }
		inline void incOk() { nbOk_++; }
		inline void incGood() { nbGood_++; }
		inline void incPerfect() { nbPerfect_++; }

		inline int getScore() const { return score_; }

		void computeRank();
		void drawConsole(std::string path);

		void operator+=(int const& a);

};



#endif // !SCORE_H
