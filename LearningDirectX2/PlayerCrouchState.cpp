#include "PlayerCrouchState.h"

PlayerCrouchState::PlayerCrouchState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 6, 6, 1, 9, 4, 0.1f);

}

PlayerCrouchState::~PlayerCrouchState() {
}

void PlayerCrouchState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerCrouchState::Update(double dt) {
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	PlayerState::Update(dt);
}

void PlayerCrouchState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	//CrouchSlash, Slash, Jump, Running, Idle,...?
	if (keyboard->GetKey(UP_ARROW))
		playerData->player->SetState(Idle);
	else if (keyboard->GetKeyDown(SLASH_BUTTON) && keyboard->GetKey(DOWN_ARROW))
		playerData->player->SetState(CrouchSlash);
	else if (keyboard->GetKeyDown(SLASH_BUTTON) && !keyboard->GetKey(DOWN_ARROW))
		playerData->player->SetState(Slash);
	else if (keyboard->GetKeyDown(JUMP_BUTTON))
		playerData->player->SetState(Jump);
	else if (keyboard->GetKey(DIK_LEFT) && !keyboard->GetKey(DIK_RIGHT))
		playerData->player->SetState(Running);
	else if (keyboard->GetKey(DIK_RIGHT) && !keyboard->GetKey(DIK_LEFT))
		playerData->player->SetState(Running);
	else if (!keyboard->GetKey(DOWN_ARROW))
		playerData->player->SetState(Idle);
}

void PlayerCrouchState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemAvailableType)
		DataManager::AddData(impactor->OnDestroy());
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		playerData->player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerCrouchState::GetState() {
	return Crouch;
}

void PlayerCrouchState::ResetState(int dummy) {
	auto player = playerData->player;
	//Collider when crouch around center point
	player->SetColliderLeft(-7);
	player->SetColliderTop(8);
	player->SetColliderBottom(-16);
	PlayerState::ResetState(dummy);
}
