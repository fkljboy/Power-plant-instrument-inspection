/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgApplication.h
*
* 	@Brief	应用层函数头文件
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-24
*
*	@MethodList
*		1.
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*
*/ 
#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_taskinfo.h"

#include <opencv2\opencv.hpp>
using namespace cv;

// 结构体方式任务分发.
int taskDistributeWithStruct(const Mat srcImg, const TaskInfo taskinfo, ResultInfo & resultinfo);

// 检测识别任务交互接口,非DLL接口，工程内部接口.
int detectTask(const Mat srcImg, const ROIInfo roi, const TaskInfo taskinfo, ResultInfo & resultinfo);

// 从XML中进行XML解析，同时进行检测
int processXMLTask(const Mat srcImg, const string xmlPath, vector<string> & resultArr, const int DevNum, const int updown);

// 根据任务列表保存元素图片
int saveElementROIimg(const vector<DetectInfo> detectList, const Mat srcImg, const int DevNum);

// 从任务列表中获取ROI信息，如要使用二维码定位则进行换算
int getROIArrayandUpdate(vector<DetectInfo> & detectList, bool withQR, QRCodePos qrPosNow, QRCodePos qrPosOrigin);

// 在C++端释放int数组内存.
bool ReleaseMemoryINT(int* buf);

// 根据XML配置文件对任务序列的ROI进行查看，确认ROI无误
int drawROIListWithXML(const Mat srcImg, const string xmlPath, Mat & resultImg);
