#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "DxLib.h"
#include "Enemy.h"

#define PI			3.14	//�~����
#define ENEMYSPEED	2		//�G�̈ړ����x



/*
�֐���		:Enemy_all
�����̊T�v	:�G�l�~�[�̏����̑S��
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:�啝�ɋL�q��ύX����ۂɍ폜�\��
*/

void Enemy_all() {

	//enemy�̏�����
	if (enemyInit == true) {
		Enemy_Init();
		enemyInit = false;
	}

	Enemy_Update();		//enemy�̍X�V

	Enemy_Draw();		//enemy�̕`��
}

/*
�֐���		:Enemy_Update
�����̊T�v	:�G�l�~�[�̍X�V
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:�Ȃ�
*/

void Enemy_Update() {

	//DrawString(0, 450, "Enemy_Update������ɉғ����܂���", GetColor(255, 255, 255));

	static bool zakoAllAtk = false;		//�U�R���U�����Ă邩����t���O
	static bool goeiAllAtk = false;		//�S�G�C���U�����Ă邩����t���O
	static bool bossAllAtk = false;		//�{�X�M�����K���U�����Ă邩����t���O

	srand((unsigned)time(NULL));		//�������Œ�l�ɂ��Ȃ����߂�

	//�U���t���O��true�̎��A���ꂼ��̊֐���
	for (int i = 0; i < 20; i++) {

		//�U�R�̍U���t���O��true�̎��U�R�̍U���������s���A����t���O��true��
		if (zako[i].atk == true) {

			zakoAllAtk = Enemy_Zako(i);
		}
		//�S�G�C�̍U���t���O��true�̎��S�G�C�̍U���������s���A����t���O��true��
		if (i < 16 && goei[i].atk == true) {

			goeiAllAtk = Enemy_Goei(i);
		}
		//�{�X�M�����K�̍U���t���O��ture�̎��{�X�M�����K�̍U���������s���A����t���O��true��
		if (i < 4 && boss[i].atk == true) {

			Enemy_Boss(i);

			bossAllAtk = true;
		}
	}

	//zakoAllAtk��false�̎��U�R�̍U�������true�ɂ���
	for (int i = 0; i < 10; i++) {
		
		//zakoAllAtk��false����zako[i].onAcitve��true�̎�zako[0�`9]�̍U���t���O��true�ɂ���
		if (zakoAllAtk == false && zako[i].onActive == true) {
			zako[rand() % 10].atk = true;
			break;
		}
		//zako[i].onActive��false����i��9�����̎�continue����
		else if (zako[i].onActive == false && i < 9) {
			continue;
		}
		//i��9�܂�continue���ꂽ�Ƃ���zako[10�`19]�̍U���t���O��ture�ɂ���
		else if(zakoAllAtk == false){

			zako[rand() % 10 + 10].atk = true;
		}
	}

	goei[8].atk = true;
	boss[0].atk = true;
}

/*
�֐���		:Enemy_Zako
�����̊T�v	:�U�R�̍U�����̏���
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:true or false
*/

bool Enemy_Zako(int zakoAtk) {
	
	static int test_Zvy = ENEMYSPEED;

	//DrawString(0, 500, "Enemy_Zako������ɉғ����܂���", GetColor(255, 255, 255));

	if (zako[zakoAtk].y < 250) {
		test_Zvy = ENEMYSPEED;
	}

	if (zako[zakoAtk].y > 750) {
		test_Zvy = -ENEMYSPEED;
	}

	zako[zakoAtk].y += test_Zvy;

	return true;
}

/*
�֐���		:Enemy_Goei
�����̊T�v	:�S�G�C�̍U�����̏���
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:true or false
*/

bool Enemy_Goei(int goeiAtk) {

	//DrawString(0, 550, "Enemy_Goei������ɉғ����܂���", GetColor(255, 255, 255));

	static int test_Gvy = ENEMYSPEED;

	if (goei[goeiAtk].y > 800) {
		goei[goeiAtk].y = -30;
	}

	goei[goeiAtk].y += test_Gvy;

	return true;
}

/*
�֐���		:Enemy_Boss
�����̊T�v	:�{�X�M�����K�̍U�����̏���
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:true or false
*/

bool Enemy_Boss(int bossAtk) {

	//DrawString(0, 600, "Enemy_Boss������ɉғ����܂���", GetColor(255, 255, 255));

	return true;
}

/*
�֐���		:Enemy_Draw
�����̊T�v	:enemy�̕`��
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:�Ȃ�
*/

void Enemy_Draw() {

	//DrawString(0, 400, "Enemy_Draw������ɉғ����Ă��܂�", GetColor(255, 255, 255));

	for (int i = 0; i < 20; i++) {

		//�U�R�̕`��
		if (zako[i].onActive == true) {
			
			DrawRotaGraph(zako[i].x, zako[i].y, 2.0f, 0, zako[i].image[0], TRUE);
		}

		//�S�G�C�̕`��
		if (i < 16 && goei[i].onActive == true) {

			DrawRotaGraph(goei[i].x, goei[i].y, 2.0f, 0, goei[i].image[0], TRUE);
		}

		//�{�X�M�����K�̕`��
		if (i < 4 && boss[i].onActive == true) {

			DrawRotaGraph(boss[i].x, boss[i].y, 2.0f, 0, boss[i].image[0], TRUE);

		}
	}
}

/*
�֐���		:Enemy_Init
�����̊T�v	:enemy�̏�����
����		:�Ȃ�
�ԋp�l		:�Ȃ�
���l		:�Ȃ�
*/

void Enemy_Init() {

	static int zakoInterval;	//�U�R�̊Ԋu
	static int goeiInterval;	//�S�G�C�̊Ԋu
	static int bossInterval;	//�{�X�M�����K�̊Ԋu

	LoadDivGraph("�摜/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemyImage);	//�G�L������enemy.Image�ɒǉ�

	//�����������S��
	for (int i = 0; i < 20; i++) {

		//�U�R�̊Ԋu�̌v�Z��y���W�̏�����
		if (i < 10) {

			zakoInterval = i * 35;
			zako[i].y = 250;
		}
		else {

			zakoInterval = (i - 10) * 35;
			zako[i].y = 200;
		}

		zako[i].x = 225 + zakoInterval;		//�U�R��x���W�̏�����
		zako[i].atk = false;				//�U�R�̍U���t���O�̏�����
		zako[i].onActive = true;			//�U�R�̕\���t���O�̏�����

		//�摜��S�̂���ʂ�
		for (int j = 0; j < 5; j++) {
			zako[i].image[j] = enemyImage[0 + j];
		}

		//�S�G�C�̏�����
		if (i < 18) {

			//�S�G�C�̊Ԋu�̌v�Z��y���W�̏�����
			if (i < 8) {

				goeiInterval = i * 35;
				goei[i].y = 150;
			}
			else {

				goeiInterval = (i - 8) * 35;
				goei[i].y = 100;
			}

			goei[i].x = 260 + goeiInterval;		//�S�G�C��x���W�̏�����
			goei[i].atk = false;				//�S�G�C�̍U���t���O�̏�����
			goei[i].onActive = true;			//�S�G�C�̕\���t���O�̏�����

			//�摜��S�̂���ʂ�
			for (int j = 0; j < 5; j++) {
				goei[i].image[j] = enemyImage[5 + j];
			}
		}

		//�{�X�M�����K�̏�����
		if (i < 4) {

			bossInterval = i * 35;				//�{�X�M�����K�̊Ԋu�̌v�Z
			boss[i].y = 50;						//�{�X�M�����K��y���W�̏�����
			boss[i].x = 330 + bossInterval;		//�{�X�M�����K��x���W�̏�����
			boss[i].atk = false;				//�{�X�M�����K�̍U���t���O�̏�����
			boss[i].onActive = true;			//�{�X�M�����K�̕\���t���O�̏�����

			//�摜��S�̂���ʂ�
			for (int j = 0; j < 10; j++) {
				boss[i].image[j] = enemyImage[10 + j];
			}
		}
	}
}