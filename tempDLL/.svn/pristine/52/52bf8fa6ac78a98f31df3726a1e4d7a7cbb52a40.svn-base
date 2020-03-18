/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_imageio.cpp
*
* 	@Brief	图像输入输出的函数.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-17
*
*	@MethodList
*		1.	int imgShowDebug(const Mat srcImg, const String name, const bool isWait);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/17		SHEN		Created.
*
*/ 
#include "sgfunc_imageio.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"

#include <opencv2\opencv.hpp>
using namespace cv;


#include <string>
using namespace std;

/**
*	@Method		imgShowDebug
*
*	@Brief		统一显示接口,仅在Debug模式下显示
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg
*
*				const String name
*
*				const bool isWait
*
*	@Para [OUT]	无
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-23
*/
int imgShowDebug(const Mat srcImg, const string name,  const bool isWait)
{

	if (srcImg.empty())
	{
		LOG(WARNING) << "函数：imgShowDebug" << "图像为空";
		return sg_ERROR;
	}

#ifdef _DEBUG

	// 如果图像过大则限制大小
	if (srcImg.rows > 350)
	{
		double scale = 350 * 1.0 / srcImg.rows;	// 注意double形式
		Mat showImg;
		resize(srcImg, showImg, Size(), scale, scale);
		imshow(name, showImg);
	}
	else
	{
		Mat showImg = srcImg.clone();
		imshow(name, showImg);
	}
	
	LOG(INFO) << "显示 " + name;

	// waitkey等待
	if (isWait)
	{
		waitKey(0);
	}

#else

	LOG(WARNING) << "Release模式不显示图像，图像名：" << name;

#endif // _DEBUG

	

	return sg_OK;
}







/**
*	@Method		drawROIArray
*
*	@Brief		在源图上绘制ROI列表，确认是否框准确
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg
*
*				const String name
*
*				const bool isWait
*
*	@Para [OUT]	无
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-25
*/
int drawROIArray(Mat & darwImg, const vector<DetectInfo> detectList)
{
	LOG(INFO) << "函数：drawROIArray（在图中绘制ROI数组）， 进入";

	int resp = sg_OK;

	if (darwImg.empty())
	{
		LOG(ERROR) << "函数：drawROIArray " << "图像为空";
		resp = sg_ERROR;
		return resp;
	}


	for (int i = 0; i < detectList.size(); i++)
	{
		LOG(INFO) << "绘制第" << i << "个框";
		// TODO:判断ROI inside
		rectangle(darwImg, Rect(detectList[i].roiinfo.startX, detectList[i].roiinfo.startY, detectList[i].roiinfo.width, detectList[i].roiinfo.height), Scalar(0, 0, 255), 7);
	}

	imgShowDebug(darwImg, "绘制ROI数组", false);	// 调试显示

	LOG(INFO) << "函数：drawROIArray（在图中绘制ROI数组）， 退出";
	return resp;
}
