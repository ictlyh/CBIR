#include "Image.h"

Image::Image()
{
}

Image::Image(char* p)
{
	strcpy_s(path, p);
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

void Image::setPath(string p)
{
	strcpy_s(path, p.c_str());
}

void Image::setFeature(Histogram features[])
{
	Histogram *color = features;
	Histogram *shape = &features[4];
	feature.setColorFeature(color);
	feature.setShapeFeature(shape);
}

void Image::showImage()
{
	IplImage * img = cvLoadImage(path, CV_LOAD_IMAGE_COLOR);
	if(img == NULL)
	{
		fprintf(stderr, "Error:load image failed in Image::showImage.\n Image path:%s\n", path);
		system("pause");
		exit(-1);
	}
	cvNamedWindow(path, CV_WINDOW_AUTOSIZE );
	cvShowImage(path, img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow(path);
}

bool Image::calcColorFeature()
{
	// ‘ÿ»ÎÕºœÒ
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_COLOR);
	if(!src)
	{
		fprintf(stderr, "Error:load image failed in Image::calcColorFeature.\n Image path:%s\n", path);
		return false;
	}
	
	//  ‰»ÎÕºœÒ◊™ªªµΩHSV—’…´ø’º‰
	IplImage * hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage * h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage * s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage * v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

	// ª“∂»ÕºœÒ
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
	return true;
}

bool Image::calcShapeFeature()
{
	// ‘ÿ»ÎÕºœÒ
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_COLOR);
	if(!src)
	{
		fprintf(stderr, "Error:load image failed in Image::calcShapeFeature.\n Image path:%s\n", path);
		return false;
	}
	// ª“∂»ÕºœÒ
	IplImage * gray = cvCreateImage(cvGetSize(src), 8, 1);
	cvCvtColor(src, gray, CV_BGR2GRAY);

	feature.calcShapeFeature(gray);

	cvReleaseImage(&src);
	cvReleaseImage(&gray);
	return true;
}

bool Image::calcFeature()
{
	if(!calcColorFeature() || !calcShapeFeature())
		return false;
	return true;
}