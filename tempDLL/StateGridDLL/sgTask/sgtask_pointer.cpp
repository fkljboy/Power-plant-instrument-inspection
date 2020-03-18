/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_pointer.cpp
*
* 	@Brief	指针仪表检测函数.
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
*		4.	int find_baseline(const Mat srcImg, double & result, Mat dstImg);
*
*		5.	int find_detectarea(const Mat srcImg, Rect & boundary);
*
*		6.	int dra.Poly(const Mat srcImg, Mat & result);
*
*		7.	int find_pointer(const Mat srcImg, double & angle, Mat dstImg);
*
*		8.	int comp(const void*a, const void*b);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		Created.
*
*	2.0		3/18		SHEN		Add Functions.
*/


#include "sgtask_pointer.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"

#include"../sgFunction/sgfunc_imageio.h"

#include <opencv2\opencv.hpp>

using namespace cv;


//#include <iostream>
//#include <stdlib.h>
//using namespace std;


/**
*	@Method		Detect_pointer
*
*	@Brief		指针式仪表检测入口.
*
*	@Para [IN]	const Mat src：	输入指针区域图像（经过ROI处理）
*
*	@Para [OUT]	double & angle：	指针的角度（下一步，根据定义规则，确认指针角度对应指针读数）
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		None
*
*	@Create		2018-03-15
*/
int Detect_pointer(const Mat srcImg, double & angle)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		return	sg_ERROR;
	}


	// 1. brighten
	Mat brightImg;
	resp = ImgBrighten(srcImg, brightImg);

	if (resp != sg_OK)
	{
		LOG(ERROR) << "指针检测中调用函数：  ImgBrighten时出错";
		return	sg_ERROR;
	}

	

	// 2. 高斯滤波
	GaussianBlur(brightImg, brightImg, Size(3, 3), 3, 3);


	// 3. 增强对比度
	Mat enhancedImg;
	resp = enhance_contrast(brightImg, enhancedImg);

	if (resp != sg_OK)
	{
		LOG(ERROR) << "指针检测中调用函数：  enhance_contrast时出错";
		return	sg_ERROR;
	}

	imgShowDebug(enhancedImg, "enhancedImg", 0);


	Mat resizeenhanceed;
	double bete = 200.0 / enhancedImg.cols;
	resize(enhancedImg, resizeenhanceed, Size(0, 0), bete, bete);
	Mat resizesrc;
	resize(srcImg, resizesrc, Size(0, 0), bete, bete);
	

	// 4. canny边缘检测
	Mat edges;
	Canny(resizeenhanceed, edges, 150, 400, 3);
	imgShowDebug(edges, "edges", 0);


	// 5. find baseline
	Mat baselinetempImg=edges(Rect(0, 0, resizeenhanceed.cols, resizeenhanceed.rows / 5));
	double baseline_angle;
	resp = find_baseline(baselinetempImg, baseline_angle, resizesrc);

	if (resp != sg_OK)
	{
		LOG(ERROR) << "指针检测中调用函数：  find_baseline时出错";
		return	sg_ERROR;
	}

	LOG(INFO) << "baseline的角度 = " << baseline_angle;


	// 6. 取指针检测区域ROI
	Mat ImgROI;
	Rect boundary;
	resp = find_detectarea(resizeenhanceed, boundary);

	if (resp != sg_OK)
	{
		LOG(ERROR) << "指针检测中调用函数：  find_detectarea时出错";
		return	sg_ERROR;
	}

	int alpha = boundary.height / 15;
	ImgROI = edges(Rect(boundary.tl() + Point(alpha, alpha), boundary.br() - Point(alpha, alpha)));

	Mat srcROI = resizesrc(Rect(boundary.tl() + Point(alpha, alpha), boundary.br() - Point(alpha, alpha)));


	// 7. drawPolyImg
	circle(ImgROI, Point(ImgROI.cols, ImgROI.rows), ImgROI.cols / 3, Scalar(0, 0, 0), -1);
	circle(ImgROI, Point(0,0), ImgROI.cols / 3, Scalar(0, 0, 0), -1);
	imgShowDebug(ImgROI, "ImgROI", 0);

	

	// 8. find_pointer
	double pointer_angle;
	resp = find_pointer(ImgROI, pointer_angle, srcROI);

	if (resp != sg_OK)
	{
		LOG(ERROR) << "指针检测中调用函数：  find_pointer时出错";
		return	sg_ERROR;
	}

	angle = pointer_angle - baseline_angle;
	LOG(INFO) << "pointer指针的角度（校正后） = " << angle ;

	return sg_OK;
}





/**
*	@Method		ImgBrighten
*
*	@Brief		增加亮度.
*
*	@Author		XU Lingli
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	Mat & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/
int ImgBrighten(const Mat srcImg, Mat & result)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：  ImgBrighten" << "  srcImg为空";
		return	sg_ERROR;
	}

	Mat ImgHLS;
	cvtColor(srcImg, ImgHLS, CV_RGB2HLS);

	//分离亮度通道
	vector<Mat> channels;
	split(ImgHLS, channels);
	Mat lightChannel = channels.at(1);

	//判断是否要提升亮度（根据对角线上的三个点的亮度值判断时候需要提升亮度）
	if (lightChannel.at<uchar>(srcImg.rows * 3 / 4, srcImg.cols / 4) < 140 &&
		lightChannel.at<uchar>(srcImg.rows / 2, srcImg.cols / 2) < 140 &&
		lightChannel.at<uchar>(srcImg.rows / 4, srcImg.cols * 3 / 4) < 140)
	{
		Mat grayImg;
		cvtColor(srcImg, grayImg, CV_BGR2GRAY);

		//叠加亮度以提升亮度
		result = lightChannel + grayImg;
	}
	else
	{
		cvtColor(srcImg, result, CV_RGB2GRAY);
	}

	return sg_OK;
}




/**
*	@Method		enhance_contrast
*
*	@Brief		增强对比度.
*
*	@Author		XU Lingli
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	Mat & result.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/
int enhance_contrast(const Mat srcImg, Mat & result)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：  enhance_contrast" << "  srcImg为空";
		return	sg_ERROR;
	}

	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(srcImg, &minVal, &maxVal, NULL, NULL);       //找到最大最小灰度值
	double gapVal = maxVal - minVal;


	// 利用灰度函数增强图片对比度
	result = srcImg.clone();
	int a = 0.2 * gapVal + minVal;
	int b = 0.4 * gapVal + minVal;
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			if (result.at<uchar>(i, j) < a)
			{
				result.at<uchar>(i, j) = 0;
			}
			else if (result.at<uchar>(i, j) < b)
			{
				double k = 255 * 1.0 / ((0.4 - 0.2) * gapVal);
				
				int temp = k * (result.at<uchar>(i, j) - a);
				if (temp < 0)
					result.at<uchar>(i, j) = 0;
				else
					result.at<uchar>(i, j) = temp;
			}
			else
				result.at<uchar>(i, j) = 255;
		}
	}

	return sg_OK;
}



/**
*	@Method		find_baseline
*
*	@Brief		This is a brief description.
*
*	@Author		XU Lingli
*
*	@Para [IN]	const Mat srcImg
*
*				Mat dstImg
*
*	@Para [OUT]	double & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/
int find_baseline(const Mat srcImg, double & result, Mat dstImg)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：  find_baseline" << "  srcImg为空";
		return	sg_ERROR;
	}


	//hough直线检测
	double alpha = srcImg.cols * 1.0 / 20;	      //alpha用来确定hough系数
	int thres = 6 * alpha;		                  //HoughLinesP中的threshold的属性int	
	double minLineLength = 5 * alpha;
	double maxLineGap = 2 * alpha;
	vector<Vec4i> lines;
	//threshold:判断直线点数的阈值。minLineLength：线段长度阈值。minLineGap : 线段上最近两点之间的阈值。
	HoughLinesP(srcImg, lines, 1, CV_PI / 180, thres, minLineLength, maxLineGap);  

	double sumangle = 0;
	int counter = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		double angle = (l[3] - l[1])*1.0 / (l[2] - l[0]);
		if (angle > 2)							//用来去除竖边框 
		{
			continue;
		}

		angle = atan(angle);

#ifdef _DEBUG
		line(dstImg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, CV_AA);
#endif // DEBUG
		
		sumangle += angle;
		counter++;
	}


	if (counter == 0)            //未找到基准线
	{
		LOG(ERROR) << "函数：  find_baseline" << "  未找到基准线";
		return sg_ERROR;
	}

	imgShowDebug(dstImg, "baselineImg", 0);

	result = (sumangle / counter) * 180 / CV_PI;
	
	LOG(INFO) << "基准线共检测到 " << counter << " 条边。";
	LOG(INFO) << "baseline = " << result ;

	return sg_OK;
}



/**
*	@Method		find_detectarea
*
*	@Brief		This is a brief description.
*
*	@Author		XU Lingli
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	Rect & boundary
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/
int find_detectarea(const Mat srcImg, Rect & boundary)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：  find_detectarea" << "  srcImg为空";
		return	sg_ERROR;
	}

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	int contourNumber = 0;
	findContours(srcImg.clone(), contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat imageContours = Mat::zeros(srcImg.size(), CV_8UC1);
	float minarea = srcImg.total();

	int minid = -1;

	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area < srcImg.rows*srcImg.cols*1.0 / 4)
			continue;
		if (area < minarea)
		{
			minarea = area;
			minid = i;
		}
	}

	if (minid == -1)
	{
		LOG(ERROR) << "函数：  find_detectarea" << "  未找到指针检测区域";
		return sg_ERROR;
	}

	boundary = boundingRect(contours[minid]);

	return sg_OK;
}



/**
*	@Method		find_pointer
*
*	@Brief		This is a brief description.
*
*	@Author		XU Lingli
*
*	@Para [IN]	const Mat srcImg
*
*				Mat dstImg
*
*	@Para [OUT]	double & angle.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/
int find_pointer(const Mat srcImg, double & angle, Mat dstImg)
{

	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：  find_pointer" << "  srcImg为空";
		return	sg_ERROR;
	}

	RNG rng;
	double rdm = rng.uniform((double)srcImg.cols * 0.045, (double)srcImg.cols * 0.05);
	RNG rng1;
	double rdm1 = rng1.uniform((double)srcImg.cols * 0.016, (double)srcImg.cols * 0.02);
	//三层循环，找到所有符合条件的直线，求平均
	double sumangle = 0;
	int counter = 0; 
	for (double maxLineGap = srcImg.cols * 0.06; maxLineGap < srcImg.cols * 0.1; maxLineGap += rng1.operator double() * 3.1)
	{
		for (int thres = srcImg.cols * 0.3; thres > srcImg.cols * 0.25; thres -= 5)
		{
			for (double minLineLength = thres - rng1.operator double(); minLineLength > srcImg.cols * 0.2; minLineLength -= rng.operator double() * 3.1)
			{
				vector<Vec4i> lines;
				HoughLinesP(srcImg, lines, 1, CV_PI / 180, thres, minLineLength, maxLineGap);
				if (lines.size() == 0)
					continue;
				for (size_t i = 0; i < lines.size(); i++)
				{
					Vec4i l = lines[i];
					double angle = (l[3] - l[1]) * 1.0 / (l[2] - l[0]);
					if (angle < -0.5)
						continue;
					angle = atan(angle);
					sumangle += angle;
					counter++;
					line(dstImg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, CV_AA);
				}
			}
		}
	}
	

	if (counter == 0)
	{
		LOG(ERROR) << "函数：  find_pointer" << "  未找到指针";
		return sg_ERROR;
	}

	angle = (sumangle / counter) * 180 / CV_PI;

	imgShowDebug(dstImg, "pointer", 0);

	LOG(INFO) << "指针共检测到 " << counter << " 条边。";
	LOG(INFO) << "pointer angle (未校正) = " << angle;


	return sg_OK;
}



