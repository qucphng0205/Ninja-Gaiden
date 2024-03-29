#include "Entity.h"

int Entity::currentID = 0;

void Entity::OnSetPosition(D3DXVECTOR3 pos) {
}

Entity::Entity() {
	Tag = NONE;
	id = ++currentID;
	isStatic = false;
}

Entity::~Entity() {
}

BoxCollider Entity::GetRect() {
	BoxCollider r;
	r.left = position.x - width / 2;
	r.top = position.y + height / 2;
	r.right = r.left + width;
	r.bottom = r.top - height;
	return r;
}

void Entity::SetActive(bool active) {
	isActive = active;
}

bool Entity::IsActive() {
	return isActive;
}

Tag Entity::GetTag() {
	return Tag;
}

void Entity::SetTag(enum Tag Tag) {
	this->Tag = Tag;
}

Layer Entity::GetType() {
	return type;
}

void Entity::SetType(Layer type) {
	this->type = type;
}

void Entity::SetStatic(bool flag) {
	isStatic = flag;
	velocity = D3DXVECTOR2(0, 0);
}


void Entity::SetPosition(float x, float y) {
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::SetPosition(D3DXVECTOR2 pos) {
	SetPosition(D3DXVECTOR3(pos));
}

void Entity::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
	OnSetPosition(position);
}

void Entity::AddPosition(D3DXVECTOR3 pos) {
	SetPosition(pos + position);
}

void Entity::AddPosition(D3DXVECTOR2 pos) {
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y) {
	AddPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR3 Entity::GetPosition() {
	return position;
}

Entity::EntityDirection Entity::GetMoveDirection() {
	return direction;
}

void Entity::SetMoveDirection(EntityDirection direction) {
	this->direction = direction;
}

void Entity::SetWidth(int width) {
	this->width = width;
}

float Entity::GetWidth() {
	return width;
}

float Entity::GetBigWidth() {
	return GetWidth();
}

void Entity::SetHeight(int height) {
	this->height = height;
}

float Entity::GetHeight() {
	return height;
}

float Entity::GetBigHeight() {
	return GetHeight();
}

void Entity::SetVelocity(D3DXVECTOR2 vel) {
	if (vel.x > 0)
		SetMoveDirection(LeftToRight);
	else
		if (vel.x < 0)
			SetMoveDirection(RightToLeft);
	velocity = vel;
}

D3DXVECTOR2 Entity::GetVelocity() {
	return velocity;
}

float Entity::GetVx(){
	return velocity.x;
}

void Entity::SetVx(float vx) {
	if (vx > 0)
		SetMoveDirection(LeftToRight);
	else
		if (vx < 0)
			SetMoveDirection(RightToLeft);
	this->velocity.x = vx;
}

void Entity::AddVx(float vx) {
	this->velocity.x += vx;
}

float Entity::GetVy() {
	return velocity.y;
}

void Entity::SetVy(float vy) {
	this->velocity.y = vy;
}

void Entity::AddVy(float vy) {
	this->velocity.y += vy;
}

void Entity::AddVelocity(D3DXVECTOR2 vel) {
	velocity.x += vel.x;
	velocity.y += vel.y;
}

int Entity::GetID() {
	return id;
}

void Entity::Update(double dt) {
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Entity::Render() {
}

void Entity::OnCollision(Entity * impactor, SideCollision side, float collisionTime, double dt) {
	//velocity = D3DXVECTOR2(0, 0);
}

EarnedData Entity::OnDestroy() {
	return EarnedData();
}
