#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

#define PI 3.141592
#define TODEG(a) a * 57.295779 // a/(2*PI)*360
#define TORAD(a) a * 0.017453 // a/180*PI

typedef struct _VECTOR2 {
	float x;
	float y;
}VECTOR2, *PVECTOR2;


__forceinline float Vec2Dot(const VECTOR2 *pV1, const VECTOR2 *pV2) {
	return pV1->x * pV2->x + pV1->y * pV2->y;
}

__forceinline float Vec2Lenth(const VECTOR2 *pV) {
	return sqrtf(pV->x * pV->x + pV->y * pV->y);
}

__forceinline float Vec2DotProduct(const VECTOR2 *pV1, const VECTOR2 *pV2) {
	return Vec2Dot(pV1, pV2) / Vec2Lenth(pV1) * Vec2Lenth(pV2);
}

__forceinline float Vec2DotProduct(const VECTOR2 *pV) {
	return pV->y * 1.0f;
}

__forceinline float Vec2Theta(const VECTOR2 *pV) {
	return (float)(((pV->x <0) ? TORAD(360.0f) : 0.0f) + (acos(-pV->y) * ((pV->x < 0) ? -1 : 1)));
}

__forceinline float Vec2Dist(const VECTOR2 *pV1, const VECTOR2 *pV2) {
	return sqrtf((pV1->x - pV2->x) * (pV1->x - pV2->x) + (pV1->y - pV2->y) * (pV1->y - pV2->y));
}

VECTOR2 Vec2Rotate(const VECTOR2 *pV, int dgree);

void Vec2Dir(VECTOR2 *pOut, const VECTOR2 *pV1, const VECTOR2 *pV2);

#endif