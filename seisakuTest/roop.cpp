#include "DxLib.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define PAI 3.14
#define ZAKOX 400;
#define ZAKOY 200;

static int mStartTime;	//測定開始時刻
static int mCount;	//カウンタ
static float mFps;	//fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;	//設定したFPS

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

struct Enemy {
	int zako[5];		//ザコの画像格納用の変数
	int goei[5];		//ゴエイの画像格納用の変数
	int boss[10];		//ボスギャラガの画像格納用の変数
	int Image[50];		//敵キャラの画像分割時の格納用の変数
	int zakoX[20];		//ザコのX座標	
	int zakoY[20];		//ザコのY座標
	int zakoatk[20];	//ザコの攻撃用flg
	int goeiX[16];		//ゴエイのX座標
	int goeiY[16];		//ゴエイのY座標
	int goeiatk[16];	//ゴエイの攻撃用flg
	int goeiatk2[8];	//ゴエイのボスギャラガ護衛時の攻撃用flg
	int bossX[4];		//ボスギャラガのX座標
	int bossY[4];		//ボスギャラガのY座標
	int bossatk[4];		//ボスギャラガの攻撃用flg
	int all;			//敵全体の動き用
	int speed;			//敵の移動量
	bool zako_onActive[20];
	bool goei_onActive[16];
	bool boss_onActive[4];
};

struct Enemy enemy;

bool Update() {
	if (mCount == 0) {	//１フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) {	//60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
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

//シーンを更新する
void UpdateScene() {
	DrawString(0, 20, "Gキーでゲーム画面、Cキーで設定、Mキーでメニュー画面になります。", GetColor(255, 255, 255));
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

//メニュー画面
void Menu() {
	DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
}

void ZakoAtk() {
	for (int i = 0; i < 20; i++) {
		if (enemy.zakoatk[i] == 1) {
			enemy.zakoY[i] += 1;
		}
	}
}

void GoeiAtk() {
	for (int i = 0; i < 16; i++) {
		if (enemy.goeiatk[i] == 1) {
			enemy.goeiY[i] += 1;
		}
	}
}

void BossAtk() {
	for (int i = 0; i < 4; i++) {
		if (enemy.bossatk[i] == 1) {
			enemy.bossY[i] += 1;
			enemy.goeiatk2[i * 2] = 1;
			enemy.goeiatk2[i * 2 + 1] = 1;
		}
		if (enemy.goeiatk2[i * 2] == 1 && enemy.goeiatk2[i * 2 + 1] == 1) {
			enemy.goeiY[i * 2] += 1;
			enemy.goeiY[i * 2 + 1] += 1;
		}
	}
}

//敵の描画
void Draw_Enemy() {
	for (int i = 0; i < 10; i++) {
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
}

//ゲーム画面
void Game() {
	int Green = GetColor(0, 255, 0); //色の設定
	int timecnt = 0;	//60フレームカウント
	int graphflg = 0;
	int testcnt = 0;

	srand((unsigned)time(NULL));

	LoadDivGraph("画像/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, enemy.Image);	//敵キャラをenemy.Imageに追加

	//各敵キャラ配列に格納
	for (int i = 0; i < 10; i++) {
		if (i < 5) {
			enemy.zako[i] = enemy.Image[i];
			enemy.goei[i] = enemy.Image[i + 5];
		}
		enemy.boss[i] = enemy.Image[i + 10];
	}
	//各キャラの隊列時の初期座標
	for (int i = 0; i < 10; i++) {
		enemy.zakoX[i] = 100 + i * 50;
		enemy.zakoX[i + 10] = 100 + i * 50;
		enemy.zakoY[i] = 200;
		enemy.zakoY[i + 10] = 250;
		if (i < 8) {
			enemy.goeiX[i] = 150 + i * 50;
			enemy.goeiY[i] = 100;
			enemy.goeiX[i + 8] = 150 + i * 50;
			enemy.goeiY[i + 8] = 150;
		}
		if (i < 4) {
			enemy.bossX[i] = 250 + i * 50;
			enemy.bossY[i] = 50;
		}
	}
	/*
	for (int i = 0; i < 20; i++) {
		enemy.zakoatk[i] = 0;
		if (i < 16) {
			enemy.goeiatk[i] = 0;
		}
		if (i < 4) {
			enemy.bossatk[i] = 0;
		}
	}
	*/
	for (int i = 0; i < 20; i++) {
		enemy.zakoatk[i] = rand() % 2;
		if (enemy.zakoatk[i] == 1) {
			testcnt++;
		}
		if (i < 16) {
			//enemy.goeiatk[i] = rand() % 2;
		}
		if (i < 8) {
			enemy.goeiatk2[i] = 0;
		}
		if (i < 4) {
			enemy.bossatk[i] = rand() % 2;
		}
	}

	enemy.all = 0;	//隊列の初期座標

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Update();

		//FPSの表示
		DrawFormatString(800, 0, Green, "FPS %.1f", mFps);
		//DrawFormatString(800, 50, Green, "all %d\nzako %d\ngoei %d\nboss %d\nflg %d\n", enemy.all, enemy.zakoX[0], enemy.goeiX[0], enemy.bossX[0], graphflg);
		for (int i = 0; i < 20; i++) {
			DrawFormatString(800, 50 + 20 * i, Green, "zako[ %d ] %d ", i, enemy.zakoatk[i]);
			if (i < 8) {
				DrawFormatString(900, 50 + 20 * i, Green, "goeiatk2[ %d ] %d ", i, enemy.goeiatk2[i]);
			}
		}
		DrawFormatString(800, 700, Green, "攻撃中の敵の数 %d ", testcnt);

		for (int i = 0; i < 20; i++) {
			if (enemy.zakoatk[i] == 1) {
				ZakoAtk();
			}
			if (i < 16 && enemy.goeiatk[i] == 1) {
				GoeiAtk();
			}
			if (i < 4 && enemy.bossatk[i] == 1) {
				BossAtk();
			}
		}

		//移動待機時間(切り替え式)
		if (timecnt == 0) {
			graphflg = 0;
		}
		else if (timecnt == 20) {
			graphflg = 1;
			if (enemy.all <= 0) {
				enemy.speed = 10;
			}
			else if (enemy.all >= 100) {
				enemy.speed = -10;
			}
			//隊列の動き
			for (int i = 0; i < 20; i++) {
				if (enemy.zakoatk[i] == 0) {
					enemy.zakoX[i] += enemy.speed;
				}
				if (i < 4 && enemy.bossatk[i] == 0) {
					enemy.bossX[i] += enemy.speed;
				}
				if (i < 8 && enemy.goeiatk2[i] == 1) {
					enemy.goeiatk[i] = 0;
					continue;
				}
				if (i < 16 && enemy.goeiatk[i] == 0 && enemy.goeiatk2[i] != 1) {
					enemy.goeiX[i] += enemy.speed;
				}
			}
			enemy.all += enemy.speed;
		}
		timecnt++;
		if (timecnt > 40)timecnt = 0;

		
		Draw_Enemy();	//Draw_Enemyへ

		Wait();
	}
}

//設定画面
void Config() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetGraphMode(1100, 800, 32);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//現在のシーンにあった処理をする
		case eScene_Menu://現在のシーンがメニューなら
			Menu();//メニュー画面
			break;
		case eScene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		case eScene_Config://現在のシーンが設定なら
			Config();//設定画面
			break;
		}

		UpdateScene();//シーンを更新する

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}