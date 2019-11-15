#include"DxLib.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define PI 3.14

int zako;
int goei;
int player;
int speed = 2;
int Image[50];
double zakoX;
double zakoY;
double goeiX;
double goeiY;
double zakomoveX;
double zakomoveY;
double goeimoveX;
double goeimoveY;
double playerX;
double playerY;

void Update() {
	double rad;
	double rad02;
	double tmpplayerX;
	double tmpplayerY;
	static double tmpzakoX = zakomoveX;
	static double tmpzakoY = zakomoveY;
	static double r = 0;
	static double r2;
	static double r3;
	static double r4 = 360;
	static int flg = 0;
	static int flg2 = 0;
	static int flg3 = 0;
	static int flg4 = 1;
	tmpplayerX = playerX;
	tmpplayerY = playerY;
	rad = r * PI / 180;
	rad02 = r4 * PI / 180;
	r2 = atan2(tmpplayerY - zakoY, (tmpplayerX + 30) - zakoX);
	r3 = atan2(tmpzakoY - zakoY, tmpzakoX - zakoX);

	//“G‚Ì‚Ù‚¤‚Ö‚Ì•ûŒü“]Š·
	if (flg4 == 1) {
		zakoX = tmpzakoX + 30 * cos(rad02);
		zakoY = tmpzakoY + 30 * sin(rad02);
		if (r4 < 180) {
			flg4 = 0;
			flg2 = 1;
		}
		r4 -= 2;
	}

	//“G‚Ì‚Ù‚¤‚Ö‚Ìs“®
	if (flg2 == 1) {
		if (zakoY > playerY) {
			flg2 = 0;
			flg = 1;
		}
		else {
			zakoX += speed * cos(r2);
			zakoY += speed * sin(r2);
		}
	}
	//“G‚Ì‹ß‚­‚Å‰ñ“]
	if (flg == 1) {
		zakoX = tmpplayerX + 30 * cos(rad);
		zakoY = tmpplayerY + 30 * sin(rad);
		if (r >= 150) {
			flg = 0;
			flg3 = 1;
		}
		else {
			r += 2;
		}
	}
	//‘à—ñ‚Ö–ß‚é
	if (flg3 == 1) {
		if (zakoX < tmpzakoX && zakoY < tmpzakoY) {
			flg3 = 0;
		}
		else {
			zakoX += speed * cos(r3);
			zakoY += speed * sin(r3);
		}
	}
}

void Draw_Goei() {
	goeiX += speed;
	goeiY += speed;
}

void Draw() {
	DrawRotaGraph((int)playerX, (int)playerY, 2.0f, 0, player, TRUE);
	DrawRotaGraph((int)zakoX, (int)zakoY, 2.0f, 0, zako, TRUE);
	DrawRotaGraph((int)goeiX, (int)goeiY, 2.0f, 0, goei, TRUE);
}

void Game() {

	srand((unsigned)time(NULL));

	LoadDivGraph("‰æ‘œ/Galaga_OBJ_enemy.png", 50, 5, 10, 17, 18, Image);
	zako = Image[0];
	goei = Image[5];
	player = Image[10];
	zakoX = 100;
	zakoY = 200;
	goeiX = 150;
	goeiY = 150;
	zakomoveX = zakoX;
	zakomoveY = zakoY;
	goeimoveX = goeiX;
	goeimoveY = goeiY;
	playerX = 400;
	playerY = 750;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Draw();
		//Update();
		Draw_Goei();
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ƒEƒBƒ“ƒhƒEƒ‚[ƒh•ÏX‚Æ‰Šú‰»‚Æ— ‰æ–ÊÝ’è

	SetGraphMode(1100, 800, 32);

	Game();
	
}