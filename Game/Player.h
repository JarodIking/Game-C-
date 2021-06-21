#pragma once

class Player{
public:
	//constructor
	inline Player(int health, int positionX, int positionY) {
		playerHealth = health;
		playerPositionX = positionX;
		playerPositionY = positionY;

	}
	
	int& RplayerHealth = playerHealth;
	int& RplayerPositionX = playerPositionX;
	int& RplayerPositionY = playerPositionY;


private:
	//player variables
	int playerHealth;
	int playerPositionX;
	int playerPositionY;

public:
	//player functions
	void playerPositionLeft(int num) {
		playerPositionX += num;
		playerPositionY -= num;

	}

	void playerPositionRight(int num) {
		playerPositionY += num;
		playerPositionX -= num;

	}



};