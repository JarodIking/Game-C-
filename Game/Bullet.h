#pragma once
struct Bullet {
	Bullet(double vx, double vy, int hx, int hy) {
		bulletVY = vx;
		bulletVX = vy;

		bulletHY = hx;
		bulletHX = hy;
	}

	double bulletVX;
	double bulletVY;

	int bulletHX;
	int bulletHY;

	bool bState = false;

	bool bulletState(bool state) {
		return bState = state;
	}


};