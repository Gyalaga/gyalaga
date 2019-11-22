#include "DxLib.h"

#define SHOT 2

int Key[256]; // キーが押されているフレーム数を格納しますううう

// キーの入力状態を更新しますううう
int gpUpdateKey()
{
	char tmpKey[256];               // 現在のキーの入力状態を格納しますううう
	GetHitKeyStateAll(tmpKey);      // 全てのキーの入力状態を得ますううう
	for (int j = 0; j < 256; j++)
	{
		if (tmpKey[j] != 0)         // i番のキーコードに対応するキーが押されていたら
		{
			Key[j]++;               // 加算しますううう
		}
		else
		{                           // 押されていなければ
			Key[j] = 0;             // 0にしますううう
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) //ウィンドウモード変更と初期化と裏画面設定
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	int px = 0, py = 500, ph = 16, pw = 16, image[32]; //自機の座標と画像変数ですううう
	int pi = 0, pj = 0, ps = 0;                      //pi:自機画像の回転用,pj:何回転するか,ps:回転速度
	int keyflg = 0, HP = 3;                          //keyflg:入力拒否用,HP:体力
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //敵の座標と画像変数ですううう
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:爆破エフェクトの速さ,bj:表示,画像変数用
	int color = GetColor(255, 255, 255);             //色コードを取得
	int shot;                                        //弾の画像
	int sx[SHOT], sy[SHOT],
		sx2[SHOT], sy2[SHOT], sw = 9, sh = 12, i;      //弾の座標
	int sf[SHOT];                                    //弾の発射フラグ
	int sf2;


	shot = LoadGraph("bullet.png");
	enemy = LoadGraph("Player.bmp");                            // 敵の画像
	LoadDivGraph("dairi.png", 16, 16, 2, 17, 17, image);        // 自機画像の分割読み込み
	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // 爆破画像の分割読み込み
			   //画像の名前、分割する数、横何分割、縦何分割、分割する画像のサイズ、変数名

	//弾が画面上に存在しているか保持する変数に
	//「存在していない」を意味する0を代入しておく
	for (i = 0; i < SHOT; i++) {
		sf[i] = 0;
	}
	
	//ショットボタンを前のフレームで押されたかどうかを保持する
	//変数に0（押されていない）を代入
	sf2 = 0;
	

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		// 画面を初期化しますううう
		ClearDrawScreen();
		// キー入力取得　ゲームオーバー時入力拒否をさせたいからif文の中に入れる
		Key[256] = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (keyflg == 0)
		{
			// 右を押していたら右に進む
			if (Key[256] & PAD_INPUT_RIGHT) px += 3;

			// 左を押していたら左に進む
			if (Key[256] & PAD_INPUT_LEFT)  px -= 3;


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

		//弾の数だけ弾を動かす処理
		for (i = 0; i < SHOT; i++) {

			//存在状態を保持している変数の内容が１（存在する）の場合のみ行う
			if (sf[i] == 1) {

				//弾 i を10ドット移動させる
				sy[i] -= 5;


				//画面外に出た場合、存在を保持している変数に0（存在しない）を代入する
				if (sy[i] < -80) {
					sf[i] = 0;
				}

				if (((sx[i] > ex && sx[i] < ex + ew) || (ex > sx[i] && ex < sx[i] + sw)) &&
					((sy[i] > ey && sy[i] < ey + eh) || (ey > sy[i] && ey < sy[i] + sh))) {
					sf[i] = 0;
					//敵の存在を保持している変数を0（存在しない)を代入する
				}

				//弾の描画
				DrawGraph(sx[i], sy[i], shot, TRUE);


			}
		}
		for (i = 0; i < SHOT; i++) {

			//存在状態を保持している変数の内容が１（存在する）の場合のみ行う
			if (sf[i] == 1) {

				//弾 i を10ドット移動させる
				sy2[i] -= 5;

				//画面外に出た場合、存在を保持している変数に0（存在しない）を代入する
				if (sy2[i] < -80) {
					sf[i] = 0;
				}

				if (((sx2[i] > ex && sx2[i] < ex + ew) || (ex > sx2[i] && ex < sx2[i] + sw)) &&
					((sy2[i] > ey && sy2[i] < ey + eh) || (ey > sy2[i] && ey < sy2[i] + sh))) {
					sf[i] = 0;
					//敵の存在を保持している変数を0（存在しない)を代入する
				}

				//弾の描画

				DrawGraph(sx2[i], sy2[i], shot, TRUE);

			}
		}




		if (keyflg == 2)
		{
			if (Key[KEY_INPUT_A] == 1)
			{
				px = 0;     py = 0;
				pi = 0;     pj = 0;
				keyflg = 0; HP = 3;
				bi = 0;     bj = 0;
			}
		}

		{   //プレイヤーの移動限度
			if (px >= 610)  px = 610;
			if (px <= 0)    px = 0;
			if (py >= 450)  py = 450;
			if (py <= 0)    py = 0;
		}

		if (px >= ex - pw && px <= ex + ew && py >= ey - ph && py <= ey + eh)//当たり判定
		{              //あたったらキー入力拒否して画像を動かしながらカウントダウンします
			keyflg = 1;//入力拒否
			ps++;
		}

		if (pi == 15)pi = 0, pj += 1; //iに上限を設定してカウントしますううう

		if (pj > 2)        //画像がうまく消せないので画像配列としては存在しない配列番号にしますううう
		{
			pi = 16;
			bi++;
			if (bi == 10)bj += 1, bi = 0;                  //自機の爆破エフェクトスピードをいじるならここ
			DrawGraph(px, py, bakuhaimage[bj], TRUE); // 画像を表示しますううう
		}

		if (ps == 3) ps = 0, pi += 1;//自機を回転のスピードをいじるならここ

		if (bj == 13)  //リセット
		{
			px = 0;     py = 0;
			pi = 0;     pj = 0;
			keyflg = 0; HP -= 1;
			bi = 0;     bj = 0;
		}

		if (HP == 0) // HPが0になったら
		{
			pi = 16; keyflg = 2;	         // キー入力を受け付けさせないようにしますううう
			DrawFormatString(250, 250, color, "GAME OVER\nAでリトライ"); // 文字を描画するよ
		}
		DrawFormatString(250, 200, color, "HP:%d", HP); // 文字を描画する
		DrawGraph(ex, ey, enemy, TRUE);       // 画像を表示しますううう
		DrawGraph(px, py, image[pi], TRUE);   // 画像を表示しますううう


	}
	DxLib_End(); // DXライブラリ終了処理しますううう
	return 0;
}