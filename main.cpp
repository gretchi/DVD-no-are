#include "DxLib.h"
#include "common.h"
#include "DVDLogo.h"
#include <time.h>


void Loop();
void Load();
void Init();


int raw_dvd_logo_image_handle = 0;

DVDLogo *dvd_logo = new DVDLogo();


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

	delete(dvd_logo);

	DxLib_End();

	return 0;
}

void Loop() {
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		
	dvd_logo->Move();
	dvd_logo->Draw();




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
