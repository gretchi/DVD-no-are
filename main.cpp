#include "DxLib.h"
#include <time.h>


#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 576
#define WINDOW_TITLE "DVD no are"

#define DVD_LOGO_WIDTH 120
#define DVD_LOGO_HEIGHT DVD_LOGO_WIDTH * 0.44140625

int raw_dvd_logo_image_handle = 0;
int colored_dvd_logo_image_handle = 0;

void Loop();
void Load();
void Init();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();

	if (DxLib_Init() == -1)
	{
		return -1;
	}


	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	SRand((int)time(NULL));


	Load();

	while (1) {
		ClearDrawScreen();

		Loop();

		ScreenFlip();

		if (ProcessMessage() == -1) {
			return -1;
		}
	}


	//WaitKey();

	DxLib_End();

	return 0;
}

void Loop() {
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawBox(0, 0, 720, 576, 0xffffff, TRUE);


	SetDrawBright(255, 0, 0);
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);

	DrawExtendGraph(0, 0, DVD_LOGO_WIDTH, DVD_LOGO_HEIGHT, raw_dvd_logo_image_handle, TRUE);



}

void Load() {
	raw_dvd_logo_image_handle = LoadGraph("./DVD_logo.png");

}

void Init() {
	SetAlwaysRunFlag(TRUE);
	SetWaitVSyncFlag(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	ChangeWindowMode(TRUE);
	SetWindowText(WINDOW_TITLE);
}
