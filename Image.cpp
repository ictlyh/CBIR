#include "Image.h"

Image::Image(char* p)
{
	path = p;
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
	IplImage * img = cvLoadImage(path);
	if(img == NULL)
	{
		fprintf(stderr, "Error:load image failed.\n Image path:%s", path);
		return ;
	}
	cvNamedWindow(path, CV_WINDOW_AUTOSIZE );
	cvShowImage(path, img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow(path);
}

void Image::calcColorFeature()
{
	// ‘ÿ»ÎÕºœÒ
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED);
	if(!src)
	{
		printf("Could not load image file: %s\n", path);
		exit(0);
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
}

void Image::calcShapeFeature()
{
	// ‘ÿ»ÎÕºœÒ
	IplImage * src = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED);
	if(!src)
	{
		printf("Could not load image file: %s\n", path);
		exit(0);
	}
	// ª“∂»ÕºœÒ
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