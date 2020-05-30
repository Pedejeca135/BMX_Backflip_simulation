#ifndef CURVES_H
#define CURVES_H

#include <stdio.h>
#include "../objects.h"
#include "drawing.h"
#include "math.h"
#include "timer.h"

void drawBezier(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt=0.05f);

class BezierTrajectory {
	public:
		BezierTrajectory(Vertex *_p1, Vertex *_p2, Vertex *_p3, Vertex *_p4,
						float _duration);
		bool started;				// If the trajectory has started
		bool finished;				// If the trajectory has finished
		float duration;				// Duration of the trajectory

		Timer *timer;				// Timer object

		Vertex *p1;					// p1 in bezier geometry vector
		Vertex *p2;					// p2 in bezier geometry vector
		Vertex *p3;					// p3 in bezier geometry vector
		Vertex *p4;					// p4 in bezier geometry vector

		void Start();				// Starts the trajectory
		void Restart();				// Restarts the trajectory
		Vertex UpdatePosition();	// Returns the current position of the trajectory
		Vertex getPosition(float t);		/// Obtains the current value of t
};

void drawBezier(BezierTrajectory traj, float dt=0.05f);

#endif
