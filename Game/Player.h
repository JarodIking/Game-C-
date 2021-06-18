#pragma once

class Player : public olcConsoleGameEngine {
public:
	//constructor
	Player(int health, int positionX, int positionY) {
		playerHealth = health;
		playerPositionX = positionX;
		playerPositionY = positionY;

	}


private:
	//private variables
	int playerHealth;
	int playerPositionX;
	int playerPositionY;



protected:
	int playerPosition(int X, int Y) {
		Fill(X, 5 * 6, Y, 5 * 6 + 10, PIXEL_SOLID, 5);

	}




};