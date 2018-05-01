#include "stdafx.h"


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

VECTOR2 Vec2Rotate(const VECTOR2 *pV, int dgree) {
	VECTOR2 result;
	result.x = pV->x * cos(dgree) - pV->y * sin(dgree);
	result.y = pV->x * sin(dgree) + pV->y * cos(dgree);
	return result;
}