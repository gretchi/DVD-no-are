#include "DxLib.h"
#include "common.h"
#include "DVDLogo.h"
#include <time.h>

#define MAX_DVD_NUM 15

void Loop();
void Load();
void Init();


int raw_dvd_logo_image_handle = 0;

DVDLogo* dvd_logo[MAX_DVD_NUM];


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

	for (int i = 0; i < MAX_DVD_NUM; i++) {
		dvd_logo[i] = new DVDLogo();
	}

	while (1) {
		ClearDrawScreen();

		Loop();

		ScreenFlip();

		if (ProcessMessage() == -1) {
			return -1;
		}
	}


	//WaitKey();

	//delete(dvd_logo);

	DxLib_End();

	return 0;
}

void Loop() {
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	for (int i = 0; i < MAX_DVD_NUM; i++) {
		dvd_logo[i]->Move();
		dvd_logo[i]->Draw();
	}



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
