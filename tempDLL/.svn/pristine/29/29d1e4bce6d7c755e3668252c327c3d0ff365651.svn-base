/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_feature.h
*
* 	@Brief	特征提取头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-18
*
*	@MethodList
*		1.	int getOTSUthresholdNoBlack(const Mat srcImg, int & thresh);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*
*/ 


#ifndef SGFUNC_FEATURE_H
#define SGFUNC_FEATURE_H


#include <opencv2\opencv.hpp>
using namespace cv;

#include <string>
using namespace std;

// 用于指示灯模板匹配
class MatchPoint
{
public:
	Point point;
	int status;
	double matchValue;

	MatchPoint(int x, int y, int state, double match)
	{
		point.x = x;
		point.y = y;
		status = state;
		matchValue = match;
	}

	bool operator < (const MatchPoint &m)const
	{
		return  point.y < m.point.y;
	}
};


// 计算图像中非零点区域类间方差对应的阈值
int getOTSUthresholdNoBlack(const Mat srcImg, int & thresh);

// 遍历像素点，检测是否匹配目标颜色
int detectColorWithPoints(const Mat srcImg, Vec3b color, const int red, const int green, const int blue, const int minimum, Mat & result, vector<vector<int>> & Points, int & figures);

// 模板匹配
int imageMatch(Mat srcImg, Mat tempImg, vector<MatchPoint> & outLights, int flag, string text, double minMatch);

#endif // !SGFUNC_FEATURE_H
