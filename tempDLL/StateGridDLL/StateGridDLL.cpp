/*
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	StateGridDLL.cpp
*
* 	@Brief	定义DLL应用程序的导出函数.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15 
*
*	@MethodList
*			1.	检测识别任务交互接口
*			1.	DllExport int DetectTask(const char* filename, const ROIInfo roi, const TaskInfo taskinfo , const char* processedName, ResultInfo & resultinfo)
*
*			2.	根据ROI数组绘制方框 DLL接口.
*			2.	DllExport int DrawROIArray(const char* filename, const ROIInfo ROIArray[], const char* processedName)
*
*			3.	初始化glog日志系统
*			3.	DllExport void GoogleGlogInit(char* exefilename)
*
*			4.	关闭glog日志系统
*			4.	DllExport void GoogleGlogShutdown()
*			
*			5.	在C++端释放内存.
*			5.	DllExport bool ReleaseMemoryFromC(unsigned char* buf)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		Created
*	2.0		3/28		SHEN		整理函数，接口成型
*	3.0		5/27		SHEN		新接口整改
*
*/ 


//定义导出DLL简写
#define DllExport extern "C" __declspec(dllexport)

#include "sgApplication/sgApplication.h"

#include "sgcore/sgcore_def.h"
#include "sgCore/sgcore_log.h"

#include "sgTask/sgtask_qrcode.h"
#include "sgFunction/sgfunc_transform.h"
#include "sgFunction/sgfunc_file.h"

#include <opencv2\opencv.hpp>
using namespace cv;


const char* glogLogDir = "巡检日志/识别日志";

/**
*	@Method		GoogleGlogInit
*
*	@Brief		初始化glog日志系统.
*
*	@Para [IN]	char* exefilename： 运行程序名
*
*				const char* glogDir： 日志保存路径
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		设置日志文件保存目录，这个目录必须是已经存在的，否则不能生成日志文件。
*
*				必须在初始化库之前调用。
*
*				相对路径是相对于Debug下.exe的相对路径
*
*	@Create		2018-03-15
*
*	@Checked	2018-05-26
*/
DllExport void GoogleGlogInit(const char* exefilename, const char* glogDir)
{
	LOG(INFO) << "函数DLL接口：GoogleGlogInit（Glog日志系统初始化)， 进入";

	glogInit(exefilename, glogDir);

	LOG(INFO) << "函数DLL接口：GoogleGlogInit（Glog日志系统初始化)， 退出";
}


/**
*	@Method		GoogleGlogShutdown
*
*	@Brief		关闭glog日志系统日志系统.
*
*	@Para [IN]	None.
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		程序运行结束时，必须关闭glog库，否则会内存溢出.
*
*	@Create		2018-03-15
*
*	@Checked	2018-05-26
*/
DllExport void GoogleGlogShutdown()
{
	LOG(INFO) << "函数DLL接口：GoogleGlogShutdown（Glog日志系统结束运行)， 进入";

	glogShutdown();

	LOG(INFO) << "函数DLL接口：GoogleGlogShutdown（Glog日志系统结束运行)， 退出";

	
}



/**
*	@Method		GoogleGlogInitShanghai
*
*	@Brief		初始化glog日志系统.固定相对路径.
*
*	@Para [IN]	char* exefilename： 运行程序名
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		程序运行结束时，必须关闭glog库，否则会内存溢出.
*
*	@Create		2018-05-31
*/
DllExport void GoogleGlogInitShanghai(const char* exefilename)
{
	glogInit(exefilename, glogLogDir);

	LOG(INFO) << "函数DLL接口：GoogleGlogInit（Glog日志系统初始化)";
}



/**
*	@Method		ReleaseMemoryFromC
*
*	@Brief		在C++端释放内存.
*
*	@Para [IN]	unsigned char* buf：	ImageInfo.data对象.
*
*	@Para [OUT]	None.
*
*	@Return		bool:
*				- true:		成功
*				- false:	失败
*
*  	@Note		C#调用方式：
*				if (imInfo.data != IntPtr.Zero)
*				{
*					visionAlgorithm.ReleaseMemoryFromC(imInfo.data);
*				}
*
*	@Create		2018-03-15
*/
DllExport bool ReleaseMemoryFromC(unsigned char* buf)
{
	if (buf == NULL)
		return false;

	free(buf);
	return true;
}



/**
*	@Method		DLL: DrawROIArray（供界面调试）
*
*	@Brief		根据ROI数组绘制方框 DLL接口.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename： 输入图像路径
*
*				const ROIInfo ROIArray[] ： ROI数组
*
*				const char* processedName：处理图像保存路径
*
*	@Para [OUT]	无
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-24
*
*	@Desperated	2018-06-03	执行过程中实现了ROI的画图。
*/
DllExport int DrawROIArray(const char* filename, const ROIInfo ROIArray[], const int num, const char* processedName, QRCodeInfo & qrcodeinfo, int cameraType)
{
	LOG(INFO) << "函数DLL接口：DrawROIArray（根据ROI数组绘制方框 DLL接口)， 进入";

	int resp = sg_OK;

	// 1. 读图及入参检测
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：DrawROIArray " << "图片路径不对，读图失败";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 畸变校正
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：DrawROIArray " << "畸变校正步骤出错";
		return resp;
	}

	// 3. 遍历数组绘制ROI
	for (int i = 0; i < num; i++)
	{
		rectangle(UndistortImg, Rect(ROIArray[i].startX,ROIArray[i].startY,ROIArray[i].width,ROIArray[i].height), Scalar(0, 0, 255), 7);
	}

	// 4. 保存至指定路径
	imwrite(processedName, UndistortImg);
	LOG(INFO) << "函数DLL接口：DrawROIArray，已保存至路径：" << processedName;

	LOG(INFO) << "函数DLL接口：DrawROIArray（根据ROI数组绘制方框 DLL接口)， 退出";
	return resp;
}



/**
*	@Method		DLL: QRCodePositionMulti
*
*	@Brief		获取二维码位置（多个）
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename: 待处理图像路径
*

*
*	@Para [OUT]	int * x：二维码坐标x数组
*
*				int * y：二维码坐标y数组
*
*				int * height：二维码高度数组
*
*				int * width：二维码宽度数组
*
*				char* qrContent：拼接而成的字符串,以‘;’为分隔符，注意初始化时提供足够大的字符串空间
*
*				int & qrNum：二维码数目
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-16
*
*	@Checked	2018-05-26
*/
DllExport int QRCodePositionMulti(const char* filename, int * x, int * y, int * height, int * width, char* qrContent, int & qrNum, int cameraType)
{
	LOG(INFO) << "函数DLL接口：QRCodePositionMulti（多个二维码检测)， 进入";
	int resp = sg_OK;

	// 1. 根据图像路径进行读图
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：QRCodePositionMulti " << "图片路径不对，读图失败";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 检测前对图像畸变校正
	Mat UndistortImg = srcImg.clone();
	
	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：QRCodePositionMulti " << "畸变校正步骤出错";
		return resp;
	}

	// 3. 进行图像中的二维码检测
	vector<QRCodePos> posList;
	vector<string> contentList;

	qrNum = 0;	// 初始化二维码检测数目为零

	resp = Detect_qrcode_multi(UndistortImg, posList, contentList);	// 调用接口进行检测
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：QRCodePositionMulti " << "二维码检测步骤出错";
		return resp;
	}

	qrNum = posList.size();	// 更新二维码检测数目

	string content = "";
	for (size_t i = 0; i < qrNum; i++)
	{
		x[i] = posList[i].startX;
		y[i] = posList[i].startY;
		height[i] = posList[i].height;
		width[i] = posList[i].width;
		content = content + contentList[i] + ";";
	}

	// 复制到返回的字符串数组中
	int buffMaxsize = 200;	// strcpy_s 缓冲长度
	strcpy_s(qrContent, buffMaxsize, content.c_str());


	LOG(INFO) << "函数DLL接口：QRCodePositionMulti（多个二维码检测)，退出";
	return sg_OK;
}



/**
*	@Method		DetectTask（供界面调试）
*
*	@Brief		检测识别任务交互接口.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename：待处理图像路径
*
*				const ROIInfo roi：待处理区域ROI
*
*				const TaskInfo taskinfo: 任务信息
*
*				int cameraType：相机校正选项
*
*	@Para [OUT]	ResultInfo & resultinfo：检测结果
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		在调试界面端，需要在得到结果之后对申请的内存进行释放
*
*	@Create		2018-03-25
*
*	@Desperated	2018-06-04 目前可以以整张图检测然后返回整张图的检测结果
*/
DllExport int DetectTask(const char* filename, const ROIInfo roi, const TaskInfo taskinfo , const char* processedName, ResultInfo & resultinfo, int cameraType)
{
	LOG(INFO) << "函数DLL接口：DetectTask（检测识别接口)，进入";

	int resp = sg_OK;

	// 1. 判空
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：DetectTask " << "图片路径不对，读图失败";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 检测前对图像畸变校正
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：DetectTask " << "畸变校正步骤出错";
		return resp;
	}


	// 3. 取ROI区域进行处理
	Mat image = UndistortImg(Rect(roi.startX, roi.startY, roi.width, roi.height));
	

	// 5. 调用任务分发接口进行检测，同时返回结果
	resp = taskDistributeWithStruct(image,taskinfo,resultinfo);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：DetectTask " << "调用调用任务分发接口进行检测 " << "该步骤出错";
		return resp;
	}

	LOG(INFO) << "函数DLL接口：DetectTask（检测识别接口)，退出";
	return sg_OK;
}



/**
*	@Method		ImgUndistort
*
*	@Brief		校正接口.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename：待处理图像路径
*
*				const ROIInfo roi：待处理区域ROI
*
*				const TaskInfo taskinfo: 任务信息
*
*				const char* processedName：处理结果图像路径（暂时没有）
*
*	@Para [OUT]	ResultInfo & resultinfo：检测结果
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-25
*/
DllExport int ImgUndistort(const char* filename, const char* savePath, const int cameraType)
{
	LOG(INFO) << "函数DLL接口：ImgUndistort（图像畸变校正)，进入";

	int resp = sg_OK;

	// 1. 判空
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：ImgUndistort " << "图片路径不对，读图失败";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 畸变校正
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：ImgUndistort " << "畸变校正步骤出错";
		return resp;
	}

	// 3. 保存至指定路径
	imwrite(savePath, UndistortImg);

	LOG(INFO) << "函数DLL接口：ImgUndistort（图像畸变校正)，退出";
	return resp;
}



/**
*	@Method		findQRcodeinRegion
*
*	@Brief		配置时在指定区域搜索二维码并返回至配置界面
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename：待处理图像路径
*
*				const int cameraType: 焦距选项
*
*				ROIInfo searchArea: 指定的二维码搜索区域
*
*	@Para [OUT]	QRCodeInfo & QRcode： 二维码在整幅图中的位置
*
*				char* qrContent：指定区域二维码的内容
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-27
*/
DllExport int findQRcodeinRegion(const char* filename, const int cameraType, ROIInfo searchArea, QRCodeInfo & QRcode, char* qrContent)
{
	LOG(INFO) << "函数DLL接口：findQRcodeinRegion（搜索区域内二维码），进入";

	int resp = sg_OK;

	// 1. 判空
	Mat srcImg = imread(filename);	//图像判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数DLL接口：findQRcodeinRegion " << "图片路径不对，读图失败，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 畸变校正
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数函数DLL接口：DetectOnece " << "畸变校正步骤出错，退出函数";
		return resp;
	}

	// 3. 获取指定区域图像
	Mat image = UndistortImg(Rect(searchArea.startX, searchArea.startY, searchArea.width, searchArea.height));

	// 4. 进行图像中的二维码检测
	vector<QRCodePos> posList;
	vector<string> contentList;

	resp = Detect_qrcode_multi(image, posList, contentList);	// 调用接口进行检测
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数函数DLL接口：DetectOnece  " << "二维码检测步骤出错";
		return resp;
	}

	if (posList.size() != 1)
	{
		LOG(ERROR) << "函数函数DLL接口：DetectOnece  " << "指定区域检测二维码失败,没检测到或者数目大于一";
		resp = sg_ERROR;
		return resp;
	}

	// 二维码在图中的位置 = 区域位置 + 二维码在区域中位置
	QRcode.startX = posList[0].startX + searchArea.startX;
	QRcode.startY = posList[0].startY + searchArea.startY;
	QRcode.width = posList[0].width;
	QRcode.height = posList[0].height;

	// 复制到返回的字符串数组中
	int buffMaxsize = 200;	// strcpy_s 缓冲长度
	strcpy_s(qrContent, buffMaxsize, contentList[0].c_str());

	LOG(INFO) << "函数DLL接口：findQRcodeinRegion（搜索区域内二维码），退出";
	return resp;
}



/**
*	@Method		drawROIwithXML
*
*	@Brief		根据XML配置文件对任务序列的ROI进行查看，确认ROI无误.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename：待处理图像路径
*
*				const char* xmlPath: 配置文件路径
*
*				const char* savePath：图像保存路径
*
*	@Para [OUT]	None.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
DllExport int drawROIwithXML(const char* filename, const char* xmlPath, const char* savePath)
{
	LOG(INFO) << "函数DLL接口：drawROIwithXML（绘制ROI方框进行查看对不对），进入";

	int resp = sg_OK;

	// 1. 判空
	Mat srcImg = imread(filename);	//图像判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：drawROIwithXML " << "图片路径不对，读图失败，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 调用函数进行绘图
	Mat resultImg;
	resp = drawROIListWithXML(srcImg, xmlPath, resultImg);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIwithXML " << "绘制ROI出错";
		return resp;
	}

	//3. 保存图像
	imwrite(savePath, resultImg);

	LOG(INFO) << "函数DLL接口：drawROIwithXML（绘制ROI方框进行查看对不对），退出";
	return resp;
}



/**
*	@Method		detectWithXML
*
*	@Brief		根据XML文件进行检测
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename：	待处理图像路径
*
*				const char* xmlPath：	配置文件路径
*
*				const int Devnum：		设备编号
*
*				const int updown：		1表示上，2表示下
*
*	@Para [OUT]	char* resultCOntent：处理结果字符串
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
DllExport int detectWithXML(const char* filename, const char* xmlPath, char* resultCOntent, const int Devnum, const int updown)
{
	LOG(INFO) << "函数DLL接口：detectWithXML（根据图像和XML进行检测） ， 进入";

	int resp = sg_OK;

	// 1. 入参判空
	string pathXML = string(xmlPath);
	if (pathXML.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：detectWithXML " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	Mat srcImg = imread(filename, 1);
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：detectWithXML " << "图像入参为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 调用接口进行检测
	vector<string> result(0);
	processXMLTask(srcImg, pathXML, result, Devnum, updown);

	// 3. 整理成字符串数组
	string content = "";

	// 此处从1开始
	for (size_t i =1; i < result.size(); i++)
	{
		if (result[i] != "")
		{
			content = content + result[i] + ";";
		}
		//content = content + result[i] + ";";
	}

	// 复制到返回的字符串数组中
	int buffMaxsize = 200;	// strcpy_s 缓冲长度
	strcpy_s(resultCOntent, buffMaxsize, content.c_str());

	LOG(INFO) << "函数DLL接口：detectWithXML（根据图像和XML进行检测） ， 推出";

	return resp;
}







#include <windows.h> 
#include <time.h>

DllExport int DetectWithResult(const char* filename, const char* xmlPath,  char* dllResult, const int DevNum)
{
	LOG(INFO) << "函数DLL接口：DetectWithResult（根据配置解析结果） ， 进入";

	int resp = sg_OK;

	// 1. 入参判空
	string pathXML = string(xmlPath);
	if (pathXML.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：detectWithXML " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	Mat srcImg = imread(filename, 1);
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：detectWithXML " << "图像入参为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 1. 获取元素个数
	int eleNum = 0;
	resp = getEleNumOptionFromXML(xmlPath, eleNum);

	
	// 2. 遍历进行结果获取和绘制ROI框

	vector<string> resultContent(eleNum+1);

	Mat drawROIImg = srcImg.clone();

	// 2. 加载XML文件
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath);

	if (tinyxml2::XML_SUCCESS != errXml)	// XML加载失败
	{
		LOG(ERROR) << "函数：getDetectListFromXML: XML文件打开失败，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 3. 获取根节点信息
	tinyxml2::XMLElement *root = docXml.RootElement();

	// 4. 对device节点进行遍历
	tinyxml2::XMLElement *device = root->FirstChildElement("device");

	while (device)
	{
		// 1. 获取名字
		tinyxml2::XMLElement *name = device->FirstChildElement("name");

		string deviceName(name->GetText());
		string deviceNameUTF8 = "";
		Convert(deviceName, deviceNameUTF8, CP_UTF8, CP_ACP);

		LOG(INFO) << "XML解析，设备名为： " << deviceNameUTF8;	// 输出信息，防止XML结构出错

		tinyxml2::XMLElement *taskorder = device->FirstChildElement("order");
		int order = atoi(taskorder->GetText());

		tinyxml2::XMLElement *result = device->FirstChildElement("result");
		string resultStr(result->GetText());
		string resultUTF8 = "";
		Convert(resultStr, resultUTF8, CP_UTF8, CP_ACP);
		LOG(INFO) << "XML解析，检测结果为： " << resultUTF8;	// 输出信息，防止XML结构出错

		// 3. roiinfo 
		tinyxml2::XMLElement *roi = device->FirstChildElement("roiinfo");

		tinyxml2::XMLElement *roistartX = roi->FirstChildElement("startX");
		int startX = atoi(roistartX->GetText());

		tinyxml2::XMLElement *roistartY = roi->FirstChildElement("startY");
		int startY = atoi(roistartY->GetText());

		tinyxml2::XMLElement *roiwidth = roi->FirstChildElement("width");
		int width = atoi(roiwidth->GetText());

		tinyxml2::XMLElement *roiheight = roi->FirstChildElement("height");
		int height = atoi(roiheight->GetText());

		// 1. 填充结果
		resultContent[order] = resultUTF8;

		// 2. 绘制方框
		rectangle(drawROIImg, Rect(startX, startY, width, height), Scalar(0, 0, 255), 7);

		// 6. 遍历下一个设备
		device = device->NextSiblingElement();
	}

	// 3. 整理成字符串数组
	string content = "";

	// 此处从1开始
	for (size_t i = 1; i < resultContent.size(); i++)
	{
		if (resultContent[i] != "")
		{
			content = content + resultContent[i] + ";";
		}
		//content = content + result[i] + ";";
	}

	// 复制到返回的字符串数组中
	int buffMaxsize = 200;	// strcpy_s 缓冲长度
	strcpy_s(dllResult, buffMaxsize, content.c_str());

	LOG(INFO) << "函数DLL接口：DetectWithResult（根据图像和XML进行检测） ， 推出";

	string ShanghaiEleSavePath = "设备元素照片/";
	string ROISaveName = ShanghaiEleSavePath  + to_string(DevNum) + "ROI" + ".jpg";
	imwrite(ROISaveName, drawROIImg);

	return resp;

}