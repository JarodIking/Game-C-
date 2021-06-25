#pragma once
#include "GameObject.h"
//Object for the bullets
using namespace std;
struct Bullet : public GameObject {
	Bullet(Location* l) : GameObject(l, 100, 10, 1){
	
	}
};