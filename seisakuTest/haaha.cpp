#include "DxLib.h"
#define PI 3.141592654
#define WIDTH 120
#define HIGHT 90
#define STARTx 50
#define STARTy 320
#define STARTw 200
#define STARTh 130

int hairetu[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Lol,     //����
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���

} eScene;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)

void irekae(int px, int py) {
	int p1 = (py * 4) + px;
	int p2 = -1;
	if (px > 0 && hairetu[p1 - 1] == 15)p2 = p1 - 1;
	if (px < 3 && hairetu[p1 + 1] == 15)p2 = p1 + 1;
	if (py > 0 && hairetu[p1 - 4] == 15)p2 = p1 - 4;
	if (py < 3 && hairetu[p1 + 4] == 15)p2 = p1 + 4;

	if (p2 != -1) {
		hairetu[p2] = hairetu[p1];
		hairetu[p1] = 15;
	}

}

//�V�[�����X�V����
void UpdateScene() {
	//DrawString(0, 20, "G�L�[�ŃQ�[����ʁAC�L�[�Őݒ�AM�L�[�Ń��j���[��ʂɂȂ�܂��B", GetColor(255, 255, 255));

}

//���j���[���
void Menu() {
	//DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
	int Title = LoadGraph("�摜/title.jpg");
	int Start = LoadGraph("�摜/kaisi.png");
	int End = LoadGraph("�摜/owari.png");
	int Neko = LoadGraph("�摜/nekoneko.png");
	DrawGraph(0, 0, Title, TRUE); //�^�C�g����`��
	DrawGraph(300, 25, Neko, TRUE); //�L��`��
	DrawGraph(STARTx, STARTy, Start, TRUE); // �w�i��`��
	DrawGraph(STARTx + 300, STARTy, End, TRUE); // �w�i��`��

	int Mouse;
	Mouse = GetMouseInput();
	DrawString(0, 20, "���N���b�N�ŃQ�[����ʁA�E�N���b�N�ŏI���A", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Lol;
		}
		if (mouseX >= STARTx + 300 && mouseX < (STARTx + 300 + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			//int mouseX, mouseY;
			DxLib_End(); // DX���C�u�����I������
		}
	}
	//if (Mouse & MOUSE_INPUT_RIGHT) {
	//	DxLib_End(); // DX���C�u�����I������
	//}
}
//�������
void Lol() {
	int bg = LoadGraph("�摜/game.jpg");
	int setumei = LoadGraph("�摜/pop.png");

	DrawGraph(0, 0, bg, TRUE); //�w�i
	DrawGraph(0, 0, setumei, TRUE); //����pop

	DrawString(0, 0, "�G���^�[�L�[�������ăQ�[���J�n�I", GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		Scene = eScene_Game;
	}
}
//�Q�[�����
void Game() {
	int nx = 30; int ny = 100;
	int x, y;
	int timelimit;
	int image[16];
	LONGLONG timecnt;

	int haikei = LoadGraph("�摜/haikei.png");
	int waku = LoadGraph("�摜/waku.png");
	LoadDivGraph("�摜/neko2.png", 16, 4, 4, WIDTH, HIGHT, image); // �摜�̕����ǂݍ���

	SetAlwaysRunFlag(TRUE);						//��A�N�e�B�u�ł��������s��

	timecnt = GetNowHiPerformanceCount();

	timelimit = 60000000;
	timecnt = GetNowHiPerformanceCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClsDrawScreen();			//��ʂɕ`����Ă�����̂����S������

		SetFontSize(20);
		SetFontThickness(8);                         //������8�ɕύX
		DrawGraph(0, 0, haikei, TRUE); // �w�i��`��
		DrawGraph(nx - 10, ny - 10, waku, FALSE); // �w�i��`��
		DrawString(0, 0, "�Q�[����ʂł��B", GetColor(0, 0, 0));
		DrawString(0, 25, "SPACE�L�[�@���@�ݒ��ʁ@", GetColor(0, 0, 0));

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (hairetu[(i * 4) + j] != 15) {
					DrawGraph(nx + (j * WIDTH), ny + (i * HIGHT), image[hairetu[(i * 4) + j]], TRUE);
				}
			}
		}

		int Mouse = GetMouseInput();
		GetMousePoint(&x, &y);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (x > j * WIDTH && x< j * WIDTH + WIDTH && y> i * HIGHT && y < i * HIGHT + HIGHT) {
					if (Mouse & MOUSE_INPUT_LEFT) {
						irekae(x / WIDTH, y / HIGHT);
					}
				}
			}
		}
		//��������
		if (GetNowHiPerformanceCount() - timecnt >= 10000) {
			timecnt = GetNowHiPerformanceCount();
			timelimit -= 10000;
		}
		//�������ԕ\��
		SetFontSize(36);                             //�T�C�Y��64�ɕύX
		SetFontThickness(8);                         //������8�ɕύX
		ChangeFont("�l�r ����");                     //��ނ�MS�����ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);     //�A���`�G�C���A�X�t�H���g�ɕύX

		DrawFormatString(475, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timelimit / 60000000, (timelimit % 60000000) / 1000000, ((timelimit % 60000000) % 1000000) / 100000, (((timelimit % 60000000) % 1000000) % 100000) / 10000);

		ScreenFlip();				//����ʂ̓��e��\��ʂɔ��f������
	}
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
		Scene = eScene_Config;
	}
}

//�ݒ���
void Config() {
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 25, "ENTER�L�[ ���@�Q�[�����", GetColor(255, 255, 255));
	int sceneflg = 0;
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		Scene = eScene_Game;
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SetGraphMode(800, 800, 32);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//���݂̃V�[���ɂ���������������
		case eScene_Menu://���݂̃V�[�������j���[�Ȃ�
			Menu();//���j���[���
			break;
		case eScene_Lol://���݂̃V�[�������[���Ȃ�
			Lol();//���[�����
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