#pragma once
#include <iostream>
#include <list>
#include "GameObject.h"
#include "Invader.h"
#include "Cover.h"

using namespace std;

//All level generation functions here
class LevelGenerator{
	LevelGenerator() {

	}

public:
	//generate rows based on level
	static void MakeInvadersRow(list<GameObject*>& objects, int rows) {
		for (int i = 0; i < rows; i++) {
			InvadersRowGenerator(objects, 20 +  (i * 10));
		}
	}

	//generate a row
	static void MakeCoversRow(list<GameObject*>& objects) {
		CoversRowGenerator(objects, 120);
	}


private: 
	
	//generate invaders
	static void InvadersRowGenerator(list<GameObject*>& objects, double Y) {
		for (double i = 0; i < 11; i++) {
			Location* LocationInvader = new Location(10 + (i * 10), Y);
			Invader* invader = new Invader(LocationInvader, 5, 5);
			objects.push_back(invader);
		}
	}

	//generate covers
	static void CoversRowGenerator(list<GameObject*>& objects, double Y) {
		for (double i = 0; i < 4; i++) {
			Location* locationCover = new Location(10 + (i * 40), Y);
			Cover* cover = new Cover(locationCover, 5, 15);
			objects.push_back(cover);
		}
	}


};