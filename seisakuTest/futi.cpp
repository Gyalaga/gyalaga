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
	DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
}
void b() {
	DrawString(0, 100, "メニュー画面です。", GetColor(255, 255, 255));
}