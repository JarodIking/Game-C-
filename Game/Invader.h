#pragma once

struct Invader {
	Invader(int health, double hX, double hY, double vX, double vY) {
		//initiate position and health
		horizontalX = hX;
		horizontalY = hY;

		verticalX = vX;
		verticalY = vY;

		invaderHealth = health;
	}

	//position variables
	int invaderHealth;
	double horizontalX;
	double horizontalY;

	double verticalX;
	double verticalY;
};