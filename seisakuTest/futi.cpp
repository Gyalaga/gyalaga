#include "DxLib.h"
void a();
void b();
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	a();
	b();
	DxLib_End();
	return 0;
}

void a() {
	DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
}
void b() {
	DrawString(0, 100, "���j���[��ʂł��B", GetColor(255, 255, 255));
}