#pragma once

//ザコの構造体
typedef struct {
	float x;
	float y;
	int cx;
	int cy;
	int image;
	bool atk;
}ENEMY_ZAKO;

//ゴエイの構造体
typedef struct {
	int x;
	int y;
	int cx;
	int cy;
	int image;
}ENEMY_GOEI;

//ボスギャラガの構造体
typedef struct {
	int x;
	int y;
	int cx;
	int cy;
	int image;
}ENEMY_BOSS;

static int enemyImage[50];		//全エネミーの画像を格納する変数
static ENEMY_ZAKO zako[20];		//ザコの構造体を配列に
static ENEMY_GOEI goei[18];		//ゴエイの構造体を配列に
static ENEMY_BOSS boss[4];		//ボスギャラガの構造体を配列に
static bool enemyinit = true;	//エネミーの初期化用flg
static int playerX;
static int playerY;

//エネミーの更新
void Enemy_Update();

//エネミーの描画
void Enemy_Draw();

//エネミーの初期化
void Enemy_Init();

//プレイヤー座標の取得
void Load_Player(int, int);

void Enemy_all();
