// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "olcConsoleGameEngine.h"
#include "Player.h"



using namespace std;




class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction(Player& player) : p(player) {}
	Player& p;


protected:
	bool OnUserCreate() override {


		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		Fill(p.playerPositionX, 5 * 29, p.playerPositionY, 5 * 29 + 10, PIXEL_SOLID, 5);

		if (IsFocused()) {
			if (GetKey(VK_LEFT).bHeld) {
				p.playerPositionLeft(1);
			}

			if (GetKey(VK_RIGHT).bHeld) {
				p.playerPositionRight(1);
			}
		}




		return true;

	}


};


int main()
{
	
	int var = 0;
	Player player(100, 70, 80);
    GameFunction game(player);

    game.ConstructConsole(160, 160, 8, 8);
    game.Start();


	//player movement
	//switch (cin.get()) {
	//	case 'a':
	//		game.left = 'a';
	//		break;
	//	case 'd':
	//		game.right = 'd';;
	//		break;

	//	default:

	//		break;
	//}


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
