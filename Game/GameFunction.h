#pragma once

class GameFunction : public olcConsoleGameEngine{
public:
	GameFunction() {

	}

private:




protected:
	bool OnUserCreate() override {
		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
		return true;
	}

};
