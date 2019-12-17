#include"DxLib.h"
#include "windows.h"
#include "bgm.h"
#include"bg.h"
#include"Game.h"
#define SHOT 2


// キー入力
int key[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている


void Keysecond() {

	static char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++) {
		if (buf[i]) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				if (key[i] == 0) {
					SE_draw();
					key[i] = 1;
				}
			}
			else if (key[i] == 1) key[i] = 2;
		}
		else key[i] = 0;
	}
}

void Key_draw() {

	int px = 0, py = 500, ph = 16, pw = 16, image[32]; //自機の座標と画像変数ですううう
	int pi = 0, pj = 0, ps = 0;                      //pi:自機画像の回転用,pj:何回転するか,ps:回転速度
	int keyflg = 0, HP = 3;                          //keyflg:入力拒否用,HP:体力
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //敵の座標と画像変数ですううう
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:爆破エフェクトの速さ,bj:表示,画像変数用
	int color = GetColor(255, 255, 255);             //色コードを取得
	static int shot = LoadGraph("bullet.png");

	int sx[SHOT], sy[SHOT],
		sx2[SHOT], sy2[SHOT], sw = 9, sh = 12, i;      //弾の座標
	int sf[SHOT];                                    //弾の発射フラグ
	int sf2;

	//弾が画面上に存在しているか保持する変数に
	//「存在していない」を意味する0を代入しておく
	for (i = 0; i < SHOT; i++) {
		sf[i] = 0;
	}

	//ショットボタンを前のフレームで押されたかどうかを保持する
	//変数に0（押されていない）を代入
	sf2 = 0;

	//スペースが押されたら弾を打つ
	if (CheckHitKey(KEY_INPUT_SPACE)) {

		//前のフレームでショットボタンを押したかが
		//保存されている変数が0だったら弾を発射
		if (sf2 == 0) {

			//画面上に出てない弾があるか、弾の数だけくり返し調べる
			for (i = 0; i < SHOT; i++) {

				
				//弾が画面上に出てない場合はその弾を画面に出す
				if (sf[i] == 0) {

					//弾の位置をセット、位置は自機の中心にする
					sx[i] = (pw - sw) / 2 + px;
					sy[i] = (ph - sh) / 2 + py;
					sx2[i] = (pw - sw) / 2 + px + 20;
					sy2[i] = (ph - sh) / 2 + py;

					//弾は現時点で存在するので、存在状態を保持する変数に1を代入する
					sf[i] = 1;

					//弾を1つ出したのでループから抜け出す
					break;

				}
				

			}			
		}
		//前のフレームでショットボタンを押されていたかを
		//保持する変数に1（押されていた）を代入する
		sf2 = 1;
	}
	else {

		//前のフレームでショットボタンを押されていなかった場合は
		//ショットボタンを押されていたかを
		//保持する変数に0（押されていない）を代入する
		sf2 = 0;

	}
}

void Key_ALL() {

	Keysecond();
	Key_draw();
	//bg_All();
}