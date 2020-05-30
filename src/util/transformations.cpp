#include "transformations.h"

// Constructor for a base transformation
// intialize the main diagonal to 1 and the rest in 0
Transformation::Transformation() {
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			if(r == c)
				mtrx[r][c] = 1.0;
			else
				mtrx[r][c] = 0.0;
		}
	}
}
// Constructor that creates a copy of other transformation
Transformation::Transformation(Transformation *cp) {
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			mtrx[r][c] = cp->mtrx[r][c];
		}
	}
}


// Method that prints the matrix of the transformation
void Transformation::PrintMtrx() {
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++)
			printf("%f ", mtrx[r][c]);

		printf("\n");
	}
}

// Method that computes the transformation with the homogenous
// coordinates of the object
// Args:
// 		h_coord: 1d array of size 4, with [x, y, z, 1]
float* Transformation::Compute(float h_coord[4]) {
	float *result;
	result = (float*)malloc(sizeof(float)*4);

	int rr, ct;
	for(rr = 0; rr < 4; rr++) {
		*(result + rr) = 0;
		for(ct = 0; ct < 4; ct++)
			*(result + rr) += h_coord[ct] * mtrx[rr][ct];
	}

	return result;
}

// Method that computes two transformations to create a new
// transformation, of the combination of the two
// Args:
// 		other: tranformation B, to compute AxB
Transformation* Transformation::Compute(Transformation other) {
	Transformation *result = new Transformation;

	for(int r = 0; r < 3; r++) {
		for(int c = 0; c < 4; c++) {
			result->mtrx[r][c] = 0.0;
			for(int i = 0; i < 4; i++) {
				result->mtrx[r][c] += mtrx[r][i] * other.mtrx[i][c];
			}
		}
	}

	return result;
}

// Static method that concatenates various tranformation to produce one final
// transformation
// Args:
// 		trans: vector with all the transformations to compute
// Returns:
// 		res: Transformation object with the final transformation
Transformation* Transformation::Concat(std::vector<Transformation> trans) {
	Transformation *result;
	Transformation *tmp;

	if(trans.size() > 1) {
		result = new Transformation(&trans.back());
		trans.pop_back();
		for(int i = trans.size()-1; i >= 0; i--) {
			tmp = result->Compute(trans[i]);
			delete result;
			result = new Transformation(tmp);
			delete tmp;
		}
	}
	
	return result;
}

// Static method that perform varios tranformations to some coordinates
// Args:
// 		trans: vector with all the transformations to compute
// 		x: x coordinate to apply
// 		y: y coordinate to apply
// 		z: z coordinate to apply
// Returns:
// 		res: 1d array of size 4 [x, y, z, 1]
float* Transformation::Concat(std::vector<Transformation> trans, float x, float y, float z) {
	float *result;
	float coord[4] = {x, y, z, 1.0};

	Transformation* tran = Concat(trans);

	result = tran->Compute(coord);
	
	return result;
}

// Constructor for the Translate transformation
// Args:
// 		dx: delta in the x coordinate
// 		dy: delta in the y coordinate
// 		dz: delta in the z coordinate
TTranslate::TTranslate(float dx, float dy, float dz) {
	mtrx[0][3] = dx;
	mtrx[1][3] = dy;
	mtrx[2][3] = dz;
}

// Constructor for the Scale transformation
// Args:
// 		sx: x ratio
// 		sy: y ratio
// 		sz: z ratio
TScale::TScale(float sx, float sy, float sz) {
	mtrx[0][0] = sx;
	mtrx[1][1] = sy;
	mtrx[2][2] = sz;
}

// Construcutor for the Rotation transformation, with no pivot
// Args:
// 		teta: rotation angle
// 		axis: rotation axis (x, y, z)
TRotation::TRotation(double _teta, char axis) {
	teta = _teta;
	switch(axis) {
		case 'x':
			mtrx[1][1] = cos(to_radians(teta));
			mtrx[1][2] = -sin(to_radians(teta));
			mtrx[2][1] = sin(to_radians(teta));
			mtrx[2][2] = cos(to_radians(teta));
			break;

		case 'y':
			mtrx[0][0] = cos(to_radians(teta));
			mtrx[0][2] = sin(to_radians(teta));
			mtrx[2][0] = -sin(to_radians(teta));
			mtrx[2][2] = cos(to_radians(teta));
			break;

		case 'z':
			mtrx[0][0] = cos(to_radians(teta));
			mtrx[0][1] = -sin(to_radians(teta));
			mtrx[1][0] = sin(to_radians(teta));
			mtrx[1][1] = cos(to_radians(teta));
			break;
	}
}

// Constructor for Rotation with respect to a pivot
// Args:
// 		teta: rotation angle
// 		axis: rotation axis (x, y, z)
// 		x, y, z: coordinates of the pivot
TRotation::TRotation(double _teta, char axis, float x, float y, float z) {
	teta = _teta;

	std::vector<Transformation> trans;
	trans.push_back(TTranslate(-x, -y, -z));
	trans.push_back(TRotation(teta, axis));
	trans.push_back(TTranslate(x, y, z));

	Transformation *tra = Transformation::Concat(trans);
	for(int r = 0; r < 3; r++)
		for(int c = 0; c < 4; c++)
			mtrx[r][c] = tra->mtrx[r][c];

	delete tra;
}

double to_radians(double degrees) {
	return (degrees * PI) / 180;
}

double to_degrees(double radians) {
	return radians * (180 / PI);
}
