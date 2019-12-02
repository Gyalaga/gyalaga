#include "DxLib.h"
#include "windows.h"
#include "SceneMgr.h"
#include "Keyborad.h"
#include"bg.h"
#include"bgm.h"

void SE_draw() {

	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	static int SE_BM = LoadSoundMem("BGM&SE/BM.wav");

	PlaySoundMem(SE_BM, DX_PLAYTYPE_BACK);
}

void BGM_draw() {

	//static int MAIN_BGM = LoadSoundMem("BGM&SE/Ave Maris Stella.mp3");
	static int MAIN_BGM = LoadSoundMem("BGM&SE/フリージア.mp3");

	PlaySoundMem(MAIN_BGM, DX_PLAYTYPE_LOOP); // メインのBGM

}
