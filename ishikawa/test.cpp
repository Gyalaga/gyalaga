#include "DxLib.h"

#define SHOT 2

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
	int px = 0, py = 500, ph = 16, pw = 16, image[32]; //���@�̍��W�Ɖ摜�ϐ��ł�������
	int pi = 0, pj = 0, ps = 0;                      //pi:���@�摜�̉�]�p,pj:����]���邩,ps:��]���x
	int keyflg = 0, HP = 3;                          //keyflg:���͋��ۗp,HP:�̗�
	int ex = 100, ey = 100, eh = 60, ew = 30, enemy; //�G�̍��W�Ɖ摜�ϐ��ł�������
	int bi = 0, bj = 0, bakuhaimage[13];             //bi:���j�G�t�F�N�g�̑���,bj:�\��,�摜�ϐ��p
	int color = GetColor(255, 255, 255);             //�F�R�[�h���擾
	int shot;                                        //�e�̉摜
	int sx[SHOT], sy[SHOT],
		sx2[SHOT], sy2[SHOT], sw = 9, sh = 12, i;      //�e�̍��W
	int sf[SHOT];                                    //�e�̔��˃t���O
	int sf2;


	shot = LoadGraph("bullet.png");
	enemy = LoadGraph("Player.bmp");                            // �G�̉摜
	LoadDivGraph("dairi.png", 16, 16, 2, 17, 17, image);        // ���@�摜�̕����ǂݍ���
	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // ���j�摜�̕����ǂݍ���
			   //�摜�̖��O�A�������鐔�A���������A�c�������A��������摜�̃T�C�Y�A�ϐ���

	//�e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ���
	//�u���݂��Ă��Ȃ��v���Ӗ�����0�������Ă���
	for (i = 0; i < SHOT; i++) {
		sf[i] = 0;
	}
	
	//�V���b�g�{�^����O�̃t���[���ŉ����ꂽ���ǂ�����ێ�����
	//�ϐ���0�i������Ă��Ȃ��j����
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
			// �E�������Ă�����E�ɐi��
			if (Key[256] & PAD_INPUT_RIGHT) px += 3;

			// ���������Ă����獶�ɐi��
			if (Key[256] & PAD_INPUT_LEFT)  px -= 3;


			//�X�y�[�X�������ꂽ��e��ł�
			if (CheckHitKey(KEY_INPUT_SPACE)) {

				//�O�̃t���[���ŃV���b�g�{�^��������������
				//�ۑ�����Ă���ϐ���0��������e�𔭎�
				if (sf2 == 0) {

					//��ʏ�ɏo�ĂȂ��e�����邩�A�e�̐���������Ԃ����ׂ�
					for (i = 0; i < SHOT; i++) {

						//�e����ʏ�ɏo�ĂȂ��ꍇ�͂��̒e����ʂɏo��
						if (sf[i] == 0) {

							//�e�̈ʒu���Z�b�g�A�ʒu�͎��@�̒��S�ɂ���
							sx[i] = (pw - sw) / 2 + px;
							sy[i] = (ph - sh) / 2 + py;
							sx2[i] = (pw - sw) / 2 + px + 20;
							sy2[i] = (ph - sh) / 2 + py;

							//�e�͌����_�ő��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���1��������
							sf[i] = 1;

							//�e��1�o�����̂Ń��[�v���甲���o��
							break;
						}

					}
				}

				//�O�̃t���[���ŃV���b�g�{�^����������Ă�������
				//�ێ�����ϐ���1�i������Ă����j��������
				sf2 = 1;
				
			}
			else {

				//�O�̃t���[���ŃV���b�g�{�^����������Ă��Ȃ������ꍇ��
				//�V���b�g�{�^����������Ă�������
				//�ێ�����ϐ���0�i������Ă��Ȃ��j��������
				sf2 = 0;
				
			}
		}

		//�e�̐������e�𓮂�������
		for (i = 0; i < SHOT; i++) {

			//���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P�i���݂���j�̏ꍇ�̂ݍs��
			if (sf[i] == 1) {

				//�e i ��10�h�b�g�ړ�������
				sy[i] -= 5;


				//��ʊO�ɏo���ꍇ�A���݂�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
				if (sy[i] < -80) {
					sf[i] = 0;
				}

				if (((sx[i] > ex && sx[i] < ex + ew) || (ex > sx[i] && ex < sx[i] + sw)) &&
					((sy[i] > ey && sy[i] < ey + eh) || (ey > sy[i] && ey < sy[i] + sh))) {
					sf[i] = 0;
					//�G�̑��݂�ێ����Ă���ϐ���0�i���݂��Ȃ�)��������
				}

				//�e�̕`��
				DrawGraph(sx[i], sy[i], shot, TRUE);


			}
		}
		for (i = 0; i < SHOT; i++) {

			//���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P�i���݂���j�̏ꍇ�̂ݍs��
			if (sf[i] == 1) {

				//�e i ��10�h�b�g�ړ�������
				sy2[i] -= 5;

				//��ʊO�ɏo���ꍇ�A���݂�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
				if (sy2[i] < -80) {
					sf[i] = 0;
				}

				if (((sx2[i] > ex && sx2[i] < ex + ew) || (ex > sx2[i] && ex < sx2[i] + sw)) &&
					((sy2[i] > ey && sy2[i] < ey + eh) || (ey > sy2[i] && ey < sy2[i] + sh))) {
					sf[i] = 0;
					//�G�̑��݂�ێ����Ă���ϐ���0�i���݂��Ȃ�)��������
				}

				//�e�̕`��

				DrawGraph(sx2[i], sy2[i], shot, TRUE);

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


	}
	DxLib_End(); // DX���C�u�����I���������܂�������
	return 0;
}