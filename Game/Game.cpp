// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "olcConsoleGameEngine.h"
#include "Player.h"
#include "Cover.h"
#include "Invader.h"
#include "Bullet.h"
#include "GameObject.h"



using namespace std;

class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction(){}

	//class variables
	list<GameObject*> Covers;
	list<GameObject*> Invaders;
	list<GameObject*> Bullets;


	Player* player;

	int i;
protected:
	void Draw() {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		DrawObjects(Covers);
		DrawObjects(Invaders);
		DrawObjects(Bullets);

		Fill(player->L->X, player->L->Y, player->L->X + player->width,player->L->Y + player->height, PIXEL_SOLID, 5);
	}

	void DrawObjects(list<GameObject*>& objects) {
		for (GameObject* object : objects) {
			//check doesnt work
			if (object != NULL && object->L != NULL)
				if (!object->DeadState())
					Fill(object->L->X, object->L->Y, object->L->X + object->width, object->L->Y + object->height, PIXEL_SOLID, 6);
		}

	}


	bool OnUserCreate() override {
		Location* locationPlayer = new Location(10, 140);
		player = new Player(locationPlayer);


		Location* locationCover = new Location(10, 120);
		Cover* cover0 = new Cover(locationCover, 5, 25);
		Covers.push_back(cover0);

		Location* LocationInvader0 = new Location(10, 100);
		Invader* invader0 = new Invader(LocationInvader0, 10, 20);
		Invaders.push_back(invader0);


		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {

		//if (i > 100) {
		//  Covers.front()->health = 0;
		//}



		if (IsFocused()) {
			if (GetKey(VK_LEFT).bHeld) {
				player->L->X -= 0.5;
			}

			if (GetKey(VK_RIGHT).bHeld) {
				player->L->X += 0.5;
			}

			if (GetKey(VK_UP).bPressed) {
			}

		}



		//this
		Draw();
		i++;
		//Fill(LP->X, LP->Y,  LP->X + P->width, LP->Y + P->height, PIXEL_SOLID, 5);

		

		
		






									//Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F)

									//	//load player
									//	Fill(p.playerPositionX, 5 * 29, p.playerPositionY, 5 * 29 + 10, PIXEL_SOLID, 5);
									//	
									//	//player movement


									//	//load cover
									//	Fill(c.left1, 6 * 20, c.right1, 6 * 20 + 10, PIXEL_SOLID, 6);
									//	Fill(c.left2, 6 * 20, c.right2, 6 * 20 + 10, PIXEL_SOLID, 6);
									//	Fill(c.left3, 6 * 20, c.right3, 6 * 20 + 10, PIXEL_SOLID, 6);
									//	Fill(c.left4, 6 * 20, c.right4, 6 * 20 + 10, PIXEL_SOLID, 6);


									//	//load invaders
									//	if (i.invaderHealth != 0) {
									//		i.UhorizontalX = i.horizontalX + j;
									//		i.UverticalX = 7 * i.verticalX + l;
									//		i.UhorizontalY = i.horizontalY + j;
									//		i.UverticalY = 7 * i.verticalY + 10 + l;
									//		Fill(i.UhorizontalX, i.UverticalX, i.UhorizontalY, i.UverticalY, PIXEL_SOLID, 7);
									//	}

									//	Fill(i1.horizontalX + j, 7 * i1.verticalX + l, i1.horizontalY + j, 7 * i1.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i2.horizontalX + j, 7 * i2.verticalX + l, i2.horizontalY + j, 7 * i2.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i3.horizontalX + j, 7 * i3.verticalX + l, i3.horizontalY + j, 7 * i3.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i4.horizontalX + j, 7 * i4.verticalX + l, i4.horizontalY + j, 7 * i4.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i5.horizontalX + j, 7 * i5.verticalX + l, i5.horizontalY + j, 7 * i5.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i6.horizontalX + j, 7 * i6.verticalX + l, i6.horizontalY + j, 7 * i6.verticalY + 10 + l, PIXEL_SOLID, 7);

									//	Fill(i7.horizontalX + j, 7 * i7.verticalX + l, i7.horizontalY + j, 7 * i7.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i8.horizontalX + j, 7 * i8.verticalX + l, i8.horizontalY + j, 7 * i8.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i9.horizontalX + j, 7 * i9.verticalX + l, i9.horizontalY + j, 7 * i9.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i10.horizontalX + j, 7 * i10.verticalX + l, i10.horizontalY + j, 7 * i10.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i11.horizontalX + j, 7 * i11.verticalX + l, i11.horizontalY + j, 7 * i11.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i12.horizontalX + j, 7 * i12.verticalX + l, i12.horizontalY + j, 7 * i12.verticalY + 10 + l, PIXEL_SOLID, 7);
									//	Fill(i13.horizontalX + j, 7 * i13.verticalX + l, i13.horizontalY + j, 7 * i13.verticalY + 10 + l, PIXEL_SOLID, 7);


									//	//invader movement
									//	if (j < 0) {
									//		k = true;
									//		l++;
									//	}
									//	else if (j > 15) {
									//		k = false;
									//		l++;
									//	}

									//	if (k == true) {
									//		j = j + 0.05;
									//	}
									//	else if (k == false) {
									//		j = j - 0.05;
									//	}


									//	//bullet movement
									//	if (b.bState == true) {

									//		b.bulletVX = b.bulletVX - 0.1;
									//		b.bulletVY = b.bulletVY - 0.1;
									//	}

									//	if (b.bulletVX < 1) {
									//		b.bulletVX = 40;
									//		b.bulletVY = 41;
									//		b.bulletHX = 500;
									//		b.bulletHY = 510;
									//		b.bulletState(false);
									//	}


									//	//load bullet
									//	Fill(b.bulletHX, b.bulletVX, b.bulletHY, b.bulletVY, PIXEL_SOLID, 8);


									//	//check if bullet hit an invader
									//	if (b.bulletHX > i.UhorizontalX && b.bulletHY < i.UhorizontalY) {
									//		leftRight = true;
									//		Fill(10, 6 * 10, 20, 6 * 10 + 10, PIXEL_SOLID, 6);
									//	}

									//	if (b.bulletVX < i.UverticalY) {
									//		topDown = true;
									//		Fill(30, 3 * 10, 40, 3 * 10 + 10, PIXEL_SOLID, 3);

									//	}

									//	if (leftRight == true && topDown == true) {
									//		i.invaderHealth = 0;
									//		b.bulletVX = 40;
									//		b.bulletVY = 41;
									//		b.bulletHX = 500;
									//		b.bulletHY = 510;
									//		leftRight = false;
									//		topDown = false;
									//		b.bulletState(false);

									//	}

									//	//check if invaders reach the end

		return true;

	}


};


int main()
{
	//create player

	//create covers

    GameFunction* game = new GameFunction();

    game->ConstructConsole(160, 160, 8, 8);
    game->Start();

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
