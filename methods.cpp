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

void dfsDirectory(char* dir, list<string> &listPath)
{
    _finddata_t FileInfo;
	char* strfind = (char*)malloc(sizeof(char) * (strlen(dir) + 3));
	strcpy(strfind, dir);
	strcat(strfind, "\\*");
    long Handle = _findfirst(strfind, &FileInfo);
    
    if (Handle == -1L)
    {
        cerr << "Can not match the folder path: " << dir << endl;
        exit(-1);
    }
    do{
        //判断是否有子目录
        if (FileInfo.attrib & _A_SUBDIR)    
        {
            // 判断是否为 . 和 ..
            if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
            {
				char* subdir = (char*) malloc (sizeof(char) * (strlen(dir) + 2 + strlen(FileInfo.name)));
				strcpy(subdir, dir);
				strcat(subdir, "\\");
				strcat(subdir, FileInfo.name);
                dfsDirectory(subdir, listPath);
				free(subdir);
            }
        }
		// 文件
        else
        {
			char* tmp = (char*) malloc (sizeof(char) * (strlen(dir) + 2 + strlen(FileInfo.name)));
			strcpy(tmp, dir);
			strcat(tmp, "\\");
			strcat(tmp, FileInfo.name);
			listPath.push_back(tmp);
			free(tmp);
        }
    }while (_findnext(Handle, &FileInfo) == 0);

    _findclose(Handle);
}

void lineToFeature(char* line, list<string> &liststr)
{
	liststr.clear();
	stringstream ss(line);
	string buf;
	while(ss >> buf)
	{
		liststr.push_back(buf);
	}
}