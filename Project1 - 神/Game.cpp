#include "Game.h"
#include "SceneMgr.h"
#include "Score.h"
#include "Keyborad2.h"
#include "DxLib.h"
#include "bgm.h"
#include "Player.h"
#include "Enemy.h"
//#include"tama.h"

//更新
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Game_Draw() {
	DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	Keysecond();
	//tama_ALL();
	Player_all();	//プレイヤーの更新

}