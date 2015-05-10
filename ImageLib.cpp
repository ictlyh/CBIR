#include "ImageLib.h"
#include "methods.h"

ImageLib::ImageLib(char* dir, char* file)
{
	libDir = dir;
	libFile = file;
}

ImageLib::ImageLib(char* dir)
{
	libDir = dir;
	libFile = "imagefeaturelib.txt";
}

ImageLib::~ImageLib()
{
}

char* ImageLib::getLibDir()
{
	return libDir;
}

char* ImageLib::getLibFile()
{
	return libFile;
}

list<Image> ImageLib::getImageList()
{
	return imageList;
}

void ImageLib::setLibDir(char* dir)
{
	libDir = dir;
}

void ImageLib::setLibFile(char* file)
{
	libFile = file;
}

void ImageLib::buildImageLib()
{
	imageList.clear();
	list<string> files;
	dfsDirectory(libDir, files);
	while(!files.empty())
	{
		char tmp[200];
		strcpy_s(tmp, files.front().c_str());
		Image *img = new Image(tmp);
		files.pop_front();
		img->calcFeature();
		imageList.push_back(*img);
	}
}

void ImageLib::saveImageLib()
{
	/*
	* 图像特征存储文件格式
	* 图像1路径
	* H 特征数组
	* S 特征数组
	* V 特征数组
	* 灰度特征数组
	* 水平特征数组
	* 竖直特征数组
	* 图像2路径
	*	.
	*	.
	*	.
	*/
	FILE* ofs;
	ofs = fopen(libFile, "wb");
	if(!ofs)
	{
		fprintf(stderr, "Error:open file failed in ImageLib::saveImageLib.\n File path:%s", libFile);
		system("pause");
		exit(-1);
	}
	for(list<Image>::iterator ite = imageList.begin(); ite != imageList.end(); ite++)
	{
		Image tmp = *ite;
		// 保存图像路径
		fputs(tmp.getPath(), ofs);
		fputs("\n", ofs);

		ColorFeature colorFeature = tmp.getFeature().getColorFeature();
		ShapeFeature shapeFeature = tmp.getFeature().getShapeFeature();
		Histogram tmpHist;
		float* tmpArray;

		// 保存 H 特征数组
		tmpHist = colorFeature.getH();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// 保存 S 特征数组
		tmpHist = colorFeature.getS();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// 保存 V 特征数组
		tmpHist = colorFeature.getV();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// 保存灰度特征数组
		tmpHist = colorFeature.getGray();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// 保存水平特征数组
		tmpHist = shapeFeature.getHorizontal();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// 保存竖直特征数组
		tmpHist = shapeFeature.getVertical();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			// 保存小数点后6位数字
			fprintf(ofs, "%.6f ", tmpArray[i]);
		}
		fputs("\n", ofs);
	}
	fclose(ofs);
}

void ImageLib::loadImageLib()
{
	imageList.clear();
	ifstream ifs;
	ifs.open(libFile, ios::in | ios::binary);
	if(!ifs)
	{
		fprintf(stderr, "Error:open file failed in ImageLib::loadImageLib.\n File path:%s", libFile);
		system("pause");
		exit(-1);
	}
	char line[10000];
	while(!ifs.eof())
	{
		ifs.getline(line, 3000);
		// 空行
		if(strlen(line) == 0)
			break;

		list<string> liststr;
		// 实例化一个图像
		Image img(line);

		// 读取H分量特征数组
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram h((int)liststr.size());
		for(int i = 0; i < h.getDim(); i++)
		{
			h.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 读取S分量特征数组
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram s((int)liststr.size());
		for(int i = 0; i < s.getDim(); i++)
		{
			s.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 读取V分量特征数组
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram v((int)liststr.size());
		for(int i = 0; i < v.getDim(); i++)
		{
			v.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 读取灰度特征数组
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram gray((int)liststr.size());
		for(int i = 0; i < gray.getDim(); i++)
		{
			gray.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 读取水平方向边缘点特征数组
		ifs.getline(line, 10000);
		lineToFeature(line, liststr);
		Histogram horizontal((int)liststr.size());
		for(int i = 0; i < horizontal.getDim(); i++)
		{
			horizontal.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 读取竖直方向边缘点特征数组
		ifs.getline(line, 10000);
		lineToFeature(line, liststr);
		Histogram vertical((int)liststr.size());
		for(int i = 0; i < vertical.getDim(); i++)
		{
			vertical.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// 设置图像特征
		Histogram features[] = { h, s, v, gray, horizontal, vertical };
		img.setFeature(features);

		// 加入图像库列表
		imageList.push_back(img);
	}
	ifs.close();
}