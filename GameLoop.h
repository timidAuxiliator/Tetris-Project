#pragma once
#include "GameGrid.h"
#include "GameStats.h"
#include "Tetromino.h"
#include "DisplayModule.h"
#include <thread>


class GameLoop
{
	public:
		GameLoop();
		~GameLoop();
		void initialize(int); //Initializes all game related objects 
		bool update();


	private:
		std::thread threadUpdate;
		bool keepUpdating = true; //Used to end threadUpdate when set to false
		int FPS = 60;

		GameGrid grid;
		GameStats stats;
		Tetromino shape = Tetromino(grid);
		DisplayModule display;
		
		
		void playerMovement();
		void runDisplayUpdate();
};

