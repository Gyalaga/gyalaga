#ifndef _ENEMY_H_
#define _ENEMY_H_

//�U�R�̍\����
typedef struct {
	int x;			//x���W
	int y;			//y���W
	int cx;			//���S��x���W
	int cy;			//���S��y���W
	int image[5];	//�摜�i�[�p
	bool atk;		//�U���t���O
	bool onActive;	//�\���t���O
}ENEMY_ZAKO;

//�S�G�C�̍\����
typedef struct {
	int x;			//x���W
	int y;			//y���W
	int cx;			//���S��x���W
	int cy;			//���S��y���W
	int image[5];	//�摜�i�[�p
	bool atk;		//�U���t���O
	bool onActive;	//�\���t���O
}ENEMY_GOEI;

//�{�X�M�����K�̍\����

typedef struct {
	int x;			//x���W
	int y;			//y���W
	int cx;			//���S��x���W
	int cy;			//���S��y���W
	int image[10];	//�摜�i�[�p
	bool atk;		//�U���t���O
	bool onActive;	//�\���t���O
}ENEMY_BOSS;

static int enemyImage[50];		//�Senemy�̉摜���i�[
static ENEMY_ZAKO zako[20];		//�U�R�̃��R�[�h
static ENEMY_GOEI goei[18];		//�S�G�C�̃��R�[�h
static ENEMY_BOSS boss[4];		//�{�X�M�����K�̃��R�[�h
static bool enemyInit = true;			//�G�l�~�[�̏������t���O

//enemy�̍X�V
extern void Enemy_Update();

//�U�R�̍U�����̏���
bool Enemy_Zako(int zakoAtk);

//�S�G�C�̍U�����̏���
bool Enemy_Goei(int goeiAtk);

//�{�X�M�����K�̍U�����̏���
bool Enemy_Boss(int bossAtk);

//enemy�̕`��
extern void Enemy_Draw();

//enemy�̏�����
extern void Enemy_Init();

//���폜�\��
void Enemy_all();

#endif // !_ENEMY_H_
