#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyborad.h"
#include "Keyborad2.h"
#include"bg.h"
#include"bgm.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	BGM_draw();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		SetGraphMode(1100, 800, 32);
		Keyborad();         //�L�[�{�[�h�̍X�V


		SceneMgr_Update();  //�X�V
		bg_All();           //�w�i�`��
		SceneMgr_Draw();    //�`��
			
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}