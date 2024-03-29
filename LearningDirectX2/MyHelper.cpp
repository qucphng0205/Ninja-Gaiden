#include "MyHelper.h"

RECT MyHelper::BoxColliderToRect(BoxCollider col) {
	RECT r;
	r.top = col.top;
	r.left = col.left;
	r.bottom = col.bottom;
	r.right = col.right;
	
	return r;
}

float MyHelper::Clamp(float x, float a, float z) {
	if (x < a)
		x = a;
	else
		if (x > z)
			x = z;
	return x;
}

float MyHelper::Distance(float x, float y) {
	return (x > y) ? x - y : y - x;
}

float MyHelper::Lerp(float a, float b, float t) {
	Clamp(t, 0, 1);
	return a + (b - a) * t;
}
