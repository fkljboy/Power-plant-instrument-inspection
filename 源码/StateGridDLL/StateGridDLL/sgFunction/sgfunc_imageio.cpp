/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_imageio.cpp
*
* 	@Brief	ͼ����������ĺ���.
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
*	@Brief		ͳһ��ʾ�ӿ�,����Debugģʽ����ʾ
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg
*
*				const String name
*
*				const bool isWait
*
*	@Para [OUT]	��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-23
*/
int imgShowDebug(const Mat srcImg, const string name,  const bool isWait)
{

	if (srcImg.empty())
	{
		LOG(WARNING) << "������imgShowDebug" << "ͼ��Ϊ��";
		return sg_ERROR;
	}

#ifdef _DEBUG

	// ���ͼ����������ƴ�С
	if (srcImg.rows > 350)
	{
		double scale = 350 * 1.0 / srcImg.rows;	// ע��double��ʽ
		Mat showImg;
		resize(srcImg, showImg, Size(), scale, scale);
		imshow(name, showImg);
	}
	else
	{
		Mat showImg = srcImg.clone();
		imshow(name, showImg);
	}
	
	LOG(INFO) << "��ʾ " + name;

	// waitkey�ȴ�
	if (isWait)
	{
		waitKey(0);
	}

#else

	LOG(WARNING) << "Releaseģʽ����ʾͼ��ͼ������" << name;

#endif // _DEBUG

	

	return sg_OK;
}







/**
*	@Method		drawROIArray
*
*	@Brief		��Դͼ�ϻ���ROI�б�ȷ���Ƿ��׼ȷ
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg
*
*				const String name
*
*				const bool isWait
*
*	@Para [OUT]	��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-25
*/
int drawROIArray(Mat & darwImg, const vector<DetectInfo> detectList)
{
	LOG(INFO) << "������drawROIArray����ͼ�л���ROI���飩�� ����";

	int resp = sg_OK;

	if (darwImg.empty())
	{
		LOG(ERROR) << "������drawROIArray " << "ͼ��Ϊ��";
		resp = sg_ERROR;
		return resp;
	}


	for (int i = 0; i < detectList.size(); i++)
	{
		LOG(INFO) << "���Ƶ�" << i << "����";
		// TODO:�ж�ROI inside
		rectangle(darwImg, Rect(detectList[i].roiinfo.startX, detectList[i].roiinfo.startY, detectList[i].roiinfo.width, detectList[i].roiinfo.height), Scalar(0, 0, 255), 7);
	}

	imgShowDebug(darwImg, "����ROI����", false);	// ������ʾ

	LOG(INFO) << "������drawROIArray����ͼ�л���ROI���飩�� �˳�";
	return resp;
}
