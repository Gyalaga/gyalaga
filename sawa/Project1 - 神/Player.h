#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PI 3.14    // �p�x���߂�̂Ɏg�p
#define SHOT 2     // �e�̍ő吔

typedef struct
{
	int x[16] = { 400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400 };
	int y[16] = { 700,700,700,700,700,700,700,700,700,700,700,700,700,700,700,700 };
	int	rote = 0, size = 2, w = 16;            // rote:���@�p�x,  size:���@�T�C�Y, w:����
	int	r = 16 * size / 2, image[2];           // r:���S, iamge:�摜�ϐ�
	int HP = 3, i = 0, score = 0;              // HP:�̗�, i:����ԍ�, score:�X�R�A
	int HP_plus = 0, HP_minus = 0;             // HP_plus:�c�@���Ɏg�p, HP_minus:�c�@���Ɏg�p
	int judgment = 0;                          // judgment:���̓����蔻��Əd�Ȃ�Ȃ��悤�ɂ���t���O
	int dualbreak =0;
	int keyflg = 0;

	bool flg_i = true;                         // flg_i:�\���p�t���O1
	bool flg_j = true;                         // flg_j:�\���p�t���O2
	bool escape = false;                       // �g���N�^�[�r�[������̒E�o�ɐ���
	bool player_recapture = false;             // �D��
	bool dualmode = false;                     // ���[�h�f���A��
}Player;// Player�̍\����	

typedef struct//HIO4�S��
{
	int shot;                    
	int Simage[10];                            // �e�̉摜
	int sx[SHOT], sy[SHOT];                    // �e�̍��W
	int	sx2[SHOT], sy2[SHOT];                  // �f���A�����[�h���̒e�̍��W
	int sw = 7, sh = 12;                       // �e�̏c��,����
	int sr = sw / 2;                           // �e�̒��S
	int sf[SHOT];                              // �e�̔��˃t���O
	int sf2;
	int j;
}Shot;// Shot�̍\����

typedef struct
{ 
	int x = 300, y = 600;                      // �G�̍��W
	int x2 = 600, y2 = 700;                    // �G�̍��W
	bool flg2 = true;                          // flg:�\���t���O
	int r = 14 * 2 / 2, enemy[50];             // �摜�ϐ�
	int player_capture = 0;                    // �����̎��@
	int alter_x, alter_y;                      // �G���@�p
	int s = 1,rote = 0;                        // s:�G�X�s�[�h, rote; �G���@�p�x

	bool Defeat = false;                       // �j��
	bool flg = true;                           // flg:�\���t���O
	bool sflg = true;                          // ���E�ړ�[false=�� || true=�E]
	bool move_flg = false;                     // �G�ړ��t���O
}Enemy;// Enemy�̍\����(��ňꕔ�c���ď����\��)

typedef struct
{
	int image[12];                             // �r�[���̉摜
	int x = 0, y = 0;                          // ���W
	int i = 0, tmp = 0;                        // i:�摜�񂵗p, tmp:�摜�ԍ��L�^�p
	int bllmcnt = 0, cnt = 0;                  // bllmcnt:�r�[�����˃J�E���g, cnt:�A�j���[�V�����̑���
	int ani[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,11,10,11,10,11,10,9,8,7,6,5,4,3,2,1,0 };
	int t_i = 0, t_j = 0;                      // �J�E���g�p

	bool x_match = false;                      // ���W���킹�p
	bool flg = false;                          // �\���t���O
}Bllm;//�g���N�^�[�r�[���̍\����

typedef struct
{
	int i = 0, j = 0;                          // i:���j�G�t�F�N�g�̑���, j:�\��
	int image[13];                             // �摜�ϐ��p

	bool flg = false;                          // �\���t���O
	bool flg2 = false;                          // �\���t���O
}Bom;//���j�A�j���[�V�����̍\����


static int color = GetColor(255, 255, 255);    // keyflg:���͋��ۗp�@�F�R�[�h���擾


static Player p;            // Player�̍\����
static Shot s;              // Shot�̍\����
static Enemy e;             // Enemy�̍\����(��ňꕔ�c���ď����\��)
static Bllm b;              //�g���N�^�[�r�[���̍\����
static Bom B;               //���j�A�j���[�V�����̍\����

void Player_Init();         //�����ݒ�

void Player_Setup();        //�ݒ�

void Player_Draw();         //�\��

void Player_Move();         //����

void Player_Shot();         //�e

void Player_Animation();    //�A�j���[�V����

void Player_Hit();          //�����蔻��

void Player_All();          //�Ăяo��

void Player_Enemy();        //�G(�����\��)

#endif // !_PLAYER_H_




