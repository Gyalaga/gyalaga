#include"DxLib.h"
#include "windows.h"
#include "bgm.h"
#include"bg.h"
#include"Game.h"
#define SHOT 2


// �L�[����
int key[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���


void Keysecond() {

	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++) {
		if (buf[i]) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				if (key[i] == 0) {
					SE_draw();
					key[i] = 1;
				}
			}
			else if (key[i] == 1) key[i] = 2;
		}
		else key[i] = 0;
	}
}

void Key_draw() {

	int px = 0, py = 500, ph = 16, pw = 16, image[32]; //���@�̍��W�Ɖ摜�ϐ��ł�������
	int pi = 0, pj = 0, ps = 0;                      //pi:���@�摜�̉�]�p,pj:����]���邩,ps:��]���x
	int keyflg = 0, HP = 3;                          //keyflg:���͋��ۗp,HP:�̗�
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //�G�̍��W�Ɖ摜�ϐ��ł�������
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:���j�G�t�F�N�g�̑���,bj:�\��,�摜�ϐ��p
	int color = GetColor(255, 255, 255);             //�F�R�[�h���擾
	static int shot = LoadGraph("bullet.png");

	int sx[SHOT], sy[SHOT],
		sx2[SHOT], sy2[SHOT], sw = 9, sh = 12, i;      //�e�̍��W
	int sf[SHOT];                                    //�e�̔��˃t���O
	int sf2;

	//�e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ���
	//�u���݂��Ă��Ȃ��v���Ӗ�����0�������Ă���
	for (i = 0; i < SHOT; i++) {
		sf[i] = 0;
	}

	//�V���b�g�{�^����O�̃t���[���ŉ����ꂽ���ǂ�����ێ�����
	//�ϐ���0�i������Ă��Ȃ��j����
	sf2 = 0;

	//�X�y�[�X�������ꂽ��e��ł�
	if (CheckHitKey(KEY_INPUT_SPACE)) {

		//�O�̃t���[���ŃV���b�g�{�^��������������
		//�ۑ�����Ă���ϐ���0��������e�𔭎�
		if (sf2 == 0) {

			//��ʏ�ɏo�ĂȂ��e�����邩�A�e�̐���������Ԃ����ׂ�
			for (i = 0; i < SHOT; i++) {

				
				//�e����ʏ�ɏo�ĂȂ��ꍇ�͂��̒e����ʂɏo��
				if (sf[i] == 0) {

					//�e�̈ʒu���Z�b�g�A�ʒu�͎��@�̒��S�ɂ���
					sx[i] = (pw - sw) / 2 + px;
					sy[i] = (ph - sh) / 2 + py;
					sx2[i] = (pw - sw) / 2 + px + 20;
					sy2[i] = (ph - sh) / 2 + py;

					//�e�͌����_�ő��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���1��������
					sf[i] = 1;

					//�e��1�o�����̂Ń��[�v���甲���o��
					break;

				}
				

			}			
		}
		//�O�̃t���[���ŃV���b�g�{�^����������Ă�������
		//�ێ�����ϐ���1�i������Ă����j��������
		sf2 = 1;
	}
	else {

		//�O�̃t���[���ŃV���b�g�{�^����������Ă��Ȃ������ꍇ��
		//�V���b�g�{�^����������Ă�������
		//�ێ�����ϐ���0�i������Ă��Ȃ��j��������
		sf2 = 0;

	}
}

void Key_ALL() {

	Keysecond();
	Key_draw();
	//bg_All();
}