#pragma once
#include <iostream>
#include "Location.h"


//GameObject Handles all common properties of all objects like the player the invader and the covers

using namespace std;

struct GameObject {
	GameObject(Location* location, int Health, double Height, double Width, bool Invincible = false ) : L(location) {
		health = Health;
		invincible = Invincible;
		height = Height;
		width = Width;
	}

	//class variable
	Location* L;

	//variables
	int health;
	bool dead = false;
	bool invincible = true;

	double height;
	double width;


	//methods

	//death state modifiers
	bool SetDeadState(bool state) {
		return dead = state;
	}
	bool DeadState() {
		if (invincible)
			return false;

		if (health <= 0)
			return true;

		return dead;
	}

	//health modifiers
	int HealthAdd(int addedHealth) {
		return health += addedHealth;
	}
	int HealthMin(int HealthDeducted) {
		return health -= HealthDeducted;
	}




	bool IsCollided(GameObject* object) {
		if(object->L->X < L->X + width &&
			object->L->X + object->width > L->X &&
			object->L->Y < L->Y + height &&
			object->L->Y + object->height > L->Y
			)
			return true;

		return false;
	}

	//height modifiers
	void SetHeight(double Height) {
		height = Height;
	}
	double Height() {
		return height;
	}

	//width modifiers
	void Width(double Width) {
		width = Width;
	}
	double Width() {
		return width;
	}



	//write move() function

	


};