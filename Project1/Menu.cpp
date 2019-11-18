#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyborad.h"

int GAME_Y = 1170;    //�u1PLAYER�v������y���W
int GAME2_Y = 1210;   //�u2PLAYER�v������y���W
int TITLE_Y = 900;   //�u�^�C�g�����S�v��y���W
int SCORE_Y = 800;   //�uHI-SCORE�v�̂����W
int ONEUP_Y = 800;   //�u1UP�v�̂����W
int TWOUP_Y = 800;   //�u2UP�v�̂����W
int NAMCO_Y = 1350;  //�unamco�v�̂����W
int NANKA_Y = 1430;
int NANKA2_Y = 1460;

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

	SetFontSize(26);                             //�T�C�Y��64�ɕύX
	SetFontThickness(8);
	ChangeFont("font/PixelMplus12-Bold.ttf");

		DrawString(350, GAME_Y, "1PLAYER", GetColor(255, 255, 255));
		DrawString(350, GAME2_Y, "2PLAYER", GetColor(255, 255, 255));
		DrawString(325, SCORE_Y, "HI--SCORE", GetColor(255, 255, 255));
		DrawString(100, ONEUP_Y, "1UP", GetColor(255, 255, 255));
		DrawString(675, TWOUP_Y, "2UP", GetColor(255, 255, 255));
		DrawString(250, NANKA_Y, "1981�@1985�@NAMCO�@LTD", GetColor(255, 255, 255));
		DrawString(250, NANKA2_Y, "ALL�@RIGHTS�@RESERVED", GetColor(255, 255, 255));

		static int title = LoadGraph("�摜/Gyaraga.jpg");
		DrawGraph(250, TITLE_Y, title, TRUE);

		static int namco = LoadGraph("�摜/namco.png");
		DrawGraph(250, NAMCO_Y, namco, TRUE);

		if (GAME_Y > 420) {     //1PLAYER��y���W��520�ɍs���܂ŁA��ɍs��������
			GAME_Y -= 2;
		}
		if (GAME2_Y > 460) {     //2PLAYER��y���W��550�ɍs���܂ŁA��ɍs��������
			GAME2_Y -= 2;
		}
		if (TITLE_Y > 150) {    //TITLE��y���W��150�ɍs���܂ŁA��ɍs��������
			TITLE_Y -= 2;
		}
		if (SCORE_Y > 50) {     //SCORE��y���W��50�ɍs���܂ŁA��ɍs��������
			SCORE_Y -= 2;
		}
		if (ONEUP_Y > 50) {     //ONEUP��y���W��50�ɍs���܂ŁA��ɍs��������
			ONEUP_Y -= 2;
		}
		if (TWOUP_Y > 50) {     //TWOUP��y���W��50�ɍs���܂ŁA��ɍs��������
			TWOUP_Y -= 2;
		}
		if (NAMCO_Y > 600) {    //NAMCO��y���W��700�ɍs���܂ŁA��ɍs��������
			NAMCO_Y -= 2;
		}
		if (NANKA_Y > 680) {
			NANKA_Y -= 2;
		}
		if (NANKA2_Y > 710) {
			NANKA2_Y -= 2;
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