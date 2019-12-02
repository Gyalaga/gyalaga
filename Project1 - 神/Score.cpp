#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"

typedef struct hiscore
{
	int score = 0;                          //�X�R�A
	int h_score = 0;                       //�n�C�X�R�A
	char String[256];                     //�ۑ��ϐ�

}HISCORE;

HISCORE high_score;
int scorex = 900, scorey = 170;           //�X�R�A�v�Z�̍��W
int high_scorex = 900, high_scorey = 90;  //�n�C�X�R�A�v�Z���W
int Black = GetColor(0, 0, 0);      // ���̐F
int Red = GetColor(255, 0, 0);            //�Ԃ̐F
int White = GetColor(255, 255, 255);            //�h��Ԃ��p�i���j                                         // �L�[��������Ă���t���[�������i�[����
int FileHandle;                           //�t�@�C��
FILE* fp;

//�X�V
void Score_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
		high_score.score = 0;             //������
	}
}

void Score_Title() {
	FileHandle = FileRead_open("h_score.dat");

	// ��s�ǂ�
	FileRead_gets(high_score.String, 256, FileHandle);

	// ��ʂɕ`��
	DrawString(375, 100, high_score.String, White);

	// �t�@�C�������
	FileRead_close(FileHandle);

}


//�X�R�A�X�V�̃Z�[�u
void Score_Save() {

	//�n�C�X�R�A�̃t�@�C�����J��
	FileHandle = FileRead_open("h_score.dat");

	// ��s�ǂ�
	FileRead_gets(high_score.String, 256, FileHandle);

	// ��ʂɕ`��
	DrawString(high_scorex, high_scorey, high_score.String, Black);

	// �t�@�C�������
	FileRead_close(FileHandle);
}

//�`��
void Score_Draw() {
	//DrawString(0, 0, "�X�R�A��ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));

	//�n�C�X�R�A�̋L�^
	fp = fopen("h_score.dat", "wb");
	fprintf(fp, "%d", high_score.h_score);

	fclose(fp);

	high_score.score += 10;

	// �n�C�X�R�A�̕����`��
	DrawFormatString(860, 30, Red, "HIGH ");
	DrawFormatString(900, 50, Red, " SCORE");

	//�X�R�A�����̕`��
	DrawFormatString(900, 130, Red, "1UP");

	//�X�R�A�����̕`��
	DrawFormatString(scorex, scorey, Black, "%d", high_score.score);

	// �n�C�X�R�A�̐����`��char�^
	DrawFormatString(high_scorex, high_scorey, Black, "%s", high_score.String);



	//char�^����int�^�ւ̕ϊ�
	high_score.h_score = atoi(high_score.String);

	//�n�C�X�R�A�X�V�A�X�R�A�A��
	if (high_score.h_score < high_score.score) {
		SetDrawScreen(DX_SCREEN_BACK);  //�h��Ԃ�                        
		DrawBox(high_scorex, high_scorey, 1100, 120, White, TRUE);

		//�h��Ԃ���̕`��
		high_score.h_score = high_score.score;
		DrawFormatString(high_scorex, high_scorey, Black, "%d", high_score.h_score);
	}
}
