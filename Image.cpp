#include "Image.h"

Image::Image(char* p)
{
	path = p;
}

Image::~Image()
{
}

char* Image::getPath()
{
	return path;
}

Feature Image::getFeature()
{
	return feature;
}

void Image::setFeature(Histogram* features)
{
	Histogram color[4] = { features[0], features[1], features[2], features[3] };
	Histogram shape[2] = { features[4], features[5] };
	feature.setColorFeature(color);
	feature.setShapeFeature(shape);
}

void Image::showImage()
{
	IplImage * img = cvLoadImage(path, CV_LOAD_IMAGE_ANYCOLOR);
	if(img == NULL)
	{
		fprintf(stderr, "Error:load image failed in Image::showImage.\n Image path:%s", path);
		system("pause");
		exit(-1);
	}
	cvNamedWindow(path, CV_WINDOW_AUTOSIZE );
	cvShowImage(path, img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow(path);
}

void Image::calcColorFeature()
{
	// 载入图像
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_ANYCOLOR);
	if(!src)
	{
		fprintf(stderr, "Error:load image failed in Image::calcColorFeature.\n Image path:%s", path);
		system("pause");
		exit(-1);
	}
	
	// 输入图像转换到HSV颜色空间
	IplImage * hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage * h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage * s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage * v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

	// 灰度图像
	IplImage * gray = cvCreateImage(cvGetSize(src), 8, 1);
	cvCvtColor(src, gray, CV_BGR2GRAY);

	IplImage * planes[] = { h_plane, s_plane,v_plane, gray};

	feature.calcColorFeature(planes);

	cvReleaseImage(&src);
	cvReleaseImage(&hsv);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);
	cvReleaseImage(&gray);
	//cvReleaseImage(planes);
}

void Image::calcShapeFeature()
{
	// 载入图像
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_ANYCOLOR);
	if(!src)
	{
		fprintf(stderr, "Error:load image failed in Image::calcShapeFeature.\n Image path:%s", path);
		system("pause");
		exit(-1);
	}
	// 灰度图像
	IplImage * gray = cvCreateImage(cvGetSize(src), 8, 1);
	cvCvtColor(src, gray, CV_BGR2GRAY);

	feature.calcShapeFeature(gray);

	cvReleaseImage(&src);
	cvReleaseImage(&gray);
}

void Image::calcFeature()
{
	calcColorFeature();
	calcShapeFeature();
}