/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_led.h
*
* 	@Brief	指示灯识别函数头文件.
*	
* 	@Author	Author
*
* 	@Create	2018-03-16
*
*	@MethodList
*		1. int Detect_led(const Mat srcImg, const unsigned int ledtype, unsigned int lednum, unsigned int * valueArr)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/16		SHEN		Created.
*
*/ 

#ifndef SGTASK_LED_H
#define SGTASK_LED_H


#include <opencv2\opencv.hpp>
using namespace cv;


// 指示灯检测识别入口.
int Detect_led(const Mat srcImg, const int ledtype, vector<int> &  valueArr);

// 排除黑色像素点的影响二值化
int otsuThreshold(const Mat grayImage, Mat& otsuImg);

// 纵差继电器指示灯检测
int led_Zongcha_detect(const Mat srcImg, vector<int> &  valueArr);

// 保护继电器指示灯检测
int led_Baohu_detect(const Mat srcImg, vector<int> &  valueArr);

// 通讯继电器指示灯检测
int led_Tongxun_detect(const Mat srcImg, vector<int> &  valueArr);

// 跳闪灯检测
int led_flash_detect(const Mat srcImg, const Mat templateImg, vector<int> &  valueArr);

// 根据投影选取四条边
int BoundProjection(const Mat Image, int *location, float scale);

//查找二值化图像中的轮廓
int searchCore(Mat binaryImg, vector<Point>& core, float colScale, float rowScale);

//对图像进行倾斜校正
int rotateCorrection(Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg, int ledKind);

//获取Hsv空间中边缘检测后的图像
int getHsvEdge(Mat mainArea, Mat& edgeHsv);

//找到位于同一行的点阵
int searchPointSameRow(vector<vector<Point>>& pointGroup, vector<Point>& coreMainOtsu,
	int rows, float rowScale);

//找到横坐标一致最多的两行
int searchMostSilmilarRow(const vector<vector<Point>> pointGroup,
	vector<Point>& downPoint, int cols, int& upRow, int& downRow);

//按横坐标或者纵坐标排列点阵
int arrangePoint(vector<Point>& pointList, int rowOrCol);


//选择点与点之间距离最多的值作为点的间隔，减小漏检点和噪声点的干扰
int maxPointDis(const vector<Point>pointList, float& averDis, int cols, float colScale, int knobKind);

//找所有点之间的列中垂直投影最多的那一列为参考线
int maxVertProjection(const Mat mainOtsu, const int upRow, const int downRow,
	const vector<Point> pointList, int& maxProjectionCol);


//确定两个灯的位置
int lightLocate(vector<Point> coreHsv, const int maxProjectionCol, const float averDis, int *label,
	const int upRow, const int downRow, vector<int> &  valueArr);


//找出连通域最多的一行
int maxContourRow(const vector<vector<Point>> pointRowGroup, vector<Point>& maxPointRow);


//找出连通域最多的一列
int maxContourCol(const vector<vector<Point>> pointColGroup, vector<Point>& maxPointCol);


//找到标识列所在的位置
int searchSignCol(const vector<Point> coreMainEdge, const Mat mainEdge,
	vector<vector<Point>>& pointColGroup, float colScale);

//找出第一个个数大于3的列
int colMoreThanThree(const vector<vector<Point>>& pointColGroup, const vector<Point> maxPointRow,
	const Mat mainEdge, const float averDis, int& signMaxRowNum, int& signColNum, int& signCol);

//找出标志行中间隔为单位距离的列
int searchAverDisCol(const int signMaxRowNum, const vector<Point> maxPointRow,
	const float averDis, const float cols, const float colScale, vector<Point>& signGroup, int ledtype);

//找出标志列中间隔为单位距离的行
int searchAverDisRow(const vector<Point> maxPointCol, const float averDis,
	const Mat edgeImg, const float colScale, vector<Point>& signGroup);

//将首尾之间未找到的标志进行插值
int insertMiddlePt(vector<Point>& signGroup, const float averDis, const int ledbKind);

//通讯继电器在标志行的首尾进行插值
int comInsertTopEndPt(vector<Point>& signGroup, const int signCol, const float averDis, float cols, int ledKind);

//纵差继电器在标志行的首尾进行插值或者删除
int difInsertTopEndPt(vector<Point>& signGroup, const vector<vector<Point>> pointColGroup,
	const float averDis, const Mat edgeImg);

//找到两排小灯中心点所在的列
int searchLightRows(int *lightRow, vector<vector<Point>>& pointColGroup, const int signColNum,
	const vector<Point> maxPointRow, const int signMaxRowNum);


//将通讯继电器每个灯所在的列提取出来单独讨论
int comLightBlockAnalyze(const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow, vector<int> & valueArr);

//找到位于同一列的点阵
int searchPointSameCol(vector<vector<Point>>& pointColGroup, const vector<Point> coreEdge,
	Mat edgeImg, float colScale);

//将每一段截取出来单独分析
int difLightBlockAnalyse(const vector<Point> signGroup, const float averDis, const Mat lampImg, vector<int> &  valueArr);

#endif // !SGTASK_LED_H
