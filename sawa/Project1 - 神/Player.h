#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PI 3.14    // 角度求めるのに使用
#define SHOT 2     // 弾の最大数

typedef struct
{
	int x[16] = { 400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400 };
	int y[16] = { 700,700,700,700,700,700,700,700,700,700,700,700,700,700,700,700 };
	int	rote = 0, size = 2, w = 16;            // rote:自機角度,  size:自機サイズ, w:横幅
	int	r = 16 * size / 2, image[2];           // r:中心, iamge:画像変数
	int HP = 3, i = 0, score = 0;              // HP:体力, i:操作番号, score:スコア
	int HP_plus = 0, HP_minus = 0;             // HP_plus:残機増に使用, HP_minus:残機減に使用
	int judgment = 0;                          // judgment:他の当たり判定と重ならないようにするフラグ
	int dualbreak =0;
	int keyflg = 0;

	bool flg_i = true;                         // flg_i:表示用フラグ1
	bool flg_j = true;                         // flg_j:表示用フラグ2
	bool escape = false;                       // トラクタービームからの脱出に成功
	bool player_recapture = false;             // 奪還
	bool dualmode = false;                     // モードデュアル
}Player;// Playerの構造体	

typedef struct//HIO4担当
{
	int shot;                    
	int Simage[10];                            // 弾の画像
	int sx[SHOT], sy[SHOT];                    // 弾の座標
	int	sx2[SHOT], sy2[SHOT];                  // デュアルモード時の弾の座標
	int sw = 7, sh = 12;                       // 弾の縦幅,横幅
	int sr = sw / 2;                           // 弾の中心
	int sf[SHOT];                              // 弾の発射フラグ
	int sf2;
	int j;
}Shot;// Shotの構造体

typedef struct
{ 
	int x = 300, y = 600;                      // 敵の座標
	int x2 = 600, y2 = 700;                    // 敵の座標
	bool flg2 = true;                          // flg:表示フラグ
	int r = 14 * 2 / 2, enemy[50];             // 画像変数
	int player_capture = 0;                    // 囚われの自機
	int alter_x, alter_y;                      // 敵自機用
	int s = 1,rote = 0;                        // s:敵スピード, rote; 敵自機角度

	bool Defeat = false;                       // 破壊
	bool flg = true;                           // flg:表示フラグ
	bool sflg = true;                          // 左右移動[false=左 || true=右]
	bool move_flg = false;                     // 敵移動フラグ
}Enemy;// Enemyの構造体(後で一部残して消去予定)

typedef struct
{
	int image[12];                             // ビームの画像
	int x = 0, y = 0;                          // 座標
	int i = 0, tmp = 0;                        // i:画像回し用, tmp:画像番号記録用
	int bllmcnt = 0, cnt = 0;                  // bllmcnt:ビーム発射カウント, cnt:アニメーションの速さ
	int ani[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,11,10,11,10,11,10,9,8,7,6,5,4,3,2,1,0 };
	int t_i = 0, t_j = 0;                      // カウント用

	bool x_match = false;                      // 座標合わせ用
	bool flg = false;                          // 表示フラグ
}Bllm;//トラクタービームの構造体

typedef struct
{
	int i = 0, j = 0;                          // i:爆破エフェクトの速さ, j:表示
	int image[13];                             // 画像変数用

	bool flg = false;                          // 表示フラグ
	bool flg2 = false;                          // 表示フラグ
}Bom;//爆破アニメーションの構造体


static int color = GetColor(255, 255, 255);    // keyflg:入力拒否用　色コードを取得


static Player p;            // Playerの構造体
static Shot s;              // Shotの構造体
static Enemy e;             // Enemyの構造体(後で一部残して消去予定)
static Bllm b;              //トラクタービームの構造体
static Bom B;               //爆破アニメーションの構造体

void Player_Init();         //初期設定

void Player_Setup();        //設定

void Player_Draw();         //表示

void Player_Move();         //動き

void Player_Shot();         //弾

void Player_Animation();    //アニメーション

void Player_Hit();          //当たり判定

void Player_All();          //呼び出し

void Player_Enemy();        //敵(合併予定)

#endif // !_PLAYER_H_




