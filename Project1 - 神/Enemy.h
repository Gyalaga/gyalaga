#pragma once

//�U�R�̍\����
typedef struct {
	float x;
	float y;
	int cx;
	int cy;
	int image;
	bool atk;
}ENEMY_ZAKO;

//�S�G�C�̍\����
typedef struct {
	int x;
	int y;
	int cx;
	int cy;
	int image;
}ENEMY_GOEI;

//�{�X�M�����K�̍\����
typedef struct {
	int x;
	int y;
	int cx;
	int cy;
	int image;
}ENEMY_BOSS;

static int enemyImage[50];		//�S�G�l�~�[�̉摜���i�[����ϐ�
static ENEMY_ZAKO zako[20];		//�U�R�̍\���̂�z���
static ENEMY_GOEI goei[18];		//�S�G�C�̍\���̂�z���
static ENEMY_BOSS boss[4];		//�{�X�M�����K�̍\���̂�z���
static bool enemyinit = true;	//�G�l�~�[�̏������pflg
static int playerX;
static int playerY;

//�G�l�~�[�̍X�V
void Enemy_Update();

//�G�l�~�[�̕`��
void Enemy_Draw();

//�G�l�~�[�̏�����
void Enemy_Init();

//�v���C���[���W�̎擾
void Load_Player(int, int);

void Enemy_all();
