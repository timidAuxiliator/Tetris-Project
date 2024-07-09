#include "Tetromino.h"
#include <random>

////Helper Functions

bool Tetromino::checkCollision(int collisionType)
{
	int coordOffset[2] = { 0, 0 }; //gridCoord offset by position in shapeArea
	int gridSize = (currSize) ? 4 : 3;

	for (int i = 0; i < gridSize; i++)
	{
		coordOffset[0] = gridCoord[0] + i;
		for (int n = 0; n < gridSize; n++)
		{
			coordOffset[1] = gridCoord[1] + n;
			if (shapeArea[i][n])
			{
				switch (collisionType)
				{
					//Checks for left collisions
					case -1:
						if (coordOffset[1] - 1 <= -1)
						{
							return true;
						}
						else if ((parentGrid->getCell(coordOffset[0], coordOffset[1] - 1)) || (parentGrid->getCell(coordOffset[0], coordOffset[1] + 1)))
						{
							return true;
						}
						break;

					//Checks for downward collision
					case 0:
						if ((coordOffset[0] + 1 >= 20) || (parentGrid->getCell((coordOffset[0] + 1), coordOffset[1])))
						{
							return true;
						}
						break;


						//Checks for right collisions
					case 1:
						if ((coordOffset[1] + 1) > 9)
						{
							return true;
						}
						else if ((parentGrid->getCell(coordOffset[0], coordOffset[1] - 1)) || (parentGrid->getCell(coordOffset[0], coordOffset[1] + 1)))
						{
							return true;
						}
						break;

					default:
						break;
				}
			}
		}
	}
	return false;
}




Tetromino::Tetromino(GameGrid& grid)
{
	int randShape = 0; //Stores a randomly chosen index value of a tetromino

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 6);

	randShape = dist(mt);
	currSize = (randShape <= 1) ? 1 : 0;
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shapeArea[i][n] = shapeArr[randShape][i][n];
		}
	}


	randShape = dist(mt);
	nextSize = (randShape <= 1) ? 1 : 0;
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shapeNext[i][n] = shapeArr[randShape][i][n];
		}
	}

	parentGrid = &grid;
}

Tetromino::~Tetromino()
{
	
}

Tetromino::displayReturn Tetromino::display()
{
	DisplayModule::displayInfo shapeData;
	displayReturn drawInfoReturn;
	std::vector<char> temp;

	shapeData.screenPos[0] = displayCoord[1];
	shapeData.screenPos[1] = displayCoord[0];

	shapeData.dimensions[0] = 4;
	shapeData.dimensions[1] = 8;
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n ++)
		{
			if (shapeArea[i][n] == 1)
			{
				temp.push_back('[');
				temp.push_back(']');
			}
			else
			{
				temp.push_back(' ');
				temp.push_back(' ');
			}
		}
		shapeData.drawData.push_back(temp);
		temp.clear();
	}
	drawInfoReturn.objects.push_back(shapeData);

	return drawInfoReturn;
}


////Shape Control Functions
void Tetromino::nextShape()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 6);
	int randShape = 0;

	currSize = nextSize;
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shapeArea[i][n] = shapeNext[i][n];
		}
	}

	randShape = dist(mt);
	nextSize = (randShape <= 1) ? 1 : 0;
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shapeNext[i][n] = shapeArr[randShape][i][n];
		}
	}

	gridCoord[0] = 0;
	gridCoord[1] = 3;
	displayCoord[0] = 0;
	displayCoord[1] = 24;
}

void Tetromino::clearShape()
{
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shapeArea[i][n] = 0;
		}
	}
}

void Tetromino::getShape(bool shape[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			shape[i][n] = shapeArea[i][n];
		}
	}
}




////Movement Functions
void Tetromino::rotateShape(bool dir)
{
	bool tempArr[4][4] = { };
	int coordOffset[2] = { };
	int gridSize = 0;

	//If rotateSize is 1 rotate tetromino on 4x4 grid, otherwise rotate on 3x3 grid
	gridSize = (currSize) ? 3 : 2;
	for (int i = 0; i <= gridSize; i++)
	{
		for (int n = 0; n <= gridSize; n++)
		{
			switch (dir)
			{
				case 0:
					tempArr[gridSize - n][i] = shapeArea[i][n];
					break;
				case 1:
					tempArr[n][gridSize - i] = shapeArea[i][n];
			}
		}
	}

	//Rotational collision handling
	for (int i = 0; i <= gridSize; i++)
	{
		coordOffset[0] = gridCoord[0] + i;
		for (int n = 0; n <= gridSize; n++)
		{
			coordOffset[1] = gridCoord[1] + n;
			if (tempArr[i][n])
			{
				if (parentGrid->getCell(coordOffset[0], coordOffset[1]))
				{
					return;
				}
				else if ((coordOffset[1] <= -1) || (coordOffset[1] >= 10) || (coordOffset[0] >= 18))
				{
					return;
				}
			}
		}
	}


	for (int i = 0; i <= gridSize; i++)
	{
		for (int n = 0; n <= gridSize; n++)
		{
			shapeArea[i][n] = tempArr[i][n];
		}
	}
}

bool Tetromino::moveStrafe(int moveDirection)
{
	switch (moveDirection)
	{
		case -1:
			if (checkCollision(-1))
			{
				return false;
			}
			gridCoord[1]--;
			displayCoord[1] -= 2;
			break;

		case 1:
			if (checkCollision(1))
			{
				return false;
			}
			gridCoord[1]++;
			displayCoord[1] += 2;
		default:
			break;
	}

	return true;
}

bool Tetromino::moveDown()
{
	if (checkCollision(0))
	{
		lockIn();
		return false;
	}

	gridCoord[0]++;
	displayCoord[0]++;
	return true;
}

int Tetromino::hardDrop()
{
	int rowDropPoint = gridCoord[0]; //The row the hard drop was started from

	while (moveDown());

	return rowDropPoint;
}

void Tetromino::lockIn()
{
	for (int i = 0; i < 4; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			if (shapeArea[i][n])
			{
				parentGrid->setCell((gridCoord[0] + i), (gridCoord[1] + n), 1);
			}
		}
	}

	nextShape();
}

void Tetromino::getCoords(int coords[])
{
	coords[0] = displayCoord[0];
	coords[1] = displayCoord[1];
}