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

void Player_All()
{
	 Player_Init();    //�����ݒ�

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
		{							
			// ��ʂ�������
			ClearDrawScreen();

			Player_Setup();        //�ݒ�
			Player_Draw();         //�\��
			Player_Move();         //����
			Player_Shot();         //�e
			Player_Animation();    //�A�j���[�V����
			Player_Hit();          //�����蔻��
			Player_Enemy();        //�G(�����\��)

			bg_All();
			Enemy_all();
			Score_Draw();
		}//whlie���̏I���
}

void Player_Init()//�����ݒ�
{
	LoadDivGraph("�摜/���@.png", 2, 1, 2, 16, 16, p.image);                  // ���@�摜�̕����ǂݍ���
	s.shot = LoadGraph("�摜/bullet.png");                                    // �e�摜�̓ǂݍ���
	LoadDivGraph("�摜/Galaga_OBJ_enemy.png", 50, 5, 9, 20, 18, e.enemy);     // �G�̉摜�̕����ǂݍ���
	LoadDivGraph("�摜/Galaga_OBJ_effect.png", 12, 5, 3, 51, 83, b.image);    // �摜�̕����ǂݍ���
	LoadDivGraph("�摜/bakuhatu.png", 9, 9, 1, 32, 32, B.image);              // ���j�摜�̕����ǂݍ���
}

void Player_Setup()//�ݒ�
{
	if (p.i >= 10)p.i = 11, p.flg_i == false, p.judgment = 3, p.keyflg = 3;    //�f�o�b�N��߂��Ƃ��f�o�b�N�G���[�����o�Ȃ��悤�ɂ���
	p.HP_plus = p.score / 70000;
	if (p.HP_plus >= 7)p.HP_plus = 7;
	if (p.escape == true)p.y[p.i]++;
	if (p.y[p.i] == 700)p.escape = false;
	DrawString(690, 450, "��\n��\n��\n��\n��\nHP\n��\n��\n��\n��", GetColor(255, 255, 255));
	if (p.x[p.i] >= 700)p.i += 1, p.HP_minus -= 1;
	if (p.dualbreak == 2)
	{
		p.i += 1, p.keyflg = 0; 
		p.HP -= 1;
		p.judgment = 0;
		p.dualbreak = 0;
		p.flg_i = true;
	}
}

void Player_Draw()//�\��
{
	DrawFormatString(250, 200, color, "HP:%d", p.HP_minus + p.HP_plus + p.HP);    // ������`�悷��
	DrawFormatString(250, 100, color, "%d", p.score);                             // ������`�悷��
	if (p.flg_i == true && p.flg_j == true && p.HP_minus + p.HP_plus + p.HP > 0)
	{
		p.score += 100;
		DrawRotaGraph(p.x[p.i], p.y[p.i], p.size, PI / 180 * p.rote, p.image[0], TRUE);
	}

	if (p.player_recapture == false && e.player_capture == 1)    //�_�[�N�T�C�h���@
	{
		if (e.alter_x >= e.x)e.alter_x--;
		if (e.alter_x <= e.x)e.alter_x++;
		DrawRotaGraph(e.alter_x, e.alter_y, p.size, PI / 180 * e.rote, p.image[e.player_capture], TRUE);
	}

	/* { �Q�[���I�[�o�[�� } ************************************************************************************************************************/
	if (p.HP_minus + p.HP_plus + p.HP <= 0)
	{
		p.keyflg = 2;    // �L�[���͂��󂯕t�������Ȃ��悤�ɂ��܂�������
		DrawFormatString(250, 250, color, "GAME OVER\nESC�Ń^�C�g��");   // ������`�悷���
	}
}

void Player_Move()//����
{
	if (p.keyflg == 0)
	{
		// �E�������Ă�����E�ɐi��
		if (CheckHitKey(KEY_INPUT_RIGHT)) p.x[p.i] += 3;

		// ���������Ă����獶�ɐi��
		if (CheckHitKey(KEY_INPUT_LEFT))  p.x[p.i] -= 3;

		//�X�y�[�X�������ꂽ��e��ł�
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (s.sf2 == 0) {
				for (s.j = 0; s.j < SHOT; s.j++) {
					if (s.sf[s.j] == 0) {
						SE_draw();
						s.sx[s.j] = (p.r - s.sw) / 2 + p.x[p.i] - 10;
						s.sy[s.j] = (p.r - s.sh) / 2 + p.y[p.i] - 10;
						s.sf[s.j] = 1;

						break;
					}
				}
			}
			s.sf2 = 1;
		}
		else {
			s.sf2 = 0;
		}
	}

	if (p.keyflg == 2)    //�Q�[���I�[�o�[���g�p�ł���L�[ ESC�\��
	{

	}

	if (p.keyflg == 3)
	{
		//�X�y�[�X�������ꂽ��e��ł�
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (s.sf2 == 0) {
				for (s.j = 0; s.j < SHOT; s.j++) {
					if (s.sf[s.j] == 0) {
						s.sx[s.j] = (p.r - s.sw) / 2 + p.x[p.i] - 10;
						s.sy[s.j] = (p.r - s.sh) / 2 + p.y[p.i] - 10;

						s.sf[s.j] = 1;

						break;
					}
				}
			}
			s.sf2 = 1;
		}
		else {
			s.sf2 = 0;
		}
	}
	//�v���C���[�̈ړ����x
	if (p.x[p.i]+p.w >= 800) p.x[p.i] = 800 - p.w;
	if (p.x[p.i] <= 0+p.w )   p.x[p.i] = 0+p.w;
}

void Player_Shot()//�e
{
	/* { �e } **************************************************************************************************************************************/
	for (s.j = 0; s.j < SHOT; s.j++) {
		if (s.sf[s.j] == 1) {
			s.sy[s.j] -= 16;
			if (s.sy[s.j] < -80) {
				s.sf[s.j] = 0;
			}

			DrawGraph(s.sx[s.j], s.sy[s.j], s.shot, TRUE);
			if (p.dualmode == true)
			{
				DrawGraph(s.sx[s.j] + 30, s.sy[s.j], s.shot, TRUE);
			}
		}
	}
	/* { �e���G�ɓ��������� } **********************************************************************************************************************/
	for (s.j = 0; s.j < SHOT; s.j++)
	{
		if (s.sf[s.j] == 1 && e.flg == true && 
		   (s.sx[s.j] - e.x) * (s.sx[s.j] - e.x) + (s.sy[s.j] - e.y) * (s.sy[s.j] - e.y) <= (s.sr + e.r) * (s.sr + e.r))//�����蔻��
		{
			e.flg = false;
			s.sf[s.j] = 0;
			b.i = 0;
			b.flg = false;
			b.bllmcnt = 0;
			e.Defeat = true;
			if (e.move_flg==true)
			{
				e.move_flg = false;
				p.rote = 0;
			    p.escape = true;
			}
		}
		if (p.dualmode == true)
		{
			if (s.sf[s.j] == 1 && e.flg == true && 
			   (s.sx[s.j] + 30 - e.x) * (s.sx[s.j] + 30 - e.x) + (s.sy[s.j] - e.y) * (s.sy[s.j] - e.y) <= (s.sr + e.r) * (s.sr + e.r)) //�����蔻��
			{
				e.flg = false;
				s.sf[s.j] = 0;
				b.i = 0;
				b.flg = false;
				b.bllmcnt = 0;
				e.Defeat = true;
				if (e.move_flg == true)
				{
					e.move_flg = false;
					p.rote = 0;
				}
			}
		}
	}

	if (e.Defeat == true && e.player_capture == 1)     //���@�����̓G��������
	{
		p.player_recapture = true;
		e.rote += 18;
		p.keyflg = 1;
		if (p.x[p.i] >= e.alter_x - 30)p.x[p.i]--;
		if (p.x[p.i] <= e.alter_x - 30)p.x[p.i]++;
		if (e.rote >= (18 * 20 * 10) + 3)
		{
			e.rote = (18 * 20 * 10) + 3;
			if (p.y[p.i] > e.alter_y)e.alter_y++;
		}
		if (p.y[p.i] == e.alter_y)
		{
			p.keyflg = 0;
			p.dualmode = true;
			if (e.alter_x >= p.x[p.i] + 28)e.alter_x -= 3;
			if (e.alter_x < p.x[p.i] + 28)e.alter_x += 3;
		}
		if (p.player_recapture == true)DrawRotaGraph(e.alter_x, e.alter_y, p.size, PI / 180 * e.rote, p.image[0], TRUE);
	}
}

void Player_Animation()//�A�j���[�V����
{
	if (p.dualmode == false)
	{
		if (B.flg == true)
		{
			p.keyflg = 1;       //���͋��� 
			B.i++;              //���j�A�j���[�V�����J�n
			if (B.i == 10)B.j += 1, B.i = 0;     //���@�̔��j�G�t�F�N�g�X�s�[�h��������Ȃ�if�̏�����ς���
			DrawRotaGraph(p.x[p.i], p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //���j�摜�\��
		}
		if (B.j == 8)          //���j�A�j���[�V�������I������烊�Z�b�g����
		{
			p.i += 1; p.keyflg = 0; p.HP -= 1;
			B.i = 0; B.j = 0;
			p.judgment = 0;
			B.flg = false;
		}
	}
	if (p.dualmode == true)
	{
		if (B.flg == true)
		{
			B.i++;              //���j�A�j���[�V�����J�n
			if (B.i == 10)B.j += 1, B.i = 0;     //���@�̔��j�G�t�F�N�g�X�s�[�h��������Ȃ�if�̏�����ς���
			DrawRotaGraph(p.x[p.i], p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //���j�摜�\��
		}
		if (B.j == 8)          //���j�A�j���[�V�������I������烊�Z�b�g����
		{
			p.dualmode = false;
			p.flg_i = false;
			B.i = 0; B.j = 0;
			p.judgment = 0;
			B.flg = false;
			p.dualbreak++;
		}

		if (B.flg2 == true)
		{
			B.i++;              //���j�A�j���[�V�����J�n
			if (B.i == 10)B.j += 1, B.i = 0;     //���@�̔��j�G�t�F�N�g�X�s�[�h��������Ȃ�if�̏�����ς���
			DrawRotaGraph(p.x[p.i] + 32, p.y[p.i], 2, PI / 180 * 0, B.image[B.j], TRUE);    //���j�摜�\��
		}
		if (B.j == 8)          //���j�A�j���[�V�������I������烊�Z�b�g����
		{
			B.i = 0; B.j = 0;
			p.judgment = 0;
			p.dualbreak++;
			B.flg2 = false;
			p.dualmode = false;
			p.player_recapture = false;
			e.player_capture = 0;
		}
	}

	/**********************************************************************************************************************************************/
	//�Gbllm�A�j���[�V����
	b.x = e.x;
	b.y = e.y + 15;
	if (e.flg == true && e.player_capture == 0)b.bllmcnt++;
	if (b.bllmcnt > 100)b.bllmcnt = 100, b.flg = true;
	if (b.bllmcnt == 100)
	{
		b.cnt++;
		if (b.cnt >= 10)b.i++, b.cnt = 0;
		b.tmp = b.ani[b.i];
		if (b.i >= 27)b.i = 0, b.bllmcnt = 0, b.flg = false;
		DrawGraph(b.x - 13 * 2, b.y - 5, b.image[b.tmp], TRUE);      // �摜��\��
	}
	/* { �G��bllm�ɓ��������ꍇ } ******************************************************************************************************************/
	/*�A�j���[�V�����̃s�N�Z�����i�����蔻��p�Ɂj
	No  x y
	1: 18,8 �@ 2: 22,16 �@3: 24,24�@  4: 28,32 �@ 5: 30,40 �@ 6: 34,48

	7: 36,56�@ 8: 40,64�@ 9: 44,72 �@10: 46,80 �@11: 46,80 �@12: 46,80 */

	if (b.flg == true)    //�r�[���Z�M�̓����蔻��
	{
		if (b.tmp >= 10 && b.tmp <= 12)
			if (e.player_capture == 0 &&
				p.x[p.i] + 16 >= b.x - 10 && p.x[p.i] <= b.x + 27 && p.y[p.i] >= b.y + 60 && p.y[p.i] <= b.y + 85)
			{
				if (p.judgment == 0 || p.judgment == 2)
				{
					p.judgment = 2;    //�r�[���Ƃ̓����蔻�肪�d�Ȃ�Ȃ��悤�ɂ���
					e.move_flg = true;
				}
			}
	}
	if (p.flg_i == true && p.HP_minus + p.HP_plus + p.HP > 0 && e.move_flg == true)    //�z�����܂�A�j���[�V�����J�n
	{
		p.keyflg = 3;    //�ړ��������͋��ۏ�Ԃɂ���
		e.alter_x = p.x[p.i], e.alter_y = p.y[p.i];    //x���W�ݒ� y���W�ݒ�
		p.rote += 18;    //��]������
		b.x_match = true;
		if (b.x_match == true)    //�G�̍��W�ɍ��킹��
		{
			b.t_i++;    //������Ƃ��ړ�
			if (b.t_i > 4)b.t_i = 0;
			if (b.t_i > 1 && p.y[p.i] >= e.y + 20)p.y[p.i]--;
			if (b.t_i > 1 && p.x[p.i] >= e.x)p.x[p.i]--;
			if (b.t_i > 1 && p.x[p.i] <= e.x)p.x[p.i]++;
		}
		if (b.i <= 9)    //�G�@�̑O�ɂ�����
		{
			p.flg_j = false;
			p.keyflg = 1;
			
			e.player_capture = 1;    //���@��G��Ԃɂ���
			b.x_match = false;
			p.rote = 0;
			b.t_j++;    //�J�E���g�J�n
			b.bllmcnt = 0;
		}
		if (b.t_j == 10)b.t_j = 0, p.y[p.i] -= 1;    //������Ƃ��ړ�������
		if (p.y[p.i] <= e.y - 32)   //�G�@�̌��ɂ����玟�̎��@��\��
		{
			p.flg_j = true;
			b.t_j = 0; e.move_flg = false;
			p.i += 1; p.keyflg = 0; p.HP -= 1;
			p.judgment = 0;
		    e.player_capture = 1;
		}
	}

}

void Player_Hit()//�����蔻��
{
	if (e.flg == true &&
		(p.x[p.i] - e.x) * (p.x[p.i] - e.x) + (p.y[p.i] - e.y) * (p.y[p.i] - e.y) <= (p.r + e.r) * (p.r + e.r)) //�����蔻��
	{
		if (p.flg_i == true && p.judgment == 0 || p.judgment == 1)B.flg = true;    //�ق��̓����蔻��Əd�Ȃ��ĂȂ��Ȃ�A�j���[�V�����Đ�
	}
	if (e.flg2 == true &&
		(p.x[p.i] - e.x2) * (p.x[p.i] - e.x2) + (p.y[p.i] - e.y2) * (p.y[p.i] - e.y2) <= (p.r + e.r) * (p.r + e.r)) //�����蔻��
	{
		if (p.flg_i == true && p.judgment == 0 || p.judgment == 1)B.flg = true;    //�ق��̓����蔻��Əd�Ȃ��ĂȂ��Ȃ�A�j���[�V�����Đ�
	}
	if (p.dualmode == true)
	{
		if (e.flg2 == true &&
			(p.x[p.i]+32 - e.x2) * (p.x[p.i] + 32  - e.x2) + (p.y[p.i] - e.y2) * (p.y[p.i] - e.y2) <= (p.r + 32 + e.r) * (p.r + e.r)) //�����蔻��
		{
			if (p.judgment == 0 || p.judgment == 1)B.flg2 = true;    //�ق��̓����蔻��Əd�Ȃ��ĂȂ��Ȃ�A�j���[�V�����Đ�
		}
	}
}
void Player_Enemy()//�G(�����\��)
{
	if (e.move_flg == false && e.sflg == true)e.x = e.x + e.s, e.y = e.y + e.s;
	if (e.x > 400)e.sflg = false;
	if (e.move_flg == false && e.sflg == false)e.x = e.x - e.s, e.y = e.y - e.s;
	if (e.x < 300)e.sflg = true;

	if (e.flg == true)DrawRotaGraph(e.x, e.y, 2.0, PI / 180 * 0, e.enemy[10], TRUE);
	if (e.flg2 == true)DrawRotaGraph(e.x2, e.y2, 2.0, PI / 180 * 0, e.enemy[10], TRUE);
}