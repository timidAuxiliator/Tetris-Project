#pragma once
#include "GameObject.h"

class GameGrid : public GameObject
{
	public:
		GameGrid();
		~GameGrid();
		virtual displayReturn display();

		void clearGrid(); //Completely clears the grid of any filled spaces
		void setCell(int, int, bool); //First two paramets set row and column, respectively. Last param sets cell state. 1 = filled, 0 = empty
		bool getCell(int, int); //Returns the state of a cell. First int determines row, second is column
		int clearLines();

	private:
		static const int gridHeight = 20;
		static const int gridWidth = 10;
		bool gridArr[gridHeight][gridWidth] = { }; //A boolean array representing a 10-wide by 20-tall Tetris game grid. 0 represents an empty space, 1 represents an occupied space
		void shiftGrid(int, int); //First parameter is row, second is amount to shift. Rows go from 0-19 with 0 at top. Max shift is 4 space
	
		struct backgroundElements
		{
			static const int boxSizeWidth = 25;
			static const int boxSizeHeight = 22;
			const char grid_bounding_box[boxSizeHeight][boxSizeWidth] =
			{
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<! . . . . . . . . . .!>"},
				{"<!********************!>"},
				{"  \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/  "}
			};

			static const int controlsTextLines = 6;
			static const int controlsTextLength = 15;
			const char controls_text[controlsTextLines][controlsTextLength] =
			{
				{"Q: Spin Left  "},
				{"E: Spin Right "},
				{"<-: Move Left "},
				{"->: Move Right"},
				{"Space: Drop   "},
				{"ESC: Quit     "}
			};
		};
};
