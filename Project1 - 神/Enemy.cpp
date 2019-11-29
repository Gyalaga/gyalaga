#include <math.h>
#include "DxLib.h"
#include "Enemy.h"
#include "Player.h"
#define PI 3.14	//円周率
#define ENEMYSPEED 2	//敵の移動速度

//エネミーの更新
void Enemy_Update() {

	static int tmppx = 0;
	static int tmppy = 0;
	static float tmpex = 0;
	static float tmpey = 0;
	static int dangle = 0;	//方向転換に必要な角度
	static int rangle = 0;	//回転に必要な角度
	static double rad;	//ラジアン値
	static double rad02;	//ラジアン値
	static double rad03;	//ラジアン値
	static double rad04;	//ラジアン値
	static bool settmp = true;
	static bool direction = false;	//方向転換flg
	static bool move = false;
	static bool rotation = false;
	static bool back = false;
	static bool backx = false;
	static bool backy = false;

	//Enemyの初期化
	if (enemyinit == true) {

		Enemy_Init();
		enemyinit = false;
	}

	if (CheckHitKey(KEY_INPUT_TAB) != 0) {
		zako[0].atk = true;
	}

	for (int i = 0; i < 20; i++) {

		//zako[i].atkがtrueの場合
		if (zako[i].atk == true) {

			//ザコの攻撃に必要な変数の初期化
			if (settmp == true) {
				tmppx = playerX;
				tmppy = playerY;
				tmpex = zako[i].x;
				tmpey = zako[i].y;
				dangle = 360;
				direction = true;
				settmp = false;
			}

			//敵のほうへの方向転換
			if (direction == true) {

				rad = dangle * PI / 180;	//ラジアン変換

				zako[i].x = tmpex + 40 * cos(rad);
				zako[i].y = tmpey + 40 * sin(rad);

				//180°回転したとき次の動きに移す
				if (dangle < 180) {
					direction = false;
					move = true;
				}

				dangle -= ENEMYSPEED;	//角度の減少
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
				DrawString(200, 150, "メニュー画面です", GetColor(255, 255, 255));
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

				/********************************************** //A案
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

//エネミーの描画
void Enemy_Draw() {

	for (int i = 0; i < 20; i++) {

		DrawRotaGraph((int)zako[i].x, (int)zako[i].y, 2.0f, 0, zako[i].image, TRUE);	//ザコの描画
		if (i < 16) {

			DrawRotaGraph(goei[i].x, goei[i].y, 2.0f, 0, goei[i].image, TRUE);	//ゴエイの描画
		}
		if (i < 4) {
			DrawRotaGraph(boss[i].x, boss[i].y, 2.0f, 0, boss[i].image, TRUE);	//ボスギャラガの描画

		}
	}
}

//エネミーの初期化
void Enemy_Init() {

	LoadDivGraph("画像/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemyImage);	//敵キャラをenemy.Imageに追加

	//ザコの初期座標
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

	//ゴエイの初期座標
	for (int i = 0; i < 8; i++) {
		goei[i].x = 150 + i * 50;
		goei[i].y = 150;
		goei[i + 8].x = 150 + i * 50;
		goei[i + 8].y = 100;
		goei[i].image = enemyImage[5];
		goei[i + 8].image = enemyImage[5];
	}

	//ボスギャラガの初期座標
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