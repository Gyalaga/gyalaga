#include "bg.h"
#include "SceneMgr.h"
#include "DxLib.h"
#define SPEED 1

static int y = 0;

void bg_Draw() {

	static int siro = LoadGraph("�摜/siro.jpg");
	static int haikei1 = LoadGraph("�摜/bg2.png");
	static int haikei2 = LoadGraph("�摜/bg3.png");
	static int haikei3 = LoadGraph("�摜/bg.pmg");
	static int count = 0;
	static int flg = 0;
	static int i = 0;
	int img[3] = { haikei1,haikei2,haikei3 };

	//1����
		DrawGraph(0, y, img[i], TRUE);
	//2����
		DrawGraph(0, y-800,img[i], TRUE);
	//3����
		DrawGraph(0, y-1600, img[i], TRUE);
	//��ԉ��܂ŃX�N���[�������珉���l�ɖ߂�
		if (y >= 1600) {
			y = 0;
		}
	    count++;               //�J�E���^�[�����Z

		if (count % 120 == 0) {                   //�����A�J�E���^�[��600�Ŋ������]�肪0�ł���Ȃ�            
			i++;
			count = 0;
		}
		if (i == 2) {
			i = 0;
		}
		DrawGraph(800, 0, siro, TRUE);
}
void bg_Update() {

	y += SPEED;
}
void bg_All() {

	bg_Draw();
	bg_Update();
}