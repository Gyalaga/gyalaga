#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyborad.h"

int GAME_Y = 900;    //�u�Q�[���v������y�ʒu
int GAME2_Y = 920;    //�u�ݒ�v������y�ʒu

typedef enum {
	eMenu_Game,       //�Q�[��
	eMenu_Config,    //�ݒ�
	eMenu_Num,        //���ڂ̐�
} eMenu;

static int Select = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��

//�X�V
void Menu_Update() {

	if (Keyborad_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
		Select = (Select + 1) % eMenu_Num;//�I����Ԃ��������
	}
	if (Keyborad_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		Select = (Select + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
	}
	if (Keyborad_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��

		switch (Select) {                            //���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Game:                           //�Q�[���I�𒆂Ȃ�
			GAME_Y = 900;
			GAME2_Y = 920;
			SceneMgr_ChangeScene(eScene_Game);       //�V�[�����Q�[����ʂɕύX
			break;
		case eMenu_Config://�ݒ�I�𒆂Ȃ�
			GAME_Y = 900;
			GAME2_Y = 920;
			SceneMgr_ChangeScene(eScene_Game);    //�V�[����ݒ��ʂɕύX
			break;
		}
	}
}

//�`��
void Menu_Draw() {

	DrawString(200, 150, "���j���[��ʂł��B", GetColor(255, 255, 255));
	DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
	DrawString(400, GAME_Y, "1PLAYER", GetColor(255, 255, 255));
	DrawString(400, GAME2_Y, "2PLAYER", GetColor(255, 255, 255));

	if (GAME_Y > 250) {
		GAME_Y -= 1;
	}
	if(GAME2_Y > 270) {
		GAME2_Y -= 1;
	}
	

	int y = 0;
	switch (Select) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�
		y = GAME_Y;    //�Q�[���̍��W���i�[
		break;
	case eMenu_Config://�ݒ�I�𒆂Ȃ�
		y = GAME2_Y;    //�ݒ�̍��W���i�[
		break;
	}
	DrawString(250, y, "��", GetColor(255, 255, 255));
}