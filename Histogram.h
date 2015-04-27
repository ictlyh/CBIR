#ifndef __HISTGRAM__H_
#define __HISTGRAM__H_

class Histogram {
private:
	int dim;
	float *feature;

public:
	Histogram();
	Histogram(int dim);
	
	void setDim(int d);
	int getDim();
	void setFeature(int index, flaot value);
	float getFeature(int index);
	float* getFeature();
};

#endif