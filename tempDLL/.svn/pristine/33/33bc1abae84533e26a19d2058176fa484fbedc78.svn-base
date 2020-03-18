/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_transform.h
*
* 	@Brief	图像变换函数的头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-17
*
*	@MethodList
*		1.	int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg);
*
*		2.	int Trans_logTransform(const Mat srcImg, const int c, Mat & result);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/17		SHEN		Cerated.
*
*/ 


#ifndef SGFUNC_TRANSFORM_H
#define SGFUNC_TRANSFORM_H


#include <opencv2\opencv.hpp>
using namespace cv;


// 线性变换图像改变对比度
int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg);

// 对数变换增大像素值较低的区域
int Trans_logTransform(const Mat srcImg, const int c, Mat & result);

// 对相机图片进行初始化
int undistortImg(const Mat srcImg, Mat & resultImg, int cameraType);

#endif // !SGFUNC_TRANSFORM_H