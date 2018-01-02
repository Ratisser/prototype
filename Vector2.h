#pragma once

#define PI 3.141592
#define TODEG(a) a/(2*PI)*360
#define TORAD(a) a/180*PI

typedef struct _VECTOR2 {
	float x;
	float y;
}VECTOR2, *PVECTOR2;



__forceinline float Vec2Dot(const VECTOR2 *pV1, const VECTOR2 *pV2) {
	return pV1->x * pV2->x + pV1->y * pV2->y;
}

__forceinline float Vec2DotProduct(const VECTOR2 *pV) {
	return pV->y * 1.0f;
}

__forceinline float Vec2Theta(const VECTOR2 *pV) {
	return (float)(((pV->x <0) ? TORAD(360.0f) : 0.0f) + (acos(-pV->y) * ((pV->x < 0) ? -1 : 1)));
}

// 루트를 씌우지 않았음
__forceinline float Vec2Dist(const VECTOR2 *pV1, const VECTOR2 *pV2) {
	return (pV1->x - pV2->x) * (pV1->x - pV2->x) + (pV1->y - pV2->y) * (pV1->y - pV2->y);
}

void Vec2Dir(VECTOR2 *pOut, const VECTOR2 *pV1, const VECTOR2 *pV2);

//void Vec2Nomalize(VECTOR2 *pOut, const VECTOR2 *pV) {
//	float vLen = pV->x*pV->x
//}