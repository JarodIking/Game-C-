#pragma once

class Player{
public:
	//constructor
	Player(int health, int positionX, int positionY) {
		playerHealth = health;
		playerPositionX = positionX;
		playerPositionY = positionY;

	}

	//player functions
	static void playerPosition(/*int X, int Y*/) {
		//Fill(X, 5 * 6, Y, 5 * 6 + 10, PIXEL_SOLID, 5);

	}


private:
	//private variables
	int playerHealth;
	int playerPositionX;
	int playerPositionY;

};