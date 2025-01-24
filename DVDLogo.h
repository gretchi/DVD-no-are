#pragma once

int GetColorByHSV(float H, float S, float V);


class DVDLogo {

public:
	DVDLogo();
	~DVDLogo();
	void Draw();
	void Move();

private:

	float x;
	float y;
	float x_speed = 1.5;
	float y_speed = 1.5;
	int is_collision = 0;
	int color;

	void Generate();
};


