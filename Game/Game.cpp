// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "olcConsoleGameEngine.h"
#include "GameFunction.h"
#include "Player.h"

using namespace std;

class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction() {

	}

private:




protected:
	bool OnUserCreate() override {
		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
		Fill(10, 5 * 6, 20, 5 * 6 + 10, PIXEL_SOLID, 5);

		return true;

		Player::playerPosition();
	}

};


int main()
{
    GameFunction game;
    Player player(100, 20, 60);

    game.ConstructConsole(160, 160, 8, 8);
    player.playerPosition(/*20, 80*/);

    game.Start();


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
