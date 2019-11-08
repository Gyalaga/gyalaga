#include "DxLib.h"
#define PI 3.141592654
#define WIDTH 175
#define HIGHT 175
#define STARTx 70
#define STARTy 620
#define STARTw 200
#define STARTh 130

int peace[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Lol,     //説明
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
	eScene_Score,   //スコア画面

} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)


void irekae(int px, int py) {
	int Green = GetColor(0, 255, 0);
	DrawString(0, 0, "入れ替わります", GetColor(0, 0, 0));
	DrawFormatString(py, px, Green, "座標[%d,%d]", py, px); 
	int p1 = (py * 4) + px;
	int p2 = -1;
	if (px > 0 && peace[p1 - 1] == 15) p2 = p1 - 1;
	if (px < 3 && peace[p1 + 1] == 15) p2 = p1 + 1;
	if (py > 0 && peace[p1 - 4] == 15) p2 = p1 - 4;
	if (py < 3 && peace[p1 + 4] == 15) p2 = p1 + 4;
	if (p2 != -1) {
		peace[p2] = peace[p1];
		peace[p1] = 15;
	}
}

//シーンを更新する
void UpdateScene() {
	//DrawString(0, 20, "Gキーでゲーム画面、Cキーで設定、Mキーでメニュー画面になります。", GetColor(255, 255, 255));

}

//メニュー画面
void Menu() {
	//DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
	int Title = LoadGraph("画像/haikeihonmei1.png");
	int Start = LoadGraph("画像/kaisi.png");
	int End = LoadGraph("画像/owari.png");
	int Neko = LoadGraph("画像/nekoneko.png");
	DrawGraph(0, 0, Title, TRUE); //タイトルを描画
	DrawGraph(300, 125, Neko, TRUE); //猫を描画
	DrawGraph(STARTx, STARTy, Start, TRUE); // 背景を描画
	DrawGraph(STARTx + 400, STARTy, End, TRUE); // 背景を描画

	int Mouse;
	Mouse = GetMouseInput();
	DrawString(0, 20, "左クリックでゲーム画面、右クリックで終了、", GetColor(255, 255, 255));
	if (Mouse & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX >= STARTx && mouseX < (STARTx + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			int mouseX, mouseY;
			Scene = eScene_Lol;
		}
		if (mouseX >= STARTx + 300 && mouseX < (STARTx + 300 + STARTw) && mouseY >= STARTy && mouseY < (STARTy + STARTh)) {
			//int mouseX, mouseY;
			DxLib_End(); // DXライブラリ終了処理
		}
	}
	//if (Mouse & MOUSE_INPUT_RIGHT) {
	//	DxLib_End(); // DXライブラリ終了処理
	//}
}
//説明画面
void Lol() {
	int bg = LoadGraph("画像/gamehaikei.png");
	int setumei = LoadGraph("画像/pop.png");

	DrawGraph(0, 0, bg, TRUE); //背景
	DrawGraph(0, 0, setumei, TRUE); //説明pop

	DrawString(0, 0, "エンターキーを押してゲーム開始！", GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		Scene = eScene_Game;
	}
}
//ゲーム画面
void Game() {
	int nx = 0; int ny = 0;
	int x, y;
	int cnt = 0;
	int timelimit;
	int image[16];
	LONGLONG timecnt;

	int haikei = LoadGraph("画像/gamehaikei.png");
	int waku = LoadGraph("画像/waku.png");
	LoadDivGraph("画像/nekotyan.png", 16, 4, 4, WIDTH, HIGHT, image); // 画像の分割読み込み
	image[15] = LoadGraph("画像/black.png");

	SetAlwaysRunFlag(TRUE);						//非アクティブでも処理を行う

	timecnt = GetNowHiPerformanceCount();

	timelimit = 00000000;
	timecnt = GetNowHiPerformanceCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_SPACE) == 0) {

		ClsDrawScreen();			//画面に描かれているものを一回全部消す

		SetFontSize(20);
		SetFontThickness(8);                         //太さを8に変更
		DrawGraph(0, 0, haikei, TRUE); // 背景を描画
		DrawGraph(nx - 10, ny - 10, waku, FALSE); // 背景を描画
		DrawString(0, 0, "ゲーム画面です。", GetColor(0, 0, 0));
		DrawString(0, 25, "SPACEキー　→　設定画面　", GetColor(0, 0, 0));

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				DrawGraph(nx + (j * WIDTH), ny + (i * HIGHT), image[(i * 4) + j], TRUE);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (image[(i * 4) + j] == (i * 4) + j) {
					cnt++;
				}
			}
		}
		if (cnt == 16) {
			Scene = eScene_Score;
			break;
		}
		else {
			cnt = 0;
		}
		int Mouse = GetMouseInput();

		GetMousePoint(&x, &y);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (x > nx + (j * WIDTH) && x<nx + (j * WIDTH) + WIDTH && y>ny + (i * HIGHT) && y < ny + (i * HIGHT) + HIGHT) {
					if (Mouse & MOUSE_INPUT_LEFT) {
						DrawString(0, 0, "ゲーム画面です。", GetColor(0, 0, 0));
						irekae(x / WIDTH, y / HIGHT);
					}
				}
			}
		}
		//制限時間
		if (GetNowHiPerformanceCount() + timecnt >= 10000) {
			timecnt = GetNowHiPerformanceCount();
			timelimit += 10000;
		}
		//制限時間表示
		SetFontSize(36);                             //サイズを64に変更
		SetFontThickness(8);                         //太さを8に変更
		ChangeFont("ＭＳ 明朝");                     //種類をMS明朝に変更
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);     //アンチエイリアスフォントに変更

		DrawFormatString(475, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timelimit / 60000000, (timelimit % 60000000) / 1000000, ((timelimit % 60000000) % 1000000) / 100000, (((timelimit % 60000000) % 1000000) % 100000) / 10000);

		ScreenFlip();				//裏画面の内容を表画面に反映させる
	}
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
		Scene = eScene_Score;
	}

}


//設定画面
void Config() {
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 30, "ENTERキー →　ゲーム画面", GetColor(255, 255, 255));
	int sceneflg = 0;
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		Scene = eScene_Game;
	}
}
void Score() {
	DrawString(0, 0, "スコア画面です。", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetGraphMode(800, 800, 32);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//現在のシーンにあった処理をする
		case eScene_Menu://現在のシーンがメニューなら
			Menu();//メニュー画面
			break;
		case eScene_Lol://現在のシーンがルールなら
			Lol();//ルール画面
			break;
		case eScene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		case eScene_Config://現在のシーンが設定なら
			Config();//設定画面
			break;
		case eScene_Score://現在のシーンがスコアなら
			Score();//スコア画面
		}

		UpdateScene();//シーンを更新する

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}