
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	static int image[12];
	int x = 0, y = 0, i = 0, cnt = 0, anitmp = 0;
	int ani[24] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,9,8,7,6,5,4,3,2,1,0 };
	LoadDivGraph("Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, image); // �摜�̕����ǂݍ���

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		cnt += 1;
		if (cnt >= 10) {
			i += 1;
			cnt = 0;
		}
		anitmp = ani[i];

		DrawGraph(0, 0, image[anitmp], TRUE);      // �摜��\��


	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}