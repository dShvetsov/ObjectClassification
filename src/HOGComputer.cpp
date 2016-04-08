#include "HOGComputer.h"
#include <tuple>
#include <vector>
#include "HOG.h"

using std::tuple;
using std::vector;
using std::tie;


vector<float> HOGComputer::computeHog(){
	Hist h;
	for (int i = 0; i < int(angl.n_rows); i++){
		for (int j = 0; j < int(angl.n_cols); j++){
			h.add(angl(i, j), abs(i, j));
		}
	}
	h.normalization();
	return h;
}
tuple<float, float, float> HOGComputer::computeCol(){
	double rs = 0, gs = 0, bs = 0;
	uint r, g, b;
	for (int i = 0; i < int(im.n_rows); i++){
		for (int j = 0; j < int(im.n_cols); j++){
			tie(r,g,b) = im(i, j);
			rs += r;
			gs += g;
			bs += b;
		}
	}
	uint cnt = im.n_cols * im.n_cols;
	if (0 == cnt){
		throw "divide by zero";
	}
	rs /= cnt;
	bs /= cnt;
	gs /= cnt;
	return std::make_tuple(rs / 255, gs / 255, bs / 255);
}
vector<float> HOGComputer::compute(){
	auto a = computeHog();
	float r, g, b;
	tie(r, g, b) = computeCol();
	a.push_back(r);
	a.push_back(g);
	a.push_back(b);
	return a;
}
