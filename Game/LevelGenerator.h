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
			InvadersRowGenerator(objects, 15 +  (i * 7.5));
		}
	}

	//generate a row
	static void MakeCoversRow(list<GameObject*>& objects) {
		CoversRowGenerator(objects, 90);
	}


private: 
	
	//generate invaders
	static void InvadersRowGenerator(list<GameObject*>& objects, double Y) {
		for (double i = 0; i < 11; i++) {
			Location* LocationInvader = new Location(7.5 + (i * 7.5), Y);
			Invader* invader = new Invader(LocationInvader, 3.75, 3.75);
			objects.push_back(invader);
		}
	}

	//generate covers
	static void CoversRowGenerator(list<GameObject*>& objects, double Y) {
		for (double i = 0; i < 4; i++) {
			Location* locationCover = new Location(7.5 + (i * 30), Y);
			Cover* cover = new Cover(locationCover, 3.75, 11.25);
			objects.push_back(cover);
		}
	}


};