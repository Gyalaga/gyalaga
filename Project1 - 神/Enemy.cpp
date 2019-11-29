#include <math.h>
#include "DxLib.h"
#include "Enemy.h"
#include "Player.h"
#define PI 3.14	//�~����
#define ENEMYSPEED 2	//�G�̈ړ����x

//�G�l�~�[�̍X�V
void Enemy_Update() {

	static int tmppx = 0;
	static int tmppy = 0;
	static float tmpex = 0;
	static float tmpey = 0;
	static int dangle = 0;	//�����]���ɕK�v�Ȋp�x
	static int rangle = 0;	//��]�ɕK�v�Ȋp�x
	static double rad;	//���W�A���l
	static double rad02;	//���W�A���l
	static double rad03;	//���W�A���l
	static double rad04;	//���W�A���l
	static bool settmp = true;
	static bool direction = false;	//�����]��flg
	static bool move = false;
	static bool rotation = false;
	static bool back = false;
	static bool backx = false;
	static bool backy = false;

	//Enemy�̏�����
	if (enemyinit == true) {

		Enemy_Init();
		enemyinit = false;
	}

	if (CheckHitKey(KEY_INPUT_TAB) != 0) {
		zako[0].atk = true;
	}

	for (int i = 0; i < 20; i++) {

		//zako[i].atk��true�̏ꍇ
		if (zako[i].atk == true) {

			//�U�R�̍U���ɕK�v�ȕϐ��̏�����
			if (settmp == true) {
				tmppx = playerX;
				tmppy = playerY;
				tmpex = zako[i].x;
				tmpey = zako[i].y;
				dangle = 360;
				direction = true;
				settmp = false;
			}

			//�G�̂ق��ւ̕����]��
			if (direction == true) {

				rad = dangle * PI / 180;	//���W�A���ϊ�

				zako[i].x = tmpex + 40 * cos(rad);
				zako[i].y = tmpey + 40 * sin(rad);

				//180����]�����Ƃ����̓����Ɉڂ�
				if (dangle < 180) {
					direction = false;
					move = true;
				}

				dangle -= ENEMYSPEED;	//�p�x�̌���
			}

			if (move == true) {

				rad02 = atan2((double)tmppy - zako[i].y, ((double)tmppx + 40) - zako[i].x);

				if (zako[i].y >= tmppy) {

					move = false;
					rotation = true;
				}
				else {

					zako[i].x += ENEMYSPEED * cos(rad02);
					zako[i].y += ENEMYSPEED * sin(rad02);
				}
				DrawString(200, 150, "���j���[��ʂł�", GetColor(255, 255, 255));
			}

			if (rotation == true) {

				rad03 = rangle * PI / 180;

				zako[i].x = tmppx + 40 * cos(rad03);
				zako[i].y = tmppy + 40 * sin(rad03);

				if (rangle >= 150) {
					rotation = false;
					back = true;
				}

				rangle += ENEMYSPEED;

			}

			if (back == true) {

				rad04 = atan2((double)tmpey - zako[i].y, (double)tmpex - zako[i].x);

				if (zako[i].y < tmpey) {
					back = false;
					zako[i].atk = false;
					zako[i].x = tmpex;
					zako[i].y = tmpey;
				}
				else {
					zako[i].x += ENEMYSPEED * cos(rad04);
					zako[i].y += ENEMYSPEED * sin(rad04);
				}

				/********************************************** //A��
				if (zako[i].x < tmpex && zako[i].y < tmppy) {
					back = false;
					zako[i].atk = false;
				}
				else {
					zako[i].x += ENEMYSPEED * cos(rad04);
					zako[i].y += ENEMYSPEED * sin(rad04);
				}
				*/
			}


		}
	}
	DrawFormatString(800, 0, GetColor(255, 255, 255), "px %d\n py %d\n ex %f\n ey %f", tmppx, tmppy, zako[0].x, zako[0].y);
}

//�G�l�~�[�̕`��
void Enemy_Draw() {

	for (int i = 0; i < 20; i++) {

		DrawRotaGraph((int)zako[i].x, (int)zako[i].y, 2.0f, 0, zako[i].image, TRUE);	//�U�R�̕`��
		if (i < 16) {

			DrawRotaGraph(goei[i].x, goei[i].y, 2.0f, 0, goei[i].image, TRUE);	//�S�G�C�̕`��
		}
		if (i < 4) {
			DrawRotaGraph(boss[i].x, boss[i].y, 2.0f, 0, boss[i].image, TRUE);	//�{�X�M�����K�̕`��

		}
	}
}

//�G�l�~�[�̏�����
void Enemy_Init() {

	LoadDivGraph("�摜/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemyImage);	//�G�L������enemy.Image�ɒǉ�

	//�U�R�̏������W
	for (int i = 0; i < 10; i++) {
		zako[i].x = 100 + i * 50;
		zako[i].y = 250;
		zako[i + 10].x = 100 + i * 50;
		zako[i + 10].y = 200;
		zako[i].image = enemyImage[0];
		zako[i + 10].image = enemyImage[0];
		zako[i].atk = false;
		zako[i + 10].atk = false;
	}

	//�S�G�C�̏������W
	for (int i = 0; i < 8; i++) {
		goei[i].x = 150 + i * 50;
		goei[i].y = 150;
		goei[i + 8].x = 150 + i * 50;
		goei[i + 8].y = 100;
		goei[i].image = enemyImage[5];
		goei[i + 8].image = enemyImage[5];
	}

	//�{�X�M�����K�̏������W
	for (int i = 0; i < 4; i++) {
		boss[i].x = 250 + i * 50;
		boss[i].y = 50;
		boss[i].image = enemyImage[10];
	}
}

void Load_Player(int lpx, int lpy) {
	playerX = lpx;
	playerY = lpy;
}

void Enemy_all()
{
	Enemy_Update();
	Enemy_Draw();
}