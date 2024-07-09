#include "GameGrid.h"

//Helper Functions

void GameGrid::shiftGrid(int row, int distance)
{
	bool tempArr[10] = { };
	
	for (int shiftLength = 0; shiftLength < distance; shiftLength++)
	{
		for (int i = row; i > 0; i--)
		{
			for (int n = 0; n < 10; n++)
			{
				gridArr[i][n] = gridArr[i - 1][n];
			}
		}
	}
}


//Public functions

GameGrid::GameGrid()
{
	for (int i = 0; i < 20; i++)
	{
		for (int n = 0; n < 10; n++)
		{
			gridArr[i][n] = 0;
		}
	}
}

GameGrid::~GameGrid()
{

}

GameGrid::displayReturn GameGrid::display()
{
	backgroundElements objDrawData;
	DisplayModule::displayInfo displayObj;
	displayReturn drawInfoReturn;
	std::vector<char> temp;

	//Draw data for the grid box
	displayObj.screenPos[0] = 16;
	displayObj.screenPos[1] = 1;

	displayObj.dimensions[0] = objDrawData.boxSizeHeight;
	displayObj.dimensions[1] = objDrawData.boxSizeWidth;
	for (int row = 0; row < objDrawData.boxSizeHeight; row++)
	{
		for(int col = 0; col < objDrawData.boxSizeWidth; col++)
		{
			temp.push_back(objDrawData.grid_bounding_box[row][col]);
		}
		displayObj.drawData.push_back(temp);
		temp.clear();
	}
	drawInfoReturn.objects.push_back(displayObj);
	displayObj.drawData.clear();


	//Draw data for the rules text
	displayObj.screenPos[0] = 42;
	displayObj.screenPos[1] = 1;

	displayObj.dimensions[0] = objDrawData.controlsTextLines;
	displayObj.dimensions[1] = objDrawData.controlsTextLength;
	for (int row = 0; row < objDrawData.controlsTextLines; row++)
	{
		for (int col = 0; col < objDrawData.controlsTextLength; col++)
		{
			temp.push_back(objDrawData.controls_text[row][col]);
		}
		displayObj.drawData.push_back(temp);
		temp.clear();
	}
	drawInfoReturn.objects.push_back(displayObj);
	displayObj.drawData.clear();


	//Draw data for game grid
	displayObj.screenPos[0] = 18;
	displayObj.screenPos[1] = 1;

	displayObj.dimensions[0] = gridHeight;
	displayObj.dimensions[1] = gridWidth * 2;
	for (int row = 0; row < displayObj.dimensions[0]; row++)
	{
		for (int col = 0; col < displayObj.dimensions[1]; col++)
		{
			if (gridArr[row][col] == 1)
			{
				temp.push_back('[');
				temp.push_back(']');
			}
			else
			{
				temp.push_back(' ');
				temp.push_back('.');
			}
		}
		displayObj.drawData.push_back(temp);
		temp.clear();
	}
	drawInfoReturn.objects.push_back(displayObj);


	return drawInfoReturn;
}

void GameGrid::clearGrid()
{
	for (int i = 0; i < 20; i++)
	{
		for (int n = 0; n < 10; n++)
		{
			gridArr[i][n] = 0;
		}
	}
}

void GameGrid::setCell(int row, int col, bool state)
{
	gridArr[row][col] = state;
}

bool GameGrid::getCell(int row, int col)
{
	return gridArr[row][col];
}

int GameGrid::clearLines()
{
	int currentRow = 19;
	int startingRow = 19;
	int linesCleared = 0;
	bool lineCleared = true;
	bool lineCheckEnd = false; //true if max number of lines reached or no more full lines found

	while ((!lineCheckEnd == currentRow >= 0))
	{
		lineCleared = true;
		switch (linesCleared)
		{
			case 0:
				startingRow = currentRow;
				break;
			case 4:
				lineCheckEnd = true;
				continue;
			default:
				break;
		}
		
		for (int col = 0; col < 10; col++)
		{
			if (!gridArr[currentRow][col])
			{
				if (linesCleared > 0)
				{
					lineCheckEnd = true;
				}
				lineCleared = false;
				currentRow--;
				break;
			}
		}
		
		if (lineCleared)
		{
			linesCleared++;
			currentRow--;
		}
	}

	if (linesCleared > 0)
	{
		shiftGrid(startingRow, linesCleared);
	}

	return linesCleared;
}