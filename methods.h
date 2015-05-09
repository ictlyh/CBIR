#ifndef __METHODS_H__
#define __METHODS_H__

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <list>
#include <io.h>
#include "Histogram.h"
using namespace std;

void calcHist(IplImage *plane, Histogram &h, int dim);
void dfsDirectory(char* dir, list<string> &listPath);
#endif