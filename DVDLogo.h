#pragma once

int GetColorByHSV(float H, float S, float V);


class DVDLogo {

public:
	DVDLogo();
	~DVDLogo();

private:
	double hue;

	void Generate();
};

