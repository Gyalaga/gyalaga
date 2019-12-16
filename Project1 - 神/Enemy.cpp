#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "DxLib.h"
#include "Enemy.h"

#define PI			3.14	//円周率
#define ENEMYSPEED	2		//敵の移動速度



/*
関数名		:Enemy_all
処理の概要	:エネミーの処理の全体
引数		:なし
返却値		:なし
備考		:大幅に記述を変更する際に削除予定
*/

void Enemy_all() {

	//enemyの初期化
	if (enemyInit == true) {
		Enemy_Init();
		enemyInit = false;
	}

	Enemy_Update();		//enemyの更新

	Enemy_Draw();		//enemyの描画
}

/*
関数名		:Enemy_Update
処理の概要	:エネミーの更新
引数		:なし
返却値		:なし
備考		:なし
*/

void Enemy_Update() {

	//DrawString(0, 450, "Enemy_Updateが正常に稼働しました", GetColor(255, 255, 255));

	static bool zakoAllAtk = false;		//ザコが攻撃してるか判定フラグ
	static bool goeiAllAtk = false;		//ゴエイが攻撃してるか判定フラグ
	static bool bossAllAtk = false;		//ボスギャラガが攻撃してるか判定フラグ

	srand((unsigned)time(NULL));		//乱数を固定値にしないために

	//攻撃フラグがtrueの時、それぞれの関数へ
	for (int i = 0; i < 20; i++) {

		//ザコの攻撃フラグがtrueの時ザコの攻撃処理を行う、判定フラグをtrueへ
		if (zako[i].atk == true) {

			zakoAllAtk = Enemy_Zako(i);
		}
		//ゴエイの攻撃フラグがtrueの時ゴエイの攻撃処理を行う、判定フラグをtrueへ
		if (i < 16 && goei[i].atk == true) {

			goeiAllAtk = Enemy_Goei(i);
		}
		//ボスギャラガの攻撃フラグがtureの時ボスギャラガの攻撃処理を行う、判定フラグをtrueへ
		if (i < 4 && boss[i].atk == true) {

			Enemy_Boss(i);

			bossAllAtk = true;
		}
	}

	//zakoAllAtkがfalseの時ザコの攻撃判定をtrueにする
	for (int i = 0; i < 10; i++) {
		
		//zakoAllAtkがfalseかつzako[i].onAcitveがtrueの時zako[0～9]の攻撃フラグをtrueにする
		if (zakoAllAtk == false && zako[i].onActive == true) {
			zako[rand() % 10].atk = true;
			break;
		}
		//zako[i].onActiveがfalseかつiが9未満の時continueする
		else if (zako[i].onActive == false && i < 9) {
			continue;
		}
		//iが9までcontinueされたときにzako[10～19]の攻撃フラグをtureにする
		else if(zakoAllAtk == false){

			zako[rand() % 10 + 10].atk = true;
		}
	}

	goei[8].atk = true;
	boss[0].atk = true;
}

/*
関数名		:Enemy_Zako
処理の概要	:ザコの攻撃時の処理
引数		:なし
返却値		:なし
備考		:true or false
*/

bool Enemy_Zako(int zakoAtk) {
	
	static int test_Zvy = ENEMYSPEED;

	//DrawString(0, 500, "Enemy_Zakoが正常に稼働しました", GetColor(255, 255, 255));

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
関数名		:Enemy_Goei
処理の概要	:ゴエイの攻撃時の処理
引数		:なし
返却値		:なし
備考		:true or false
*/

bool Enemy_Goei(int goeiAtk) {

	//DrawString(0, 550, "Enemy_Goeiが正常に稼働しました", GetColor(255, 255, 255));

	static int test_Gvy = ENEMYSPEED;

	if (goei[goeiAtk].y > 800) {
		goei[goeiAtk].y = -30;
	}

	goei[goeiAtk].y += test_Gvy;

	return true;
}

/*
関数名		:Enemy_Boss
処理の概要	:ボスギャラガの攻撃時の処理
引数		:なし
返却値		:なし
備考		:true or false
*/

bool Enemy_Boss(int bossAtk) {

	//DrawString(0, 600, "Enemy_Bossが正常に稼働しました", GetColor(255, 255, 255));

	return true;
}

/*
関数名		:Enemy_Draw
処理の概要	:enemyの描画
引数		:なし
返却値		:なし
備考		:なし
*/

void Enemy_Draw() {

	//DrawString(0, 400, "Enemy_Drawが正常に稼働しています", GetColor(255, 255, 255));

	for (int i = 0; i < 20; i++) {

		//ザコの描画
		if (zako[i].onActive == true) {
			
			DrawRotaGraph(zako[i].x, zako[i].y, 2.0f, 0, zako[i].image[0], TRUE);
		}

		//ゴエイの描画
		if (i < 16 && goei[i].onActive == true) {

			DrawRotaGraph(goei[i].x, goei[i].y, 2.0f, 0, goei[i].image[0], TRUE);
		}

		//ボスギャラガの描画
		if (i < 4 && boss[i].onActive == true) {

			DrawRotaGraph(boss[i].x, boss[i].y, 2.0f, 0, boss[i].image[0], TRUE);

		}
	}
}

/*
関数名		:Enemy_Init
処理の概要	:enemyの初期化
引数		:なし
返却値		:なし
備考		:なし
*/

void Enemy_Init() {

	static int zakoInterval;	//ザコの間隔
	static int goeiInterval;	//ゴエイの間隔
	static int bossInterval;	//ボスギャラガの間隔

	LoadDivGraph("画像/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemyImage);	//敵キャラをenemy.Imageに追加

	//初期化処理全体
	for (int i = 0; i < 20; i++) {

		//ザコの間隔の計算とy座標の初期化
		if (i < 10) {

			zakoInterval = i * 35;
			zako[i].y = 250;
		}
		else {

			zakoInterval = (i - 10) * 35;
			zako[i].y = 200;
		}

		zako[i].x = 225 + zakoInterval;		//ザコのx座標の初期化
		zako[i].atk = false;				//ザコの攻撃フラグの初期化
		zako[i].onActive = true;			//ザコの表示フラグの初期化

		//画像を全体から個別へ
		for (int j = 0; j < 5; j++) {
			zako[i].image[j] = enemyImage[0 + j];
		}

		//ゴエイの初期化
		if (i < 18) {

			//ゴエイの間隔の計算とy座標の初期化
			if (i < 8) {

				goeiInterval = i * 35;
				goei[i].y = 150;
			}
			else {

				goeiInterval = (i - 8) * 35;
				goei[i].y = 100;
			}

			goei[i].x = 260 + goeiInterval;		//ゴエイのx座標の初期化
			goei[i].atk = false;				//ゴエイの攻撃フラグの初期化
			goei[i].onActive = true;			//ゴエイの表示フラグの初期化

			//画像を全体から個別へ
			for (int j = 0; j < 5; j++) {
				goei[i].image[j] = enemyImage[5 + j];
			}
		}

		//ボスギャラガの初期化
		if (i < 4) {

			bossInterval = i * 35;				//ボスギャラガの間隔の計算
			boss[i].y = 50;						//ボスギャラガのy座標の初期化
			boss[i].x = 330 + bossInterval;		//ボスギャラガのx座標の初期化
			boss[i].atk = false;				//ボスギャラガの攻撃フラグの初期化
			boss[i].onActive = true;			//ボスギャラガの表示フラグの初期化

			//画像を全体から個別へ
			for (int j = 0; j < 10; j++) {
				boss[i].image[j] = enemyImage[10 + j];
			}
		}
	}
}