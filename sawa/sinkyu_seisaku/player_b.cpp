#include "DxLib.h"
int Key[256]; // �L�[��������Ă���t���[�������i�[���܂�������

// �L�[�̓��͏�Ԃ��X�V���܂�������
int gpUpdateKey()
{
	char tmpKey[256];               // ���݂̃L�[�̓��͏�Ԃ��i�[���܂�������
	GetHitKeyStateAll(tmpKey);      // �S�ẴL�[�̓��͏�Ԃ𓾂܂�������
	for (int j = 0; j < 256; j++)
	{
		if (tmpKey[j] != 0)         // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		{
			Key[j]++;               // ���Z���܂�������
		}
		else
		{                           // ������Ă��Ȃ����
			Key[j] = 0;             // 0�ɂ��܂�������
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	int px = 0, py = 0, ph = 16, pw = 16, image[32];  //���@�̍��W�Ɖ摜�ϐ��ł�������
	int pi = 0, pj = 0, ps = 0;                      //pi:���@�摜�̉�]�p,pj:����]���邩,ps:��]���x
	int keyflg = 0, HP = 3;                          //keyflg:���͋��ۗp,HP:�̗�
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //�G�̍��W�Ɖ摜�ϐ��ł�������
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:���j�G�t�F�N�g�̑���,bj:�\��,�摜�ϐ��p
	int color = GetColor(255, 255, 255);             //�F�R�[�h���擾
	int shot;                                     //�e�̉摜
	int sx[20], sy[20], sw = 9, sh = 12, i;                                 //�e�̍��W
	int sf[20]; //�e�̔��˃t���O
	int sf2;
	int Simage[10];

	shot = LoadGraph("bullet.png");
	enemy = LoadGraph("Player.bmp");                            // �G�̉摜
	LoadDivGraph("dairi.png", 16, 16, 2, 17, 17, image);        // ���@�摜�̕����ǂݍ���
	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // ���j�摜�̕����ǂݍ���
			   //�摜�̖��O�A�������鐔�A���������A�c�������A��������摜�̃T�C�Y�A�ϐ���

	for (i = 0; i < 20; i++) {
		sf[i] = 0;
	}
	sf2 = 0;

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		// ��ʂ����������܂�������
		ClearDrawScreen();
		// �L�[���͎擾�@�Q�[���I�[�o�[�����͋��ۂ�������������if���̒��ɓ����
		Key[256] = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (keyflg == 0)
		{
			// ��������Ă������ɐi��
			if (Key[256] & PAD_INPUT_UP)    py -= 3;

			// ���������Ă����牺�ɐi��
			if (Key[256] & PAD_INPUT_DOWN)  py += 3;

			// �E�������Ă�����E�ɐi��
			if (Key[256] & PAD_INPUT_RIGHT) px += 3;

			// ���������Ă����獶�ɐi��
			if (Key[256] & PAD_INPUT_LEFT)  px -= 3;

			
			//�X�y�[�X�������ꂽ��e��ł�
			if (CheckHitKey (KEY_INPUT_SPACE)) {
				if (sf2==0) {
					for (i = 0; i < 20; i++) {
						if (sf[i] == 0) {
							sx[i] =( pw - sw) / 2 + px;
							sy[i] = (ph - sh) / 2 + py;

							sf[i] = 1;

							break;
						}

					}
					
				}
				sf2 = 1;
			}
			else {
				sf2 = 0;
			}
		}

		for (i = 0; i < 20; i++) {
			if (sf[i] == 1) {
				sy[i] -= 16;
				if (sy[i] < -80) {
					sf[i] = 0;
				}

				DrawGraph(sx[i], sy[i], shot, TRUE);
			}
		}
		
		
		

		if (keyflg == 2)
		{
			if (Key[KEY_INPUT_A] == 1)
			{
				px = 0;     py = 0;
				pi = 0;     pj = 0;
				keyflg = 0; HP = 3;
				bi = 0;     bj = 0;
			}
		}

		{   //�v���C���[�̈ړ����x
			if (px >= 610)  px = 610;
			if (px <= 0)    px = 0;
			if (py >= 450)  py = 450;
			if (py <= 0)    py = 0;
		}

		if (px >= ex - pw && px <= ex + ew && py >= ey - ph && py <= ey + eh)//�����蔻��
		{              //����������L�[���͋��ۂ��ĉ摜�𓮂����Ȃ���J�E���g�_�E�����܂�
			keyflg = 1;//���͋���
			ps++;
		}

		if (pi == 15)pi = 0, pj += 1; //i�ɏ����ݒ肵�ăJ�E���g���܂�������

		if (pj > 2)        //�摜�����܂������Ȃ��̂ŉ摜�z��Ƃ��Ă͑��݂��Ȃ��z��ԍ��ɂ��܂�������
		{
			pi = 16;
			bi++;
			if (bi == 10)bj += 1, bi = 0;                  //���@�̔��j�G�t�F�N�g�X�s�[�h��������Ȃ炱��
			DrawGraph(px, py, bakuhaimage[bj], TRUE); // �摜��\�����܂�������
		}

		if (ps == 3) ps = 0, pi += 1;//���@����]�̃X�s�[�h��������Ȃ炱��

		if (bj == 13)  //���Z�b�g
		{
			px = 0;     py = 0;
			pi = 0;     pj = 0;
			keyflg = 0; HP -= 1;
			bi = 0;     bj = 0;
		}

		if (HP == 0) // HP��0�ɂȂ�����
		{
			pi = 16; keyflg = 2;	         // �L�[���͂��󂯕t�������Ȃ��悤�ɂ��܂�������
			DrawFormatString(250, 250, color, "GAME OVER\nA�Ń��g���C"); // ������`�悷���
		}
		DrawFormatString(250, 200, color, "HP:%d", HP); // ������`�悷��
		DrawGraph(ex, ey, enemy, TRUE);       // �摜��\�����܂�������
		DrawGraph(px, py, image[pi], TRUE);   // �摜��\�����܂�������
		//�e�̕`��
		
	}
	DxLib_End(); // DX���C�u�����I���������܂�������
	return 0;
}