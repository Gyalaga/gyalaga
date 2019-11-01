#include "DxLib.h"

// �O���[�o���ϐ�
int pics[16];
int pic_all;
int panel[16];
enum { TITLE, MAIN, CLEAR } status = TITLE;

// �I�������p�l���Ƌ󔒂����ւ���
void change(int x, int y) {
	int p1 = y * 4 + x;
	int p2 = -1;
	if (x > 0 && panel[p1 - 1] == 15) p2 = p1 - 1;
	if (x < 3 && panel[p1 + 1] == 15) p2 = p1 + 1;
	if (y > 0 && panel[p1 - 4] == 15) p2 = p1 - 4;
	if (y < 3 && panel[p1 + 4] == 15) p2 = p1 + 4;
	if (p2 != -1) {
		panel[p2] = panel[p1];
		panel[p1] = 15;
	}
}

// �^�C�g�����
void gameTitle() {
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		// �����p�l���̃V���b�t��
		for (int i = 0; i < 16; i++) panel[i] = i;
		for (int i = 0; i < 1000; i++) {
			change(GetRand(3), GetRand(3));
		}
		status = MAIN;
	}
	DrawGraph(0, 0, pic_all, FALSE);
	DrawString(102, 142, "CLICK TO START", GetColor(255, 0, 0));
}

// ���C�����
void gameMain() {
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int x, y;
		GetMousePoint(&x, &y);
		change(x / 80, y / 80);
		// �p�l�����S��������������
		bool clear = true;
		for (int i = 0; i < 16; i++) {
			if (panel[i] != i) clear = false;
		}
		if (clear) status = CLEAR;
	}
	// �p�l���̕`��
	for (int i = 0; i < 16; i++) {
		if (panel[i] < 15) {
			DrawGraph((i % 4) * 80, (i / 4) * 80, pics[panel[i]], FALSE);
		}
	}
}

// �I�����
void gameClear() {
	DrawGraph(0, 0, pic_all, FALSE);
	DrawString(115, 142, "GAME CLEAR!", GetColor(255, 0, 0));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(320, 320, 32);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	LoadDivGraph("�摜/pic.png", 16, 4, 4, 80, 80, pics);
	pic_all = LoadGraph("pic.png");
	while (!ProcessMessage()) {
		ClearDrawScreen();
		switch (status) {
		case TITLE: gameTitle(); break;
		case MAIN: gameMain(); break;
		case CLEAR: gameClear(); break;
		}
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}