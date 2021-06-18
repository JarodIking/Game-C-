#pragma once

class Player : public olcConsoleGameEngine {
public:
	//constructor
	Player(int health, int positionX, int positionY) {
		playerHealth = health;
		playerPositionX = positionX;
		playerPositionY = positionY;

	}

	//player functions
	void playerPosition(int X, int Y) {
		Fill(X, 5 * 6, Y, 5 * 6 + 10, PIXEL_SOLID, 5);

	}

	bool OnUserCreate() override {
		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//player position
		Fill(playerPositionX, 5 * 6, playerPositionY, 5 * 6 + 10, PIXEL_SOLID, 5);


		return true;
	}


private:
	//private variables
	int playerHealth;
	int playerPositionX;
	int playerPositionY;

};