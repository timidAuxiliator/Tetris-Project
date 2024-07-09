#pragma once
#include "GameGrid.h"

class Tetromino : public GameGrid
{
	public:
		Tetromino(GameGrid&); //Selects two shapes to fill shapeArea and shapeNext on initialization
		~Tetromino();
		displayReturn display();

		//Shape control Functions
		void nextShape(); //Moves shapeNext to shapeArea, then puts new tetromino in shapeNext
		void clearShape(); //Only clears shapeArea
		void getShape(bool [][4]); //Returns shapeArea as boolean array
		
		
		//Movement Functions
		void rotateShape(bool); //Rotates a shape. 0 counter-clockwise, 1 = clockwise
		bool moveStrafe(int); //-1 = left, 1 = right. Returns false is movement failed
		bool moveDown(); //Returns false if movement causes collision
		int hardDrop();
		void lockIn();
		void getCoords(int[]);


	private:
		const bool shapeArr[7][4][4] = { {{ 0, 0, 0, 0 },
										{ 0, 1, 1, 0 },
										{ 0, 1, 1, 0 },
										{ 0, 0, 0, 0 }},
			//Square [0][n][n]

			{{ 0, 0, 0, 0 },
			 { 1, 1, 1, 1 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 }},
			//Line [1][n][n]

		   {{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }},
			//T-Piece [2][n][n]

		   {{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 }},
			//L-Piece [3][n][n]

		   {{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }},
			//Reverese L-Piece [4][n][n]

		   {{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }},
			//S-Piece [5][n][n]

		   {{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }} };
		//Z-piece [6][n][n]


		bool shapeArea[4][4] = { }; //Stores current tetromino
		bool shapeNext[4][4] = { }; //Stores next tetromino. Used for preview
		bool currSize = 0; //0 = 3x3 tetromino rotation, 1 = 4x4 tetromino rotation
		bool nextSize = 0; //Ditto as above

		int gridCoord[2] = { 0, 3 }; //Location in GameGrid. Used for field placement
		int displayCoord[2] = { 0, 24 }; //Location in the console. Used for frame drawing

		GameGrid* parentGrid;

		bool checkCollision(int);
};
