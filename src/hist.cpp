#include "hist.h"
#include <math.h>
#include <iostream>
void Hist::add(float value, float factor)
{
	v.at(DetectClasster(value)) += factor;
}

int Hist::DetectClasster(float value)
{
	float tmp = (end - start) / count;
	return int(value - start) / tmp;
} 

void Hist::normalization()
{
	static int numb = 0;
	float len = 0;
	for (int i = 0; i < count; i++){
		len = len + v[i] * v[i];
	}
	if (len < 0.000000001)
	{
		return;
	}
	len = sqrt(len);
	for (int i = 0; i < count; i++){
		v[i] /= len;
	}
	numb++;
}