/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgcore_safetyCheck.h
*
* 	@Brief	用来进行安全监测的源文件.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-06-03
*
*	@MethodList
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		6/03		SHEN		Created.
*
*/

#include "../sgCore/sgcore_safetyCheck.h"

#include "sgcore_def.h"
#include <opencv2\opencv.hpp>
using namespace cv;


// 判断ROI是否在图像内
int checkRectInside(const Mat srcImg, const Rect roiRect)
{
	int resp = sg_OK;
	Rect srcImgRect = Rect(0, 0, srcImg.cols, srcImg.rows);

	// 判断ROI是否在图像内
	bool is_inside = (srcImgRect & roiRect) == roiRect;
	if (is_inside)
	{
		return sg_OK;
	}
	else
	{
		return sg_ERROR;
	}
}