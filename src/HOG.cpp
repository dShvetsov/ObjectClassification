#include "HOG.h"
#include <tuple>
#include <math.h>
#include <vector>
#include "HOGComputer.h"

using std::vector;

void HOG::ComputeGrad()
{
	Matrix<float> tmp = src_image.unary_map(rgb2bright());
	Matrix<std::tuple<float, float>> g = tmp.unary_map(Sobel());
	float x, y;
	for (int i = 0; i < int(g.n_rows); i++){
		for (int j = 0; j < int(g.n_cols); j++){
			std::tie(x, y) = g(i, j);
			grad_abs(i, j) = sqrt(x*x + y*y);
			grad_angle(i, j) = atan2(y, x);
		}
	}
}

vector<float> &HOG::ComputeHog(int countx, int county)
{
	if (0 == countx){
		return hog;
	}
	if (0 == county){
		county = countx;
	}
	int sizex = grad_angle.n_rows / countx;
	int sizey = grad_angle.n_cols / county;
	for (int i = 0; i < countx; i++){
		for (int j = 0; j < county; j++){
			auto hlp1 = grad_angle.submatrix(i * sizex, j * sizey, sizex, sizey);
			auto hlp2 = grad_abs.submatrix(i * sizex, j * sizey, sizex, sizey);
			auto hlp3 = src_image.submatrix(i * sizex, j * sizey, sizex, sizey);
			HOGComputer hc(hlp1, hlp2, hlp3);
			auto tmp = hc.compute();
			hog.insert(hog.end(), tmp.begin(), tmp.end());
		}
	}
	return hog;
}

float HOG::rgb2bright::operator()(const Image &im) const
{
	uint r, g, b;
	tie(r,g,b) = im(0,0);
	return 0.299 * r + 0.587 * g + 0.114 * b; 
}

tuple<float, float> HOG::Sobel::operator ()(const Matrix<float> & in) const
{
	int sizex = 2 * vert_radius + 1;
	int sizey = 2 * hor_radius + 1;

 /*	float sobelx[3][3] = { {-1, 0, 1},
						{-2, 0, 2},
						{-1, 0, 1} };
	float sobely[3][3] = { { 1,  2,  1},
							{ 0,  0,  0},
							{-1, -2, -1}}; */
	float sobelx[3][3] = { {0, 0, 0},
						{-1, 0, 1},
						{0, 0, 0} };
	float sobely[3][3] = { { 0,  1,  0},
							{ 0,  0,  0},
							{0, -1, 0}};

	float x = 0, y = 0;

	for (int i = 0; i < sizex; i++){
		for (int j = 0; j < sizey; j++){
			x += in(i,j) * sobelx[i][j];
			y += in(i,j) * sobely[i][j];
		}
	}
	return std::make_tuple(x, y);
}