#include "Eagle.h"
#include "Debug.h"

Eagle::Eagle() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EAGLE, "Resources/Sprites/eaglespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	eagleFollowState = new EagleFollowState(enemyData);
	//Set Tag
	Tag = EAGLE;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_EAGLE)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
	point = 300;
}

Eagle::~Eagle() {
	delete eagleFollowState;
	eagleFollowState = NULL;
}

void Eagle::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
}

#include "Player.h"
int i = 0;
void Eagle::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);

	Enemy::Update(dt);

	D3DXVECTOR3 target = Player::GetInstance()->GetPosition();
	target.y -= 10;
	D3DXVECTOR2 accelerate = D3DXVECTOR2(0, 0);

	if (target.x < position.x)
		accelerate.x = -EAGLE_ACCELERATE_X;
	else if (target.x > position.x)
		accelerate.x = EAGLE_ACCELERATE_X;

	position.y = MyHelper::Lerp(position.y, target.y, 0.02f);

	AddVelocity(accelerate);
}

void Eagle::SetColliderTop(int top) {
	collider.top = top;
}

void Eagle::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Eagle::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Eagle::SetColliderRight(int right) {
	collider.right = right;
}

void Eagle::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = eagleFollowState;
	enemyData->state->ResetState();
}

BoxCollider Eagle::GetCollider() {
	return collider;
}

void Eagle::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
	i = 0;
}
