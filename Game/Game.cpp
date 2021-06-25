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
		if (player == NULL) {
			Location* locationPlayer = new Location(10, 140);
			player = new Player(locationPlayer);

		}


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
		return true;

	}


};


int main()
{
    GameFunction* game = new GameFunction();

    game->ConstructConsole(160, 160, 8, 8);
    game->Start();

    return 0;
}  
