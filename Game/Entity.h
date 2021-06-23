#pragma once
#include "GameObject.h"


struct Entity : public GameObject {
	Entity(Location l) : GameObject(l) {

	}

	//variables
	bool health;

	//methods
	bool HealthState(bool state) {
		health = state;
	}

	double ChangeX(double x) {
		L.X = x;
	}

	double ChangeY(double y) {
		L.Y = y;
	}


	
};