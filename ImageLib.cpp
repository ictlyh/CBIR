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
		Image img(files.front);
		files.pop_front();
		img.calcFeature();
		imageList.push_back(img);
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
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);
	}
	fclose(ofs);
}

void ImageLib::loadImageLib()
{
	ifstream ifs;
	ifs.open(libFile, ios::in | ios::binary);
	char line[3000];
	while(!ifs.eof())
	{
		ifs.getline(line, 3000);
		if(ifs.failbit)
			break;
		Image img(line);
		list<string> liststr;

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram h(liststr.size());
		for(int i = 0; i < h.getDim(); i++)
		{
			h.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram s(liststr.size());
		for(int i = 0; i < s.getDim(); i++)
		{
			s.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram v(liststr.size());
		for(int i = 0; i < v.getDim(); i++)
		{
			v.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram gray(liststr.size());
		for(int i = 0; i < gray.getDim(); i++)
		{
			gray.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram horizontal(liststr.size());
		for(int i = 0; i < horizontal.getDim(); i++)
		{
			horizontal.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram vertical(liststr.size());
		for(int i = 0; i < vertical.getDim(); i++)
		{
			vertical.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		Histogram features[] = { h, s, v, gray, horizontal, vertical };
		img.setFeature(features);

		imageList.push_back(img);
	}
}