#include "DxLib.h"
#include"Setup.h"

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���
} eScene;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)

void irekae(int px, int py) {
	DrawString(500, 0, "�͖{�ł��B", GetColor(175, 175, 175));
	int p1 = (py * 2) + px;
	int p2 = -1;
	if (px > 0 && hairetu[p1 - 1] == 0)p2 = p1 - 1;
	if (px < 1 && hairetu[p1 + 1] == 0)p2 = p1 + 1;
	if (py > 0 && hairetu[p1 - 2] == 0)p2 = p1 - 2;
	if (py < 1 && hairetu[p1 + 2] == 0)p2 = p1 + 2;

	if (p2 != -1) {
		hairetu[p2] = hairetu[p1];
		hairetu[p1] = 0;
	}

}

//�V�[�����X�V����
void UpdateScene() {
	DrawString(0, 20, "G�L�[�ŃQ�[����ʁAC�L�[�Őݒ�AM�L�[�Ń��j���[��ʂɂȂ�܂��B", GetColor(255, 255, 255));
	if (CheckHitKey(KEY_INPUT_G) != 0) {
		Scene = eScene_Game;
	}
	if (CheckHitKey(KEY_INPUT_C) != 0) {
		Scene = eScene_Config;
	}
	if (CheckHitKey(KEY_INPUT_M) != 0) {
		Scene = eScene_Menu;
	}
}

//���j���[���
void Menu() {
	DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
}

//�Q�[�����
void Game() {
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(0, 0, 0));

	int SetBackgroundColor(int Red, int Green, int Blue);

	SetBackgroundColor(255, 255, 255);
	Mouse = GetMouseInput();
	GetMousePoint(&x, &y);
	for(int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			if (x > (j * 240) && x< (j * 240) + 240 && y>(i * 240) && y <(i * 240) + 240) {
				if (Mouse & MOUSE_INPUT_LEFT) {
					DrawString(500, 0, "abe�ł��B", GetColor(0, 0, 0));
					irekae(x / 240, y / 240);
				}
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DrawGraph(j*240, i*240, gazou[hairetu[(i*2)+j]], TRUE);
		}
	}
}

//�ݒ���
void Config() {
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	
	gazou[0] = LoadGraph("�摜/black.png");
	gazou[3] = LoadGraph("�摜/red.png");
	gazou[1] = LoadGraph("�摜/blue.png");
	gazou[2] = LoadGraph("�摜/sentokunn.png");

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//���݂̃V�[���ɂ���������������
		case eScene_Menu://���݂̃V�[�������j���[�Ȃ�
			Menu();//���j���[���
			break;
		case eScene_Game://���݂̃V�[�����Q�[���Ȃ�
			Game();//�Q�[�����
			break;
		case eScene_Config://���݂̃V�[�����ݒ�Ȃ�
			Config();//�ݒ���
			break;
		}

		UpdateScene();//�V�[�����X�V����

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}