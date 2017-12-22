#pragma once


/*
0-20 = 0
21-40 = 2
41-60 = 4
61-80 = 6
81-100 = 8
101-120 = 10
121-140 = 12
141-160 = 14
161-180 = 16

0-19 20-39 40-59 60-79 80-99 100-119 120-139 140-159 160-179
0	1		2	 3		4	 5	  	 6		 7		  8

0~-20 = 1
-21~40 = 3
-41~60 = 5
-61~80 = 7
-81~-100 = 9
-101~120 = 11
-121~140 = 13
-141~-160 = 15
-161~-180 = 17

*/
void a() {
	int iArray[19] = { 16,16,15,13,11,9,7,5,3,0,2,4,6,8,10,12,14,16,16 };
	int *pIndex = &iArray[9];
}

class SpriteManager
{
private:
	List **UltraSprite;
public:
	__forceinline SpriteManager* GetInstance() { static SpriteManager instance;return &instance; }
	void Init();


	SpriteManager();
	~SpriteManager();
};