/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_analog.cpp
*
* 	@Brief	模拟指示器识别函数.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1.
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		Created.
*
*/ 


#include "sgtask_analog.h"


#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"
#include "../sgCore/sgcore_math.h"
#include"../sgCore/sgcore_safetyCheck.h"

#include "../sgFunction/sgfunc_feature.h"

#include <opencv2\opencv.hpp>
using namespace cv;


/**
*	@Method		Detect_analog
*
*	@Brief		模拟指示器识别入口.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg：	输入模拟指示器区域图像（经过ROI处理）
*
*				const unsigned int analogtype：	模拟指示器类型，三类
*											1.	类型一 : sg_analog_type_circles
*											2.	类型二 : sg_analog_type_lights
*											3.	类型三 : sg_analog_type_squarelights
*				
*				const unsigned int analognum：	区域内模拟指示器个数
*
*	@Para [OUT]	int * valueArr： 模拟指示器检测结果
*				检测结果为int数组，每个元素为检测结果，数组排序按照从上到下，从左到右原则。
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-16
*/
int Detect_analog(const Mat srcImg, const unsigned int analogtype, vector<int> & valueArr)
{
	LOG(INFO) << "函数：Detect_analog（模拟指示器接口）， 进入";


	int resp = sg_OK;

	// 1. 图像判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： Detect_analog" << "  图像为空,退出函数";
		resp = sg_ERROR;
		return resp;
	}


	// 2. 分流判断
	Mat resultImg;	// 预留作为返回图像
	if (sg_analog_type_circles == analogtype)			// 有圆无灯
	{
		resp = analog_circles_detect(srcImg, resultImg, valueArr);
		if (resp != sg_OK)
		{
			LOG(ERROR) << "函数： Detect_analog： " << "  circles类型检测出错";
			return resp;
		}
		
	}
	else if (sg_analog_type_twoPanels == analogtype)	// 两个方格
	{
		resp = analog_twopannels_detect(srcImg, resultImg, valueArr);
		if (resp != sg_OK)
		{
			LOG(ERROR) << "函数： Detect_analog： " << "  twoPanels类型检测出错";
			return resp;
		}
	}
	else if (sg_analog_type_onePanel == analogtype)		// 单个panel
	{
		resp = analog_onepanel_detect(srcImg, resultImg, valueArr);
		if (resp != sg_OK)
		{
			LOG(ERROR) << "函数： Detect_analog： " << "  onePanel类型检测出错";
			return resp;
		}
	}
	else if (sg_analog_type_lights == analogtype)		// 有圆有灯
	{
		resp = analog_lights_detect(srcImg, resultImg, valueArr);
		if (resp != sg_OK)
		{
			LOG(ERROR) << "函数： Detect_analog： " << "  lights类型检测出错";
			return resp;
		}
	}


	LOG(INFO) << "函数：Detect_analog（模拟指示器接口）， 退出";
	return sg_OK;
}

/**
*	@Method		thinImage
*
*	@Brief		图像细化函数
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	const Mat dst
*
*	@Return		无
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
Mat thinImage(const Mat & src, const int maxIterations)
{
	assert(src.type() == CV_8UC1);
	int width = src.cols;
	int height = src.rows;
	Mat dst;
	src.copyTo(dst);
	int count = 0; //记录迭代次数
	while (true)
	{
		count++;
		if (maxIterations != -1 && count > maxIterations) //限制次数并且迭代次数到达
			break;
		vector<uchar *> mFlag; //用于标记需要删除的点
							   //对点标记
		for (int i = 0; i < height;++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//如果满足四个条件，进行标记
				//  p9 p2 p3
				//  p8 p1 p4
				//  p7 p6 p5
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
					{
						//标记
						mFlag.push_back(p + j);
					}
				}
			}
		}
		//将标记的点删除
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}
		//直到没有点满足，算法结束
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//将mFlag清空
		}
		//对点标记
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//如果满足四个条件，进行标记
				//  p9 p2 p3
				//  p8 p1 p4
				//  p7 p6 p5
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);

				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
					{
						//标记
						mFlag.push_back(p + j);
					}
				}
			}
		}
		//将标记的点删除
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		//直到没有点满足，算法结束
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//将mFlag清空
		}
	}
	return dst;
}

/**
*	@Method		getDistance
*
*	@Brief		计算像素点距离
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	cvPoint point0,cvPoint pointA
*
*	@Para [OUT]	double distance
*
*	@Return		无
*
*  	@Note		计算两个凸包间距离
*
*	@Create		2018-05-26
*/
double getDistance(CvPoint pointO, CvPoint pointA)
{
	double distance;
	distance = powf((pointO.x - pointA.x), 2) + powf((pointO.y - pointA.y), 2);
	distance = sqrtf(distance);

	return distance;
}

/**
*	@Method		detectColorWithPoints
*
*	@Brief		This is a brief description.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*				Vec3b color
*
*				const int red
*
*				const int green
*
*				const int blue
*
*				const int minimum
*
*	@Para [OUT]	Mat & result
*
*				vector<vector<int>> & Points
*
*				int & figures
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int detectColorWithPoints(const Mat srcImg, Vec3b color, const int red, const int green, const int blue, const int minimum, Mat & result, vector<Point> & Points, int & figures)//核心处理：遍历像素点，检测是否匹配目标颜色
{
	figures = 0;
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			int pb = srcImg.at<Vec3b>(i, j)[0];
			int pg = srcImg.at<Vec3b>(i, j)[1];
			int pr = srcImg.at<Vec3b>(i, j)[2];
			int dis0 = abs(pb - color[0]);
			int dis1 = abs(pg - color[1]);
			int dis2 = abs(pr - color[2]);
			if (dis0 <= red && dis1 <= green && dis2 <= blue && sqrt(dis0 ^ 2 + dis1 ^ 2 + dis2 ^ 2) <= minimum)
			{
				result.at<Vec3b>(i, j)[0] = 255;//M中符合颜色检测条件的像素点设为白色
				result.at<Vec3b>(i, j)[1] = 255;
				result.at<Vec3b>(i, j)[2] = 255;

				Points[figures].x = i;//存放符合颜色检测条件的像素点坐标
				Points[figures].y = j;
				figures++;//统计符合颜色检测条件的像素点个数
			}
			else
			{
				result.at<Vec3b>(i, j)[0] = 0;//M中不符合颜色检测条件的像素点设为黑色
				result.at<Vec3b>(i, j)[1] = 0;
				result.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	if (figures == 0)
	{
		return sg_ERROR;
	}
	else
	{
		return sg_OK;
	}

}

/**
*	@Method		detectLuminance
*
*	@Brief		This is a brief description.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*				const int L1
*
*				const int L2
*
*	@Para [OUT]	Mat & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int detectLuminance(const Mat srcImg, const int L1, const int L2, Mat &result)
{
	int figures = 0;
	for (int i = 0;i < srcImg.rows;i++)
	{
		for (int j = 0;j < srcImg.cols;j++)
		{
			int Luminance = srcImg.at<Vec3b>(i, j)[2];
			if (Luminance >= L1 && Luminance <= L2)
			{
				figures++;
				result.at<Vec3b>(i, j)[0] = 255;//M中符合L分量检测条件的像素点设为白色
				result.at<Vec3b>(i, j)[1] = 255;
				result.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	if (figures == 0)
	{
		return sg_ERROR;
	}
	else
	{
		return sg_OK;
	}
}

/**
*	@Method		drawDetectLines
*
*	@Brief		画直线函数
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	Mat& image, const vector<Vec4i>& lines, Scalar & color
*
*	@Para [OUT]	无
*
*	@Return		无
*
*  	@Note		调试用
*
*	@Create		2018-05-26
*/
void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color)
{
	// 将检测到的直线在图上画出来  
	vector<Vec4i>::const_iterator it = lines.begin();
	while (it != lines.end())
	{
		Point pt1((*it)[0], (*it)[1]);
		Point pt2((*it)[2], (*it)[3]);
		line(image, pt1, pt2, color, 2); //  线条宽度设置为2  
		++it;
	}
}

/**
*	@Method		analog_circles_detect
*
*	@Brief		模拟指示器类型circles的入口.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	outArgName output argument description.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int analog_circles_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	//1.对srcImg作颜色检测（analog黑色边框） -> black1
	int r1 = 35;
	int g1 = 35;
	int b1 = 35;
	Vec3b target1;
	target1[0] = b1;
	target1[1] = g1;
	target1[2] = r1;

	Mat black1(srcImg.rows, srcImg.cols, CV_8UC3, Scalar(0, 0, 0));
	int figures1;
	vector<Point> Points1(50000);
	resp = detectColorWithPoints(srcImg, target1, 60, 60, 60, 100, black1, Points1, figures1);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "srcImg颜色检测错误";
		return resp;
	}

	//2.对black1作形态学操作 -> dilation
	Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat dilation;
	morphologyEx(black1, dilation, MORPH_CLOSE, element1);//对检测结果进行开、闭操作
	morphologyEx(dilation, dilation, MORPH_OPEN, element2);//剔除一些干扰的像素点

	//3.dilation 预处理 -> grayImg, blurImg, binary, canny, thinning
	Mat grayImg;//灰度图
	cvtColor(dilation, grayImg, CV_BGR2GRAY);
	Mat blurImg;//高斯滤波后的灰度图
	GaussianBlur(grayImg, blurImg, Size(9, 9), 2, 2);
	Mat binary;//二值图
	threshold(blurImg, binary, 128, 1, THRESH_BINARY);
	Mat canny;//边缘检测
	Canny(blurImg, canny, 25, 50);
	Mat thinning = thinImage(binary);//图像细化
	thinning = thinning * 255;

	//4.查找thinning中所有轮廓 -> contours1
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(thinning, contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//5.查找contours1中size最大的轮廓 -> contours2
	vector<Point> contours2(1);
	int maxsize1 = contours1[0].size();
	for (int i = 0;i < contours1.size();i++)
	{
		if (contours1[i].size() >= maxsize1)
		{
			maxsize1 = contours1[i].size();
			contours2 = contours1[i];
		}
	}

	//4.对contours2作多边形逼近 -> contours2_poly
	vector<Point> contours2_poly(contours2.size());
	approxPolyDP(Mat(contours2), contours2_poly, 5, true);

	//查找contours2_poly中所有凸包的纵坐标的上下限 -> max_y, min_y
	int min_y = contours2_poly[0].y;
	int max_y = contours2_poly[0].y;
	int middle_x;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].y <= min_y)
		{
			min_y = contours2_poly[i].y;
		}
		if (contours2_poly[i].y >= max_y)
		{
			max_y = contours2_poly[i].y;
			middle_x = contours2_poly[i].x;
		}
	}
	int min_x = contours2_poly[0].x;
	int max_x = contours2_poly[0].x;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].x <= min_x)
		{
			min_x = contours2_poly[i].x;
		}
		if (contours2_poly[i].x >= max_x)
		{
			max_x = contours2_poly[i].x;
		}
	}

	//contours2_poly 复制 -> apex1
	vector<Point> apex1;
	apex1.assign(contours2_poly.begin(), contours2_poly.end());

	//根据max_y和min_y确定plate的相对位置，删除contours2_poly中不在该位置内的凸包 ->apex1
	vector<Point>::iterator it1 = apex1.begin();
	for (int i = 0;i < contours2_poly.size() && it1 != apex1.end();i++)
	{
		if ((contours2_poly[i].y - min_y) >(max_y - min_y) / 2.5 || (contours2_poly[i].y - min_y) < (max_y - min_y) / 10)
		{
			it1 = apex1.erase(it1);
		}
		else
		{
			++it1;
		}
	}

	//删除apex1中坐标接近或重合的点 -> apex2
	double distance;
	vector<Point> apex2;
	apex2.assign(apex1.begin(), apex1.end());
	vector<Point>::iterator it2 = apex2.begin();
	vector<Point> apex3;
	apex3.assign(apex1.begin(), apex1.end());
	vector<Point>::iterator it3 = apex3.begin();
	for (int i = 0;i < apex1.size() - 1;i++)
	{
		for (int j = 0;j < apex1.size();j++)
		{
			if (j != i)
			{
				distance = getDistance(apex1[i], apex1[j]);
				if (distance <= 2)
				{
					it2 = apex2.erase(it2);
					break;
				}
			}
		}
		if (*it3 == *it2)
		{
			++it2;
		}
		++it3;
	}

	//对apex2作多边形逼近找凸包 -> apex2_poly
	vector<Point> apex2_poly(apex2.size());
	approxPolyDP(Mat(apex2), apex2_poly, 5, true);

	////从srcImg中截取apex2_poly对应的表盘 -> panel
	//Rect rectPanel = boundingRect(apex2_poly);
	//Mat panel = Mat::zeros(rectPanel.size(), CV_8UC3);
	//srcImg(rectPanel).copyTo(panel);
	//imshow("panel", panel);

	int apex2_min_y = apex2_poly[0].y;
	int apex2_max_y = apex2_poly[0].y;
	for (int i = 0;i < apex2_poly.size();i++)
	{
		if (apex2_poly[i].y <= apex2_min_y)
		{
			apex2_min_y = apex2_poly[i].y;
		}
		if (apex2_poly[i].y >= apex2_max_y)
		{
			apex2_max_y = apex2_poly[i].y;
		}
	}

	int apex2_min_x = apex2_poly[0].x;
	int apex2_max_x = apex2_poly[0].x;
	for (int i = 0;i < apex2_poly.size();i++)
	{
		if (apex2_poly[i].x <= apex2_min_x)
		{
			apex2_min_x = apex2_poly[i].x;
		}
		if (apex2_poly[i].x >= apex2_max_x)
		{
			apex2_max_x = apex2_poly[i].x;
		}
	}

	int panel_width = (max_y - min_y) / 11 * 1.4;
	int panel_height = (max_y - min_y) / 11 * 2.6;
	int panel_x = apex2_max_x - panel_height / 2;
	int panel_y = apex2_min_y;
	//if (panel_x + panel_width > srcImg.cols || panel_y + panel_height > srcImg.rows)
	//{
	//	return sg_ERROR;
	//}
	resp = checkRectInside(srcImg, Rect(panel_x, panel_y, panel_width, panel_height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "panel ROI取值错误";
		return resp;
	}
	Mat panel;
	panel = srcImg(Rect(panel_x, panel_y, panel_width, panel_height));

	//plate上半部分为plate_up，下半部分为plate_down
	Mat panel_up = panel(Rect(0, 0, panel.cols, panel.rows / 2));
	Mat panel_down = panel(Rect(0, panel.rows / 2, panel.cols, panel.rows / 2));

	//对panelup_canny作预处理 -> panelup_grayImg, panelup_blurImg, panelup_canny
	Mat panelup_grayImg;
	cvtColor(panel_up, panelup_grayImg, CV_BGR2GRAY);
	Mat panelup_blurImg;
	GaussianBlur(panelup_grayImg, panelup_blurImg, Size(3, 3), 2, 2);
	Mat panelup_canny;
	Canny(panelup_blurImg, panelup_canny, 25, 50);

	//查找panelup_canny中所有轮廓 -> contours3
	vector<vector<Point>> contours3;
	vector<Vec4i> hierarchy3;
	findContours(panelup_canny, contours3, hierarchy3, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//查找contours3中size最大的轮廓 -> contours4
	vector<Point> contours4(1);
	int maxsize3 = contours3[0].size();
	for (int i = 0;i < contours3.size();i++)
	{
		if (contours3[i].size() >= maxsize3)
		{
			maxsize3 = contours3[i].size();
			contours4 = contours3[i];
		}
	}

	//对contours4作多边形逼近 ->contours4_poly
	vector<Point> contours4_poly(contours4.size());
	approxPolyDP(Mat(contours4), contours4_poly, 5, true);
	if (contours4_poly.size() == 0)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "inner边缘检测错误";
		return sg_ERROR;
	}

	//从plate_up上截取contours4_poly对应的内部表盘 ->inner
	Rect rectInner = boundingRect(contours4_poly);
	Mat inner = Mat::zeros(rectInner.size(), CV_8UC3);
	panel_up(rectInner).copyTo(inner);

	//根据inner长宽确定目标区域位置 -> middle
	resp = checkRectInside(inner, Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circls_detect, " << "middle1 ROI取值错误";
		return resp;
	}
	Mat middle1 = inner(Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));

	//19.对middle1作颜色检测，统计符合条件的像素点数 -> figures2
	int r2 = 0;
	int g2 = 0;
	int b2 = 0;
	Vec3b target2;
	target2[0] = b2;
	target2[1] = g2;
	target2[2] = r2;

	int figures2;
	vector<Point> Points2(1000);
	Mat black2(middle1.rows, middle1.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(middle1, target2, 120, 100, 100, 180, black2, Points2, figures2);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "middle1颜色检测错误";
		return resp;
	}

	//20.计算figures在middle总像素数s中所占比例 -> ratio
	int s = middle1.cols*middle1.rows;
	float ratio = figures2*1.0 / s;

	//21.判断ratio大小，阈值设0.3，ratio >= 0.3连接，反之断开
	if (ratio >= 0.2)
	{
		valueArr[0] = sg_analog_Connect;
	}
	else
	{
		valueArr[0] = sg_analog_DisConnect;
	}

	////对paneldown_canny作预处理 -> paneldown_grayImg, paneldown_blurImg, paneldown_canny
	//Mat paneldown_grayImg;
	//cvtColor(panel_down, paneldown_grayImg, CV_BGR2GRAY);
	//Mat paneldown_blurImg;
	//GaussianBlur(paneldown_grayImg, paneldown_blurImg, Size(3, 3), 2, 2);
	//Mat paneldown_canny;
	//Canny(paneldown_blurImg, paneldown_canny, 25, 50);
	//imshow("canny", paneldown_canny);
	//waitKey(0);

	////查找panelup_canny中所有轮廓 -> contours3
	//vector<vector<Point>> contours5;
	//vector<Vec4i> hierarchy5;
	//findContours(paneldown_canny, contours5, hierarchy5, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	////查找contours3中size最大的轮廓 -> contours4
	//vector<Point> contours6(1);
	//int maxsize5 = contours5[0].size();
	//for (int i = 0;i < contours5.size();i++)
	//{
	//	if (contours5[i].size() >= maxsize5)
	//	{
	//		maxsize5 = contours5[i].size();
	//		contours6 = contours5[i];
	//	}
	//}

	////对contours4作多边形逼近 ->contours4_poly
	//vector<Point> contours6_poly(contours6.size());
	//approxPolyDP(Mat(contours6), contours6_poly, 5, true);

	////从plate_up上截取contours4_poly对应的内部表盘 ->inner
	//Rect rectInner2 = boundingRect(contours6_poly);
	//Mat inner2 = Mat::zeros(rectInner2.size(), CV_8UC3);
	//panel_down(rectInner2).copyTo(inner2);
	//imshow("inner2", inner2);
	//waitKey(0);

	////22.根据panel_down长宽确定检测区域的位置 -> middle2
	//Mat middle2 = inner2(Rect(inner2.cols / 6, inner2.rows / 6, inner2.cols / 1.4, inner2.rows / 1.4));
	//imshow("middle2", middle2);
	//waitKey(0);

	resp = checkRectInside(panel_down, Rect(panel_down.cols / 3.5, panel_down.rows / 3, panel_down.cols / 2, panel_down.rows / 2));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "middle2 ROI取值错误";
		return resp;
	}
	Mat middle2 = panel_down(Rect(panel_down.cols / 3.5, panel_down.rows / 3, panel_down.cols / 2, panel_down.rows / 2));

	//23.middle2 预处理 -> gray, blurImg, canny
	Mat middle2_grayImg;
	cvtColor(middle2, middle2_grayImg, CV_BGR2GRAY);
	Mat middle2_blurImg;
	GaussianBlur(middle2_grayImg, middle2_blurImg, Size(9, 9), 2, 2);
	Mat middle2_canny;
	Canny(middle2_blurImg, middle2_canny, 25, 50);

	//24.对canny作直线检测 -> lines
	vector<Vec4i> lines1;// 霍夫变换检测直线，最小投票为60，线条不短于10，间隙不小于50  
	double rho = 1;	//以像素为单位的距离精度,即直线搜索时的步进尺寸的单位半径			
	double theta = CV_PI / 180;	//以弧度为单位的角度精度，即直线搜索时的步进尺寸的单位角度
	int threshold = 15;	//累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值，大于阈值的线段才可以被检测到并返回到结果中
	double minLineLength = 10; //默认值为0，标示最低线段的长度，比这个设定参数短的线段就不能被显现出来			
	double maxLineGap = 20;	//默认值为0，允许将统一行点与点之间连接起来的最大距离。
	HoughLinesP(middle2_canny, lines1, rho, theta, threshold, minLineLength, maxLineGap);
	if (lines1.size() == 0)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "panel_down直线检测错误";
		return sg_ERROR;
	}


	//25.统计lines中直线的角度 -> Angle
	vector<Vec4i> lines1_max;
	int x1 = lines1[0][2] - lines1[0][0];
	int y1 = lines1[0][3] - lines1[0][1];
	int maxlength1 = sqrt(x1*x1 + y1*y1);
	int maxnumber1 = 0;
	for (int i = 0;i < lines1.size();i++)
	{
		int x = lines1[i][2] - lines1[i][0];
		int y = lines1[i][2] - lines1[i][0];
		int length = sqrt(x*x + y*y);
		if (length >= maxlength1)
		{
			maxlength1 = length;
			maxnumber1 = i;
		}
	}
	lines1_max.push_back(lines1[maxnumber1]);

	float Angle1 = 0.0;
	Vec4i l1 = lines1_max[0];
	if (l1[2] == l1[0])
	{
		Angle1 = 90.0;
	}
	else
	{
		Angle1 = abs(atan((l1[3] - l1[1])*1.0 / (l1[2] - l1[0])) / M_PI * 180);
	}

	//26.根据Angle大小判断paneldown状态
	int angle = cvRound(Angle1);
	if (angle <= 91 && angle >= 85)//纵向
	{
		valueArr[1] = sg_analog_Connect;
	}
	else
	{
		valueArr[1] = sg_analog_DisConnect;
	}

	//27.contours2_poly 复制 -> apex4
	vector<Point> apex4;
	apex4.assign(contours2_poly.begin(), contours2_poly.end());
	vector<Point>::iterator it4 = apex4.begin();

	//28.删除contours2_poly中不在circle位置内的点 -> apex4
	for (int i = 0;i < contours2_poly.size() && it4 != apex4.end();i++)
	{
		if ((contours2_poly[i].y - min_y) >(max_y - min_y) / 16 * 10.5 || (contours2_poly[i].y - min_y) < (max_y - min_y) / 16 * 6 || (contours2_poly[i].x - min_x) > (max_x - min_x) / 2)
		{
			it4 = apex4.erase(it4);
		}
		else
		{
			++it4;
		}
	}

	//29.从srcImg中截取圆形表盘区域 -> circle_area
	Rect rectCircle = boundingRect(apex4);
	Mat circle_area = Mat::zeros(rectCircle.size(), CV_8UC3);
	srcImg(rectCircle).copyTo(circle_area);

	//30.从circle_area中进一步截取圆形表盘 -> circle
	int circle_x = 0;
	int circle_y = rectCircle.height / 2;
	int circle_width = rectCircle.width;
	int circle_height = rectCircle.height / 2;
	resp = checkRectInside(circle_area, Rect(circle_x, circle_y, circle_width, circle_height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "circle ROI取值错误";
		return resp;
	}
	Mat circle;
	circle = circle_area(Rect(circle_x, circle_y, circle_width, circle_height));
	resize(circle, circle, Size(circle.cols * 5, circle.rows * 5));

	//31.circle 预处理 -> circle_gray, circle_blur, circlr_canny
	Mat circle_gray;//灰度化
	cvtColor(circle, circle_gray, CV_BGR2GRAY);
	Mat circle_blur;//高斯滤波
	GaussianBlur(circle_gray, circle_blur, Size(9, 9), 2, 2);
	Mat circle_canny;//边缘检测
	Canny(circle_blur, circle_canny, 15, 30);

	//32.对circle_canny作直线检测 -> circle_lines
	vector<Vec4i> circle_lines;// 霍夫变换检测直线，最小投票为30，线条不短于50，间隙不小于50  
	double rho1 = 1;	//以像素为单位的距离精度,即直线搜索时的步进尺寸的单位半径			
	double theta1 = CV_PI / 180;	//以弧度为单位的角度精度，即直线搜索时的步进尺寸的单位角度
	int threshold1 = 30;	//累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值，大于阈值的线段才可以被检测到并返回到结果中
	double minLineLength1 = 50; //默认值为0，标示最低线段的长度，比这个设定参数短的线段就不能被显现出来			
	double maxLineGap1 = 50;	//默认值为0，允许将统一行点与点之间连接起来的最大距离。
	HoughLinesP(circle_canny, circle_lines, rho1, theta1, threshold1, minLineLength1, maxLineGap1);
	if (circle_lines.size() == 0)
	{
		LOG(ERROR) << "函数：analog_circles_detect, " << "circle直线检测错误";
		return sg_ERROR;
	}
	
	//33.查找circle_lines中length最长的线段 -> circle_lines_max
	vector<Vec4i> circle_lines_max;
	int x2 = circle_lines[0][2] - circle_lines[0][0];
	int y2 = circle_lines[0][3] - circle_lines[0][1];
	int maxlength2 = sqrt(x2*x2 + y2*y2);
	int maxnumber2 = 0;
	for (int i = 0;i < circle_lines.size();i++)
	{
		int x = circle_lines[i][2] - circle_lines[i][0];
		int y = circle_lines[i][2] - circle_lines[i][0];
		int length = sqrt(x*x + y*y);
		if (length >= maxlength2)
		{
			maxlength2 = length;
			maxnumber2 = i;
		}
	}
	circle_lines_max.push_back(circle_lines[maxnumber2]);

	//34.统计circle_lines_max中直线的角度 -> circle_Angle
	float circle_Angle = 0.0;
	Vec4i l2 = circle_lines_max[0];
	if (l2[2] == l2[0])
	{
		circle_Angle = 90.0;
	}
	else
	{
		circle_Angle = abs(atan((l2[3] - l2[1])*1.0 / (l2[2] - l2[0])) / M_PI * 180);
	}

	//35.根据circle_Angle大小判断circle状态
	int circle_angle = cvRound(circle_Angle);
	if (circle_angle <= 91 && circle_angle >= 85)//纵向
	{
		valueArr[2] = sg_analog_Connect;
	}
	else
	{
		valueArr[2] = sg_analog_DisConnect;
	}
	return sg_OK;
}

/**
*	@Method		analog_twoPanels_detect
*
*	@Brief		模拟指示器类型twoPanels的入口.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	outArgName output argument description.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int analog_twopannels_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		return	sg_ERROR;
	}
	
	//1.对srcImg作颜色检测（analog黑色边框） -> black1
	int r1 = 35;
	int g1 = 35;
	int b1 = 35;
	Vec3b target1;
	target1[0] = b1;
	target1[1] = g1;
	target1[2] = r1;

	Mat black1(srcImg.rows, srcImg.cols, CV_8UC3, Scalar(0, 0, 0));
	int figures1;
	vector<Point> Points1(50000);
	resp = detectColorWithPoints(srcImg, target1, 60, 60, 60, 100, black1, Points1, figures1);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "srcImg颜色检测错误";
		return resp;
	}

	//2.对black1作形态学操作 -> dilation
	Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat dilation;
	morphologyEx(black1, dilation, MORPH_CLOSE, element1);//对检测结果进行开、闭操作
	morphologyEx(dilation, dilation, MORPH_OPEN, element2);//剔除一些干扰的像素点

	//3.dilation 预处理 -> gray, blurImg, binary, canny, thinning
	Mat grayImg;//灰度图
	cvtColor(dilation, grayImg, CV_BGR2GRAY);
	Mat blurImg;//高斯滤波后的灰度图
	GaussianBlur(grayImg, blurImg, Size(9, 9), 2, 2);
	Mat binary;//二值图
	threshold(grayImg, binary, 128, 1, THRESH_BINARY);
	Mat canny;//边缘检测
	Canny(blurImg, canny, 25, 50);
	Mat thinning = thinImage(binary);//图像细化
	thinning = thinning * 255;

	//4.查找thinning中所有轮廓 -> contours1
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(thinning, contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//5.查找contours1中size最大的轮廓 -> contours2
	vector<Point> contours2(1);
	int maxsize1 = contours1[0].size();
	for (int i = 0;i < contours1.size();i++)
	{
		if (contours1[i].size() >= maxsize1)
		{
			maxsize1 = contours1[i].size();
			contours2 = contours1[i];
		}
	}

	//6.对contours2作多边形逼近 -> contours2_poly
	vector<Point> contours2_poly(contours2.size());
	approxPolyDP(Mat(contours2), contours2_poly, 5, true);

	//7.查找contours2_poly中所有凸包的纵坐标的上下限，横坐标的上下限 -> max_y, min_y, max_x, min_x
	int min_y = contours2_poly[0].y;
	int max_y = contours2_poly[0].y;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].y <= min_y)
		{
			min_y = contours2_poly[i].y;
		}
		if (contours2_poly[i].y >= max_y)
		{
			max_y = contours2_poly[i].y;
		}
	}

	int min_x = contours2_poly[0].x;
	int max_x = contours2_poly[0].x;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].x <= min_x)
		{
			min_x = contours2_poly[i].x;
		}
		if (contours2_poly[i].x >= max_x)
		{
			max_x = contours2_poly[i].x;
		}
	}

	//8.contours2_poly 复制 -> apex1
	vector<Point> apex1;
	apex1.assign(contours2_poly.begin(), contours2_poly.end());

	//9.根据max_y和min_y确定plate的相对位置，删除contours2_poly中不在该位置内的凸包 -> apex1
	vector<Point>::iterator it1 = apex1.begin();
	for (int i = 0;i < contours2_poly.size() && it1 != apex1.end();i++)
	{
		if ((contours2_poly[i].y - min_y) >(max_y - min_y) / 2.5 || (contours2_poly[i].y - min_y) < (max_y - min_y) / 10)
		{
			it1 = apex1.erase(it1);
		}
		else
		{
			++it1;
		}
	}

	//10.删除apex1中坐标接近或重合的点 -> apex2
	double distance;
	vector<Point> apex2;
	apex2.assign(apex1.begin(), apex1.end());
	vector<Point>::iterator it2 = apex2.begin();
	vector<Point> apex3;
	apex3.assign(apex1.begin(), apex1.end());
	vector<Point>::iterator it3 = apex3.begin();
	for (int i = 0;i < apex1.size() - 1;i++)
	{
		for (int j = 0;j < apex1.size();j++)
		{
			if (j != i)
			{
				distance = getDistance(apex1[i], apex1[j]);
				if (distance <= 2)
				{
					it2 = apex2.erase(it2);
					break;

				}
			}
		}
		if (*it3 == *it2)
		{
			++it2;
		}
		++it3;
	}

	//11.对apex2作多边形逼近找凸包 -> apex2_poly
	vector<Point> apex2_poly(apex2.size());
	approxPolyDP(Mat(apex2), apex2_poly, 5, true);

	//12.从srcImg中截取apex2_poly对应的表盘 -> panel
	Rect rectPanel = boundingRect(apex2_poly);
	Mat panel = Mat::zeros(rectPanel.size(), CV_8UC3);
	srcImg(rectPanel).copyTo(panel);

	//13.panel上半部分为panel_up，下半部分为panel_down
	Mat panel_up = panel(Rect(0, 0, panel.cols, panel.rows / 2));
	Mat panel_down = panel(Rect(0, panel.rows / 2, panel.cols, panel.rows / 2));

	//14.对panelup_canny作预处理 -> panelup_grayImg, panelup_blurImg, panelup_canny
	Mat panelup_grayImg;
	cvtColor(panel_up, panelup_grayImg, CV_BGR2GRAY);
	Mat panelup_blurImg;
	GaussianBlur(panelup_grayImg, panelup_blurImg, Size(3, 3), 2, 2);
	Mat panelup_canny;
	Canny(panelup_blurImg, panelup_canny, 25, 50);

	//15.查找panelup_canny中所有轮廓 -> contours3
	vector<vector<Point>> contours3;
	vector<Vec4i> hierarchy3;
	findContours(panelup_canny, contours3, hierarchy3, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//16.查找contours3中size最大的轮廓 -> contours4
	vector<Point> contours4(1);
	int maxsize3 = contours3[0].size();
	for (int i = 0;i < contours3.size();i++)
	{
		if (contours3[i].size() >= maxsize3)
		{
			maxsize3 = contours3[i].size();
			contours4 = contours3[i];
		}
	}

	//17.对contours4作多边形逼近 -> contours4_poly
	vector<Point> contours4_poly(contours4.size());
	approxPolyDP(Mat(contours4), contours4_poly, 5, true);
	if (contours4_poly.size() == 0)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "inner轮廓检测错误";
		return sg_ERROR;
	}

	//18.从panel_up上截取contours4_poly对应的内部表盘 -> inner
	Rect rectInner = boundingRect(contours4_poly);
	Mat inner = Mat::zeros(rectInner.size(), CV_8UC3);
	panel_up(rectInner).copyTo(inner);

	//19.根据inner长宽确定目标区域位置 -> middle1
	resp = checkRectInside(inner, Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "middle1 ROI取值错误";
		return resp;
	}
	Mat middle1 = inner(Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));

	//20.对middle1作颜色检测，统计符合条件的像素点数 -> figures2
	int r2 = 0;
	int g2 = 0;
	int b2 = 0;
	Vec3b target2;
	target2[0] = b2;
	target2[1] = g2;
	target2[2] = r2;

	int figures2;
	vector<Point> Points2(1000);
	Mat black2(middle1.rows, middle1.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(middle1, target2, 120, 100, 100, 180, black2, Points2, figures2);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "middle1颜色检测错误";
		return resp;
	}

	//21.计算figures2在middle1总像素数s中所占比例 -> ratio
	int s = middle1.cols*middle1.rows;
	float ratio = figures2*1.0 / s;

	//22.判断ratio大小，阈值设0.3，ratio >= 0.3连接，反之断开
	if (ratio >= 0.2)
	{
		valueArr[0] = sg_analog_Connect;
	}
	else
	{
		valueArr[0] = sg_analog_DisConnect;
	}

	//23.根据panel_down长宽确定检测区域的位置 -> middle2
	resp = checkRectInside(panel_down, Rect(panel_down.cols / 3.5, panel_down.rows / 3, panel_down.cols / 2.2, panel_down.rows / 2.2));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "middle2 ROI取值错误";
		return resp;
	}
	Mat middle2 = panel_down(Rect(panel_down.cols / 3.5, panel_down.rows / 3, panel_down.cols / 2.2, panel_down.rows / 2.2));

	//24.middle2 预处理 -> middle2_grayImg, middle2_blurImg, middle2_canny
	Mat middle2_grayImg;
	cvtColor(middle2, middle2_grayImg, CV_BGR2GRAY);
	Mat middle2_blurImg;
	GaussianBlur(middle2_grayImg, middle2_blurImg, Size(9, 9), 2, 2);
	Mat middle2_canny;
	Canny(middle2_blurImg, middle2_canny, 25, 50);

	//25.对middle2_canny作直线检测 -> lines
	vector<Vec4i> lines;// 霍夫变换检测直线，最小投票为60，线条不短于10，间隙不小于50  
	double rho = 1;	//以像素为单位的距离精度,即直线搜索时的步进尺寸的单位半径			
	double theta = CV_PI / 180;	//以弧度为单位的角度精度，即直线搜索时的步进尺寸的单位角度
	int threshold = 15;	//累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值，大于阈值的线段才可以被检测到并返回到结果中
	double minLineLength = 10; //默认值为0，标示最低线段的长度，比这个设定参数短的线段就不能被显现出来			
	double maxLineGap = 20;	//默认值为0，允许将统一行点与点之间连接起来的最大距离。
	HoughLinesP(middle2_canny, lines, rho, theta, threshold, minLineLength, maxLineGap);
	if (lines.size() == 0)
	{
		LOG(ERROR) << "函数：analog_twopanels_detect, " << "panel_down直线检测错误";
		return sg_ERROR;
	}

	//26.找lines1中length最长的直线 -> lines1_max
	vector<Vec4i> lines_max;
	int x1 = lines[0][2] - lines[0][0];
	int y1 = lines[0][3] - lines[0][1];
	int maxlength1 = sqrt(x1*x1 + y1*y1);
	int maxnumber1 = 0;
	for (int i = 0;i < lines.size();i++)
	{
		int x = lines[i][2] - lines[i][0];
		int y = lines[i][2] - lines[i][0];
		int length = sqrt(x*x + y*y);
		if (length >= maxlength1)
		{
			maxlength1 = length;
			maxnumber1 = i;
		}
	}
	lines_max.push_back(lines[maxnumber1]);

	//27.统计lines1_max中直线的角度 -> Angle1
	float Angle = 0.0;
	Vec4i l1 = lines_max[0];
	if (l1[2] == l1[0])
	{
		Angle = 90.0;
	}
	else
	{
		Angle = abs(atan((l1[3] - l1[1])*1.0 / (l1[2] - l1[0])) / M_PI * 180);
	}

	//28.根据Angle大小判断paneldown状态
	int angle = cvRound(Angle);
	if (angle <= 91 && angle >= 85)//纵向 连接
	{
		valueArr[1] = sg_analog_Connect;
	}
	else
	{
		valueArr[1] = sg_analog_DisConnect;
	}
	return sg_OK;
}

/**
*	@Method		analog_onePanel_detect
*
*	@Brief		模拟指示器类型onePanel的入口.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	outArgName output argument description.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int analog_onepanel_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr)
{
	int resp = sg_OK;
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	//1.对srcImg作颜色检测（analog黑色边框） -> black1
	int r1 = 35;
	int g1 = 35;
	int b1 = 35;
	Vec3b target1;
	target1[0] = b1;
	target1[1] = g1;
	target1[2] = r1;

	Mat black1(srcImg.rows, srcImg.cols, CV_8UC3, Scalar(0, 0, 0));
	int figures1;
	vector<Point> Points1(50000);
	resp = detectColorWithPoints(srcImg, target1, 60, 60, 60, 100, black1, Points1, figures1);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_onepanel_detect, " << "srcImg颜色检测错误";
		return resp;
	}
	
	//2.对black1作形态学操作 -> dilation
	Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat dilation;
	morphologyEx(black1, dilation, MORPH_CLOSE, element1);//对检测结果进行开、闭操作
	morphologyEx(dilation, dilation, MORPH_OPEN, element2);//剔除一些干扰的像素点

	//3.dilation 预处理 -> gray, blurImg, binary, canny, thinning
	Mat grayImg;//灰度图
	cvtColor(dilation, grayImg, CV_BGR2GRAY);
	Mat blurImg;//高斯滤波后的灰度图
	GaussianBlur(grayImg, blurImg, Size(9, 9), 2, 2);
	Mat binary;//二值图
	threshold(grayImg, binary, 128, 1, THRESH_BINARY);
	Mat canny;//边缘检测
	Canny(blurImg, canny, 25, 50);
	Mat thinning = thinImage(binary);//图像细化
	thinning = thinning * 255;

	//4.查找thinning中所有轮廓 -> contours1
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(thinning, contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//5.查找contours1中size最大的轮廓 -> contours2
	vector<Point> contours2(1);
	int maxsize1 = contours1[0].size();
	for (int i = 0;i < contours1.size();i++)
	{
		if (contours1[i].size() >= maxsize1)
		{
			maxsize1 = contours1[i].size();
			contours2 = contours1[i];
		}
	}

	//4.对contours2作多边形逼近 -> contours2_poly
	vector<Point> contours2_poly(contours2.size());
	approxPolyDP(Mat(contours2), contours2_poly, 5, true);

	//查找contours2_poly中所有凸包的纵坐标的上下限 -> max_y, min_y
	int min_y = contours2_poly[0].y;
	int max_y = contours2_poly[0].y;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].y <= min_y)
		{
			min_y = contours2_poly[i].y;
		}
		if (contours2_poly[i].y >= max_y)
		{
			max_y = contours2_poly[i].y;
		}
	}

	int min_x = contours2_poly[0].x;
	int max_x = contours2_poly[0].x;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].x <= min_x)
		{
			min_x = contours2_poly[i].x;
		}
		if (contours2_poly[i].x >= max_x)
		{
			max_x = contours2_poly[i].x;
		}
	}

	//contours2_poly 复制 -> apex1
	vector<Point> apex1;
	apex1.assign(contours2_poly.begin(), contours2_poly.end());

	//根据max_y和min_y确定plate的相对位置，删除contours2_poly中不在该位置内的凸包 ->apex1
	vector<Point>::iterator it1 = apex1.begin();
	for (int i = 0;i < contours2_poly.size() && it1 != apex1.end();i++)
	{
		if ((contours2_poly[i].y - min_y) >(max_y - min_y) / 8 * 3.5 || (contours2_poly[i].y - min_y) < (max_y - min_y) / 8 * 1.8 /*|| (contours2_poly[i].x - min_x) < (max_x - min_x) / 4 * 2.5*/)
		{
			it1 = apex1.erase(it1);
		}
		else
		{
			++it1;
		}
	}

	//查找apex1中所有凸包的纵坐标的上下限，横坐标的上下限 -> apex1_max_y, apex1_min_y, apex1_max_x, apex1_min_x
	int apex1_min_y = apex1[0].y;
	int apex1_max_y = apex1[0].y;
	for (int i = 0;i < apex1.size();i++)
	{
		if (apex1[i].y <= apex1_min_y)
		{
			apex1_min_y = apex1[i].y;
		}
		if (apex1[i].y >= apex1_max_y)
		{
			apex1_max_y = apex1[i].y;
		}
	}

	int apex1_min_x = apex1[0].x;
	int apex1_max_x = apex1[0].x;
	for (int i = 0;i < apex1.size();i++)
	{
		if (apex1[i].x <= apex1_min_x)
		{
			apex1_min_x = apex1[i].x;
		}
		if (apex1[i].x >= apex1_max_x)
		{
			apex1_max_x = apex1[i].x;
		}
	}

	int panelup_width = (max_y - min_y) / 8;
	int panelup_height = (max_y - min_y) / 8;
	int panelup_x = apex1_max_x - panelup_width;
	int panelup_y = apex1_min_y;
	resp = checkRectInside(srcImg, Rect(panelup_x, panelup_y, panelup_width, panelup_height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_onepanel_detect, " << "panel_up ROI取值错误";
		return resp;
	}
	Mat panel_up;
	panel_up = srcImg(Rect(panelup_x, panelup_y, panelup_width, panelup_height));

	//对panelup_canny作预处理 -> panelup_grayImg, panelup_blurImg, panelup_canny
	Mat panelup_grayImg;
	cvtColor(panel_up, panelup_grayImg, CV_BGR2GRAY);
	Mat panelup_blurImg;
	GaussianBlur(panelup_grayImg, panelup_blurImg, Size(3, 3), 2, 2);
	Mat panelup_canny;
	Canny(panelup_blurImg, panelup_canny, 25, 50);

	//查找panelup_canny中所有轮廓 -> contours3
	vector<vector<Point>> contours3;
	vector<Vec4i> hierarchy3;
	findContours(panelup_canny, contours3, hierarchy3, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//查找contours3中size最大的轮廓 -> contours4
	vector<Point> contours4(1);
	int maxsize3 = contours3[0].size();
	for (int i = 0;i < contours3.size();i++)
	{
		if (contours3[i].size() >= maxsize3)
		{
			maxsize3 = contours3[i].size();
			contours4 = contours3[i];
		}
	}

	//对contours4作多边形逼近 ->contours4_poly
	vector<Point> contours4_poly(contours4.size());
	approxPolyDP(Mat(contours4), contours4_poly, 5, true);
	if (contours4_poly.size() == 0)
	{
		LOG(ERROR) << "函数：analog_onepanel_detect, " << "inner边缘检测错误";
		return sg_ERROR;
	}

	//从plate_up上截取contours4_poly对应的内部表盘 ->inner
	Rect rectInner = boundingRect(contours4_poly);
	Mat inner = Mat::zeros(rectInner.size(), CV_8UC3);
	panel_up(rectInner).copyTo(inner);

	//根据inner长宽确定目标区域位置 -> middle
	resp = checkRectInside(inner, Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_onepanel_detect, " << "middle1 ROI取值错误";
		return resp;
	}
	Mat middle1 = inner(Rect(inner.cols / 3, 0, inner.cols / 2.5, inner.rows / 4));

	//19.对middle1作颜色检测，统计符合条件的像素点数 -> figures2
	int r2 = 0;
	int g2 = 0;
	int b2 = 0;
	Vec3b target2;
	target2[0] = b2;
	target2[1] = g2;
	target2[2] = r2;

	int figures2;
	vector<Point> Points2(1000);
	Mat black2(middle1.rows, middle1.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(middle1, target2, 120, 100, 100, 180, black2, Points2, figures2);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_onepanel_detect, " << "middle1颜色检测错误";
		return resp;
	}

	//20.计算figures在middle总像素数s中所占比例 -> ratio
	int s = middle1.cols*middle1.rows;
	float ratio = figures2*1.0 / s;

	//21.判断ratio大小，阈值设0.3，ratio >= 0.3连接，反之断开
	if (ratio >= 0.2)
	{
		valueArr[0] = sg_analog_Connect;
	}
	else
	{
		valueArr[0] = sg_analog_DisConnect;
	}
	return sg_OK;
}

/**
*	@Method		analog_lights_detect
*
*	@Brief		模拟指示器类型lights的入口.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	outArgName output argument description.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-26
*/
int analog_lights_detect(const Mat srcImg, Mat & resultImg, vector<int> & valueArr)
{
	int resp = sg_OK;
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	//1.srcImg 预处理 -> grayImg, blurImg, binary, thinning
	Mat grayImg;//灰度化
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	Mat blurImg;//高斯滤波
	GaussianBlur(grayImg, blurImg, Size(9, 9), 2, 2);
	Mat binary;//二值化
	threshold(blurImg, binary, 128, 1, THRESH_BINARY_INV);
	Mat thinning = thinImage(binary);//图像细化
	thinning = thinning * 255;

	//2.查找thinning中所有轮廓 -> contours1
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(thinning, contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	//3.查找contours1中size最大的轮廓 -> contours2
	vector<Point> contours2(1);
	int maxsize1 = contours1[0].size();
	for (int i = 0;i < contours1.size();i++)
	{
		if (contours1[i].size() >= maxsize1)
		{
			maxsize1 = contours1[i].size();
			contours2 = contours1[i];
		}
	}

	//4.对contours2作多边形逼近 -> contours2_poly
	vector<Point> contours2_poly(contours2.size());
	approxPolyDP(Mat(contours2), contours2_poly, 5, true);

	//5.找contours2_poly中点的纵坐标的上下限maxy和miny，横坐标的上下限maxx和minx
	int miny = contours2_poly[0].y;
	int maxy = contours2_poly[0].y;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].y <= miny)
		{
			miny = contours2_poly[i].y;
		}
		if (contours2_poly[i].y >= maxy)
		{
			maxy = contours2_poly[i].y;
		}
	}

	int minx = contours2_poly[0].x;
	int maxx = contours2_poly[0].x;
	for (int i = 0;i < contours2_poly.size();i++)
	{
		if (contours2_poly[i].x <= minx)
		{
			minx = contours2_poly[i].x;
		}
		if (contours2_poly[i].x >= maxx)
		{
			maxx = contours2_poly[i].x;
		}
	}

	//6.contours2_poly 复制 -> apex1
	vector<Point> apex1;
	apex1.assign(contours2_poly.begin(), contours2_poly.end());

	//7.删除apex1中不在panel位置内的点 -> apex1
	vector<Point>::iterator it1 = apex1.begin();
	for (int i = 0;i < contours2_poly.size() && it1 != apex1.end();i++)
	{
		if ((contours2_poly[i].y - miny) >(maxy - miny) / 2.5 || (contours2_poly[i].y - miny) < (maxy - miny) / 10)
		{
			it1 = apex1.erase(it1);
		}
		else
		{
			++it1;
		}
	}

	//8.从srcImg上截取apex1对应的矩形表盘 -> panel;
	Rect rectPanel = boundingRect(apex1);
	Mat panel = Mat::zeros(rectPanel.size(), CV_8UC3);
	srcImg(rectPanel).copyTo(panel);

	//9.截取panel上半部分 -> panel_up ; 截取dial下半部分 -> panel_down
	Mat panel_up = panel(Rect(0, 0, panel.cols, panel.rows / 2));
	Mat panel_down = panel(Rect(0, panel.rows / 2, panel.cols, panel.rows / 2));

	//10.将panel_up和panel_down转换到HSL空间 -> hslImg_up, hslImg_down
	Mat hslImg_up;
	cvtColor(panel_up, hslImg_up, CV_BGR2HLS_FULL);
	Mat hslImg_down;
	cvtColor(panel_down, hslImg_down, CV_BGR2HLS_FULL);

	//11.检测hslImg_up和hslImg_down中符合L分量检测条件的像素点 -> M_up, M_down
	Mat M_up(hslImg_up.rows, hslImg_up.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectLuminance(hslImg_up, 230, 255, M_up);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "panel_up亮度检测错误";
		return resp;
	}

	Mat M_down(hslImg_down.rows, hslImg_down.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectLuminance(hslImg_down, 230, 255, M_down);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "panel_down亮度检测错误";
		return resp;
	}

	//12.对M_up,M_down作形态学操作 -> M_up, M_down
	Mat element = getStructuringElement(MORPH_RECT, Size(21, 21));

	resize(M_up, M_up, Size(M_up.cols * 5, M_up.rows * 5));
	morphologyEx(M_up, M_up, MORPH_CLOSE, element);//对检测结果进行开、闭操作
	morphologyEx(M_up, M_up, MORPH_OPEN, element);//剔除一些干扰的像素点

	resize(M_down, M_down, Size(M_down.cols * 5, M_down.rows * 5));
	morphologyEx(M_down, M_down, MORPH_CLOSE, element);//对检测结果进行开、闭操作
	morphologyEx(M_down, M_down, MORPH_OPEN, element);//剔除一些干扰的像素点

	//13.对M_up作颜色检测 -> figures1
	int r1 = 255;
	int g1 = 255;
	int b1 = 255;
	Vec3b target1;
	target1[0] = b1;
	target1[1] = g1;
	target1[2] = r1;

	int figures1;
	vector<Point> Points1(50000);
	Mat white1(M_up.rows, M_up.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(M_up, target1, 150, 150, 150, 250, white1, Points1, figures1);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "panel_up颜色检测错误";
		return resp;
	}

	//14.查找符合颜色检测条件的像素点集Points1中横坐标的上下限 -> left_x, right_x
	int left_x = Points1[0].x;
	int right_x = Points1[0].x;
	for (int i = 0;i < figures1;i++)
	{
		if (Points1[i].x <= left_x)
		{
			left_x = Points1[i].x;
		}
		if (Points1[i].x >= right_x)
		{
			right_x = Points1[i].x;
		}

	}

	//15.根据left_x和right_x确定检测区域的位置 -> middle1
	int middle1_x = (right_x - left_x) / 3 + left_x;
	int middle1_y = M_up.rows / 10;
	int middle1_width = M_up.cols / 5;
	int middle1_height = M_up.rows / 3.5;
	resp = checkRectInside(M_up, Rect(middle1_x, middle1_y, middle1_width, middle1_height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "middle1 ROI取值错误";
		return resp;
	}
	Mat middle1;
	middle1 = M_up(Rect(middle1_x, middle1_y, middle1_width, middle1_height));

	//16.对middle1作颜色检测 -> figures2
	int r2 = 255;
	int g2 = 255;
	int b2 = 255;
	Vec3b target2;
	target2[0] = b2;
	target2[1] = g2;
	target2[2] = r2;

	int figures2;
	vector<Point> Points2(10000);
	Mat white2(middle1.rows, middle1.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(middle1, target2, 150, 150, 150, 250, white2, Points2, figures2);
	CHECKRESP(resp);

	//17.计算figures2在middle1总像素数s中所占比例 -> ratio
	int s = middle1.cols*middle1.rows;
	float ratio = figures2*1.0 / s;

	//18.判断ratio大小，阈值设0.3，ratio >= 0.3连接，反之断开
	if (ratio >= 0.3)
	{
		valueArr[0] = sg_analog_Connect;
	}
	else
	{
		valueArr[0] = sg_analog_DisConnect;
	}

	//19.M_down 预处理 -> Mdown_gray, Mdown_blur, Mdown_canny
	Mat Mdown_gray;//灰度化
	cvtColor(M_down, Mdown_gray, CV_BGR2GRAY);
	Mat Mdown_blur;//高斯滤波
	GaussianBlur(Mdown_gray, Mdown_blur, Size(9, 9), 2, 2);
	Mat Mdown_canny;//边缘检测
	Canny(Mdown_blur, Mdown_canny, 25, 50);

	//20.对M_down作直线检测 -> lines1
	vector<Vec4i> lines1;// 霍夫变换检测直线，最小投票为30，线条不短于50，间隙不小于50  
	double rho1 = 1;	//以像素为单位的距离精度,即直线搜索时的步进尺寸的单位半径			
	double theta1 = CV_PI / 180;	//以弧度为单位的角度精度，即直线搜索时的步进尺寸的单位角度
	int threshold1 = 30;	//累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值，大于阈值的线段才可以被检测到并返回到结果中
	double minLineLength1 = 30; //默认值为0，标示最低线段的长度，比这个设定参数短的线段就不能被显现出来			
	double maxLineGap1 = 50;	//默认值为0，允许将统一行点与点之间连接起来的最大距离。
	HoughLinesP(Mdown_canny, lines1, rho1, theta1, threshold1, minLineLength1, maxLineGap1);
	if (lines1.size() == 0)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "panel_down直线检测错误";
		return sg_ERROR;
	}
	//21.查找lines1中length最长的线段 -> lines1_max
	vector<Vec4i>lines1_max;
	int x1 = lines1[0][2] - lines1[0][0];
	int y1 = lines1[0][3] - lines1[0][1];
	int maxlength1 = sqrt(x1*x1 + y1*y1);
	int maxnumber1 = 0;
	for (int i = 0;i < lines1.size();i++)
	{
		int x = lines1[i][2] - lines1[i][0];
		int y = lines1[i][3] - lines1[i][1];
		int length = sqrt(x*x + y*y);
		if (length >= maxlength1)
		{
			maxlength1 = length;
			maxnumber1 = i;
		}
	}
	lines1_max.push_back(lines1[maxnumber1]);

	//22.统计lines1_max中直线的角度 -> Angle1
	float Angle1 = 0.0;
	Vec4i l1 = lines1_max[0];
	if (l1[2] == l1[0])
	{
		Angle1 = 90.0;
	}
	else
	{
		Angle1 = abs(atan((l1[3] - l1[1])*1.0 / (l1[2] - l1[0])) / M_PI * 180);
	}

	//23.根据Angle1大小判断panel_down状态
	int angle = cvRound(Angle1);
	if (angle <= 91 && angle >= 85)//纵向
	{
		valueArr[1] = sg_analog_Connect;
	}
	else
	{
		valueArr[1] = sg_analog_DisConnect;
	}

	////24.在srcImg上截取contours2对应的模拟指示器ROI -> analog
	//Rect rectanalog = boundingRect(contours2);
	//Mat analog = Mat::zeros(rectanalog.size(), CV_8UC3);
	//srcImg(rectanalog).copyTo(analog);

	//24.在srcImg上截取circle表盘 -> circle
	int L = maxy - miny;
	int upline = L / 2 + miny;
	int downline = L / 16 * 11 + miny;
	int circle_width = (downline - upline) / 2;
	int circle_height = downline - upline;
	int circle_x = minx - circle_width / 2;
	int circle_y = upline;

	resp = checkRectInside(srcImg, Rect(circle_x, circle_y, circle_width, circle_height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "circle ROI取值错误";
		return resp;
	}
	Mat circle;
	circle = srcImg(Rect(circle_x, circle_y, circle_width, circle_height));
	resize(circle, circle, Size(circle.cols * 5, circle.rows * 5));

	//25.对circle作颜色检测 -> white3
	int r3 = 255;
	int g3 = 255;
	int b3 = 255;
	Vec3b target3;
	target3[0] = b3;
	target3[1] = g3;
	target3[2] = r3;

	int figures3;
	vector<Point> Points3(5000);
	Mat white3(circle.rows, circle.cols, CV_8UC3, Scalar(0, 0, 0));
	resp = detectColorWithPoints(circle, target3, 20, 20, 20, 30, white3, Points3, figures3);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "circle颜色检测错误";
		return resp;
	}

	//26.对white3作形态学操作 -> dilation
	Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat dilation;
	morphologyEx(white3, dilation, MORPH_CLOSE, element1);//对检测结果进行开、闭操作
	morphologyEx(dilation, dilation, MORPH_OPEN, element2);//剔除一些干扰的像素点

	//27.dilation 预处理 -> circle_gray, circle_blur, circle_canny
	Mat circle_gray;//灰度化
	cvtColor(dilation, circle_gray, CV_BGR2GRAY);
	Mat circle_blur;//高斯滤波
	GaussianBlur(circle_gray, circle_blur, Size(9, 9), 2, 2);
	Mat circle_canny;//边缘检测
	Canny(circle_blur, circle_canny, 25, 50);

	//28.对circle_canny作直线检测 -> lines2
	vector<Vec4i> lines2;// 霍夫变换检测直线，最小投票为30，线条不短于50，间隙不小于50  
	double rho2 = 1;	//以像素为单位的距离精度,即直线搜索时的步进尺寸的单位半径			
	double theta2 = CV_PI / 180;	//以弧度为单位的角度精度，即直线搜索时的步进尺寸的单位角度
	int threshold2 = 30;	//累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值，大于阈值的线段才可以被检测到并返回到结果中
	double minLineLength2 = 30; //默认值为0，标示最低线段的长度，比这个设定参数短的线段就不能被显现出来			
	double maxLineGap2 = 50;	//默认值为0，允许将统一行点与点之间连接起来的最大距离。
	HoughLinesP(circle_canny, lines2, rho2, theta2, threshold2, minLineLength2, maxLineGap2);
	if (lines2.size() == 0)
	{
		LOG(ERROR) << "函数：analog_lights_detect, " << "circle直线检测错误";
		return sg_ERROR;
	}

	//29.查找lines2中length最长的线段 -> lines2_max
	vector<Vec4i> lines2_max;
	int x2 = lines2[0][2] - lines2[0][0];
	int y2 = lines2[0][3] - lines2[0][1];
	int maxlength2 = sqrt(x2*x2 + y2*y2);
	int maxnumber2 = 0;
	for (int i = 0;i < lines2.size();i++)
	{
		int x = lines2[i][2] - lines2[i][0];
		int y = lines2[i][2] - lines2[i][0];
		int length = sqrt(x*x + y*y);
		if (length >= maxlength2)
		{
			maxlength2 = length;
			maxnumber2 = i;
		}
	}
	lines2_max.push_back(lines2[maxnumber2]);

	//30.统计lines2_max中直线的角度 -> Angle2
	float Angle2 = 0.0;
	Vec4i l2 = lines2_max[0];
	if (l2[2] == l2[0])
	{
		Angle2 = 90.0;
	}
	else
	{
		Angle2 = abs(atan((l2[3] - l2[1])*1.0 / (l2[2] - l2[0])) / M_PI * 180);
	}

	//31.根据Angle2大小判断circle状态
	int angle2 = cvRound(Angle2);
	if (angle2 <= 91 && angle2 >= 85)//纵向
	{
		valueArr[2] = sg_analog_Connect;
	}
	else
	{
		valueArr[2] = sg_analog_DisConnect;
	}
	return sg_OK;
}

