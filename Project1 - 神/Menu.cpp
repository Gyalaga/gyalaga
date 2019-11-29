#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyborad.h"

int GAME_Y = 1170;    //「1PLAYER」文字のy座標
int GAME2_Y = 1210;   //「2PLAYER」文字のy座標
int TITLE_Y = 900;   //「タイトルロゴ」のy座標
int SCORE_Y = 800;   //「HI-SCORE」のｙ座標
int ONEUP_Y = 800;   //「1UP」のｙ座標
int TWOUP_Y = 800;   //「2UP」のｙ座標
int NAMCO_Y = 1350;  //「namco」のｙ座標
int NANKA_Y = 1430;
int NANKA2_Y = 1460;

typedef enum {
	eMenu_Game,       //ゲーム
	eMenu_Config,    //設定
	eMenu_Num,        //項目の数
} eMenu;

static int Select = eMenu_Game;    //現在の選択状態(初期はゲーム選択中

//更新
void Menu_Update() {

	if (Keyborad_Get(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
		Select = (Select + 1) % eMenu_Num;//選択状態を一つ下げる
	}
	if (Keyborad_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		Select = (Select + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	}
	if (Keyborad_Get(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら

		switch (Select) {                            //現在選択中の状態によって処理を分岐
		case eMenu_Game:                           //ゲーム選択中なら
			GAME_Y = 900;
			GAME2_Y = 920;
			SceneMgr_ChangeScene(eScene_Game);       //シーンをゲーム画面に変更
			break;
		case eMenu_Config://設定選択中なら
			GAME_Y = 900;
			GAME2_Y = 920;
			SceneMgr_ChangeScene(eScene_Game);    //シーンを設定画面に変更
			break;
		
		}
	}
}

//描画
void Menu_Draw() {

	SetFontSize(26);                             //サイズを64に変更
	SetFontThickness(8);
	ChangeFont("font/PixelMplus12-Bold.ttf");

		DrawString(350, GAME_Y, "1PLAYER", GetColor(255, 255, 255));
		DrawString(350, GAME2_Y, "2PLAYER", GetColor(255, 255, 255));
		DrawString(325, SCORE_Y, "HI--SCORE", GetColor(255, 255, 255));
		DrawString(100, ONEUP_Y, "1UP", GetColor(255, 255, 255));
		DrawString(675, TWOUP_Y, "2UP", GetColor(255, 255, 255));
		DrawString(250, NANKA_Y, "1981　1985　NAMCO　LTD", GetColor(255, 255, 255));
		DrawString(250, NANKA2_Y, "ALL　RIGHTS　RESERVED", GetColor(255, 255, 255));

		static int title = LoadGraph("画像/Gyaraga.jpg");
		DrawGraph(250, TITLE_Y, title, TRUE);

		static int namco = LoadGraph("画像/namco.png");
		DrawGraph(250, NAMCO_Y, namco, TRUE);

		if (GAME_Y > 420) {     //1PLAYERのy座標が520に行くまで、上に行き続ける
			GAME_Y -= 2;
		}
		if (GAME2_Y > 460) {     //2PLAYERのy座標が550に行くまで、上に行き続ける
			GAME2_Y -= 2;
		}
		if (TITLE_Y > 150) {    //TITLEのy座標が150に行くまで、上に行き続ける
			TITLE_Y -= 2;
		}
		if (SCORE_Y > 50) {     //SCOREのy座標が50に行くまで、上に行き続ける
			SCORE_Y -= 2;
		}
		if (ONEUP_Y > 50) {     //ONEUPのy座標が50に行くまで、上に行き続ける
			ONEUP_Y -= 2;
		}
		if (TWOUP_Y > 50) {     //TWOUPのy座標が50に行くまで、上に行き続ける
			TWOUP_Y -= 2;
		}
		if (NAMCO_Y > 600) {    //NAMCOのy座標が700に行くまで、上に行き続ける
			NAMCO_Y -= 2;
		}
		if (NANKA_Y > 680) {
			NANKA_Y -= 2;
		}
		if (NANKA2_Y > 710) {
			NANKA2_Y -= 2;
		}

		int y = 0;
		switch (Select) {//現在の選択状態に従って処理を分岐
		case eMenu_Game://ゲーム選択中なら
			y = GAME_Y;    //ゲームの座標を格納
			break;
		case eMenu_Config://設定選択中なら
			y = GAME2_Y;    //設定の座標を格納
			break;
		}
		DrawString(250, y, "■", GetColor(255, 255, 255));
	}