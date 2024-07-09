#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include <queue>

class DisplayModule
{
	public:
		//Specifies color of console text
		
		struct displayInfo
		{
			enum color { blue = 9, green, cyan, red, pink, yellow, white };
			//Pointer to 2D char array that holds image data
			std::vector<std::vector<char>> drawData;
			int screenPos[2] = { 0, 0 }; //X, Y
			int dimensions[2] = { 0, 0 }; //First is height, second is width
			color objColor = white;
		};

		DisplayModule();
		~DisplayModule();

		void initialize(); //Takes a GameGrid and GameStats object to display then primes the first frame in nextFrame array
		void updateFrame(); //Draws the next frame on the screen
		void clearFrame();
		void insertData(displayInfo);


	private:
		static const int grid_Size_X = 56; //Width of the frame in characters
		static const int grid_Size_Y = 28; //Height of the frame in characters
		char currentFrame[grid_Size_Y][grid_Size_X] = { };
		char nextFrame[grid_Size_Y][grid_Size_X] = { };
		std::queue<displayInfo> drawList;

		const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		void cursorPos(int, int);

		void clearBuffer();
};

