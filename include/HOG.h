#ifndef __HOG_H
#define __HOG_H
#include <tuple>
#include <vector>
#include "matrix.h"


typedef Matrix<std::tuple<unsigned int, unsigned int, unsigned int>> Image; 

using std::vector;
using std::tie;
using std::tuple;

class HOG{
	const Image &src_image;
	Matrix<float> grad_abs;
	Matrix<float> grad_angle;
	vector<float> hog;
	struct rgb2bright{
		float operator()(const Image &im) const;
		static const int vert_radius = 0;
		static const int hor_radius = 0;
	};
	struct Sobel{
		tuple<float, float> operator ()(const Matrix<float> & in) const;
		static const int vert_radius = 1;
		static const int hor_radius = 1;
	};
	void ComputeGrad();
public:
	HOG(const Image &im):src_image(im), grad_abs(im.n_rows, im.n_cols), grad_angle(im.n_rows, im.n_cols),  hog(0,0) {
		ComputeGrad();
	}
	vector<float> &ComputeHog(int countx = 0, int county = 0);
};

#endif