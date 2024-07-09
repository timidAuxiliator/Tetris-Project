#pragma once
#include "GameObject.h"

class GameStats : public GameObject
{
	public:
		GameStats();
		~GameStats();
		displayReturn display();

		void incrementScore(int); //Increments the value of totalScore by a given int value
		int getTotalScore(); //Returns the current value of totalScore

		void incrementLineClear(int); //Increments the value of linesCleared by 1
		int getLinesCleared(); //Returns the current value of linesCleared

		void setLevel(int);
		int getLevel();
		void resetStats(); //Resets the value of totalScore and linesCleared to 0


	private:
		struct backgroundElements
		{
			static const int scoreTextLines = 9;
			static const int scoreTextLength = 8;
			const char score_text[scoreTextLines][scoreTextLength] =
			{
				{"Level: "},
				{"       "},
				{"       "},
				{"Score: "},
				{"       "},
				{"       "},
				{"Line   "},
				{"Clears:"},
				{"       "}
			};
		};
		

		int totalScore = 0;
		int linesCleared = 0;
		int level = 0;
};
