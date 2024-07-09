// Console-Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <windows.h>
#include <iostream>
#include <iomanip>
#include "GameLoop.h"


int main()
{
    int levelSelect = 0;
    std::cout << "Choose level (0-9): ";
    std::cin >> levelSelect;

    GameLoop game;
    game.initialize(levelSelect);

    //The main game loop. Continues as long as the escape key isn't pressed
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x01) )
    {
        if (!game.update())
        {

            while ((getchar()) != '\n');
            std::cout << "/````\\    /\\    |\\    /|  |````     /```\\  \\    /  |````  |``\\" << std::endl;
            std::cout << "|   __   /__\\   | \\  / |  |----    |     |  \\  /   |----  |__/" << std::endl;
            std::cout << "\\____/  /    \\  |  \\/  |  |____     \\___/    \\/    |____  |  \\" << std::endl;
            std::cout << "                       Press enter key to exit                       " << std::endl;
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            std::cin.get();
            break;
        }     
    };

    return 0;
}
/*





"/````\    /\    |\    /|  |````     /```\  \    /  |````  |``\"
"|   __   /__\   | \  / |  |––––    |     |  \  /   |----  |__/"
"\____/  /    \  |  \/  |  |____     \___/    \/    |____  |  \"
*/
