#include "DxLib.h"
#include<math.h>

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
	int zako[5];	//ザコの画像格納用の変数
	int goei[5];	//ゴエイの画像格納用の変数
	int boss[10];	//ボスギャラガの画像格納用の変数
	int Image[50];	//敵キャラの画像分割時の格納用の変数
	int zakoX[20];	//ザコのX座標	
	int zakoY[20];	//ザコのY座標
	int goeiX[16];	//ゴエイのX座標
	int goeiY[16];	//ゴエイのY座標
	int bossX[4];	//ボスギャラガのX座標
	int bossY[4];	//ボスギャラガのY座標
	int all;		//敵全体の動き用
	int speed;		//敵の移動量
};

struct Enemy enemy;

bool Update() {
	if (mCount == 0) {	//１フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) {	//60フレーム目なら平均を計算する
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

//ゲーム画面
void Game() {
	int Green = GetColor(0, 255, 0); //色の設定
	int timecnt = 0;	//60フレームカウント
	int graphflg = 0;

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
			enemy.goeiY[i] = 150;
			enemy.goeiX[i + 8] = 150 + i * 50;
			enemy.goeiY[i + 8] = 100;
		}
		if (i < 4) {
			enemy.bossX[i] = 250 + i * 50;
			enemy.bossY[i] = 50;
		}
	}

	enemy.all = 0;	//隊列の初期座標

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Update();

		//FPSの表示
		DrawFormatString(800, 0, Green, "FPS %.1f", mFps);
		DrawFormatString(800, 50, Green,"all %d\nzako %d\ngoei %d\nboss %d\nflg %d\n",enemy.all,enemy.zakoX[0],enemy.goeiX[0],enemy.bossX[0],graphflg);

		//移動待機時間(切り替え式)
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
			//隊列の動き
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
			//graphflgが0のとき1枚目の画像を表示
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
			//graphflgが1のとき2枚目の画像を表示
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