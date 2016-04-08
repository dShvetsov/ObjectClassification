#ifndef __HOGComputer_h
#define __HOGComputer_h

#include "matrix.h"
#include "hist.h"
#include "HOG.h"
#include <vector>

using std::vector;

class HOGComputer{
	const Matrix<float> &abs;
	const Matrix<float> &angl;
	const Image &im;
public:
	HOGComputer(const Matrix<float> &_angl,const Matrix<float> &_abs, const Image &_im):abs(_abs), angl(_angl), im(_im){}

	vector<float> computeHog();
	tuple<float, float, float> computeCol();
	vector<float> compute();
};

#endif