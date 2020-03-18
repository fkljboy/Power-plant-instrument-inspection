/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_knob.h
*
* 	@Brief	旋钮识别函数头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1.	int Detect_knob(const Mat srcImg, const unsigned int Knobtype, const unsigned int platetype, unsigned int & angle);
*
*		2.	int PanelDetect_knob(const Mat srcImg, const unsigned int platetype, Mat & panel);
*
*		3.	int AngleDetect_knob(const Mat srcImg, const unsigned int Knobtype, unsigned int & angle);
*
*		4.	int PanelAreaMaybe(const Mat srcImg, Mat & erodeImg, const unsigned int platetype, const vector<vector<Point>> contours, int & panelNum, vector<Rect> & boundRect);
*
*		5.	int BoundProjection(const Mat erodeImg, int * location);
*
*		6.	int PanelLocation(const Mat erodeImg, const vector<Rect> boundRect, const int panelNum, int * location);
*
*		7.	int removeFrame(const Mat knobImg_bin, const Mat knob_Img, Mat & result);
*
*		8.	int SquareHeadKnobDetection(const Mat srcImg, unsigned int & resultAngle);
*
*		9.	int angleOfMaxLine(const Mat edge, Mat & drawImg, int & angle);
*
*		10.	int link_gap(Mat &threImage);
*
*		11.	int extend_Bound(const Mat threMat, Mat & result);
*
*		12.	int cacBoundRectRandomDirection(const Mat srcMat, int & angle);
*
*		13.	int SharpHeadKnobDetection(const Mat srcImg, unsigned int & resultAngle);
*
*       14. int eraseSmallArea(Mat edge, Mat srcImg, Mat& mainAreaImg);
*
*       15. int CircleKnobDetection(const Mat srcImg, int & resultAngle);
*
*       16. int searchCircleKnob(Mat binImg, vector<Point>& knobContour);
*
*       17. int circleKnobAngleCalc(const Mat srcImg, const Mat otsuImg, vector<Point> knobContour, int& resultAngle);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		created.
*
*	2.0		3/17		SHEN		Add 13 Methods.
*
*/ 

#ifndef SGTASK_KNOB_H
#define SGTASK_KNOB_H

#include <opencv2\opencv.hpp>
using namespace cv;

//旋钮检测入口.
int Detect_knob(const Mat srcImg, const unsigned int Knobtype, int & angle);

//旋钮表盘定位
int PanelDetect_knob(const Mat srcImg, const unsigned int platetype, Mat & panel);

//旋钮角度识别
int AngleDetect_knob(const Mat srcImg, const unsigned int Knobtype, int & angle);

//通过连通域法找到旋钮表盘所在的区域
int PanelAreaMaybe(const Mat srcImg, Mat & erodeImg, const unsigned int platetype, const vector<vector<Point>> contours, int & panelNum, vector<Rect> & boundRect);

//根据投影选取四条边
int BoundProjection(const Mat erodeImg, int * location);

//得到旋钮表盘的顶点坐标
int PanelLocation(const Mat erodeImg, const vector<Rect> boundRect, const int panelNum, int * location);

//抠出旋钮表盘区域
int GetPanelArea(const Mat srcImg, const Mat erodeImg, const Mat binaryImg, const vector<Rect> boundRect, int panelNum, Mat & knobImg, Mat & knobImg_bin);

//剔除四周边框
int removeFrame(const Mat knobImg_bin, const Mat knob_Img, Mat & result);

//方头旋钮识别
int SquareHeadKnobDetection(const Mat srcImg, int & resultAngle);

//图像中最长直线的角度
int angleOfMaxLine(const Mat edge, Mat & drawImg, int & angle);

//连接旋钮区域断裂的部分
int link_gap(Mat &threImage);

//扩展旋钮图片并用白色像素点填充
int extend_Bound(const Mat threMat, Mat & result);

//找出旋钮的倾斜外接矩形，通过计算对角线的角度得到旋钮角度.
int cacBoundRectRandomDirection(const Mat srcMat, int & angle);

//尖头旋钮识别
int SharpHeadKnobDetection(const Mat srcImg, int & resultAngle);

//圆形旋钮识别
int CircleKnobDetection(const Mat srcImg, int & resultAngle);

//消除二值图像中小面积的连通域
int eraseSmallArea(Mat edge, Mat srcImg, Mat& mainAreaImg);

//找到圆形旋钮的倾斜外接矩形
int searchCircleKnob(Mat binImg, vector<Point>& knobContour);

//圆形旋钮角度计算
int circleKnobAngleCalc(const Mat srcImg, const Mat otsuImg, vector<Point> knobContour, int& resultAngle);

#endif // !SGTASK_KNOB_H
