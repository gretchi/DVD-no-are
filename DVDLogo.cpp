#include "DxLib.h"
#include "common.h"
#include "DVDLogo.h"


extern int raw_dvd_logo_image_handle;


DVDLogo::DVDLogo() {
	x = GetRand(SCREEN_WIDTH - DVD_LOGO_WIDTH);
	y = GetRand(SCREEN_HEIGHT - DVD_LOGO_HEIGHT);
	color = GetColorByHSV((float)GetRand(360), 0.8, 1.0);
}

DVDLogo::~DVDLogo() {

}

void DVDLogo::Generate() {
	CreateMaskScreen();


}

void DVDLogo::Move() {
	is_collision = 0;

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



void DVDLogo::Draw() {
	SetDrawBright((color >> 16) & 0xFF, (color >> 8) & 0xFF, (color >> 0) & 0xFF);
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawExtendGraph(x, y, x + DVD_LOGO_WIDTH, y + DVD_LOGO_HEIGHT, raw_dvd_logo_image_handle, TRUE);

}




int GetColorByHSV(float H, float S, float V)
{
	int hi;
	float f, p, q, t;
	float r, g, b;
	int ir, ig, ib;

	hi = (int)(H / 60.0f);
	hi = hi == 6 ? 5 : hi %= 6;
	f = H / 60.0f - (float)hi;
	p = V * (1.0f - S);
	q = V * (1.0f - f * S);
	t = V * (1.0f - (1.0f - f) * S);
	switch (hi)
	{
	case 0: r = V; g = t; b = p; break;
	case 1: r = q; g = V; b = p; break;
	case 2: r = p; g = V; b = t; break;
	case 3: r = p; g = q; b = V; break;
	case 4: r = t; g = p; b = V; break;
	case 5: r = V; g = p; b = q; break;
	}

	ir = (int)(r * 255.0f);
	if (ir > 255) ir = 255;
	else if (ir < 0) ir = 0;

	ig = (int)(g * 255.0f);
	if (ig > 255) ig = 255;
	else if (ig < 0) ig = 0;

	ib = (int)(b * 255.0f);
	if (ib > 255) ib = 255;
	else if (ib < 0) ib = 0;

	return GetColor(ir, ig, ib);
}

