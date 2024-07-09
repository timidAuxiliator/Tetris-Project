#include "GameStats.h"
#include <string>

GameStats::GameStats()
{

}

GameStats::~GameStats()
{

}

GameStats::displayReturn GameStats::display()
{
	backgroundElements backgroundDrawData;
	DisplayModule::displayInfo scoreText;
	displayReturn drawInfoReturn;
	std::vector<char> temp;
	std::string tempStr = " ";

	//Creaters obj that stores text for displaying scores
	scoreText.screenPos[0] = 0;
	scoreText.screenPos[1] = 1;
	scoreText.dimensions[0] = backgroundDrawData.scoreTextLines;
	scoreText.dimensions[1] = backgroundDrawData.scoreTextLength - 1;
	for (int i = 0; i < backgroundDrawData.scoreTextLines; i++)
	{
		for (int n = 0; n < backgroundDrawData.scoreTextLength - 1; n++)
		{
			temp.push_back(backgroundDrawData.score_text[i][n]);
		}
		scoreText.drawData.push_back(temp);
		temp.clear();
	}

	//Adds in current level value into scoreText
	tempStr = std::to_string(level);
	for (int i = 0; i < 8; i++)
	{
		if (i <= tempStr.size())
		{
			temp.push_back(tempStr[i]);
		}
		else
		{
			temp.push_back(' ');
		}

	}
	scoreText.drawData[1].swap(temp);
	temp.clear();

	//Adds in current score value into scoreText
	tempStr = std::to_string(totalScore);
	for (int i = 0; i < 8; i++)
	{
		if (i <= tempStr.size())
		{
			temp.push_back(tempStr[i]);
		}
		else
		{
			temp.push_back(' ');
		}
		
	}
	scoreText.drawData[4].swap(temp);
	temp.clear();

	//Adds in current line clears into scoreText
	tempStr = std::to_string(linesCleared);
	for (int i = 0; i < 8; i++)
	{
		if (i <= tempStr.size())
		{
			temp.push_back(tempStr[i]);
		}
		else
		{
			temp.push_back(' ');
		}
	}
	scoreText.drawData[8].swap(temp);


	drawInfoReturn.objects.push_back(scoreText);
	return drawInfoReturn;
}

void GameStats::incrementScore(int scoreAdd)
{
	totalScore += scoreAdd;
}

int GameStats::getTotalScore()
{
	return totalScore;
}

void GameStats::incrementLineClear(int lines)
{
	linesCleared += lines;
}

int GameStats::getLinesCleared()
{
	return linesCleared;
}

void GameStats::setLevel(int newLevel)
{
	level = newLevel;
}

int GameStats::getLevel()
{
	return level;
}

void GameStats::resetStats()
{
	totalScore = 0;
	linesCleared = 0;
}