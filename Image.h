#ifndef __IMAGE__H_
#define __IMAGE__H_

#include "Feature.h"

class Image {
private:
	char* path;
	Feature feature;

public:
	Image(char* p);
	char* getPath();
	void showImage();
	void calcColorFeature();
	void calcShapeFeature();
	void calcFeature();
};

#endif