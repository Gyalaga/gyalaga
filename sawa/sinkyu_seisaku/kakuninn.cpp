#include "DxLib.h"
#define PI 3.14
int Key[256]; // キーが押されているフレーム数を格納します
void player();
// キーの入力状態を更新します
int gpUpdateKey()
{
	char tmpKey[256];               // 現在のキーの入力状態を格納します
	GetHitKeyStateAll(tmpKey);      // 全てのキーの入力状態を得ます
	for (int j = 0; j < 256; j++)
	{
		if (tmpKey[j] != 0)         // i番のキーコードに対応するキーが押されていたら
		{
			Key[j]++;               // 加算します
		}
		else
		{                           // 押されていなければ
			Key[j] = 0;             // 0にします
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) //ウィンドウモード変更と初期化と裏画面設定
{
	// 画面モードの設定
	SetGraphMode(1100, 800, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	player();
	DxLib_End(); // DXライブラリ終了処理します
	return 0;
}

void player()
{
	/* { プレイヤー用の変数 } ***********************************************************************************/
	int px[16] = { 400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400 };
	int py[16] = { 600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600 };
	bool pflg[16] = { true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true, };
	int	prote = 0, psize = 2;               //prote:自機角度,  psize:自機サイズ
	int	pr = 14 * psize / 2, pimage[2];     //自機の座標と画像変数
	int HP = 3, i = 0, hflg = 1, flg = 1;   //   HP:体力,i:操作する番号,  hflg,flg:表示用フラグ
	int out = 0;                            //他の当たり判定と重ならないようにするフラグ
	int pb = 0;                             //文を見やすくする用
	int pq = 0;
	int ij=0, s=0, is=0;
	LoadDivGraph("自機.png", 2, 1, 2, 16, 16, pimage);   //自機画像の分割読み込み
	 //画像の名前、分割する数、横何分割、縦何分割、分割する画像のサイズ、変数名

	/* { 弾用の変数 } *******************************************************************************************/
	int shot;                                     //弾の画像
	int sx[20], sy[20], sw = 9, sh = 12, j;                                 //弾の座標
	int sf[20]; //弾の発射フラグ
	int sf2;
	int Simage[10];
	int sr = sw / 2;
	shot = LoadGraph("bullet.png");
	/* { エネミー用の変数 } *************************************************************************************/
	int ex = 400, ey = 500, er = 15 * 3 / 2, enemy[50]; //敵の座標と画像変数
	int ep = 0, eflg = 0, efp = 0, fps = 0;

	LoadDivGraph("Galaga_OBJ_enemy.png", 50, 5, 9, 19, 20, enemy); // 敵の画像の分割読み込み

	int es = 0, esflg = 0;  //敵の移動用
	int epx, epy;           //敵自機用
	/* { ビーム兄貴用の変数 } ***********************************************************************************/
	static int bmimage[12];
	int bmx = 0, bmy = 0;
	int bmi = 0, bmcnt = 0, bmanitmp = 0, bllmflg = 0;
	int bllmcnt = 0, bmt = 0, bllm = 0;
	int bmani[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,11,10,11,10,11,10,9,8,7,6,5,4,3,2,1,0 };

	LoadDivGraph("Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, bmimage); // 画像の分割読み込み
	/* { 吸い込まれアニメーション用の変数 } *********************************************************************/
	int q = 0, t1 = 0, t2 = 0;

	/* { 爆破用の変数 } *****************************************************************************************/
	int bi = 0, bj = 0, bakuhaimage[13]; //bi:爆破エフェクトの速さ,bj:表示,画像変数用
	int bflg = 0;//フラグ用

	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // 爆破画像の分割読み込み

	/* { そのほかの変数 } ***************************************************************************************/
	int keyflg = 0, color = GetColor(255, 255, 255); // keyflg:入力拒否用　色コードを取得

	/** { セットアップ } ****************************************************************************************/
	for (j = 0; j < 20; j++) {
		sf[j] = 0;
	}
	sf2 = 0;
	/************************************************************************************************************/
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		// 画面を初期化
		ClearDrawScreen();
		// キー入力取得　ゲームオーバー時入力拒否をさせたいからif文の中に入れる
		Key[256] = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (keyflg == 0)
		{
			// 右を押していたら右に進む
			if (Key[256] & PAD_INPUT_RIGHT) px[i] += 3;

			// 左を押していたら左に進む
			if (Key[256] & PAD_INPUT_LEFT)  px[i] -= 3;

			//スペースが押されたら弾を打つ
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				if (sf2 == 0) {
					for (j = 0; j < 20; j++) {
						if (sf[j] == 0) {
							sx[j] = (pr - sw) / 2 + px[i];
							sy[j] = (pr - sh) / 2 + py[i];

							sf[j] = 1;

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

		if (keyflg == 2)//ゲームオーバー時使用できるキー
		{
			if (Key[KEY_INPUT_A] == 1)
			{
			   px[0] = 400;  py[0] = 600;
			   px[1] = 400;  py[1] = 600;
			   px[2] = 400;  py[2] = 600;
				  i  =   0; keyflg =   0;
				 HP  =   3;    out =   0;
				flg  =   1;   hflg =   1;
			}
		}
		//プレイヤーの移動限度
		if (px[i] >= 1100 - 24) px[i] = 1100 - 22;
		if (px[i] <= 0 + 24)    px[i] =    0 + 22;
		/* { 弾 } ***********************************************************************************************/

		for (j = 0; j < 20; j++) {
			if (sf[j] == 1) {
				sy[j] -= 16;
				if (sy[j] < -80) {
					sf[j] = 0;
				}

				DrawGraph(sx[j], sy[j], shot, TRUE);
			}
		}

		/* { 敵移動 } *******************************************************************************************/
		if (pb == 0 && esflg == 0)ex = ex + es;
		if (ex > 600)esflg = 1;
		if (pb == 0 && esflg == 1)ex = ex - es;
		if (ex < 0)esflg = 0;

		/* { 敵と普通に当たった場合 } ***************************************************************************/
		//敵との当たり判定
		if (eflg==0&&(px[i] - ex) * (px[i] - ex) + (py[i] - ey) * (py[i] - ey) <= (pr + er) * (pr + er)) //当たり判定
		{
			if (out == 0 || out == 1)bflg = 1;//ほかの当たり判定と重なってないならアニメーション再生
		}
		if (bflg == 1)
		{
			keyflg = 1;  //入力拒否 
			   flg = 0;  //プレイヤーを非表示
		    bi++;        //爆破アニメーション開始
			if (bi == 10)bj += 1, bi = 0; //自機の爆破エフェクトスピードをいじるならifの条件を変える
			DrawRotaGraph(px[i], py[i], 3.5, PI / 180 * 0, bakuhaimage[bj], TRUE);//爆破画像表示
		}
		if (bj == 13)  //爆破アニメーションが終わったらリセットする
		{
			i += 1; keyflg = 0; HP -= 1;
			bi = 0; bj = 0;
			hflg += 1; out = 0;
			flg = 1; bflg = 0;
		}

		/********************************************************************************************************/
		//敵bllmアニメーション
		bmx = ex;
		bmy = ey + 15;
		if(eflg==0&&bllm==0)bllmcnt++;
		DrawFormatString(50, 200, color, "bllmcnt%d", bllmcnt); // 文字を描画する
		if (bllmcnt > 300)bllmcnt = 300, bllmflg = 1;
		if (bllmcnt == 300)
		{
			bmt++;
			if (bmt >= 10)bmi++, bmt = 0;
			bmanitmp = bmani[bmi];
			if (bmi >= 27)bmi = 0, bllmcnt = 0, bllmflg = 0;
			DrawGraph(bmx - er, bmy, bmimage[bmanitmp], TRUE);      // 画像を表示
		}
		/* { 敵のbllmに当たった場合 } ***************************************************************************/
		/*アニメーションのピクセル数（当たり判定用に）
		No  x y
		1: 18,8 　 2: 22,16 　3: 24,24　  4: 28,32 　 5: 30,40 　 6: 34,48

		7: 36,56　 8: 40,64　 9: 44,72 　10: 46,80 　11: 46,80 　12: 46,80 */

		if (bllmflg == 1)//ビーム兄貴の当たり判定
		{
			if (bmanitmp >= 10 && bmanitmp <= 12)
			if (ep == 0 && px[i] + 32 >= bmx - 8 && px[i] <= bmx + 18 && py[i] >= bmy && py[i] <= bmy + 20
			|| px[i] + 32 >= bmx - 13 && px[i] <= bmx + 23 && py[i] >= bmy + 20 && py[i] <= bmy + 30
			|| px[i] + 32 >= bmx - 18 && px[i] <= bmx + 28 && py[i] >= bmy + 40 && py[i] <= bmy + 60
			|| px[i] + 32 >= bmx - 23 && px[i] <= bmx + 33 && py[i] >= bmy + 60 && py[i] <= bmy + 85)
			{
				if (out == 0 || out == 2)
				{
					out = 2;//ビームとの当たり判定が重ならないようにする
					pb = 1;
				}
			}
		}
		if (pb == 1)//吸い込まれアニメーション開始
		{
			     flg = 0, keyflg = 1; //非表示にして入力拒否状態にする
			 epx = px[i],epy = py[i]; //x座標設定 y座標設定
		     prote += 18;  //回転させる
			    ep  =  1;  //自機を敵状態にする
			     q  =  1;
			if (q == 1)//敵の座標に合わせる
			{
				t2++;//ちょっとずつ移動
				if (t2 >4 )t2 = 0;
				if (t2 >1 && py[i] >= ey + 20)py[i]--;
				if (t2 >1 && px[i] >= ex)px[i]--;
				if (t2 >1 && px[i] <= ex)px[i]++;
			}
			DrawFormatString(25, 25, color, "%d",t2); // 文字を描画するよ
			if (bmi == 0&&py[i] <= ey + 20)//敵機の前についたら
			{
				    q = 0;
				prote = 0;
				     t1++; //カウント開始
					 bllmcnt = 0;
			}
			if (t1 == 10)t1 = 0, py[i] -= 1;//ちょっとずつ移動させる
			if (py[i] <= ey - 32)//敵機の後ろについたら次の自機を表示
			{
				t1 = 0; pb = 0;
				i += 1; keyflg = 0; HP -= 1;
				hflg += 1; out = 0;
				flg = 1,bllm = 1;
			}
		}

		/* { 弾が敵に当たったら } *******************************************************************************/
		for (j = 0; j < 20; j++)
		{
			if (eflg == 0 && (sx[j] - ex) * (sx[j] - ex) + (sy[j] - ey) * (sy[j] - ey) <= (sr + er) * (sr + er)) //当たり判定
			{
				eflg = 1;
				sf[j] = 0;
				bmi = 0;
				bllmflg = 0;
				bllmcnt = 0;
				efp = 1;
			}
		}
		if (efp==1&&ep == 1)
		{
			fps = 1;
			prote += 18;
			if (prote >= (18 * 20 * 20) + 3)
			{
				prote = (18 * 20 * 20) + 3;
				if (px[i] >= epx-30)px[i]--;
				if (px[i] <= epx-30)px[i]++;
				keyflg = 1;
				efp = 1;
				if(py[i]>epy)epy++;
			}
			if (py[i] == epy)
			{
				keyflg = 0;
				if (epx >= px[i] + 28)epx -=3;
				if (epx < px[i] + 28)epx +=3;
			}
			if (fps == 1)DrawRotaGraph(epx, epy, psize, PI / 180 * prote, pimage[0], TRUE);
			DrawFormatString(550, 550, color, "%d",prote); // 文字を描画するよ
			DrawFormatString(750, 550, color, "%d", efp); // 文字を描画するよ
		}

		/* { ゲームオーバー時 } *********************************************************************************/
		if (HP <= 0) // HPが0になったら
		{
			hflg = 0; keyflg = 2;	         // キー入力を受け付けさせないようにしますううう
			DrawFormatString(250, 250, color, "GAME OVER\nAでリトライ"); // 文字を描画するよ
		}
		/* { その他 } *******************************************************************************************/
		if (i >= 16)i = 15, out = 3;//デバックやめたときデバックエラー文が出ないようにする
		ij = s / 70000;

		if (px[i] >= 700)i += 1, is -= 1;
		/* { 表示 } *********************************************************************************************/
		DrawFormatString(250, 200, color, "HP:%d", HP); // 文字を描画する
		if (is + ij + HP > 0)
		{
			DrawRotaGraph(px[i], py[i], psize, PI / 180 * 0, pimage[0], TRUE);
		}

		if (fps == 0 && ep == 1) //ダークサイド自機
		{
			if (epx >= ex)epx--;
			if (epx <= ex)epx++;
			DrawRotaGraph(epx, epy, psize, PI / 180 * prote, pimage[ep], TRUE);
		}

		if(eflg==0)DrawRotaGraph(ex, ey, 3.0, PI / 180 * 0, enemy[0], TRUE);
		/*********************************************************************************************************/

	}//whlie文の終わり
}