// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "olcConsoleGameEngine.h"
#include "Player.h"
#include "Cover.h"
#include "Invader.h"
#include "Bullet.h"



using namespace std;

class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction(Player& player, Cover& cover, Bullet& bullet,
		Invader& invader, 
		Invader& invader1, 
		Invader& invader2, 
		Invader& invader3, 
		Invader& invader4, 
		Invader& invader5, 
		Invader& invader6,
		Invader& invader7,
		Invader& invader8,
		Invader& invader9,
		Invader& invader10,
		Invader& invader11,
		Invader& invader12,
		Invader& invader13)
		: 
		p(player), 
		c(cover), 
		b(bullet),
		i(invader), 
		i1(invader1),
		i2(invader2),
		i3(invader3),
		i4(invader4), 
		i5(invader5), 
		i6(invader6),
		i7(invader7),
		i8(invader8),
		i9(invader9),
		i10(invader10),
		i11(invader11),
		i12(invader12),
		i13(invader13) {}


	Player& p;
	Cover& c;
	Bullet& b;
	Invader& i;
	Invader& i1;
	Invader& i2;
	Invader& i3;
	Invader& i4;
	Invader& i5;
	Invader& i6;

	Invader& i7;
	Invader& i8;
	Invader& i9;
	Invader& i10;
	Invader& i11;
	Invader& i12;
	Invader& i13;



	//invader movement variables
	double j;
	bool k;
	double l;

	//bullet collision variables
	bool topDown = false;
	bool leftRight = false;


protected:
	bool OnUserCreate() override {


		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {
		//create screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//load player
		Fill(p.playerPositionX, 5 * 29, p.playerPositionY, 5 * 29 + 10, PIXEL_SOLID, 5);
		
		//player movement
		if (IsFocused()) {
			if (GetKey(VK_LEFT).bHeld) {
				p.playerPositionLeft(1);
			}

			if (GetKey(VK_RIGHT).bHeld) {
				p.playerPositionRight(1);
			}

			if (GetKey(VK_UP).bPressed) {
				b.bulletState(true);
				b.bulletVX = 28;
				b.bulletVY = 28;
			}

		}


		//load cover
		Fill(c.left1, 6 * 20, c.right1, 6 * 20 + 10, PIXEL_SOLID, 6);
		Fill(c.left2, 6 * 20, c.right2, 6 * 20 + 10, PIXEL_SOLID, 6);
		Fill(c.left3, 6 * 20, c.right3, 6 * 20 + 10, PIXEL_SOLID, 6);
		Fill(c.left4, 6 * 20, c.right4, 6 * 20 + 10, PIXEL_SOLID, 6);


		//load invaders
		if (i.invaderHealth != 0) {
			Fill(i.horizontalX + j, 7.1 * i.verticalX + l, i.horizontalY + j, 7 * i.verticalY + 10 + l, PIXEL_SOLID, 7);
		}

		Fill(i1.horizontalX + j, 7 * i1.verticalX + l, i1.horizontalY + j, 7 * i1.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i2.horizontalX + j, 7 * i2.verticalX + l, i2.horizontalY + j, 7 * i2.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i3.horizontalX + j, 7 * i3.verticalX + l, i3.horizontalY + j, 7 * i3.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i4.horizontalX + j, 7 * i4.verticalX + l, i4.horizontalY + j, 7 * i4.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i5.horizontalX + j, 7 * i5.verticalX + l, i5.horizontalY + j, 7 * i5.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i6.horizontalX + j, 7 * i6.verticalX + l, i6.horizontalY + j, 7 * i6.verticalY + 10 + l, PIXEL_SOLID, 7);

		Fill(i7.horizontalX + j, 7 * i7.verticalX + l, i7.horizontalY + j, 7 * i7.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i8.horizontalX + j, 7 * i8.verticalX + l, i8.horizontalY + j, 7 * i8.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i9.horizontalX + j, 7 * i9.verticalX + l, i9.horizontalY + j, 7 * i9.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i10.horizontalX + j, 7 * i10.verticalX + l, i10.horizontalY + j, 7 * i10.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i11.horizontalX + j, 7 * i11.verticalX + l, i11.horizontalY + j, 7 * i11.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i12.horizontalX + j, 7 * i12.verticalX + l, i12.horizontalY + j, 7 * i12.verticalY + 10 + l, PIXEL_SOLID, 7);
		Fill(i13.horizontalX + j, 7 * i13.verticalX + l, i13.horizontalY + j, 7 * i13.verticalY + 10 + l, PIXEL_SOLID, 7);


		//invader movement
		if (j < 0) {
			k = true;
			l++;
		}
		else if (j > 15) {
			k = false;
			l++;
		}

		if (k == true) {
			j = j + 0.05;
		}
		else if (k == false) {
			j = j - 0.05;
		}

		//load bullet
		Fill(b.bulletHX, 8 * b.bulletVX, b.bulletHY, 8 * b.bulletVY + 10, PIXEL_SOLID, 8);

		//bullet movement
		if (b.bState == true) {
			b.bulletHX = p.playerPositionX +4;
			b.bulletHY = p.playerPositionY -4;

			b.bulletVX = b.bulletVX - 0.25;
			b.bulletVY = b.bulletVY - 0.25;
		}

		if (b.bulletVX < 1) {
			b.bulletVX = 40;
			b.bulletVY = 41;
			b.bulletHX = 500;
			b.bulletHY = 510;
			b.bulletState(false);
		}

		//check if bullet hit an invader
		if (b.bulletHX > i.horizontalX && b.bulletHX < i.horizontalY) {
			leftRight = true;
			Fill(10, 6 * 10, 20, 6 * 10 + 10, PIXEL_SOLID, 6);
		}

		if (b.bulletVY < i.verticalY) {
			topDown = true;
			Fill(30, 3 * 10, 40, 3 * 10 + 10, PIXEL_SOLID, 3);

		}

		if (leftRight == true && topDown == true) {
			i.invaderHealth = 0;
			b.bulletVX = 40;
			b.bulletVY = 41;
			b.bulletHX = 500;
			b.bulletHY = 510;
			leftRight = false;
			topDown = false;
			b.bulletState(false);

		}

		//check if invaders reach the end


		return true;

	}


};


int main()
{
	
	Player player(100, 70, 80);
	Cover cover;
	Bullet bullet(40, 41, 500, 510);

	Invader invader(100, 10, 20, 2, 2);
	Invader invader1(100, 30, 40, 2, 2);
	Invader invader2(100, 50, 60, 2, 2);
	Invader invader3(100, 70, 80, 2, 2);
	Invader invader4(100, 90, 100, 2, 2);
	Invader invader5(100, 110, 120, 2, 2);
	Invader invader6(100, 130, 140, 2, 2);

	Invader invader7(100, 10, 20, 4, 4);
	Invader invader8(100, 30, 40, 4, 4);
	Invader invader9(100, 50, 60, 4, 4);
	Invader invader10(100, 70, 80, 4, 4);
	Invader invader11(100, 90, 100, 4, 4);
	Invader invader12(100, 110, 120, 4, 4);
	Invader invader13(100, 130, 140, 4, 4);



    GameFunction game(player, cover, bullet,
		invader,
		invader1, 
		invader2, 
		invader3, 
		invader4, 
		invader5, 
		invader6,
		invader7,
		invader8,
		invader9,
		invader10,
		invader11,
		invader12,
		invader13);

    game.ConstructConsole(160, 160, 8, 8);
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
