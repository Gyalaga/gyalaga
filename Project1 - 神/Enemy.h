#ifndef _ENEMY_H_
#define _ENEMY_H_

//ザコの構造体
typedef struct {
	int x;			//x座標
	int y;			//y座標
	int cx;			//中心のx座標
	int cy;			//中心のy座標
	int image[5];	//画像格納用
	bool atk;		//攻撃フラグ
	bool onActive;	//表示フラグ
}ENEMY_ZAKO;

//ゴエイの構造体
typedef struct {
	int x;			//x座標
	int y;			//y座標
	int cx;			//中心のx座標
	int cy;			//中心のy座標
	int image[5];	//画像格納用
	bool atk;		//攻撃フラグ
	bool onActive;	//表示フラグ
}ENEMY_GOEI;

//ボスギャラガの構造体

typedef struct {
	int x;			//x座標
	int y;			//y座標
	int cx;			//中心のx座標
	int cy;			//中心のy座標
	int image[10];	//画像格納用
	bool atk;		//攻撃フラグ
	bool onActive;	//表示フラグ
}ENEMY_BOSS;

static int enemyImage[50];		//全enemyの画像を格納
static ENEMY_ZAKO zako[20];		//ザコのレコード
static ENEMY_GOEI goei[18];		//ゴエイのレコード
static ENEMY_BOSS boss[4];		//ボスギャラガのレコード
static bool enemyInit = true;			//エネミーの初期化フラグ

//enemyの更新
extern void Enemy_Update();

//ザコの攻撃時の処理
bool Enemy_Zako(int zakoAtk);

//ゴエイの攻撃時の処理
bool Enemy_Goei(int goeiAtk);

//ボスギャラガの攻撃時の処理
bool Enemy_Boss(int bossAtk);

//enemyの描画
extern void Enemy_Draw();

//enemyの初期化
extern void Enemy_Init();

//※削除予定
void Enemy_all();

#endif // !_ENEMY_H_
