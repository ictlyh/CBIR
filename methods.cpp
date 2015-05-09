#include "methods.h"

void calcHist(IplImage *plane, Histogram &h, int dim)
{
	h.setDim(dim);
	int width = plane->width;
	int height = plane->height;
	int step = plane->widthStep;
	uchar * data = (uchar * )plane->imageData;
	// 统计每个值的数量
	for(int i = 0; i < height; i ++ )
	{
		int tmp = i * step;
		for(int j = 0; j < width; j ++ )
		{
			h.setFeature(data[tmp + j], h.getFeature(data[tmp + j]) + 1);
		}
	}

	// 归一化直方图
	int tmp = width * height;
	for(int i = 0; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i) / tmp);
	}

	// 转换为累加直方图
	for(int i = 1; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i - 1) + h.getFeature(i));
	}
}