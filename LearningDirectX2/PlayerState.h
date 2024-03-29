#pragma once
#include "Entity.h"
#include "Animation.h"
#include "PlayerData.h"
#include "KeyBoard.h"
#include "GameConfig.h"
#include "Textures.h"

class PlayerState {
public:
	enum State{
		Idle,
		Running,
		Slash,
		Crouch,
		CrouchSlash,
		Jump,
		Falling,
		Climb,
		UseItem,
		Injured,
	};
	~PlayerState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60);
	virtual State GetState();
	virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	virtual BoxCollider GetBody();
	virtual void ResetState(int dummy);
	Animation *GetAnimation() { return m_Animation; }
protected:
	Animation *m_Animation;
	PlayerState(PlayerData *data);
	PlayerState();
	PlayerData *playerData;
};
