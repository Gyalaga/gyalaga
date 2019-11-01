#include "DxLib.h"
#include<math.h>

#define PAI 3.14
#define ZAKOX 400;
#define ZAKOY 200;

static int mStartTime;	//����J�n����
static int mCount;	//�J�E���^
static float mFps;	//fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���
} eScene;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)

struct Enemy {
	int zako[5];	//�U�R�̉摜�i�[�p�̕ϐ�
	int goei[5];	//�S�G�C�̉摜�i�[�p�̕ϐ�
	int boss[10];	//�{�X�M�����K�̉摜�i�[�p�̕ϐ�
	int Image[50];	//�G�L�����̉摜�������̊i�[�p�̕ϐ�
	int zakoX[20];	//�U�R��X���W	
	int zakoY[20];	//�U�R��Y���W
	int goeiX[16];	//�S�G�C��X���W
	int goeiY[16];	//�S�G�C��Y���W
	int bossX[4];	//�{�X�M�����K��X���W
	int bossY[4];	//�{�X�M�����K��Y���W
	int all;		//�G�S�̂̓����p
	int speed;		//�G�̈ړ���
};

struct Enemy enemy;

bool Update() {
	if (mCount == 0) {	//�P�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) {	//60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f/((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0) {
		Sleep(waitTime);
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
	int Green = GetColor(0, 255, 0); //�F�̐ݒ�
	int timecnt = 0;	//60�t���[���J�E���g
	int graphflg = 0;

	LoadDivGraph("�摜/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemy.Image);	//�G�L������enemy.Image�ɒǉ�

	//�e�G�L�����z��Ɋi�[
	for (int i = 0; i < 10; i++) {
		if (i < 5) {
			enemy.zako[i] = enemy.Image[i];
			enemy.goei[i] = enemy.Image[i + 5];
		}
		enemy.boss[i] = enemy.Image[i + 10];
	}
	//�e�L�����̑��񎞂̏������W
	for (int i = 0; i < 10; i++) {
		enemy.zakoX[i] = 100 + i * 50;
		enemy.zakoX[i + 10] = 100 + i * 50;
		enemy.zakoY[i] = 200;
		enemy.zakoY[i + 10] = 250;
		if (i < 8) {
			enemy.goeiX[i] = 150 + i * 50;
			enemy.goeiY[i] = 150;
			enemy.goeiX[i + 8] = 150 + i * 50;
			enemy.goeiY[i + 8] = 100;
		}
		if (i < 4) {
			enemy.bossX[i] = 250 + i * 50;
			enemy.bossY[i] = 50;
		}
	}

	enemy.all = 0;	//����̏������W

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Update();

		//FPS�̕\��
		DrawFormatString(800, 0, Green, "FPS %.1f", mFps);
		DrawFormatString(800, 50, Green,"all %d\nzako %d\ngoei %d\nboss %d\nflg %d\n",enemy.all,enemy.zakoX[0],enemy.goeiX[0],enemy.bossX[0],graphflg);

		//�ړ��ҋ@����(�؂�ւ���)
		if (timecnt == 0) {
			graphflg = 0;
		}
		else if (timecnt == 60) {
			graphflg = 1;
			if (enemy.all <= 0) {
				enemy.speed = 10;
			}
			else if (enemy.all >= 100) {
				enemy.speed = -10;
			}
			//����̓���
			for (int i = 0; i < 20; i++) {
				enemy.zakoX[i] += enemy.speed;
				if (i < 16) {
					enemy.goeiX[i] += enemy.speed;
				}
				if (i < 4) {
					enemy.bossX[i] += enemy.speed;
				}
			}
			enemy.all += enemy.speed;
		}
		timecnt++;
		if (timecnt > 120)timecnt = 0;

		for (int i = 0; i < 10; i++) {
			//graphflg��0�̂Ƃ�1���ڂ̉摜��\��
			if (graphflg == 0) {
				DrawRotaGraph(enemy.zakoX[i], enemy.zakoY[i], 2.0f, 0, enemy.zako[0], TRUE);
				DrawRotaGraph(enemy.zakoX[i + 10], enemy.zakoY[i + 10], 2.0f, 0, enemy.zako[0], TRUE);
				if (i < 8) {
					DrawRotaGraph(enemy.goeiX[i], enemy.goeiY[i], 2.0f, 0, enemy.goei[0], TRUE);
					DrawRotaGraph(enemy.goeiX[i + 8], enemy.goeiY[i + 8], 2.0f, 0, enemy.goei[0], TRUE);
				}
				if (i < 4) {
					DrawRotaGraph(enemy.bossX[i], enemy.bossY[i], 2.0f, 0, enemy.boss[0], TRUE);
				}
			}
			//graphflg��1�̂Ƃ�2���ڂ̉摜��\��
			else if (graphflg == 1) {
				DrawRotaGraph(enemy.zakoX[i], enemy.zakoY[i], 2.0f, 0, enemy.zako[1], TRUE);
				DrawRotaGraph(enemy.zakoX[i + 10], enemy.zakoY[i + 10], 2.0f, 0, enemy.zako[1], TRUE);
				if (i < 8) {
					DrawRotaGraph(enemy.goeiX[i], enemy.goeiY[i], 2.0f, 0, enemy.goei[1], TRUE);
					DrawRotaGraph(enemy.goeiX[i + 8], enemy.goeiY[i + 8], 2.0f, 0, enemy.goei[1], TRUE);
				}
				if (i < 4) {
					DrawRotaGraph(enemy.bossX[i], enemy.bossY[i], 2.0f, 0, enemy.boss[1], TRUE);
				}
			}
		}
		Wait();
	}
}

//�ݒ���
void Config() {
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SetGraphMode(1100, 800, 32);

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