#include "curves.h"

// Function that draws a bezier line with points
// Args:
// 		p1: p1 in bezier geometry vector
// 		p2: p2 in bezier geometry vector
// 		p3: p3 in bezier geometry vector
// 		p4: p4 in bezier geometry vector
// 		dt: the amount that t will change during interpolation
void drawBezier(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt) {
	float x, y, z;

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	for(float t = 0; t <= 1; t += dt) {
		// Calculate common opperations
		float t_3 = t * t * t;
		float t_2 = t * t;
		float _3_t_3 = 3 * t_3;
		float _3_t_2 = 3 * t_2;
		float _3_t = 3 * t;

		// Calculate expresions
		float exp1 = -t_3 + _3_t_2 - _3_t + 1;
		float exp2 = _3_t_3 - 6*t_2 + _3_t;
		float exp3 = -_3_t_3 + _3_t_2;
		float exp4 = t_3;

		// Obtains coordinates
		x = exp1*p1.x + exp2*p2.x + exp3*p3.x + exp4*p4.x;
		y = exp1*p1.y + exp2*p2.y + exp3*p3.y + exp4*p4.y;
		z = exp1*p1.z + exp2*p2.z + exp3*p3.z + exp4*p4.z;

		//fputpixel(x, y, z);
		glVertex3f(x, y, z);
	}
	//fputpixel(p4.x, p4.y, p4.z);
	glVertex3f(x, y, z);
	glEnd();
}

// Function that draws the bezier curve of the trajectory
// Args:
// 		traj: the BezierTrajectory Object
// 		dt: the amount that t will change during interpolation
void drawBezier(BezierTrajectory traj, float dt) {
	Vertex p1 = *traj.p1;
	Vertex p2 = *traj.p2;
	Vertex p3 = *traj.p3;
	Vertex p4 = *traj.p4;

	drawBezier(*traj.p1, *traj.p2, *traj.p3, *traj.p4, dt);
}

// Constructor for the BezierTrajectory
BezierTrajectory::BezierTrajectory(Vertex *_p1, Vertex *_p2, Vertex *_p3,
								   Vertex *_p4, float _duration) {
	p1 = new Vertex(_p1); 
	p2 = new Vertex(_p2); 
	p3 = new Vertex(_p3); 
	p4 = new Vertex(_p4);

	started = false;
	finished = false;
	duration = _duration;
}

// Starts the calculation of the trajectory
void BezierTrajectory::Start() {
	if(timer == NULL)
		timer = new Timer();
	else
		timer->Restart();

	started = true;
	finished = false;
}

// Restarts the trajectory
void BezierTrajectory::Restart() { Start(); }

// Gets the curretn position on the trajectory
Vertex BezierTrajectory::UpdatePosition() {
	double deltaTimer = timer->Delta();

	float t = deltaTimer / duration;


	if(t <= 1) {
		float x, y, z;

		// Calculate common opperations
		float t_3 = t * t * t;
		float t_2 = t * t;
		float _3_t_3 = 3 * t_3;
		float _3_t_2 = 3 * t_2;
		float _3_t = 3 * t;

		// Calculate expresions
		float exp1 = -t_3 + _3_t_2 - _3_t + 1;
		float exp2 = _3_t_3 - 6*t_2 + _3_t;
		float exp3 = -_3_t_3 + _3_t_2;
		float exp4 = t_3;

		// Obtains coordinates
		x = exp1*p1->x + exp2*p2->x + exp3*p3->x + exp4*p4->x;
		y = exp1*p1->y + exp2*p2->y + exp3*p3->y + exp4*p4->y;
		z = exp1*p1->z + exp2*p2->z + exp3*p3->z + exp4*p4->z;

		return Vertex(x, y, z);
	} else {
		finished = true;
		return *p4;
	}
}

// Obtians the current value of the trayectorie at some t
// Args:
// 		ct: amount of t, value between 0 and 1
Vertex BezierTrajectory::getPosition(float t) {
	if(t <= 1 && t >= 0) {
		float x, y, z;

		// Calculate common opperations
		float t_3 = t * t * t;
		float t_2 = t * t;
		float _3_t_3 = 3 * t_3;
		float _3_t_2 = 3 * t_2;
		float _3_t = 3 * t;

		// Calculate expresions
		float exp1 = -t_3 + _3_t_2 - _3_t + 1;
		float exp2 = _3_t_3 - 6*t_2 + _3_t;
		float exp3 = -_3_t_3 + _3_t_2;
		float exp4 = t_3;

		// Obtains coordinates
		x = exp1*p1->x + exp2*p2->x + exp3*p3->x + exp4*p4->x;
		y = exp1*p1->y + exp2*p2->y + exp3*p3->y + exp4*p4->y;
		z = exp1*p1->z + exp2*p2->z + exp3*p3->z + exp4*p4->z;

		return Vertex(x, y, z);
	} else {
		return *p4;
	}
}
