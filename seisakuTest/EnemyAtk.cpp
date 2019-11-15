#include"DxLib.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define PI 3.14

int zako;
int player;
int Image[50];
double zakoX;
double zakoY;
double zakomoveX;
double zakomoveY;
double playerX;
double playerY;

void Update() {
	double rad;
	double rad02;
	double tmpplayerX;
	double tmpplayerY;
	static double tmpzakoX = zakomoveX;
	static double tmpzakoY = zakomoveY;
	static int r = 0;
	static int r2;
	static int flg = 1;
	static int flg2 = 1;
	tmpplayerX = playerX;
	tmpplayerY = playerY;
	rad = r * PI / 180;
	r2 = atan2(zakoY - playerY, zakoX - playerX);

	if (flg2 == 1) {
		zakoX -= 2 * cos(r2);
		zakoY -= 2 * sin(r2);
	}
	if (flg == 0) {
		zakoX = tmpplayerX + 30 * cos(rad);
		zakoY = tmpplayerY + 30 * sin(rad);
		r++;
	}
}

void Draw() {
	DrawRotaGraph(zakoX, zakoY, 2.0f, 0, zako, TRUE);
	DrawRotaGraph(playerX, playerY, 2.0f, 0, player, TRUE);
}

void Game() {

	srand((unsigned)time(NULL));

	LoadDivGraph("画像/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, Image);
	zako = Image[0];
	player = Image[10];
	zakoX = 100;
	zakoY = 200;
	zakomoveX = zakoX;
	zakomoveY = zakoY;
	playerX = 400;
	playerY = 750;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Draw();
		Update();
	}
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetGraphMode(1100, 800, 32);

	Game();
	
}