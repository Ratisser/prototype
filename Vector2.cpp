#include "stdafx.h"
#include "Vector2.h"


void  Vec2Dir(VECTOR2 *pOut, const VECTOR2 *pV1, const VECTOR2 *pV2) {
	float len;
	pOut->x = pV2->x - pV1->x;
	pOut->y = pV2->y - pV1->y;
	len = pOut->x * pOut->x + pOut->y * pOut->y;
	pOut->x = pOut->x * pOut->x * ((pOut->x < 0) ? -1 : 1);
	pOut->y = pOut->y * pOut->y * ((pOut->y < 0) ? -1 : 1);
	pOut->x /= len;
	pOut->y /= len;
}