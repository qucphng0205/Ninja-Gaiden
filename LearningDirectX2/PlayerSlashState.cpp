#include "PlayerSlashState.h"

PlayerSlashState::PlayerSlashState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 2, 2, 3, 9, 4, 0.08f);
}

PlayerSlashState::~PlayerSlashState() {
}

void PlayerSlashState::Update(double dt) {

	//slash from 0 -> 1 -> 2
	if (m_Animation->GetCurrentFrameID() != 0 && isSlash < 2)
		isSlash++;

	auto player = playerData->player;

	if (m_Animation->IsLastFrame(dt)) {
		if (player->status != Player::OnGround) {
			//jump or falling is not important, on air time is exactly important thing
			player->SetState(Jump);
		}
		else
			if (KeyBoard::GetInstance()->GetKey(DOWN_ARROW))
				player->SetState(Crouch);
			else
				player->SetState(Idle);
		return;
	}

	if (player->status != Player::OnGround) {

		player->timeOnAir += dt;
		if (player->timeOnAir > 1)
			player->timeOnAir = 1;

		player->SetVy(MyHelper::Lerp(PLAYER_JUMP_FORCE, -PLAYER_JUMP_FORCE, JUMP_TO_GROUND_SPEED * player->timeOnAir));

		if (player->GetVelocity().y <= 0)
			player->status = Player::Falling;
	}

	PlayerState::Update(dt);
}

void PlayerSlashState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerSlashState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	auto player = playerData->player;
	if (keyboard->GetKeyDown(JUMP_BUTTON) && player->status == Player::OnGround)
		player->SetState(Jump);
	else
		if (player->GetVelocity().y != 0) {

			if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW)) {
				if (player->GetMoveDirection() == Player::RightToLeft)
					player->SetVx(-PLAYER_RUN_VELOCITY);
				else {
					player->SetVx(-PLAYER_RUN_VELOCITY / 3.0f);
					player->SetMoveDirection(Player::LeftToRight);
				}
			}
			else
				if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW)) {
					if (player->GetMoveDirection() == Player::LeftToRight)
						player->SetVx(PLAYER_RUN_VELOCITY);
					else {
						player->SetVx(PLAYER_RUN_VELOCITY / 3.0f);
						player->SetMoveDirection(Player::RightToLeft);
					}
				}
				else player->SetVx(0);
		}
}

void PlayerSlashState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {

	Player *player = playerData->player;

	auto impactorType = impactor->GetType();

	////--DEBUG
	//if (impactorType == Layer::EnemyType)
	//	impactor = impactor;

	if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType || impactorType == Layer::ItemAvailableType || impactorType == Layer::ItemHolderType) {

		bool isSlash = this->isSlash == 1;

		if (CollideWithKatana(impactor->GetRect()) && isSlash) {
			if (impactorType != Layer::ItemAvailableType)
				DataManager::AddData(impactor->OnDestroy());
		}
		else
			if (CollideWithBody(impactor->GetRect())) {
				if (impactorType == Layer::ItemAvailableType) {
					DataManager::AddData(impactor->OnDestroy());
				}
				else if (impactorType != Layer::ItemHolderType) {
					player->InjuredByOther(impactor);
				}
			}
		return;
	}
	else if (impactor->GetType() == StaticType && side == Entity::Bottom && player->status == Player::Falling) {
		player->status = Player::OnGround;
		player->timeOnAir = 0;
		auto keyboard = KeyBoard::GetInstance();
		if (keyboard->GetKey(LEFT_ARROW) && !(keyboard->GetKey(RIGHT_ARROW)))
			player->SetState(Running);
		else
			if (keyboard->GetKey(RIGHT_ARROW) && !(keyboard->GetKey(LEFT_ARROW)))
				player->SetState(Running);
			else
				if (keyboard->GetKey(DOWN_ARROW))
					player->SetState(Crouch);
				else
					player->SetState(Idle);
	}
}

PlayerState::State PlayerSlashState::GetState() {
	return Slash;
}

void PlayerSlashState::ResetState(int dummy) {
	auto player = playerData->player;

	//right + left collider is slash range 
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	player->SetColliderLeft(-7);
	player->SetColliderRight(31);

	isSlash = 0;

	gnhpSound::GetInstance()->PlayFX(SOUND_SLASH);

	PlayerState::ResetState(dummy);

	if (dummy != 0)
		m_Animation->SetCurrentFrame(dummy);
}

BoxCollider PlayerSlashState::GetBody() {
	BoxCollider body = playerData->player->GetRect();
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		body.right -= 24;
	else
		body.left += 24;
	return body;
}

#include "CollisionDetector.h"
bool PlayerSlashState::CollideWithKatana(BoxCollider r) {
	BoxCollider katana = playerData->player->GetRect();
	katana.top -= 3;
	katana.bottom += 0;
	//tinh tu tay
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		katana.left += 14;
	else
		katana.right -= 14;
	if (CollisionDetector::IsCollide(katana, r))
		return true;
	return false;
}

bool PlayerSlashState::CollideWithBody(BoxCollider r) {
	BoxCollider body = GetBody();
	if (CollisionDetector::IsCollide(body, r))
		return true;
	return false;
}
