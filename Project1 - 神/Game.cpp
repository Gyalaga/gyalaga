#include "Game.h"
#include "SceneMgr.h"
#include "Score.h"
#include "Keyborad2.h"
#include "DxLib.h"
#include "bgm.h"
#include "Player.h"
#include "Enemy.h"
//#include"tama.h"

//�X�V
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game_Draw() {
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
	Keysecond();
	//tama_ALL();
	Player_all();	//�v���C���[�̍X�V

}