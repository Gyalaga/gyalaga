#include "DxLib.h"
#include "Score.h"

typedef struct hiscore
{
	int score = 0;                          //�X�R�A
	int h_score = 0;                       //�n�C�X�R�A
	char String[256];                     //�ۑ��ϐ�

}HISCORE;

HISCORE high_score;

int scorex = 950, scorey = 200;            //�X�R�A�v�Z�̍��W
int high_scorex = 950, high_scorey = 90;  //�n�C�X�R�A�v�Z���W
int Black = GetColor(0, 0, 0);            // ���̐F
int Red = GetColor(255, 0, 0);            //�Ԃ̐F
int White = GetColor(255, 255, 255);      //�h��Ԃ��p�i���j            
int FileHandle;                           //�t�@�C��
FILE* fp;

//�X�V
void Score_Update() {
	high_score.score = 0;
}

//�`��
void Score_Save() {

	//�n�C�X�R�A�̃t�@�C�����J��
	FileHandle = FileRead_open("h_score.dat");

	// ��s�ǂ�
	FileRead_gets(high_score.String, 256, FileHandle);

	// ��ʂɕ`��
	DrawString(high_scorex, high_scorey, high_score.String, White);

	// �t�@�C�������
	FileRead_close(FileHandle);
}


void Score_Draw() {
	

	//�n�C�X�R�A�̋L�^
	fp = fopen("h_score.dat", "wb");
	fprintf(fp, "%d", high_score.h_score);

	fclose(fp);

	

	// �n�C�X�R�A�̕����`��
	DrawFormatString(900, 30, Red, "HIGH ");
	DrawFormatString(950, 50, Red, " SCORE");

	//�X�R�A�����̕`��
	DrawFormatString(900, 160, Red, "1UP");

	//�X�R�A�����̕`��
	DrawFormatString(scorex, scorey, White, "%d", high_score.score);

	// �n�C�X�R�A�̐����`��char�^
	DrawFormatString(high_scorex, high_scorey, White, "%s", high_score.String);

	//char�^����int�^�ւ̕ϊ�
	high_score.h_score = atoi(high_score.String);

	//�n�C�X�R�A�X�V�A�X�R�A�A��
	if (high_score.h_score < high_score.score) {
		SetDrawScreen(DX_SCREEN_BACK);  //�h��Ԃ�                        
		DrawBox(high_scorex, high_scorey, 1000, 150, Black, TRUE);

		//�h��Ԃ���̕`��
		high_score.h_score = high_score.score;
		DrawFormatString(high_scorex, high_scorey, White, "%d", high_score.h_score);
	}

}

void Score_Title() {
	
	//�n�C�X�R�A�̃t�@�C�����J��
	FileHandle = FileRead_open("h_score.dat");

	// ��s�ǂ�
	FileRead_gets(high_score.String, 256, FileHandle);

	// ��ʂɕ`��
	DrawString(140, 90, high_score.String, White);

	// ��ʂɕ`��
	DrawString(390, 90, high_score.String, White);

	// �t�@�C�������
	FileRead_close(FileHandle);

	//�X�R�A�����̕`��
	DrawFormatString(650, 90, White, "0");
}