#include "Game.h"
#include "windows.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Player.h"
#include "bg.h"
#include "Score.h"
#include "SceneMgr.h"
#include "bgm.h"
#include "Score.h"
#define PI 3.14
#define SHOT 2
	void Player_Update() {
		/* { �v���C���[�p�̕ϐ� } ***********************************************************************************/
		int px[16] = { 400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400 };
		int py[16] = { 700,700,700,700,700,700,700,700,700,700,700,700,700,700,700,700 };
		bool  pflg = true;
		int	prote = 0, psize = 2;               //prote:���@�p�x,  psize:���@�T�C�Y
		int	pr = 16 * psize / 2, pimage[2];     //���@�̍��W�Ɖ摜�ϐ�
		int HP = 3, i = 0, hflg = 1, flg = 1;   //   HP:�̗�,i:���삷��ԍ�,  hflg,flg:�\���p�t���O
		int out = 0;                            //���̓����蔻��Əd�Ȃ�Ȃ��悤�ɂ���t���O
		int pb = 0;                             //�������₷������p
		int pq = 0;
		int ij = 0, s = 0, is = 0;
		LoadDivGraph("�摜/���@.png", 2, 1, 2, 16, 16, pimage);   //���@�摜�̕����ǂݍ���
		 //�摜�̖��O�A�������鐔�A�c�������A���������A��������摜�̃T�C�Y�A�ϐ���
		int dualmode = false;//���[�h�f���A��
		/* { �e�p�̕ϐ� } *******************************************************************************************/
		int shot;                                     //�e�̉摜
		int sx[SHOT], sy[SHOT], sx2[SHOT], sy2[SHOT], sw = 7, sh = 12, j;                                 //�e�̍��W
		int sf[SHOT]; //�e�̔��˃t���O
		int sf2;
		int Simage[10];
		int sr = sw / 2;
		shot = LoadGraph("�摜/bullet.png");
		/* { �G�l�~�[�p�̕ϐ� } *************************************************************************************/
		int ex = 400, ey = 600, er = 14 * 2 / 2, enemy[50]; //�G�̍��W�Ɖ摜�ϐ�
		int ep = 0, eflg = 0, efp = 0, fps = 0;
		LoadDivGraph("�摜/Galaga_OBJ_enemy.png", 50, 5, 9, 20, 18, enemy); // �G�̉摜�̕����ǂݍ���
		int rote = 0;
		int es = 1, esflg = 0;  //�G�̈ړ��p
		int epx, epy;           //�G���@�p
		/* { �r�[���Z�M�p�̕ϐ� } ***********************************************************************************/
		static int bmimage[12];
		int bmx = 0, bmy = 0;
		int bmi = 0, bmcnt = 0, bmanitmp = 0, bllmflg = 0;
		int bllmcnt = 0, bmt = 0, bllm = 0;
		int bmani[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,10,11,10,11,10,11,10,9,8,7,6,5,4,3,2,1,0 };

		LoadDivGraph("�摜/Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, bmimage); // �摜�̕����ǂݍ���
		/* { �z�����܂�A�j���[�V�����p�̕ϐ� } *********************************************************************/
		int q = 0, t1 = 0, t2 = 0;
		int c = 0;
		/* { ���j�p�̕ϐ� } *****************************************************************************************/
		int bi = 0, bj = 0, bakuhaimage[13]; //bi:���j�G�t�F�N�g�̑���,bj:�\��,�摜�ϐ��p
		int bflg = 0;//�t���O�p

		LoadDivGraph("�摜/bakuha.png", 13, 13, 1, 17, 17, bakuhaimage); // ���j�摜�̕����ǂݍ���

		/* { ���̂ق��̕ϐ� } ***************************************************************************************/
		int keyflg = 0, color = GetColor(255, 255, 255); // keyflg:���͋��ۗp�@�F�R�[�h���擾

		/** { �Z�b�g�A�b�v } ****************************************************************************************/
		for (j = 0; j < SHOT; j++) {
			sf[j] = 0;
		}
		sf2 = 0;
		/************************************************************************************************************/
		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
		{							
			// ��ʂ�������
			ClearDrawScreen();
			bg_All();
			Enemy_all();
			Score_Draw();
			if (keyflg == 0)
			{
				// �E�������Ă�����E�ɐi��
				if (CheckHitKey(KEY_INPUT_RIGHT)) px[i] += 3;

				// ���������Ă����獶�ɐi��
				if (CheckHitKey(KEY_INPUT_LEFT))  px[i] -= 3;

				//�X�y�[�X�������ꂽ��e��ł�
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					if (sf2 == 0) {
						for (j = 0; j < SHOT; j++) {
							if (sf[j] == 0) {
								SE_draw();
								sx[j] = (pr - sw) / 2 + px[i] - 10;
								sy[j] = (pr - sh) / 2 + py[i] - 10;
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

			if (keyflg == 2)//�Q�[���I�[�o�[���g�p�ł���L�[ ESC�\��
			{

			}

			if (keyflg == 3)
			{
				//�X�y�[�X�������ꂽ��e��ł�
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					if (sf2 == 0) {
						for (j = 0; j < SHOT; j++) {
							if (sf[j] == 0) {
								sx[j] = (pr - sw) / 2 + px[i] - 10;
								sy[j] = (pr - sh) / 2 + py[i] - 10;

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
			//�v���C���[�̈ړ����x
			if (px[i] >= 1100 - 32) px[i] = 1100 - 32;
			if (px[i] <= 0 + 32)    px[i] = 0 + 32;
			/* { �e } ***********************************************************************************************/

			for (j = 0; j < SHOT; j++) {
				if (sf[j] == 1) {
					sy[j] -= 16;
					if (sy[j] < -80) {
						sf[j] = 0;
					}

					DrawGraph(sx[j], sy[j], shot, TRUE);
					if (dualmode == true)
					{
						DrawGraph(sx[j] + 30, sy[j], shot, TRUE);
					}
				}
			}

			/* { �G�ړ� } *******************************************************************************************/
			if (pb == 0 && esflg == 0)ex = ex + es;
			if (ex > 600)esflg = 1;
			if (pb == 0 && esflg == 1)ex = ex - es;
			if (ex < 0)esflg = 0;

			/* { �G�ƕ��ʂɓ��������ꍇ } ***************************************************************************/
			//�G�Ƃ̓����蔻��
			if (eflg == 0 && (px[i] - ex) * (px[i] - ex) + (py[i] - ey) * (py[i] - ey) <= (pr + er) * (pr + er)) //�����蔻��
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
				out = 0;
				flg = 1; bflg = 0;
			}

			/********************************************************************************************************/
			//�Gbllm�A�j���[�V����
			bmx = ex;
			bmy = ey + 15;
			if (eflg == 0 && bllm == 0)bllmcnt++;
			DrawFormatString(50, 200, color, "bllmcnt%d", bllmcnt); // ������`�悷��
			if (bllmcnt > 100)bllmcnt = 100, bllmflg = 1;
			if (bllmcnt == 100)
			{
				bmt++;
				if (bmt >= 10)bmi++, bmt = 0;
				bmanitmp = bmani[bmi];
				if (bmi >= 27)bmi = 0, bllmcnt = 0, bllmflg = 0;
				DrawGraph(bmx - 13 * 2, bmy - 5, bmimage[bmanitmp], TRUE);      // �摜��\��
			}
			/* { �G��bllm�ɓ��������ꍇ } ***************************************************************************/
			/*�A�j���[�V�����̃s�N�Z�����i�����蔻��p�Ɂj
			No  x y
			1: 18,8 �@ 2: 22,16 �@3: 24,24�@  4: 28,32 �@ 5: 30,40 �@ 6: 34,48

			7: 36,56�@ 8: 40,64�@ 9: 44,72 �@10: 46,80 �@11: 46,80 �@12: 46,80 */

			if (bllmflg == 1)//�r�[���Z�M�̓����蔻��
			{
				if (bmanitmp >= 10 && bmanitmp <= 12)
					if (ep == 0 && px[i] + 16 >= bmx - 10 && px[i] <= bmx + 27 && py[i] >= bmy + 60 && py[i] <= bmy + 85)
					{
						if (out == 0 || out == 2)
						{
							out = 2;//�r�[���Ƃ̓����蔻�肪�d�Ȃ�Ȃ��悤�ɂ���
							pb = 1;
						}
					}
			}
			if (pflg == true && is + ij + HP > 0 && pb == 1)//�z�����܂�A�j���[�V�����J�n
			{
				keyflg = 3;
				flg = 0; //��\���ɂ��Ĉړ��������͋��ۏ�Ԃɂ���
				epx = px[i], epy = py[i]; //x���W�ݒ� y���W�ݒ�
				prote += 18;  //��]������
				q = 1;
				if (q == 1)//�G�̍��W�ɍ��킹��
				{
					t2++;//������Ƃ��ړ�
					if (t2 > 4)t2 = 0;
					if (t2 > 1 && py[i] >= ey + 20)py[i]--;
					if (t2 > 1 && px[i] >= ex)px[i]--;
					if (t2 > 1 && px[i] <= ex)px[i]++;
				}
				DrawFormatString(25, 25, color, "%d", t2); // ������`�悷���
				if (bmi <= 9)//�G�@�̑O�ɂ�����
				{
					keyflg = 1;
					ep = 1;  //���@��G��Ԃɂ���
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
					out = 0;
					flg = 1, bllm = 1;
				}
			}

			/* { �e���G�ɓ��������� } *******************************************************************************/
			for (j = 0; j < SHOT; j++)
			{
				if (sf[j] == 1 && eflg == 0 && (sx[j] - ex) * (sx[j] - ex) + (sy[j] - ey) * (sy[j] - ey) <= (sr + er) * (sr + er)) //�����蔻��
				{
					eflg = 1;
					sf[j] = 0;
					bmi = 0;
					bllmflg = 0;
					bllmcnt = 0;
					efp = 1;
					if (pb == 1)
					{
						pb = 0;
						prote = 0;
						c = 1;
					}
				}
				if (dualmode == true)
				{
					if (sf[j] == 1 && eflg == 0 && (sx[j] + 30 - ex) * (sx[j] + 30 - ex) + (sy[j] - ey) * (sy[j] - ey) <= (sr + er) * (sr + er)) //�����蔻��
					{
						eflg = 1;
						sf[j] = 0;
						bmi = 0;
						bllmflg = 0;
						bllmcnt = 0;
						efp = 1;
						if (pb == 1)
						{
							pb = 0;
							prote = 0;
							c = 1;
						}
					}
				}
			}

			if (efp == 1 && ep == 1)//���@�����̓G��������
			{
				fps = 1;
				rote += 18;
				keyflg = 1;
				if (px[i] >= epx - 30)px[i]--;
				if (px[i] <= epx - 30)px[i]++;
				if (rote >= (18 * 20 * 20) + 3)
				{
					rote = (18 * 20 * 20) + 3;
					efp = 1;
					if (py[i] > epy)epy++;
				}
				if (py[i] == epy)
				{
					keyflg = 0;
					dualmode = true;
					if (epx >= px[i] + 28)epx -= 3;
					if (epx < px[i] + 28)epx += 3;
				}
				if (fps == 1)DrawRotaGraph(epx, epy, psize, PI / 180 * rote, pimage[0], TRUE);
				DrawFormatString(550, 550, color, "%d", rote); // ������`�悷���
				DrawFormatString(750, 550, color, "%d", efp); // ������`�悷���
			}




			/* { �Q�[���I�[�o�[�� } *********************************************************************************/
			if (is + ij + HP <= 0)
			{
				hflg = 0; keyflg = 2;	         // �L�[���͂��󂯕t�������Ȃ��悤�ɂ��܂�������
				DrawFormatString(250, 250, color, "GAME OVER\nESC�Ń^�C�g��"); // ������`�悷���
			}
			/* { ���̑� } *******************************************************************************************/
			if (i >= 10)i = 11, pflg == false, out = 3, keyflg = 3;//�f�o�b�N��߂��Ƃ��f�o�b�N�G���[�����o�Ȃ��悤�ɂ���
			ij = s / 70000;
			if (ij >= 7)ij = 7;
			if (px[i] >= 700)i += 1, is -= 1;
			if (c == 1)py[i]++;
			if (py[i] == 700)c = 0;
			/* { �\�� } *********************************************************************************************/
			DrawFormatString(250, 200, color, "HP:%d", is + ij + HP); // ������`�悷��
			DrawFormatString(250, 100, color, "%d", s); // ������`�悷��
			if (pflg == true && is + ij + HP > 0)
			{
				s += 100;
				DrawRotaGraph(px[i], py[i], psize, PI / 180 * prote, pimage[0], TRUE);
			}

			if (fps == 0 && ep == 1) //�_�[�N�T�C�h���@
			{
				if (epx >= ex)epx--;
				if (epx <= ex)epx++;
				DrawRotaGraph(epx, epy, psize, PI / 180 * rote, pimage[ep], TRUE);
			}

			if (eflg == 0)DrawRotaGraph(ex, ey, 2.0, PI / 180 * 0, enemy[10], TRUE);
			/*********************************************************************************************************/

		}//whlie���̏I���
	}
	void Player_all()
	{
		Player_Update();
	}


