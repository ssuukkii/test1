#pragma once

/* ���������� ����ϱ����� ���ǵ��� ��Ƴ��´�.*/
/* ��Ÿ �ٸ� ������ϵ鵵 ��Ƴ��´�. */
#include <process.h>

//#define WINSIZEX 1280
//#define WINSIZEY 720
namespace Client
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;

	enum LEVELID { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };
}

extern HWND		g_hWnd;



using namespace Client;



