#include "DxLib.h"
#define PI 3.14
int Key[256]; // �L�[��������Ă���t���[�������i�[���܂�
void player();
// �L�[�̓��͏�Ԃ��X�V���܂�
int gpUpdateKey()
{
	char tmpKey[256];               // ���݂̃L�[�̓��͏�Ԃ��i�[���܂�
	GetHitKeyStateAll(tmpKey);      // �S�ẴL�[�̓��͏�Ԃ𓾂܂�
	for (int j = 0; j < 256; j++)
	{
		if (tmpKey[j] != 0)         // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		{
			Key[j]++;               // ���Z���܂�
		}
		else
		{                           // ������Ă��Ȃ����
			Key[j] = 0;             // 0�ɂ��܂�
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1100, 800, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	player();
	DxLib_End(); // DX���C�u�����I���������܂�
	return 0;
}

void player()
{
	/* { �v���C���[�p�̕ϐ� } ***********************************************************************************/
	int px[16] = { 400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400 };
	int py[16] = { 600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600 };
	bool pflg[16] = { true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true, };
	int	prote = 0, psize = 2;               //prote:���@�p�x,  psize:���@�T�C�Y
	int	pr = 14 * psize / 2, pimage[2];     //���@�̍��W�Ɖ摜�ϐ�
	int HP = 3, i = 0, hflg = 1, flg = 1;   //   HP:�̗�,i:���삷��ԍ�,  hflg,flg:�\���p�t���O
	int out = 0;                            //���̓����蔻��Əd�Ȃ�Ȃ��悤�ɂ���t���O
	int pb = 0;                             //�������₷������p
	int pq = 0;
	int ij=0, s=0, is=0;
	LoadDivGraph("���@.png", 2, 1, 2, 16, 16, pimage);   //���@�摜�̕����ǂݍ���
	 //�摜�̖��O�A�������鐔�A���������A�c�������A��������摜�̃T�C�Y�A�ϐ���

	/* { �e�p�̕ϐ� } *******************************************************************************************/
	int shot;                                     //�e�̉摜
	int sx[20], sy[20], sw = 9, sh = 12, j;                                 //�e�̍��W
	int sf[20]; //�e�̔��˃t���O
	int sf2;
	int Simage[10];
	int sr = sw / 2;
	shot = LoadGraph("bullet.png");
	/* { �G�l�~�[�p�̕ϐ� } *************************************************************************************/
	int ex = 400, ey = 500, er = 15 * 3 / 2, enemy[50]; //�G�̍��W�Ɖ摜�ϐ�
	int ep = 0, eflg = 0, efp = 0, fps = 0;

	LoadDivGraph("Galaga_OBJ_enemy.png", 50, 5, 9, 19, 20, enemy); // �G�̉摜�̕����ǂݍ���

	int es = 0, esflg = 0;  //�G�̈ړ��p
	int epx, epy;           //�G���@�p
	/* { �r�[���Z�M�p�̕ϐ� } ***********************************************************************************/
	static int bmimage[12];
	int bmx = 0, bmy = 0;
	int bmi = 0, bmcnt = 0, bmanitmp = 0, bllmflg = 0;
	int bllmcnt = 0, bmt = 0, bllm = 0;
	int bmani[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,11,10,11,10,11,10,9,8,7,6,5,4,3,2,1,0 };

	LoadDivGraph("Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, bmimage); // �摜�̕����ǂݍ���
	/* { �z�����܂�A�j���[�V�����p�̕ϐ� } *********************************************************************/
	int q = 0, t1 = 0, t2 = 0;

	/* { ���j�p�̕ϐ� } *****************************************************************************************/
	int bi = 0, bj = 0, bakuhaimage[13]; //bi:���j�G�t�F�N�g�̑���,bj:�\��,�摜�ϐ��p
	int bflg = 0;//�t���O�p

	LoadDivGraph("bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // ���j�摜�̕����ǂݍ���

	/* { ���̂ق��̕ϐ� } ***************************************************************************************/
	int keyflg = 0, color = GetColor(255, 255, 255); // keyflg:���͋��ۗp�@�F�R�[�h���擾

	/** { �Z�b�g�A�b�v } ****************************************************************************************/
	for (j = 0; j < 20; j++) {
		sf[j] = 0;
	}
	sf2 = 0;
	/************************************************************************************************************/
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		// ��ʂ�������
		ClearDrawScreen();
		// �L�[���͎擾�@�Q�[���I�[�o�[�����͋��ۂ�������������if���̒��ɓ����
		Key[256] = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (keyflg == 0)
		{
			// �E�������Ă�����E�ɐi��
			if (Key[256] & PAD_INPUT_RIGHT) px[i] += 3;

			// ���������Ă����獶�ɐi��
			if (Key[256] & PAD_INPUT_LEFT)  px[i] -= 3;

			//�X�y�[�X�������ꂽ��e��ł�
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				if (sf2 == 0) {
					for (j = 0; j < 20; j++) {
						if (sf[j] == 0) {
							sx[j] = (pr - sw) / 2 + px[i];
							sy[j] = (pr - sh) / 2 + py[i];

							sf[j] = 1;

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

		if (keyflg == 2)//�Q�[���I�[�o�[���g�p�ł���L�[
		{
			if (Key[KEY_INPUT_A] == 1)
			{
			   px[0] = 400;  py[0] = 600;
			   px[1] = 400;  py[1] = 600;
			   px[2] = 400;  py[2] = 600;
				  i  =   0; keyflg =   0;
				 HP  =   3;    out =   0;
				flg  =   1;   hflg =   1;
			}
		}
		//�v���C���[�̈ړ����x
		if (px[i] >= 1100 - 24) px[i] = 1100 - 22;
		if (px[i] <= 0 + 24)    px[i] =    0 + 22;
		/* { �e } ***********************************************************************************************/

		for (j = 0; j < 20; j++) {
			if (sf[j] == 1) {
				sy[j] -= 16;
				if (sy[j] < -80) {
					sf[j] = 0;
				}

				DrawGraph(sx[j], sy[j], shot, TRUE);
			}
		}

		/* { �G�ړ� } *******************************************************************************************/
		if (pb == 0 && esflg == 0)ex = ex + es;
		if (ex > 600)esflg = 1;
		if (pb == 0 && esflg == 1)ex = ex - es;
		if (ex < 0)esflg = 0;

		/* { �G�ƕ��ʂɓ��������ꍇ } ***************************************************************************/
		//�G�Ƃ̓����蔻��
		if (eflg==0&&(px[i] - ex) * (px[i] - ex) + (py[i] - ey) * (py[i] - ey) <= (pr + er) * (pr + er)) //�����蔻��
		{
			if (out == 0 || out == 1)bflg = 1;//�ق��̓����蔻��Əd�Ȃ��ĂȂ��Ȃ�A�j���[�V�����Đ�
		}
		if (bflg == 1)
		{
			keyflg = 1;  //���͋��� 
			   flg = 0;  //�v���C���[���\��
		    bi++;        //���j�A�j���[�V�����J�n
			if (bi == 10)bj += 1, bi = 0; //���@�̔��j�G�t�F�N�g�X�s�[�h��������Ȃ�if�̏�����ς���
			DrawRotaGraph(px[i], py[i], 3.5, PI / 180 * 0, bakuhaimage[bj], TRUE);//���j�摜�\��
		}
		if (bj == 13)  //���j�A�j���[�V�������I������烊�Z�b�g����
		{
			i += 1; keyflg = 0; HP -= 1;
			bi = 0; bj = 0;
			hflg += 1; out = 0;
			flg = 1; bflg = 0;
		}

		/********************************************************************************************************/
		//�Gbllm�A�j���[�V����
		bmx = ex;
		bmy = ey + 15;
		if(eflg==0&&bllm==0)bllmcnt++;
		DrawFormatString(50, 200, color, "bllmcnt%d", bllmcnt); // ������`�悷��
		if (bllmcnt > 300)bllmcnt = 300, bllmflg = 1;
		if (bllmcnt == 300)
		{
			bmt++;
			if (bmt >= 10)bmi++, bmt = 0;
			bmanitmp = bmani[bmi];
			if (bmi >= 27)bmi = 0, bllmcnt = 0, bllmflg = 0;
			DrawGraph(bmx - er, bmy, bmimage[bmanitmp], TRUE);      // �摜��\��
		}
		/* { �G��bllm�ɓ��������ꍇ } ***************************************************************************/
		/*�A�j���[�V�����̃s�N�Z�����i�����蔻��p�Ɂj
		No  x y
		1: 18,8 �@ 2: 22,16 �@3: 24,24�@  4: 28,32 �@ 5: 30,40 �@ 6: 34,48

		7: 36,56�@ 8: 40,64�@ 9: 44,72 �@10: 46,80 �@11: 46,80 �@12: 46,80 */

		if (bllmflg == 1)//�r�[���Z�M�̓����蔻��
		{
			if (bmanitmp >= 10 && bmanitmp <= 12)
			if (ep == 0 && px[i] + 32 >= bmx - 8 && px[i] <= bmx + 18 && py[i] >= bmy && py[i] <= bmy + 20
			|| px[i] + 32 >= bmx - 13 && px[i] <= bmx + 23 && py[i] >= bmy + 20 && py[i] <= bmy + 30
			|| px[i] + 32 >= bmx - 18 && px[i] <= bmx + 28 && py[i] >= bmy + 40 && py[i] <= bmy + 60
			|| px[i] + 32 >= bmx - 23 && px[i] <= bmx + 33 && py[i] >= bmy + 60 && py[i] <= bmy + 85)
			{
				if (out == 0 || out == 2)
				{
					out = 2;//�r�[���Ƃ̓����蔻�肪�d�Ȃ�Ȃ��悤�ɂ���
					pb = 1;
				}
			}
		}
		if (pb == 1)//�z�����܂�A�j���[�V�����J�n
		{
			     flg = 0, keyflg = 1; //��\���ɂ��ē��͋��ۏ�Ԃɂ���
			 epx = px[i],epy = py[i]; //x���W�ݒ� y���W�ݒ�
		     prote += 18;  //��]������
			    ep  =  1;  //���@��G��Ԃɂ���
			     q  =  1;
			if (q == 1)//�G�̍��W�ɍ��킹��
			{
				t2++;//������Ƃ��ړ�
				if (t2 >4 )t2 = 0;
				if (t2 >1 && py[i] >= ey + 20)py[i]--;
				if (t2 >1 && px[i] >= ex)px[i]--;
				if (t2 >1 && px[i] <= ex)px[i]++;
			}
			DrawFormatString(25, 25, color, "%d",t2); // ������`�悷���
			if (bmi == 0&&py[i] <= ey + 20)//�G�@�̑O�ɂ�����
			{
				    q = 0;
				prote = 0;
				     t1++; //�J�E���g�J�n
					 bllmcnt = 0;
			}
			if (t1 == 10)t1 = 0, py[i] -= 1;//������Ƃ��ړ�������
			if (py[i] <= ey - 32)//�G�@�̌��ɂ����玟�̎��@��\��
			{
				t1 = 0; pb = 0;
				i += 1; keyflg = 0; HP -= 1;
				hflg += 1; out = 0;
				flg = 1,bllm = 1;
			}
		}

		/* { �e���G�ɓ��������� } *******************************************************************************/
		for (j = 0; j < 20; j++)
		{
			if (eflg == 0 && (sx[j] - ex) * (sx[j] - ex) + (sy[j] - ey) * (sy[j] - ey) <= (sr + er) * (sr + er)) //�����蔻��
			{
				eflg = 1;
				sf[j] = 0;
				bmi = 0;
				bllmflg = 0;
				bllmcnt = 0;
				efp = 1;
			}
		}
		if (efp==1&&ep == 1)
		{
			fps = 1;
			prote += 18;
			if (prote >= (18 * 20 * 20) + 3)
			{
				prote = (18 * 20 * 20) + 3;
				if (px[i] >= epx-30)px[i]--;
				if (px[i] <= epx-30)px[i]++;
				keyflg = 1;
				efp = 1;
				if(py[i]>epy)epy++;
			}
			if (py[i] == epy)
			{
				keyflg = 0;
				if (epx >= px[i] + 28)epx -=3;
				if (epx < px[i] + 28)epx +=3;
			}
			if (fps == 1)DrawRotaGraph(epx, epy, psize, PI / 180 * prote, pimage[0], TRUE);
			DrawFormatString(550, 550, color, "%d",prote); // ������`�悷���
			DrawFormatString(750, 550, color, "%d", efp); // ������`�悷���
		}

		/* { �Q�[���I�[�o�[�� } *********************************************************************************/
		if (HP <= 0) // HP��0�ɂȂ�����
		{
			hflg = 0; keyflg = 2;	         // �L�[���͂��󂯕t�������Ȃ��悤�ɂ��܂�������
			DrawFormatString(250, 250, color, "GAME OVER\nA�Ń��g���C"); // ������`�悷���
		}
		/* { ���̑� } *******************************************************************************************/
		if (i >= 16)i = 15, out = 3;//�f�o�b�N��߂��Ƃ��f�o�b�N�G���[�����o�Ȃ��悤�ɂ���
		ij = s / 70000;

		if (px[i] >= 700)i += 1, is -= 1;
		/* { �\�� } *********************************************************************************************/
		DrawFormatString(250, 200, color, "HP:%d", HP); // ������`�悷��
		if (is + ij + HP > 0)
		{
			DrawRotaGraph(px[i], py[i], psize, PI / 180 * 0, pimage[0], TRUE);
		}

		if (fps == 0 && ep == 1) //�_�[�N�T�C�h���@
		{
			if (epx >= ex)epx--;
			if (epx <= ex)epx++;
			DrawRotaGraph(epx, epy, psize, PI / 180 * prote, pimage[ep], TRUE);
		}

		if(eflg==0)DrawRotaGraph(ex, ey, 3.0, PI / 180 * 0, enemy[0], TRUE);
		/*********************************************************************************************************/

	}//whlie���̏I���
}