#include "DxLib.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	int x = 0;
	int font = CreateFontToHandle("‚l‚r ƒSƒVƒbƒN", 16, 6, DX_FONTTYPE_EDGE);
	int flag = 0;
	ChangeFontType(DX_FONTTYPE_EDGE);

	while ((ScreenFlip() == 0) && (ProcessMessage() == 0) && (ClearDrawScreen() == 0)) {
		//‚±‚±‚ÉŒvŽZˆ—‚ð‘‚­
		if (flag == 0) {
			x++;
			if (x >= 255) flag = 1;
		}
		else if (flag == 1) {
			x--;
			if (x <= 0) flag = 0;
		}


		//‚±‚±‚É•`‰æˆ—‚ð‘‚­
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(0, 0, GetColor(255, 0, 0), "“§–¾“x=%d", x);

		DrawString(0, 48, "TEST", GetColor(0, 0, 0), GetColor(255, 255, 255));
		DrawStringToHandle(0, 64, "TEST", GetColor(0, 0, 0), font, GetColor(255, 255, 255));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawString(0, 96, "TEST", GetColor(0, 0, 0), GetColor(255, 255, 255));
		DrawStringToHandle(0, 112, "TEST", GetColor(0, 0, 0), font, GetColor(255, 255, 255));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, x);
		DrawString(0, 144, "TEST", GetColor(0, 0, 0), GetColor(255, 255, 255));
		DrawStringToHandle(0, 160, "TEST", GetColor(0, 0, 0), font, GetColor(255, 255, 255));
	}
}