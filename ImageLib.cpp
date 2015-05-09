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
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ���� S ��������
		tmpHist = colorFeature.getS();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ���� V ��������
		tmpHist = colorFeature.getV();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ����Ҷ���������
		tmpHist = colorFeature.getGray();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ����ˮƽ��������
		tmpHist = shapeFeature.getHorizontal();
		tmpArray = tmpHist.getFeature();
		for(int i = 0; i < tmpHist.getDim(); i++)
		{
			fprintf(ofs, "%4f ", tmpArray[i]);
		}
		fputs("\n", ofs);

		// ������ֱ��������
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
	imageList.clear();
	ifstream ifs;
	ifs.open(libFile, ios::in | ios::binary);
	char line[3000];
	while(!ifs.eof())
	{
		ifs.getline(line, 3000);
		// ���л����ļ�����
		if(ifs.failbit)
			break;

		list<string> liststr;
		// ʵ����һ��ͼ��
		Image img(line);

		// ��ȡH������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram h(liststr.size());
		for(int i = 0; i < h.getDim(); i++)
		{
			h.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡS������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram s(liststr.size());
		for(int i = 0; i < s.getDim(); i++)
		{
			s.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡV������������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram v(liststr.size());
		for(int i = 0; i < v.getDim(); i++)
		{
			v.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡ�Ҷ���������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram gray(liststr.size());
		for(int i = 0; i < gray.getDim(); i++)
		{
			gray.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡˮƽ�����Ե����������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram horizontal(liststr.size());
		for(int i = 0; i < horizontal.getDim(); i++)
		{
			horizontal.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ��ȡ��ֱ�����Ե����������
		ifs.getline(line, 3000);
		lineToFeature(line, liststr);
		Histogram vertical(liststr.size());
		for(int i = 0; i < vertical.getDim(); i++)
		{
			vertical.setFeature(i, atof(liststr.front().c_str()));
			liststr.pop_front();
		}

		// ����ͼ������
		Histogram features[] = { h, s, v, gray, horizontal, vertical };
		img.setFeature(features);

		// ����ͼ����б�
		imageList.push_back(img);
	}
	ifs.close();
}