#ifndef __HIST_H
#define __HIST_H

#include <vector>
#include <cstdlib>
#include <math.h>

using std::vector;

/** 
* @brief Histogramm
* This class is container for Histogramm of doublue value
* values will be divide into some count of classters, and accamulate
*/

class Hist
{
	vector <float> v;
	const int count;
	float start;
	float end;
/** 
* @brief detect number of classter, which is contains value
* @param value -- value, which we was append
* @return indicator of classter
*/
	int DetectClasster(float value);
public:
	~Hist() {}
/**
* @brief Constructor
* @param _start value, which start space of histogram
* @param _end value, which end space of histogram
* @param _count count of classters
*/
	Hist( int _count = 8, float _start = -M_PI, float _end = M_PI) :  v(_count, 0), count(_count),  start(_start), end(_end){};
/**
* @brief add value in histogram
* @param value is value, you want append
*/
	void add(float value, float factor = 1);
/**
* @brief histogramm as vector
*/
	operator vector<float>() const {return v;}
/** 
* @brief vector normalization
*/
	void normalization();
};


#endif