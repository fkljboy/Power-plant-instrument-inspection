/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_transform.h
*
* 	@Brief	ͼ��任������ͷ�ļ�.
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


// ���Ա任ͼ��ı�Աȶ�
int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg);

// �����任��������ֵ�ϵ͵�����
int Trans_logTransform(const Mat srcImg, const int c, Mat & result);

// �����ͼƬ���г�ʼ��
int undistortImg(const Mat srcImg, Mat & resultImg, int cameraType);

#endif // !SGFUNC_TRANSFORM_H