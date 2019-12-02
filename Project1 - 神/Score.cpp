#include "DxLib.h"
#include "Score.h"

typedef struct hiscore
{
	int score = 0;                          //スコア
	int h_score = 0;                       //ハイスコア
	char String[256];                     //保存変数

}HISCORE;

HISCORE high_score;

int scorex = 950, scorey = 200;            //スコア計算の座標
int high_scorex = 950, high_scorey = 90;  //ハイスコア計算座標
int Black = GetColor(0, 0, 0);            // 黒の色
int Red = GetColor(255, 0, 0);            //赤の色
int White = GetColor(255, 255, 255);      //塗りつぶす用（白）            
int FileHandle;                           //ファイル
FILE* fp;

//更新
void Score_Update() {
	high_score.score = 0;
}

//描画
void Score_Save() {

	//ハイスコアのファイルを開く
	FileHandle = FileRead_open("h_score.dat");

	// 一行読む
	FileRead_gets(high_score.String, 256, FileHandle);

	// 画面に描画
	DrawString(high_scorex, high_scorey, high_score.String, White);

	// ファイルを閉じる
	FileRead_close(FileHandle);
}


void Score_Draw() {
	

	//ハイスコアの記録
	fp = fopen("h_score.dat", "wb");
	fprintf(fp, "%d", high_score.h_score);

	fclose(fp);

	

	// ハイスコアの文字描画
	DrawFormatString(900, 30, Red, "HIGH ");
	DrawFormatString(950, 50, Red, " SCORE");

	//スコア文字の描画
	DrawFormatString(900, 160, Red, "1UP");

	//スコア数字の描画
	DrawFormatString(scorex, scorey, White, "%d", high_score.score);

	// ハイスコアの数字描画char型
	DrawFormatString(high_scorex, high_scorey, White, "%s", high_score.String);

	//char型からint型への変換
	high_score.h_score = atoi(high_score.String);

	//ハイスコア更新、スコア連動
	if (high_score.h_score < high_score.score) {
		SetDrawScreen(DX_SCREEN_BACK);  //塗りつぶし                        
		DrawBox(high_scorex, high_scorey, 1000, 150, Black, TRUE);

		//塗りつぶし後の描画
		high_score.h_score = high_score.score;
		DrawFormatString(high_scorex, high_scorey, White, "%d", high_score.h_score);
	}

}

void Score_Title() {
	
	//ハイスコアのファイルを開く
	FileHandle = FileRead_open("h_score.dat");

	// 一行読む
	FileRead_gets(high_score.String, 256, FileHandle);

	// 画面に描画
	DrawString(140, 90, high_score.String, White);

	// 画面に描画
	DrawString(390, 90, high_score.String, White);

	// ファイルを閉じる
	FileRead_close(FileHandle);

	//スコア数字の描画
	DrawFormatString(650, 90, White, "0");
}