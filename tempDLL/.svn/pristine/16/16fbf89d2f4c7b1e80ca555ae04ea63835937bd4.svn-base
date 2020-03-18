/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_pointer.h
*
* 	@Brief	指针仪表检测函数头文件.
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

// 指针仪表检测入口
int Detect_pointer(const Mat src, double & angle);

// 增加亮度
int ImgBrighten(const Mat srcImg, Mat & result);

// 增强对比度
int enhance_contrast(const Mat srcImg, Mat & result);

// 利用指针仪表的上边框作为baseline
int find_baseline(const Mat srcImg, double & result, Mat dstImg);

// 检测仪表内边框，利用其内边框的外接矩形作为指针检测区域
int find_detectarea(const Mat srcImg, Rect & boundary);

// 去除标签等干扰
int drawPoly(const Mat srcImg, Mat & result);

// 检测指针
int find_pointer(const Mat srcImg, double & angle, Mat dstImg);

// 用于find_pointer函数中qsort函数排序（从小到大 && 正负数排序）
int comp(const void*a, const void*b);

#endif // !SGTASK_POINTER_H
