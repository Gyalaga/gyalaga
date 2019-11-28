#include "DxLib.h"
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
	int px = 0, py = 0, ph = 16, pw = 16, image[32];  //自機の座標と画像変数ですううう
	int pi = 0, pj = 0, ps = 0;                      //pi:自機画像の回転用,pj:何回転するか,ps:回転速度
	int keyflg = 0, HP = 3;                          //keyflg:入力拒否用,HP:体力
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //敵の座標と画像変数ですううう
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:爆破エフェクトの速さ,bj:表示,画像変数用
	int color = GetColor(255, 255, 255);             //色コードを取得
	int shot;                                     //弾の画像
	int sx[20], sy[20], sw = 9, sh = 12, i;                                 //弾の座標
	int sf[20]; //弾の発射フラグ
	int sf2;
	int Simage[10];

	shot = LoadGraph("bullet.png");
	enemy = LoadGraph("Player.bmp");                            // 敵の画像
	LoadDivGraph("dairi.png", 16, 16, 2, 17, 17, image);        // 自機画像の分割読み込み
	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // 爆破画像の分割読み込み
			   //画像の名前、分割する数、横何分割、縦何分割、分割する画像のサイズ、変数名

	for (i = 0; i < 20; i++) {
		sf[i] = 0;
	}
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
			// 上を押していたら上に進む
			if (Key[256] & PAD_INPUT_UP)    py -= 3;

			// 下を押していたら下に進む
			if (Key[256] & PAD_INPUT_DOWN)  py += 3;

			// 右を押していたら右に進む
			if (Key[256] & PAD_INPUT_RIGHT) px += 3;

			// 左を押していたら左に進む
			if (Key[256] & PAD_INPUT_LEFT)  px -= 3;

			
			//スペースが押されたら弾を打つ
			if (CheckHitKey (KEY_INPUT_SPACE)) {
				if (sf2==0) {
					for (i = 0; i < 20; i++) {
						if (sf[i] == 0) {
							sx[i] =( pw - sw) / 2 + px;
							sy[i] = (ph - sh) / 2 + py;

							sf[i] = 1;

							break;
						}

					}
					
				}
				sf2 = 1;
			}
			else {
				sf2 = 0;
			}
		}

		for (i = 0; i < 20; i++) {
			if (sf[i] == 1) {
				sy[i] -= 16;
				if (sy[i] < -80) {
					sf[i] = 0;
				}

				DrawGraph(sx[i], sy[i], shot, TRUE);
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
		//弾の描画
		
	}
	DxLib_End(); // DXライブラリ終了処理しますううう
	return 0;
}