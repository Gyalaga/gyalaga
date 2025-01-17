#include"DxLib.h"

static int Key[256];  //キーの入力状態を格納

//キーの入力状態を更新
void Keyborad() {

	char tmpKey[256];           // 現在のキーの入力状態を格納
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++) {

		if (tmpKey[i] != 0) { //i番のキーコードに対応するキーが押されていたら
			Key[i]++;         //加算
		}
		else {                //押されていなければ
			Key[i] = 0;       //0にする
		}
	}
}

// KeyCodeのキーの入力状態を取得する

int Keyborad_Get(int KeyCode) {

	return Key[ KeyCode ];
}

