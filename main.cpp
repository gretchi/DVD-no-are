#include "DxLib.h"
#include "DVDLogo.h"
#include <time.h>


#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 576
#define WINDOW_TITLE "DVD no are"

#define DVD_LOGO_WIDTH 160
#define DVD_LOGO_HEIGHT DVD_LOGO_WIDTH * 0.44140625

int raw_dvd_logo_image_handle = 0;
int colored_dvd_logo_image_handle = 0;

void Loop();
void Load();
void Init();


int x = 0;
int y = 0;
int x_speed = 1;
int y_speed = 1;

int color = GetColorByHSV(GetRand(360), 255.0, 255.0);


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

	int is_collision = 0;
	
	
	SetDrawBright((color >> 16) & 0xFF, (color >> 8) & 0xFF, (color >> 0) & 0xFF);

	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);

	DrawExtendGraph(x, y, x + DVD_LOGO_WIDTH, y + DVD_LOGO_HEIGHT, raw_dvd_logo_image_handle, TRUE);

	x += x_speed;
	y += y_speed;


	if (x + DVD_LOGO_WIDTH > SCREEN_WIDTH) {
		x_speed *= -1;
		is_collision = 1;
	}
	if (y + DVD_LOGO_HEIGHT > SCREEN_HEIGHT) {
		y_speed *= -1;
		is_collision = 1;
	}
	if (x < 0) {
		x_speed *= -1;
		is_collision = 1;
	}
	if (y < 0) {
		y_speed *= -1;
		is_collision = 1;
	}


	if (is_collision) {
		color = GetColorByHSV((float)GetRand(360), 0.8, 1.0);
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
