/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_analog.h
*
* 	@Brief	模拟指示器识别函数头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1. int Detect_analog(const Mat srcImg, const unsigned int analogtype, const unsigned int analognum, unsigned int * valueArr)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		Created.
*	
*/ 

#ifndef SGTASK_ANALOG_H
#define SGTASK_ANALOG_H

#include <opencv2\opencv.hpp>
using namespace cv;


// 模拟指示器识别入口.
int Detect_analog(const Mat srcImg, const unsigned int analogtype, vector<int> &valueArr);

Mat thinImage(const Mat & src, const int maxIterations = -1);

double getDistance(CvPoint pointO, CvPoint pointA);

int detectColorWithPoints(const Mat srcImg, Vec3b color, const int red, const int green, const int blue, const int minimum, Mat & result, vector<Point> & Points, int & figures);

void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color);

int analog_circles_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr);

int analog_twopannels_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr);

int analog_onepanel_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr);

int analog_lights_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr);

#endif // !SGTASK_ANALOG_H
