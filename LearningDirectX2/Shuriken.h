#pragma once
#include "Weapon.h"
#include "Player.h"

class Shuriken : public Weapon {
public:
	Shuriken();
	virtual void Update(double dt);
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Instantiate(D3DXVECTOR3 position);
	virtual EarnedData OnDestroy();
};