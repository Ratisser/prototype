// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifdef _DEBUG
#define DEBUG_GAME(x) x
#else
#define DEBUG_GAME(x)
#endif


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "resource.h"


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <math.h>

#include "GameFramework.h"
#include "Game.h"
#include "Vector2.h"
#include "SoundManager.h"

#include "Unit.h"
#include "Marine.h"
#include "Zergling.h"
#include "Ultra.h"
#include "Ghost.h"

#endif