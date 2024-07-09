#pragma once
#include "DisplayModule.h"
#include <vector>

class GameObject
{
	public:
		//Allows for the return of multiple displayInfo objects if needed
		struct displayReturn
		{
			std::vector<DisplayModule::displayInfo> objects;
		};
		
		GameObject();
		~GameObject();
		virtual displayReturn display() = 0;


	private:
		
};

