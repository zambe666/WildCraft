#pragma once
class cMainGame
{
public:
	const HRESULT Init();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	cMainGame();
	~cMainGame();
};

