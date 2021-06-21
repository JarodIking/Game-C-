#pragma once

struct Player{
	//constructor
	inline Player(int health, int positionX, int positionY) {
		playerHealth = health;
		playerPositionX = positionX;
		playerPositionY = positionY;

	}
	
	//player variables
	int playerHealth;
	int playerPositionX;
	int playerPositionY;

	//player functions
	void playerPositionLeft(int num) {
		playerPositionX -= num;
		playerPositionY -= num;

	}

	void playerPositionRight(int num) {
		playerPositionY += num;
		playerPositionX += num;

	}



};