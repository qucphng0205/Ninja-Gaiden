#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "SoldierFollowState.h"
#include "SoldierAttackState.h"
#include "ObjectPooling.h"

class Soldier : public Enemy {
public:
	Soldier();
	~Soldier();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	void Update(double dt) override;
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void Spawn() override;
	void SpawnBullet();
protected:
	EnemyState
		*soldierFollowState,
		*soldierAttackState;
};