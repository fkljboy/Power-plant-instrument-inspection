/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_taskinfo.h
*
* 	@Brief	短接片开关状态检测头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-05-24
*
*	@MethodList
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		5/24		SHEN		Created.
*
*/ 

#ifndef SGTASK_TASKINFO_H
#define SGTASK_TASKINFO_H

#include <opencv2\opencv.hpp>
using namespace cv;

#include "../sgCore/sgcore_def.h"


// 旋钮的语义转换类
class knob_refer {
public:
	vector<knobStall> knobs;

	knob_refer(void);

	string getContextWithAngle(double angle);	//返回换算结果
};


// 类检测信息：包括设备名，RoiInfo, TaskINFO,ResultINFO,ReferINFO //先不考虑换算，即ReferINFO
class DetectInfo
{
public:
	string deviceName;	// 设备名称
	ROIInfo roiinfo;	// ROI信息
	TaskInfo taskinfo;	// 任务信息
	ResultInfo resultinfo;	// 结果信息
	knob_refer knobrefer;	// 旋钮语义转换类

	DetectInfo(void);
	DetectInfo(string dname, ROIInfo roi, TaskInfo task, knob_refer refer);

	string getKnobInfo(void);
};


#endif // !SGTASK_TASKINFO_H
