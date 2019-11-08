#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyborad.h"

int GAME_Y = 900;    //「ゲーム」文字のy位置
int GAME2_Y = 920;    //「設定」文字のy位置

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

	DrawString(200, 150, "メニュー画面です。", GetColor(255, 255, 255));
	DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
	DrawString(400, GAME_Y, "1PLAYER", GetColor(255, 255, 255));
	DrawString(400, GAME2_Y, "2PLAYER", GetColor(255, 255, 255));

	if (GAME_Y > 250) {
		GAME_Y -= 1;
	}
	if(GAME2_Y > 270) {
		GAME2_Y -= 1;
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