#include "Similarity.h"

Similarity::Similarity()
{
	colorWeight = 0.5;
	shapeWeight = 0.5;
}

Similarity::Similarity(float color, float shape)
{
	colorWeight = color;
	shapeWeight = shape;
}

Similarity::~Similarity()
{
}

void Similarity::setColorWeight(float color)
{
	colorWeight = color;
}

void Similarity::setShapeWeight(float shape)
{
	shapeWeight = shape;
}

float Similarity::getColorWeight()
{
	return colorWeight;
}

float Similarity::getShapeWeight()
{
	return shapeWeight;
}
/*
 * ����ֱ��ͼ�ཻ����ֱ��ͼ���ƶȣ�Ҳ���Բ��ÿ����ȷ���
 */
float Similarity::similarity(Histogram a, Histogram b)
{
	float molecule = 0.0;
	float denominator = 0.0;
	for(int i = 0; i < a.getDim(); i++)
	{
		if(a.getFeature(i) > b.getFeature(i))
			molecule += b.getFeature(i);
		else
			molecule += a.getFeature(i);
		denominator += b.getFeature(i);
	}
	return molecule / denominator;
}

float Similarity::similarity(Image a, Image b)
{
	float colorSim = 0.0;
	float shapeSim = 0.0;
	ColorFeature aColor = a.getFeature().getColorFeature();
	ColorFeature bColor = b.getFeature().getColorFeature();
	ShapeFeature aShape = a.getFeature().getShapeFeature();
	ShapeFeature bShape = b.getFeature().getShapeFeature();
	colorSim = similarity(aColor.getH(), bColor.getH())
		+ similarity(aColor.getS(), bColor.getS())
		+ similarity(aColor.getV(), bColor.getV());
	shapeSim = similarity(aShape.getHorizontal(), bShape.getHorizontal())
		+ similarity(aShape.getVertical(), bShape.getVertical());
	// ������ɫ����״Ȩ�ؼ���ͼ�����ƶ�
	return colorWeight * colorSim / 3 + shapeWeight * shapeSim / 2;
}