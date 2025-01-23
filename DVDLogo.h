#pragma once

int GetColorByHSV(float H, float S, float V);


class DVDLogo {

public:
	DVDLogo();
	~DVDLogo();
	void Draw();
	void Move();

private:

	int x;
	int y;
	int x_speed = 1;
	int y_speed = 1;
	int is_collision = 0;
	int color;

	void Generate();
};


