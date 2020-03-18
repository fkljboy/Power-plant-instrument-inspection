/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_pointer.h
*
* 	@Brief	ָ���Ǳ��⺯��ͷ�ļ�.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1.	int Detect_pointer(const Mat src, double & angle)
*
*		2.	int ImgBrighten(const Mat srcImg, Mat & result);
*
*		3.	int enhance_contrast(const Mat srcImg, Mat & result);
*
*		4.	int find_baseline(const Mat srcImg, double & result);
*
*		5.	int find_detectarea(const Mat srcImg, Rect & boundary);
*
*		6.	int drawPoly(const Mat srcImg, Mat & result);
*
*		7.	int find_pointer(const Mat srcImg, const int mark, double & angle);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		created.
*
*	2.0		3/18		SHEN		Add Functions.
*/

#ifndef SGTASK_POINTER_H
#define SGTASK_POINTER_H


#include <opencv2\opencv.hpp>
using namespace cv;

// ָ���Ǳ������
int Detect_pointer(const Mat src, double & angle);

// ��������
int ImgBrighten(const Mat srcImg, Mat & result);

// ��ǿ�Աȶ�
int enhance_contrast(const Mat srcImg, Mat & result);

// ����ָ���Ǳ���ϱ߿���Ϊbaseline
int find_baseline(const Mat srcImg, double & result, Mat dstImg);

// ����Ǳ��ڱ߿��������ڱ߿����Ӿ�����Ϊָ��������
int find_detectarea(const Mat srcImg, Rect & boundary);

// ȥ����ǩ�ȸ���
int drawPoly(const Mat srcImg, Mat & result);

// ���ָ��
int find_pointer(const Mat srcImg, double & angle, Mat dstImg);

// ����find_pointer������qsort�������򣨴�С���� && ����������
int comp(const void*a, const void*b);

#endif // !SGTASK_POINTER_H
