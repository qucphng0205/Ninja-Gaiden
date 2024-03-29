#include "ObjectPooling.h"
#include <iterator>

ObjectPooling *ObjectPooling::instance = NULL;

ObjectPooling * ObjectPooling::GetInstance() {
	//USED TO BUG: su dung addKnife ma khong instantiate doi tuong ObjectPooling
	if (instance == NULL)
		instance = new ObjectPooling();
	return instance;
}

void ObjectPooling::AddKnife(int number) {
	Unit *unit;
	pool[KNIFE_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Knife* knife = new Knife();
		unit = new Unit(Grid::GetInstance(), knife);
		pool[KNIFE_POOL_INDEX].push_back(unit);
	}
}

int ObjectPooling::CheckQuantity(int index) {
	int quantity = 0;
	auto knives = pool[index];
	for (size_t i = 0; i < knives.size(); i++)
		if (!knives[i]->GetEntity()->IsActive())
			quantity++;
	return quantity;
}

bool ObjectPooling::Instantiate(int index, D3DXVECTOR3 position) {
	auto weapons = pool[index];
	for (size_t i = 0; i < weapons.size(); i++) {
		Weapon *weapon = (Weapon*)weapons[i]->GetEntity();
		if (!weapon->IsActive()) {
			weapon->Instantiate(position);
			weapons[i]->Move(weapon->GetPosition());
			return true;
		}
	}
	return false;
}

void ObjectPooling::AddBullet(int number) {
	Unit *unit;
	pool[BULLET_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Bullet* bullet = new Bullet();
		unit = new Unit(Grid::GetInstance(), bullet);
		pool[BULLET_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddShuriken(int number) {
	Unit *unit;
	pool[SHURIKEN_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Shuriken* shuriken = new Shuriken();
		unit = new Unit(Grid::GetInstance(), shuriken);
		pool[SHURIKEN_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddBigShuriken(int number) {
	Unit *unit;
	pool[BIGSHURIKEN_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		BigShuriken* bigShuriken = new BigShuriken();
		unit = new Unit(Grid::GetInstance(), bigShuriken);
		pool[BIGSHURIKEN_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddFlames(int number) {
	Unit *unit;
	pool[FLAMES_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Flames* flames = new Flames();
		unit = new Unit(Grid::GetInstance(), flames);
		pool[FLAMES_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddBigBullet(int number) {
	Unit *unit;
	pool[BIGBULLET_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		BigBullet* bigBullet = new BigBullet();
		unit = new Unit(Grid::GetInstance(), bigBullet);
		pool[BIGBULLET_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddDarts(int number) {
	Unit *unit;
	pool[DARTS_POOL_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Dart* dart = new Dart();
		unit = new Unit(Grid::GetInstance(), dart);
		pool[DARTS_POOL_INDEX].push_back(unit);
	}
}

ObjectPooling::ObjectPooling() {
	if (instance != NULL)
		delete this;
	instance = this;
}
