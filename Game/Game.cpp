// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "olcConsoleGameEngine.h"
#include "Player.h"
#include "Cover.h"
#include "Invader.h"
#include "Bullet.h"
#include "GameObject.h"
#include "LevelGenerator.h"



using namespace std;

class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction(){}

	//class variables
	list<GameObject*> Covers;
	list<GameObject*> Invaders;
	list<GameObject*> Bullets;
	list<GameObject*> BulletsInvaders;

	//single objects
	GameObject* Invader;

	//variables
	int invaderDirection = 1;
	bool isRunning = false;

	int lvl = 1;

	Player* player;

protected:
	//fill in screen
	void Draw() {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		DrawObjects(Covers);
		DrawObjects(Invaders);
		DrawObjects(Bullets);
		DrawObjects(BulletsInvaders);



		Fill(player->L->X, player->L->Y, player->L->X + player->width,player->L->Y + player->height, PIXEL_SOLID, FG_GREEN);
	}

	//draw objects
	void DrawObjects(list<GameObject*>& objects) {
		for (GameObject* object : objects) {
			//check doesnt work
			if (object != NULL && object->L != NULL) {
				if (!object->DeadState()) {
					if (object->health < 6) 
						Fill(object->L->X, object->L->Y, object->L->X + object->width, object->L->Y + object->height, PIXEL_SOLID, FG_RED);
					else 
						Fill(object->L->X, object->L->Y, object->L->X + object->width, object->L->Y + object->height, PIXEL_SOLID, 6);
				}
			}
		}
	}

	//create bullets
	void MakeBullet(double X, double Y) {
		Location* locationBullet = new Location(X, Y);
		Bullet* bullet = new Bullet(locationBullet);
		Bullets.push_back(bullet);

	}

	void MakeBulletInvader(GameObject* invader) {
			Location* locationBulletInvader = new Location(invader->L->X + invader->Width()/2, invader->L->Y);
			Bullet* bullet = new Bullet(locationBulletInvader);
			BulletsInvaders.push_back(bullet);
	}

	GameObject* SelectShootingInvader(list<GameObject*>& invaders) {
		list<GameObject*> aliveInvaders;
		for (GameObject* invader : invaders)
			if (!invader->DeadState())
				aliveInvaders.push_back(invader);

		int rnd = rand() % aliveInvaders.size();
		int i = 0;
		GameObject* output = NULL;

		for (GameObject* invader : aliveInvaders) {
			if (rnd == i) {
				output = invader;
				break;
			}
			i++;
		}

		return output;
	}

	//update bullet coordinates for player
	void UpdateBullets(list<GameObject*>& objects, double Y) {
		list<GameObject*> deleted;
		for (GameObject* object : objects)
			if (object->L->Y > 1) {
				object->L->Y -= Y;
				if(CheckCollision(Invaders, object) ||
					CheckCollision(Covers, object))
					deleted.push_back(object);
			}
			else
				deleted.push_back(object);

		for (GameObject* object : deleted)
			objects.remove(object);
	}

	void UpdateBulletsInvaders(list<GameObject*>& objects, double Y) {
		list<GameObject*> deleted;
		for (GameObject* object : objects)
			if (object->L->Y > 1) {
				object->L->Y -= Y;
				if (CheckCollision(player, object) || 
					CheckCollision(Covers, object))
					deleted.push_back(object);
			}
			else
				deleted.push_back(object);

		for (GameObject* object : deleted)
			objects.remove(object);

	}

	//update coordinates of the invaders
	void UpdateInvaders(list<GameObject*>& objects, double X) {
		bool changeDirection = false;
		for (GameObject* object : objects) {
			object->L->X += X * invaderDirection;
			if (object->L->X >= 150 || object->L->X <= 0)
				changeDirection = true;
		}
		if (changeDirection) {
			invaderDirection *= -1;
			for (GameObject* object : objects)
				object->L->Y += 5;
		}
		CollisionCheckCoverInvader(Covers, objects);
	}

	//Collision check bullet
	bool CheckCollision(list<GameObject* >& objects, GameObject* bullet) {
		for (GameObject* object : objects)
			if(!object->DeadState())
				if (object->IsCollided(bullet)) {
					object->health -= 1;
					if(object->health <= 0)
						object->SetDeadState(true);
					return true;
				}
		return false;
	}

	bool CheckCollision(GameObject* object, GameObject* bullet) {
		if (!object->DeadState())
			if (object->IsCollided(bullet)) {
				object->health -= 1;
				if (object->health <= 0)
					object->SetDeadState(true);
				return true;
			}
		return false;
	}


	//check collision invader and cover
	void CollisionCheckCoverInvader(list<GameObject* >& covers, list<GameObject* >& invaders) {
		for (GameObject* cover : covers) {
			for (GameObject* invader : invaders) {
				if (invader->DeadState())
					continue;
				if (cover->IsCollided(invader)) {
					player->health = 0;
					break;
				}
			}
		}
	}

	void Setup() {
		Location* locationPlayer = new Location(10, 140);
		player = new Player(locationPlayer);


		LevelGenerator::MakeCoversRow(Covers);
		LevelGenerator::MakeInvadersRow(Invaders, lvl);

		isRunning = true;

	}

	void Reset() {
		isRunning = false;

		 Covers.clear();
		 Invaders.clear();
		 Bullets.clear();
		 BulletsInvaders.clear();

		 delete player;

		 invaderDirection = 1;
		 lvl = 1;

		 Setup();
	}

	void NextLevel() {
		isRunning = false;

		Covers.clear();
		Invaders.clear();
		Bullets.clear();
		BulletsInvaders.clear();

		delete player;

		invaderDirection = 1;
		lvl++;

		Setup();

	}



	bool OnUserCreate() override {
		Setup();
		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {

		if (!isRunning) {
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
			return true;
		}

		if (player->DeadState()) {
			Reset();
			return true;
		}

		bool oneAlive = false;
		for (GameObject* invader : Invaders) {
			if (!invader->DeadState()) {
				oneAlive = true;
				break;
			}
		}

		if (!oneAlive) {
			NextLevel();
			return true;
		}

		int rnd = rand() % 150 / lvl;
		if (rnd < 1) {
			Invader = SelectShootingInvader(Invaders);
			MakeBulletInvader(Invader);
		}

		//player movement
		if (IsFocused()) {
			if (GetKey(VK_LEFT).bHeld) {
				if (player->L->X != 0)
					player->L->X -= 0.5;
				else
					player->L->X = player->L->X;
			}

			if (GetKey(VK_RIGHT).bHeld) {
				if(player->L->X != 150)
					player->L->X += 0.5;
				else
					player->L->X = player->L->X;
			}

			if (GetKey(VK_UP).bHeld) {
				if (Bullets.size() < 1)
					MakeBullet(player->L->X + player->Width()/2, player->L->Y);
			}


			if (GetKey(VK_DELETE).bPressed) {
			}

		}

		//GameObject movement 
		UpdateBullets(Bullets, 1.5);
		UpdateBulletsInvaders(BulletsInvaders, -0.5);
		UpdateInvaders(Invaders, 0.05);


		//this
		Draw();
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
