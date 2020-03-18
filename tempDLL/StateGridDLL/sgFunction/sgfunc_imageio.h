/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_imageio.h
*
* 	@Brief	图像输入输出的函数头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-17
*
*	@MethodList
*		1.
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/17		SHEN		Created.
*
*/



#ifndef SGFUNC_IMAGEIO_H
#define SGFUNC_IMAGEIO_H

#include <opencv2\opencv.hpp>
using namespace cv;

#include <string>
using namespace std;

#include "../sgCore/sgcore_taskinfo.h"

// 图像显示调试接口
int imgShowDebug(const Mat srcImg, const string name, const bool isWait);

// 绘制ROI数组
int drawROIArray(Mat & darwImg, vector<DetectInfo> detectList);

#endif // !SGFUNC_IMAGEIO_H