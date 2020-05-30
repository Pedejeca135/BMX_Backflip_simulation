#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#define PI 3.14159265

// Father class for implementation of 3d transformations
class Transformation {
	public:
		Transformation();	// constructor that inizialize default values
		Transformation(Transformation *cp);
		float* Compute(float h_coord[4]);
		Transformation* Compute(Transformation other);
		void PrintMtrx();

		// Static methods
		static Transformation* Concat(std::vector<Transformation> trans);
		static float* Concat(std::vector<Transformation> trans, float x, float y, float z);

		// renglon, columna
		float mtrx[4][4];	// 4x4 matrix for the 3d transformations
};

// Class for a Translation transformation
class TTranslate: public Transformation {
	public:
		TTranslate(float dx, float dy, float dz);

};

// Class for a ratation tranformation
class TRotation: public Transformation {
	public:
		TRotation(double _teta, char axis);
		TRotation(double _teta, char axis, float x, float y, float z);

	private:
		float teta;
};

class TScale: public Transformation {
	public:
		TScale(float sx, float sy, float sz);
};

double to_radians(double degrees);
double to_degrees(double radians);

#endif
