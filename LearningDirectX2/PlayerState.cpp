#include "PlayerState.h"

PlayerState::PlayerState(PlayerData * data) {
	this->playerData = data;
}

PlayerState::PlayerState() {
}

PlayerState::~PlayerState() {
}

void PlayerState::Update(double dt) {
}

void PlayerState::Render() {

}

void PlayerState::HandleInput() {
}

void PlayerState::OnCollision(Entity * impactor, Entity::SideCollision side) {
}

PlayerState::State PlayerState::GetState() {
	return Idle;
}

int PlayerState::GetAnimationHeight() {
	return m_Animation->GetHeightCurrentFrame();
}

int PlayerState::GetAnimationWidth() {
	return m_Animation->GetWidthCurrentFrame();
}

void PlayerState::ResetState(int dummy) {
	m_Animation->ResetAnimation();
}