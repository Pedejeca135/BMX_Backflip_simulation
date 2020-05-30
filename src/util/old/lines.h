#ifndef LINES_H
#define LINES_H

#include "../objects.h"
#include "drawing.h"
#include <iostream>
#include <math.h>
#include "timer.h"
#include <vector>
//#include <GLUT/glut.h>

void drawLineDDA(Vertex vi, Vertex vf);

void drawLineBRE(Vertex v1, Vertex vf);

// Class that stores the information in order to perform a line trajectory
class LineTrajectory {
	private:
		Vertex *p1;						// Starting point of the line
		Vertex *p2;						// Ending point of the line
		int numPoints;					// Total number of points in betwen
		std::vector<Vertex> points;		// List with the points in betwen

		Timer *timer;					// Timer for the elapsed time
		
		void CalculatePointsDDA();
		void CalculatePointsBRE();

	public:
		LineTrajectory(Vertex *_p1, Vertex *_p2, float _duration, char typeL='B');
		
		bool started;					// If the trajectory has started
		bool finished;					// If the trajectory has finished
		float duration;					// Duration of the trajectory

		void Start();					// Starts the trajectory
		void Restart();					// Restarts the trajectory
		Vertex UpdatePosition();		// Returns the current position of the trajectory
};

#endif
