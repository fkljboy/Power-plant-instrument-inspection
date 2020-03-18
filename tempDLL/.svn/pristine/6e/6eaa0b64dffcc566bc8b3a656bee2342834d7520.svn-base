#include <opencv2/opencv.hpp>

using namespace cv;

//#include <vld.h>  

#include "../StateGridDLL/sgFunction/tinyxml2.cpp"

#include "../StateGridDLL/sgCore/sgcore_platform.h"
#include "../StateGridDLL/sgCore/sgcore_log.cpp"

#include "../StateGridDLL/sgFunction/sgfunc_imageio.cpp"
#include "../StateGridDLL/sgApplication/sgApplication.cpp"
#include "../StateGridDLL/sgFunction/sgfunc_feature.cpp"
#include "../StateGridDLL/sgFunction/sgfunc_transform.cpp"
#include "../StateGridDLL/sgTask/sgtask_analog.cpp"
#include "../StateGridDLL/sgTask/sgtask_pointer.cpp"
#include "../StateGridDLL/sgTask/sgtask_led.cpp"
#include "../StateGridDLL/sgTask/sgtask_knob.cpp"
#include "../StateGridDLL/sgTask/sgtask_qrcode.cpp"

#include "../StateGridDLL/sgCore/sgcore_taskinfo.cpp"



#include "../StateGridDLL/sgFunction/sgfunc_file.cpp"
#include "../StateGridDLL/sgTask/DealImageUtil.h"
#include "../StateGridDLL/sgTask/DealImageUtil.cpp"
#include "../StateGridDLL/sgTask/ImageDeal.h"
#include "../StateGridDLL/sgTask/ImageDeal.cpp"

#include "../StateGridDLL/sgCore/sgcore_safetyCheck.h"
#include "../StateGridDLL/sgCore/sgcore_safetyCheck.cpp"

//Glog日志库日志保存路径
const char* glogLogDir = "巡检日志/识别日志";

int main(int argc, char* argv[])
{
	// 方式二：检测内存泄漏
	//EnableMemLeakCheck();

	// 方式三：
	//_CrtSetBreakAlloc(14375);
	//_CrtSetBreakAlloc(6595);
	//_CrtSetBreakAlloc(459);

	//_CrtSetBreakAlloc(295);
	//_CrtSetBreakAlloc(218);
	//_CrtSetBreakAlloc(150);

	//int resp = sg_OK;
	// glog初始化，必须，勿删
	glogInit(argv[0], glogLogDir);

	int num = 60;
	int updown = 1;
	Mat src = imread("设备图片/Dev60_1.jpg", 1);
	string xmlPath = "配置文件/XML_DEV_60_1.xml";
	vector<string> result(0);
    int resp= processXMLTask(src, xmlPath, result, num, updown);

	// 3. 整理成字符串数组
	string content = "";

	// 此处从1开始
	// 虽然此处报内存泄漏,但string标准类不去怀疑
	for (size_t i = 1; i < result.size(); i++)
	{
		if (result[i] != "")
		{
			content.append(result[i]);
			content.append(";");
			//content = content + result[i] + ";" ;
		}
	}


	LOG(INFO) << "结果： " << content;

	//system("pause");

	// glog关闭，必须，勿删
	glogShutdown();

	//int i = _CrtDumpMemoryLeaks();
	//assert(i == 0);

	// 方式一
	//_CrtDumpMemoryLeaks();
	return 0;
	
}