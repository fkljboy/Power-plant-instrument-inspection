#include "sgcore_def.h"
#include "sgcore_taskinfo.h"


// 默认构造函数，一般不会发生
DetectInfo::DetectInfo(void)
{
	deviceName = "";
	roiinfo = ROIInfo();
	taskinfo = TaskInfo();
	knobrefer = knob_refer();
}

// 构造函数
DetectInfo::DetectInfo(string dname, ROIInfo roi, TaskInfo task, knob_refer refer)
{
	deviceName = dname;
	roiinfo = roi;
	taskinfo = task;
	knobrefer = refer;
}

string DetectInfo::getKnobInfo(void)
{
	return knobrefer.getContextWithAngle(resultinfo.result);
}


knob_refer::knob_refer(void)
{
	knobs = vector<knobStall>(0);
}


string knob_refer::getContextWithAngle(double angle)
{
	for (size_t i = 0; i < knobs.size(); i++)
	{
		if (angle >= knobs[i].min_angle && angle < knobs[i].max_angle)
		{
			return knobs[i].context;
		}
	}
	return "检测错误";
}