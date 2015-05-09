#include "ShapeFeature.h"
#include "methods.h"

ShapeFeature::~ShapeFeature()
{
}

Histogram ShapeFeature::getHorizontal()
{
	return horizontal;
}

Histogram ShapeFeature::getVertical()
{
	return vertical;
}

void ShapeFeature::setHorizontal(Histogram horiz)
{
	horizontal.setDim(horiz.getDim());
	horizontal.setFeature(horiz.getFeature());
}

void ShapeFeature::setVertival(Histogram verti)
{
	vertical.setDim(verti.getDim());
	vertical.setFeature(verti.getFeature());
}

void ShapeFeature::calcHorizontal(IplImage * gray)
{
	int width = gray->width;
	int height = gray->height;
	int step = gray->widthStep;
	uchar * data = (uchar * )gray->imageData;
	// ���ػҶ�ֵ�ΧΪ[-255,255]
	horizontal.setDim(511);
	// ͳ��ÿ��ֵ�����ص���Ŀ
	for(int i = 0; i < height; i++)
	{
		int tmp = i * step;
		horizontal.setFeature(data[tmp] + 255, horizontal.getFeature(data[tmp] + 255) + 1);
		for(int j = 1; j < width; j++)
		{
			int index = data[tmp + j] - data[tmp + j - 1] + 255;
			horizontal.setFeature(index, horizontal.getFeature(index) + 1);
		}
	}
	// ��һ��
	int tmp = width * height;
	for(int i = 0; i < horizontal.getDim(); i++)
		horizontal.setFeature(i, horizontal.getFeature(i) / tmp);
	// ת��Ϊ�ۼ�ֱ��ͼ
	for(int i = 1; i < horizontal.getDim(); i++)
		horizontal.setFeature(i, horizontal.getFeature(i) + horizontal.getFeature(i - 1));
}

void ShapeFeature::calcVertical(IplImage * gray)
{
	int width = gray->width;
	int height = gray->height;
	int step = gray->widthStep;
	uchar * data = (uchar * )gray->imageData;
	// ���ػҶ�ֵ�ΧΪ[-255,255]
	vertical.setDim(511);
	// ͳ��ÿ��ֵ�����ص���Ŀ
	for(int j = 0; j < width; j++)
		vertical.setFeature(data[j] + 255, vertical.getFeature(data[j] + 255) + 1);
	for(int i = 1; i < height; i++)
	{
		for(int j = 1; j < width; j++)
		{
			int index = data[(i - 1) * step + j] - data[i * step + j] + 255;
			vertical.setFeature(index, vertical.getFeature(index) + 1);
		}
	}
	// ��һ��
	int tmp = width * height;
	for(int i = 0; i < vertical.getDim(); i++)
		vertical.setFeature(i, vertical.getFeature(i) / tmp);
	// ת��Ϊ�ۼ�ֱ��ͼ
	for(int i = 1; i < vertical.getDim(); i++)
		vertical.setFeature(i, vertical.getFeature(i) + vertical.getFeature(i - 1));
}