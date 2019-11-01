#include "DxLib.h"
#include<math.h>

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

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
	int gazou = LoadGraph("画像/sentokunn.png");
	int gazou2 = LoadGraph("画像/sentokunn2.png");
	int neko = LoadGraph("画像/nekoneko2.png");
	int x;
	int y;
	int bx;
	int by;
	int setx;
	int sety;
	int flg;
	int durability;
	x = 0;
	y = 0;
	setx = 0;
	sety = 0;
	flg = 0;
	durability = 100;
	int Green = GetColor(0, 255, 0);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawGraph(x, y, gazou, TRUE);
		if (durability > 0) {
			DrawGraph(400, 100, gazou2, TRUE);
		}
		if (flg == 1) {
			DrawGraph(bx, by, neko, TRUE);
			bx += 3;
			if (bx + 50 >= 400 && bx <= 400 + 240 && by + 46 >= 100 && by <= 100 + 240) {
				durability -= 20;
				if (durability <= 0)durability = 0;
				flg = 0;
			}
			if (bx >= 800) {
				flg = 0;
			}
		}
		DrawFormatString(100, 100, Green, "座標[%d,%d]", x, y);
		DrawFormatString(400, 100, Green, "enemy HP[%d]",durability);
		DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
		/*
		if (setx >= 360)setx = 0;
		if (sety >= 360)sety = 0;
		setx++;
		sety++;
		x = sin(setx * (3.14 / 180));
		y = cos(sety * (3.14 / 180));
		*/

		if (x < 100) {
			x++;
		}
		else {
			x = 100;
		}
		if (x == 100 && y < 100) {
			y++;
		}
		else if(y >= 100){
			y = 100;
		}
		if (CheckHitKey(KEY_INPUT_D) != 0 && flg == 0) {
			bx = x + 210;
			by = y + 75;
			flg = 1;
		}
		if (CheckHitKey(KEY_INPUT_Q) != 0) {
			Scene = eScene_Menu;
			break;
		}
	}
}

//設定画面
void Config() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

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
