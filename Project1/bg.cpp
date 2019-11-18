#include "bg.h"
#include "SceneMgr.h"
#include "DxLib.h"
#define SPEED 1

static int y = 0;

void bg_Draw() {

	static int siro = LoadGraph("画像/siro.jpg");
	static int haikei1 = LoadGraph("画像/bg2.png");
	static int haikei2 = LoadGraph("画像/bg3.png");
	static int haikei3 = LoadGraph("画像/bg.pmg");
	static int count = 0;
	static int flg = 0;
	static int i = 0;
	int img[3] = { haikei1,haikei2,haikei3 };

	//1枚目
		DrawGraph(0, y, img[i], TRUE);
	//2枚目
		DrawGraph(0, y-800,img[i], TRUE);
	//3毎目
		DrawGraph(0, y-1600, img[i], TRUE);
	//一番下までスクロールしたら初期値に戻す
		if (y >= 1600) {
			y = 0;
		}
	    count++;               //カウンターを加算

		if (count % 120 == 0) {                   //もし、カウンターを600で割った余りが0であるなら            
			i++;
			count = 0;
		}
		if (i == 2) {
			i = 0;
		}
		DrawGraph(800, 0, siro, TRUE);
}
void bg_Update() {

	y += SPEED;
}
void bg_All() {

	bg_Draw();
	bg_Update();
}