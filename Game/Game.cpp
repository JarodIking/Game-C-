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

	//player object
	Player* player;

protected:
	//fill in screen function
	void Draw() {
		//create screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//fill in updated coordinates
		DrawObjects(Covers);
		DrawObjects(Invaders);
		DrawObjects(Bullets);
		DrawObjects(BulletsInvaders);
		
		//fill in updated player coordinates
		Fill(player->L->X, player->L->Y, player->L->X + player->width,player->L->Y + player->height, PIXEL_SOLID, FG_GREEN);
	}

	//draw objects
	void DrawObjects(list<GameObject*>& objects) {
		for (GameObject* object : objects) {
			//check for empty elements in list
			if (object != NULL && object->L != NULL) {
				//check if object are alive
				if (!object->DeadState()) {
					//check object health and colour that object accordingly
					if (object->health < 6) 
						Fill(object->L->X, object->L->Y, object->L->X + object->width, object->L->Y + object->height, PIXEL_SOLID, FG_RED);
					else 
						Fill(object->L->X, object->L->Y, object->L->X + object->width, object->L->Y + object->height, PIXEL_SOLID, 6);
				}
			}
		}
	}

	//create bullets for player
	void MakeBullet(double X, double Y) {
		Location* locationBullet = new Location(X, Y);
		Bullet* bullet = new Bullet(locationBullet);
		Bullets.push_back(bullet);

	}

	//create bullets for an invader
	void MakeBulletInvader(GameObject* invader) {
			Location* locationBulletInvader = new Location(invader->L->X + invader->Width()/2, invader->L->Y);
			Bullet* bullet = new Bullet(locationBulletInvader);
			BulletsInvaders.push_back(bullet);
	}

	//randomly choose an invader that is alive too shoot
	GameObject* SelectShootingInvader(list<GameObject*>& invaders) {
		//find any invaders that are alive and put them in a new list
		list<GameObject*> aliveInvaders;
		for (GameObject* invader : invaders)
			if (!invader->DeadState())
				aliveInvaders.push_back(invader);

		//create random integer to select an element
		int rnd = rand() % aliveInvaders.size();
		int i = 0;

		//take randomly selected invader and put inside an object variable
		GameObject* output = NULL;
		for (GameObject* invader : aliveInvaders) {
			//loop throught each object here to see if it matches randomly selected invader
			if (rnd == i) {
				output = invader;
				break;
			}
			i++;
		}

		//return selected invader
		return output;
	}


	//update bullet coordinates for player
	void UpdateBullets(list<GameObject*>& objects, double Y) {
		//A seperate list to push deleted objects too otherwise a crash will occur in DrawObjects()
		list<GameObject*> deleted;

		//go throught each bullet a player has fired
		for (GameObject* object : objects)
			//check to see if player bullet is out of bounds, if so push bullet to 'deleted' list
			if (object->L->Y > 1) {
				object->L->Y -= Y;
				//A collision check to see if bullet hits an invader
				if(CheckCollision(Invaders, object) ||
					CheckCollision(Covers, object))
					deleted.push_back(object);
			}
			else
				deleted.push_back(object);

		//remove any objects in 'deleted' list
		for (GameObject* object : deleted)
			objects.remove(object);
	}

	//update bullet coordinates for invaders
	void UpdateBulletsInvaders(list<GameObject*>& objects, double Y) {
		//A seperate list to push deleted objects too otherwise a crash will occur in DrawObjects()
		list<GameObject*> deleted;
		for (GameObject* object : objects)
			//check to see if player bullet is out of bounds, if so push bullet to 'deleted' list
			if (object->L->Y > 1) {
				object->L->Y -= Y;
				//A collision check to see if bullet hits the player
				if (CheckCollision(player, object) || 
					CheckCollision(Covers, object))
					deleted.push_back(object);
			}
			else
				deleted.push_back(object);

		//remove any objects in 'deleted' list
		for (GameObject* object : deleted)
			objects.remove(object);

	}

	//update coordinates of the invaders
	void UpdateInvaders(list<GameObject*>& objects, double X) {
		bool changeDirection = false;
		//move the invaders
		for (GameObject* object : objects) {
			object->L->X += X * invaderDirection;
			if (object->L->X >= 150 || object->L->X <= 0)
				changeDirection = true;
		}
		//change direction of invaders
		if (changeDirection) {
			invaderDirection *= -1;
			for (GameObject* object : objects)
				object->L->Y += 5;
		}
		//fire function to check if invaders have reached the cover
		CollisionCheckCoverInvader(Covers, objects);
	}

	//Collision check bullet invader to player
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

	//collision check bullet invader to player
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

	//setup the game
	void Setup() {
		if (player == NULL) {
			Location* locationPlayer = new Location(10, 140);
			player = new Player(locationPlayer);

		}


		LevelGenerator::MakeCoversRow(Covers);
		LevelGenerator::MakeInvadersRow(Invaders, lvl);

		isRunning = true;

	}

	//reset the game
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

	//advance the game to next level
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

	//initalize games
	bool OnUserCreate() override {
		Setup();
		return true;

	}

	//game loop
	bool OnUserUpdate(float fElapsedTime) override {
		//check if the game is running
		if (!isRunning) {
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
			return true;
		}

		//check if player is dead
		if (player->DeadState()) {
			Reset();
			return true;
		}

		//check if invaders are dead
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

		//fire bullet invader
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

			//fire player bullet
			if (GetKey(VK_UP).bHeld) {
				if (Bullets.size() < 1)
					MakeBullet(player->L->X + player->Width()/2, player->L->Y);
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

//construct the console
int main()
{
    GameFunction* game = new GameFunction();

    game->ConstructConsole(160, 160, 8, 8);
    game->Start();

    return 0;
}  
