#include "Game.h"
#include "windows.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Player.h"
#include "bg.h"
#include "Score.h"
#include "SceneMgr.h"
#include "bgm.h"
#include "Score.h"

void Player_All()
{
	 Player_Init();    //初期設定

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
		{							
			// 画面を初期化
			ClearDrawScreen();

			Player_Setup();        //設定
			Player_Draw();         //表示
			Player_Move();         //動き
			Player_Shot();         //弾
			Player_Animation();    //アニメーション
			Player_Hit();          //当たり判定
			Player_Enemy();        //敵(合併予定)

			bg_All();
			Enemy_all();
			Score_Draw();
		}//whlie文の終わり
}

void Player_Init()//初期設定
{
	LoadDivGraph("画像/自機.png", 2, 1, 2, 16, 16, p.image);                  // 自機画像の分割読み込み
	s.shot = LoadGraph("画像/bullet.png");                                    // 弾画像の読み込み
	LoadDivGraph("画像/Galaga_OBJ_enemy.png", 50, 5, 9, 20, 18, e.enemy);     // 敵の画像の分割読み込み
	LoadDivGraph("画像/Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, b.image);    // 画像の分割読み込み
	LoadDivGraph("画像/bakuhatu.png", 9, 9, 1, 32, 32, B.image);              // 爆破画像の分割読み込み
}

void Player_Setup()//設定
{
	if (p.i >= 10)p.i = 11, p.flg_i == false, p.judgment = 3, p.keyflg = 3;    //デバックやめたときデバックエラー文が出ないようにする
	p.HP_plus = p.score / 70000;
	if (p.HP_plus >= 7)p.HP_plus = 7;
	if (p.escape == true)p.y[p.i]++;
	if (p.y[p.i] == 700)p.escape = false;
	DrawString(690, 450, "こ\nれ\nよ\nり\n先\nHP\n減\nり\nま\nす", GetColor(255, 255, 255));
	if (p.x[p.i] >= 700)p.i += 1, p.HP_minus -= 1;
	if (p.dualbreak == 2)
	{
		p.i += 1, p.keyflg = 0; 
		p.HP -= 1;
		p.judgment = 0;
		p.dualbreak = 0;
		p.flg_i = true;
	}
}

void Player_Draw()//表示
{
	DrawFormatString(250, 200, color, "HP:%d", p.HP_minus + p.HP_plus + p.HP);    // 文字を描画する
	DrawFormatString(250, 100, color, "%d", p.score);                             // 文字を描画する
	if (p.flg_i == true && p.flg_j == true && p.HP_minus + p.HP_plus + p.HP > 0)
	{
		p.score += 100;
		DrawRotaGraph(p.x[p.i], p.y[p.i], p.size, PI / 180 * p.rote, p.image[0], TRUE);
	}

	if (p.player_recapture == false && e.player_capture == 1)    //ダークサイド自機
	{
		if (e.alter_x >= e.x)e.alter_x--;
		if (e.alter_x <= e.x)e.alter_x++;
		DrawRotaGraph(e.alter_x, e.alter_y, p.size, PI / 180 * e.rote, p.image[e.player_capture], TRUE);
	}

	/* { ゲームオーバー時 } ************************************************************************************************************************/
	if (p.HP_minus + p.HP_plus + p.HP <= 0)
	{
		p.keyflg = 2;    // キー入力を受け付けさせないようにしますううう
		DrawFormatString(250, 250, color, "GAME OVER\nESCでタイトル");   // 文字を描画するよ
	}
}

void Player_Move()//動き
{
	if (p.keyflg == 0)
	{
		// 右を押していたら右に進む
		if (CheckHitKey(KEY_INPUT_RIGHT)) p.x[p.i] += 3;

		// 左を押していたら左に進む
		if (CheckHitKey(KEY_INPUT_LEFT))  p.x[p.i] -= 3;

		//スペースが押されたら弾を打つ
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (s.sf2 == 0) {
				for (s.j = 0; s.j < SHOT; s.j++) {
					if (s.sf[s.j] == 0) {
						SE_draw();
						s.sx[s.j] = (p.r - s.sw) / 2 + p.x[p.i] - 10;
						s.sy[s.j] = (p.r - s.sh) / 2 + p.y[p.i] - 10;
						s.sf[s.j] = 1;

						break;
					}
				}
			}
			s.sf2 = 1;
		}
		else {
			s.sf2 = 0;
		}
	}

	if (p.keyflg == 2)    //ゲームオーバー時使用できるキー ESC予定
	{

	}

	if (p.keyflg == 3)
	{
		//スペースが押されたら弾を打つ
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (s.sf2 == 0) {
				for (s.j = 0; s.j < SHOT; s.j++) {
					if (s.sf[s.j] == 0) {
						s.sx[s.j] = (p.r - s.sw) / 2 + p.x[p.i] - 10;
						s.sy[s.j] = (p.r - s.sh) / 2 + p.y[p.i] - 10;

						s.sf[s.j] = 1;

						break;
					}
				}
			}
			s.sf2 = 1;
		}
		else {
			s.sf2 = 0;
		}
	}
	//プレイヤーの移動限度
	if (p.x[p.i]+p.w >= 800) p.x[p.i] = 800 - p.w;
	if (p.x[p.i] <= 0+p.w )   p.x[p.i] = 0+p.w;
}

void Player_Shot()//弾
{
	/* { 弾 } **************************************************************************************************************************************/
	for (s.j = 0; s.j < SHOT; s.j++) {
		if (s.sf[s.j] == 1) {
			s.sy[s.j] -= 16;
			if (s.sy[s.j] < -80) {
				s.sf[s.j] = 0;
			}

			DrawGraph(s.sx[s.j], s.sy[s.j], s.shot, TRUE);
			if (p.dualmode == true)
			{
				DrawGraph(s.sx[s.j] + 30, s.sy[s.j], s.shot, TRUE);
			}
		}
	}
	/* { 弾が敵に当たったら } **********************************************************************************************************************/
	for (s.j = 0; s.j < SHOT; s.j++)
	{
		if (s.sf[s.j] == 1 && e.flg == true && 
		   (s.sx[s.j] - e.x) * (s.sx[s.j] - e.x) + (s.sy[s.j] - e.y) * (s.sy[s.j] - e.y) <= (s.sr + e.r) * (s.sr + e.r))//当たり判定
		{
			e.flg = false;
			s.sf[s.j] = 0;
			b.i = 0;
			b.flg = false;
			b.bllmcnt = 0;
			e.Defeat = true;
			if (e.move_flg==true)
			{
				e.move_flg = false;
				p.rote = 0;
			    p.escape = true;
			}
		}
		if (p.dualmode == true)
		{
			if (s.sf[s.j] == 1 && e.flg == true && 
			   (s.sx[s.j] + 30 - e.x) * (s.sx[s.j] + 30 - e.x) + (s.sy[s.j] - e.y) * (s.sy[s.j] - e.y) <= (s.sr + e.r) * (s.sr + e.r)) //当たり判定
			{
				e.flg = false;
				s.sf[s.j] = 0;
				b.i = 0;
				b.flg = false;
				b.bllmcnt = 0;
				e.Defeat = true;
				if (e.move_flg == true)
				{
					e.move_flg = false;
					p.rote = 0;
				}
			}
		}
	}

	if (e.Defeat == true && e.player_capture == 1)     //自機持ちの敵だったら
	{
		p.player_recapture = true;
		e.rote += 18;
		p.keyflg = 1;
		if (p.x[p.i] >= e.alter_x - 30)p.x[p.i]--;
		if (p.x[p.i] <= e.alter_x - 30)p.x[p.i]++;
		if (e.rote >= (18 * 20 * 10) + 3)
		{
			e.rote = (18 * 20 * 10) + 3;
			if (p.y[p.i] > e.alter_y)e.alter_y++;
		}
		if (p.y[p.i] == e.alter_y)
		{
			p.keyflg = 0;
			p.dualmode = true;
			if (e.alter_x >= p.x[p.i] + 28)e.alter_x -= 3;
			if (e.alter_x < p.x[p.i] + 28)e.alter_x += 3;
		}
		if (p.player_recapture == true)DrawRotaGraph(e.alter_x, e.alter_y, p.size, PI / 180 * e.rote, p.image[0], TRUE);
	}
}

void Player_Animation()//アニメーション
{
	if (p.dualmode == false)
	{
		if (B.flg == true)
		{
			p.keyflg = 1;       //入力拒否 
			B.i++;              //爆破アニメーション開始
			if (B.i == 10)B.j += 1, B.i = 0;     //自機の爆破エフェクトスピードをいじるならifの条件を変える
			DrawRotaGraph(p.x[p.i], p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //爆破画像表示
		}
		if (B.j == 8)          //爆破アニメーションが終わったらリセットする
		{
			p.i += 1; p.keyflg = 0; p.HP -= 1;
			B.i = 0; B.j = 0;
			p.judgment = 0;
			B.flg = false;
		}
	}
	if (p.dualmode == true)
	{
		if (B.flg == true)
		{
			B.i++;              //爆破アニメーション開始
			if (B.i == 10)B.j += 1, B.i = 0;     //自機の爆破エフェクトスピードをいじるならifの条件を変える
			DrawRotaGraph(p.x[p.i], p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //爆破画像表示
		}
		if (B.j == 8)          //爆破アニメーションが終わったらリセットする
		{
			p.dualmode = false;
			p.flg_i = false;
			B.i = 0; B.j = 0;
			p.judgment = 0;
			B.flg = false;
			p.dualbreak++;
		}

		if (B.flg2 == true)
		{
			B.i++;              //爆破アニメーション開始
			if (B.i == 10)B.j += 1, B.i = 0;     //自機の爆破エフェクトスピードをいじるならifの条件を変える
			DrawRotaGraph(p.x[p.i] + 32, p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //爆破画像表示
		}
		if (B.j == 8)          //爆破アニメーションが終わったらリセットする
		{
			B.i = 0; B.j = 0;
			p.judgment = 0;
			p.dualbreak++;
			B.flg2 = false;
			p.dualmode = false;
			p.player_recapture = false;
			e.player_capture = 0;
		}
	}

	/**********************************************************************************************************************************************/
	//敵bllmアニメーション
	b.x = e.x;
	b.y = e.y + 15;
	if (e.flg == true && e.player_capture == 0)b.bllmcnt++;
	if (b.bllmcnt > 100)b.bllmcnt = 100, b.flg = true;
	if (b.bllmcnt == 100)
	{
		b.cnt++;
		if (b.cnt >= 10)b.i++, b.cnt = 0;
		b.tmp = b.ani[b.i];
		if (b.i >= 27)b.i = 0, b.bllmcnt = 0, b.flg = false;
		DrawGraph(b.x - 13 * 2, b.y - 5, b.image[b.tmp], TRUE);      // 画像を表示
	}
	/* { 敵のbllmに当たった場合 } ******************************************************************************************************************/
	/*アニメーションのピクセル数（当たり判定用に）
	No  x y
	1: 18,8 　 2: 22,16 　3: 24,24　  4: 28,32 　 5: 30,40 　 6: 34,48

	7: 36,56　 8: 40,64　 9: 44,72 　10: 46,80 　11: 46,80 　12: 46,80 */

	if (b.flg == true)    //ビーム兄貴の当たり判定
	{
		if (b.tmp >= 10 && b.tmp <= 12)
			if (e.player_capture == 0 &&
				p.x[p.i] + 16 >= b.x - 10 && p.x[p.i] <= b.x + 27 && p.y[p.i] >= b.y + 60 && p.y[p.i] <= b.y + 85)
			{
				if (p.judgment == 0 || p.judgment == 2)
				{
					p.judgment = 2;    //ビームとの当たり判定が重ならないようにする
					e.move_flg = true;
				}
			}
	}
	if (p.flg_i == true && p.HP_minus + p.HP_plus + p.HP > 0 && e.move_flg == true)    //吸い込まれアニメーション開始
	{
		p.keyflg = 3;    //移動だけ入力拒否状態にする
		e.alter_x = p.x[p.i], e.alter_y = p.y[p.i];    //x座標設定 y座標設定
		p.rote += 18;    //回転させる
		b.x_match = true;
		if (b.x_match == true)    //敵の座標に合わせる
		{
			b.t_i++;    //ちょっとずつ移動
			if (b.t_i > 4)b.t_i = 0;
			if (b.t_i > 1 && p.y[p.i] >= e.y + 20)p.y[p.i]--;
			if (b.t_i > 1 && p.x[p.i] >= e.x)p.x[p.i]--;
			if (b.t_i > 1 && p.x[p.i] <= e.x)p.x[p.i]++;
		}
		if (b.i <= 9)    //敵機の前についたら
		{
			p.flg_j = false;
			p.keyflg = 1;
			
			e.player_capture = 1;    //自機を敵状態にする
			b.x_match = false;
			p.rote = 0;
			b.t_j++;    //カウント開始
			b.bllmcnt = 0;
		}
		if (b.t_j == 10)b.t_j = 0, p.y[p.i] -= 1;    //ちょっとずつ移動させる
		if (p.y[p.i] <= e.y - 32)   //敵機の後ろについたら次の自機を表示
		{
			p.flg_j = true;
			b.t_j = 0; e.move_flg = false;
			p.i += 1; p.keyflg = 0; p.HP -= 1;
			p.judgment = 0;
		    e.player_capture = 1;
		}
	}

}

void Player_Hit()//当たり判定
{
	if (e.flg == true &&
		(p.x[p.i] - e.x) * (p.x[p.i] - e.x) + (p.y[p.i] - e.y) * (p.y[p.i] - e.y) <= (p.r + e.r) * (p.r + e.r)) //当たり判定
	{
		if (p.flg_i == true && p.judgment == 0 || p.judgment == 1)B.flg = true;    //ほかの当たり判定と重なってないならアニメーション再生
	}
	if (e.flg2 == true &&
		(p.x[p.i] - e.x2) * (p.x[p.i] - e.x2) + (p.y[p.i] - e.y2) * (p.y[p.i] - e.y2) <= (p.r + e.r) * (p.r + e.r)) //当たり判定
	{
		if (p.flg_i == true && p.judgment == 0 || p.judgment == 1)B.flg = true;    //ほかの当たり判定と重なってないならアニメーション再生
	}
	if (p.dualmode == true)
	{
		if (e.flg2 == true &&
			(p.x[p.i]+32 - e.x2) * (p.x[p.i] + 32  - e.x2) + (p.y[p.i] - e.y2) * (p.y[p.i] - e.y2) <= (p.r + 32 + e.r) * (p.r + e.r)) //当たり判定
		{
			if (p.judgment == 0 || p.judgment == 1)B.flg2 = true;    //ほかの当たり判定と重なってないならアニメーション再生
		}
	}
}
void Player_Enemy()//敵(合併予定)
{
	if (e.move_flg == false && e.sflg == true)e.x = e.x + e.s, e.y = e.y + e.s;
	if (e.x > 400)e.sflg = false;
	if (e.move_flg == false && e.sflg == false)e.x = e.x - e.s, e.y = e.y - e.s;
	if (e.x < 300)e.sflg = true;

	if (e.flg == true)DrawRotaGraph(e.x, e.y, 2.0, PI / 180 * 0, e.enemy[10], TRUE);
	if (e.flg2 == true)DrawRotaGraph(e.x2, e.y2, 2.0, PI / 180 * 0, e.enemy[10], TRUE);
}