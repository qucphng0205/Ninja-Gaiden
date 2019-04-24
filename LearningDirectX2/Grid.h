#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"

class GridCell {
	//use topleft coordinates
	D3DXVECTOR2 pos;
	BoxCollider rect;
	//nhung vat the nam trong gridcell
	std::vector<Entity*> m_Entities;
	//nhung vat the co dinh trong map
	std::vector<Entity*> m_StaticEntities;
public:
	GridCell() { pos = D3DXVECTOR2(0, 0); }
	GridCell(D3DXVECTOR2 position) { pos = position; };
	GridCell(float x, float y) { pos = D3DXVECTOR2(x, y); };
	void SetRect(float width, float height);
	BoxCollider GetRect() { return rect; }
	//xoa het vat the
	void ClearAllEntities();
	//day entities trong gridcell vao entities
	void GetAllEntityTo(std::vector<Entity*> &entities);
	//day entity vao mang entities gridcell
	void PushEntity(Entity *entity);
	//day static entity cua map vao day
	void PushStaticEntity(Entity *entity);
	~GridCell();
};

class Grid {
	int rows;
	int columns;
	float cellWidth;
	float cellHeight;
	GridCell **cells;
	//kiem tra xem r1 va r2 co chong len nhau
	bool IsOverlap(BoxCollider r1, BoxCollider r2);
public:
	//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
	Grid(BoxCollider r, int rows = GRID_ROWS, int columns = GRID_COLUMNS);
	//Se clear toan bo entities o trong toan bo gridcell
	void Clear();
	//Dua entity vao gridcell nao do de gridcell do dua vao mang entities cua no
	void InsertEntity(Entity *entity);
	//dua static entity vao gridcell nao do de gridcell do dua vao mang static entities cua no
	void InsertStaticEntity(Entity *entity);
	//Lay nhung entity co kha nang va cham voi BoxCollider r
	void GetEntityWithRect(std::vector<Entity*> &entities, BoxCollider r);
	~Grid();
};