#pragma once
#include "GameObject.h"
using namespace std;
struct Bullet : public GameObject {
	Bullet(Location* l) : GameObject(l, 100, 10, 1){
	
	}
};