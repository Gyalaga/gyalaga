#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"

typedef struct hiscore
{
	int score = 0;                          //スコア
	int h_score = 0;                       //ハイスコア
	char String[256];                     //保存変数

}HISCORE;

HISCORE high_score;
int scorex = 900, scorey = 170;           //スコア計算の座標
int high_scorex = 900, high_scorey = 90;  //ハイスコア計算座標
int Black = GetColor(0, 0, 0);      // 白の色
int Red = GetColor(255, 0, 0);            //赤の色
int White = GetColor(255, 255, 255);            //塗りつぶす用（黒）                                         // キーが押されているフレーム数を格納する
int FileHandle;                           //ファイル
FILE* fp;

//更新
void Score_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		high_score.score = 0;             //初期化
	}
}

void Score_Title() {
	FileHandle = FileRead_open("h_score.dat");

	// 一行読む
	FileRead_gets(high_score.String, 256, FileHandle);

	// 画面に描画
	DrawString(375, 100, high_score.String, White);

	// ファイルを閉じる
	FileRead_close(FileHandle);

}


//スコア更新のセーブ
void Score_Save() {

	//ハイスコアのファイルを開く
	FileHandle = FileRead_open("h_score.dat");

	// 一行読む
	FileRead_gets(high_score.String, 256, FileHandle);

	// 画面に描画
	DrawString(high_scorex, high_scorey, high_score.String, Black);

	// ファイルを閉じる
	FileRead_close(FileHandle);
}

//描画
void Score_Draw() {
	//DrawString(0, 0, "スコア画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));

	//ハイスコアの記録
	fp = fopen("h_score.dat", "wb");
	fprintf(fp, "%d", high_score.h_score);

	fclose(fp);

	high_score.score += 10;

	// ハイスコアの文字描画
	DrawFormatString(860, 30, Red, "HIGH ");
	DrawFormatString(900, 50, Red, " SCORE");

	//スコア文字の描画
	DrawFormatString(900, 130, Red, "1UP");

	//スコア数字の描画
	DrawFormatString(scorex, scorey, Black, "%d", high_score.score);

	// ハイスコアの数字描画char型
	DrawFormatString(high_scorex, high_scorey, Black, "%s", high_score.String);



	//char型からint型への変換
	high_score.h_score = atoi(high_score.String);

	//ハイスコア更新、スコア連動
	if (high_score.h_score < high_score.score) {
		SetDrawScreen(DX_SCREEN_BACK);  //塗りつぶし                        
		DrawBox(high_scorex, high_scorey, 1100, 120, White, TRUE);

		//塗りつぶし後の描画
		high_score.h_score = high_score.score;
		DrawFormatString(high_scorex, high_scorey, Black, "%d", high_score.h_score);
	}
}
