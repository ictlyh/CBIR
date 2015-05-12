#include "ImageLib.h"
#include "methods.h"

ImageLib::ImageLib()
{
	libFile = "imagefeaturelib.txt";
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
		if(img->calcFeature())
			imageList.push_back(*img);
	}
}

bool ImageLib::saveImageLib()
{
	/*
	* ͼ�������洢�ļ���ʽ
	* ͼ��1·��
	* H ��������
	* S ��������
	* V ��������
	* �Ҷ���������
	* ˮƽ��������
	* ��ֱ��������
	* ͼ��2·��
	*	.
	*	.
	*	.
	*/
	FILE* ofs;
	ofs = fopen(libFile, "wb");
	if(!ofs)
	{
		fprintf(stderr, "Error:open file failed in ImageLib::saveImageLib.\n File path:%s", libFile);
		return false;
	}
	for(list<Image>::iterator ite = imageList.begin(); ite != imageList.end(); ite++)
	{
		Image tmp = *ite;
		// ����ͼ��·��
		fputs(tmp.getPath(), ofs);
		fputs("\n", ofs);

		ColorFeature colorFeature = tmp.getFeature().getColorFeature();
		ShapeFeature shapeFeature = tmp.getFeature().getShapeFeature();
		Histogram tmpHist;
		float* tmpArray;

		// ���� H ��������
		tmpHist = colorFeature.getH();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ���� S ��������
		tmpHist = colorFeature.getS();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ���� V ��������
		tmpHist = colorFeature.getV();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ����Ҷ���������
		tmpHist = colorFeature.getGray();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ����ˮƽ��������
		tmpHist = shapeFeature.getHorizontal();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ������ֱ��������
		tmpHist = shapeFeature.getVertical();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%.4f ", tmpArray[i]);
		}
		fputs("\n", ofs);
	}
	fclose(ofs);
	return true;
}

bool ImageLib::loadImageLib()
{
	imageList.clear();
	ifstream ifs;
	ifs.open(libFile, ios::in | ios::binary);
	if(!ifs)
	{
		fprintf(stderr, "Error:open file failed in ImageLib::loadImageLib.\n File path:%s", libFile);
		return false;
	}
	char line[10000];
	while(!ifs.eof())
	{
		ifs.getline(line, 3000);
		// ����
		if(strlen(line) == 0)
			break;

		list<string> liststr;
		// ʵ����һ��ͼ��
		Image img(line);

		// ��ȡH������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram h((int)liststr.size());
		for(int i = 0; i < h.getDim(); i++)
		{
			h.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡS������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram s((int)liststr.size());
		for(int i = 0; i < s.getDim(); i++)
		{
			s.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡV������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram v((int)liststr.size());
		for(int i = 0; i < v.getDim(); i++)
		{
			v.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡ�Ҷ���������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram gray((int)liststr.size());
		for(int i = 0; i < gray.getDim(); i++)
		{
			gray.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡˮƽ�����Ե����������
		ifs.getline(line, 10000);
		lineToFeature(line, liststr);
		Histogram horizontal((int)liststr.size());
		for(int i = 0; i < horizontal.getDim(); i++)
		{
			horizontal.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡ��ֱ�����Ե����������
		ifs.getline(line, 10000);
		lineToFeature(line, liststr);
		Histogram vertical((int)liststr.size());
		for(int i = 0; i < vertical.getDim(); i++)
		{
			vertical.setFeature(i, (float)atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ����ͼ������
		Histogram features[] = { h, s, v, gray, horizontal, vertical };
		img.setFeature(features);

		// ����ͼ����б�
		imageList.push_back(img);
	}
	ifs.close();
	return true;
}
