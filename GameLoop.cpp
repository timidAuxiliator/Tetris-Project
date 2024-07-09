#include "GameLoop.h"
#include <functional>

//Helper Functions

void GameLoop::playerMovement()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x01)
	{
		shape.moveStrafe(-1);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x01)
	{
		shape.moveStrafe(1);
	}
	else if ((GetAsyncKeyState(0x51) & 0x01))
	{
		shape.rotateShape(0);
	}
	else if ((GetAsyncKeyState(0x45) & 0x01))
	{
		shape.rotateShape(1);
	}
	else if ((GetAsyncKeyState(VK_SPACE) & 0x01))
	{
		stats.incrementScore(19 - shape.hardDrop());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void GameLoop::runDisplayUpdate()
{
	auto insertDrawData = [this](GameObject::displayReturn obj) -> void
	{
		for (int unsigned i = 0; i < obj.objects.size(); i++)
		{
			display.insertData(obj.objects[i]);
		}
	};

	while(keepUpdating)
	{		
		playerMovement();
		insertDrawData(grid.display());
		insertDrawData(stats.display());
		insertDrawData(shape.display());
		display.updateFrame();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
	}
}



//Public Functions

GameLoop::GameLoop()
{
	
}

GameLoop::~GameLoop()
{

}

void GameLoop::initialize(int playerLevel)
{
	stats.setLevel(playerLevel);
	threadUpdate = std::thread(&GameLoop::runDisplayUpdate, this);
	threadUpdate.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(800 / (stats.getLevel() + 1)));
}

bool GameLoop::update()
{
	int shapeCoords[2];
	shape.getCoords(shapeCoords);
	bool blockDropSuccess = shape.moveDown();
	stats.incrementLineClear(grid.clearLines());

	if (blockDropSuccess == 0 && shapeCoords[0] == 0)
	{
		keepUpdating = false;
		display.clearFrame();
		return false;
	}
	else if (blockDropSuccess == 0)
	{
		stats.incrementScore(3 * (stats.getLevel() + 1));
		return true;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(800 / (stats.getLevel() + 1)));

	return true;
}