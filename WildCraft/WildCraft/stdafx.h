// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <assert.h>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <functional>

#pragma region ������ ���� ���
extern HWND g_hWnd;
const DWORD WIN_START_POS_X = 0;
const DWORD WIN_START_POS_Y = 0;
const DWORD WIN_SIZE_WIDTH = 1280;
const DWORD WIN_SIZE_HEIGHT = 800;
const DWORD WIN_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
#pragma endregion

