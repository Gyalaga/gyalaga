#include "DxLib.h"
#include"Setup.h"

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

void irekae(int px, int py) {
	DrawString(500, 0, "河本です。", GetColor(175, 175, 175));
	int p1 = (py * 2) + px;
	int p2 = -1;
	if (px > 0 && hairetu[p1 - 1] == 0)p2 = p1 - 1;
	if (px < 1 && hairetu[p1 + 1] == 0)p2 = p1 + 1;
	if (py > 0 && hairetu[p1 - 2] == 0)p2 = p1 - 2;
	if (py < 1 && hairetu[p1 + 2] == 0)p2 = p1 + 2;

	if (p2 != -1) {
		hairetu[p2] = hairetu[p1];
		hairetu[p1] = 0;
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
	DrawString(0, 0, "ゲーム画面です。", GetColor(0, 0, 0));

	int SetBackgroundColor(int Red, int Green, int Blue);

	SetBackgroundColor(255, 255, 255);
	Mouse = GetMouseInput();
	GetMousePoint(&x, &y);
	for(int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			if (x > (j * 240) && x< (j * 240) + 240 && y>(i * 240) && y <(i * 240) + 240) {
				if (Mouse & MOUSE_INPUT_LEFT) {
					DrawString(500, 0, "abeです。", GetColor(0, 0, 0));
					irekae(x / 240, y / 240);
				}
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DrawGraph(j*240, i*240, gazou[hairetu[(i*2)+j]], TRUE);
		}
	}
}

//設定画面
void Config() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	
	gazou[0] = LoadGraph("画像/black.png");
	gazou[3] = LoadGraph("画像/red.png");
	gazou[1] = LoadGraph("画像/blue.png");
	gazou[2] = LoadGraph("画像/sentokunn.png");

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