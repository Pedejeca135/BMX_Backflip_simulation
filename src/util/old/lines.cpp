#include "lines.h"

// Function that draws a line, using DDA algorithm
// Args:
// 		vi: vertex of the starting point
// 		vf: vertex of the end point
void drawLineDDA(Vertex vi, Vertex vf) {
	int dx = (int)(vf.x - vi.x), dy = (int)(vf.y - vi.y);
	int steps, k;
	float xlnc, ylnc, x = vi.x, y = vi.y;

	if(fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	xlnc = (float)(dx) / (float)(steps);
	ylnc = (float)(dy) / (float)(steps);

	putpixel(round(x), round(y));
	
	for(k = 0; k < steps; k++) {
		x += xlnc;
		y += ylnc;

		putpixel(round(x), round(y));
	}
}

// Function that draw a line using Bresenham algorithm
// Args:
// 		vi: vertex of the starting point
// 		vf: vertex of the end point
void drawLineBRE(Vertex vi, Vertex vf) {
	float dx = vf.x - vi.x, dy = vf.y - vi.y;
	float _2dy = 2.0f * dy;
	float _2dy_2dx = _2dy - 2.0f*dx;
	float pk = _2dy - dx;

	float x = vi.x, y = vi.y;

	putpixel(round(x), round(y));

	for(int k = 0; k < (int)(dx-1); k++) {
		if(pk < 0) {
			x++; y = y;
			pk += _2dy;
		} else {
			x++; y++;
			pk += _2dy_2dx;
		}

		putpixel(round(x), round(y));
	}
}

/*** LineTrajectory CLASS ***/
// Constructor of the LineTrajectory
// Args:
// 		*_p1: pointer to the starting point vertex
// 		*_p2: pointer to the end point vertex
// 		_duration: the total duration of the trajectory
LineTrajectory::LineTrajectory(Vertex *_p1, Vertex *_p2, float _duration, char typeL) {
	p1 = _p1; p2 = _p2;
	duration = _duration;

	started = false;
	finished = false;

	if(typeL == 'B')	
		CalculatePointsBRE();
	else if(typeL == 'D')	
		CalculatePointsDDA();
}

// Private method that creates the in betwen points of the trajectory,
// using DDA algorithm
void LineTrajectory::CalculatePointsDDA() {
	int dx = (int)(p2->x - p1->x), dy = (int)(p2->y - p1->y);
	int steps, k;
	float xlnc, ylnc, x = p1->x, y = p1->y;

	if(fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	xlnc = (float)(dx) / (float)(steps);
	ylnc = (float)(dy) / (float)(steps);

	numPoints = 0;

	for(k = 0; k < steps; k++) {
		x += xlnc;
		y += ylnc;

		points.push_back(Vertex(round(x), round(y), 0));
		numPoints++;
	}
}

// Private method that creates the in betwen points of the trajectory,
// using Bresenham algorithm
void LineTrajectory::CalculatePointsBRE() {
	float dx = p2->x - p1->x, dy = p2->y - p1->y;
	float _2dy = 2.0f * dy;
	float _2dy_2dx = _2dy - 2.0f*dx;
	float pk = _2dy - dx;

	float x = p1->x, y = p1->y;

	numPoints = 0;

	for(int k = 0; k < (int)(dx-1); k++) {
		if(pk < 0) {
			x++; y = y;
			pk += _2dy;
		} else {
			x++; y++;
			pk += _2dy_2dx;
		}

		points.push_back(Vertex(round(x), round(y), 0));
		numPoints++;
	}
}

// Starts the calculation of the trajectory
void LineTrajectory::Start() {
	if(timer == NULL)
		timer = new Timer();
	else
		timer->Restart();

	started = true;
	finished = false;
}

// Restarts the calculation of the trajectory
void LineTrajectory::Restart() { Start(); }

// Gets the current position on the trajectory
Vertex LineTrajectory::UpdatePosition() {
	double deltaTimer = timer->Delta();
	float t = (deltaTimer / duration);
	if(t > 1.0) {
		t = 1.0;
		finished = true;
	}

	int index = round(t * numPoints) - 1;

	return points[index];
}


