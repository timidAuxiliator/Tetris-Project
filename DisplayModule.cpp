#include "DisplayModule.h"
#include <iostream>

//Helper Functions
void DisplayModule::cursorPos(int x, int y)
{
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void DisplayModule::clearBuffer()
{
	for (int row = 0; row < grid_Size_Y; row++)
	{
		for (int col = 0; col < grid_Size_X; col++)
		{
			nextFrame[row][col] = ' ';
		}
	}
}


//Public Functions
DisplayModule::DisplayModule()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	COORD screenSize{ (SHORT)56, (SHORT)26 };

	GetConsoleCursorInfo(hOut, &cursorInfo);
	GetConsoleScreenBufferInfo(hOut, &consoleInfo);

	
	cursorInfo.bVisible = false; 
	SetConsoleCursorInfo(hOut, &cursorInfo);

	//SetConsoleWindowInfo(hOut, );
	SetConsoleScreenBufferSize(hOut, screenSize);

}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::initialize()
{
	


}

void DisplayModule::updateFrame()
{
	//Puts elements into the frame buffer
	displayInfo* temp = nullptr;
	while(!drawList.empty())
	{
		temp = &drawList.front();
		int curPos[2] = { temp->screenPos[0], temp->screenPos[1] };

		for (int row = 0; row < temp->dimensions[0]; row++)
		{
			for (int col = 0; col < temp->dimensions[1]; col++)
			{
				if (temp->drawData[row][col] != ' ')
				{
					nextFrame[(curPos[1] + row)][(curPos[0] + col)] = temp->drawData[row][col];
				}
				
			}
		}
		drawList.pop();
	}
	

	//Compares the current frame to the next frame and only draws any new changes
	for (int i = 0; i < grid_Size_Y; i++)
	{
		for (int n = 0; n < grid_Size_X; n++)
		{
			if (currentFrame[i][n] != nextFrame[i][n])
			{
				currentFrame[i][n] = nextFrame[i][n];
				cursorPos(n, i);
				std::cout << nextFrame[i][n];
			}
		}
	}

	clearBuffer();
}

void DisplayModule::clearFrame()
{
	for (int row = 0; row < grid_Size_Y; row++)
	{
		for (int col = 0; col < grid_Size_X; col++)
		{
			cursorPos(col, row);
			std::cout << ' ';
		}
	}

	cursorPos(0, 0);
}

void DisplayModule::insertData(displayInfo obj)
{
	drawList.push(obj);
}