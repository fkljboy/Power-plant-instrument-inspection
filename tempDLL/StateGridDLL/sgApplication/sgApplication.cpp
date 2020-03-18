/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgApplication.cpp
*
* 	@Brief	应用层函数.
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
*	1.0		3/24		SHEN		Created.
*
*/ 
#include "sgApplication.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"
#include "../sgCore/sgcore_taskinfo.h"
#include "../sgCore/sgcore_safetyCheck.h"

#include "../sgFunction/sgfunc_transform.h"
#include "../sgFunction/sgfunc_file.h"
#include "../sgFunction/sgfunc_imageio.h"

#include "../sgTask/sgtask_analog.h"
#include "../sgTask/sgtask_knob.h"
#include "../sgTask/sgtask_pointer.h"
#include "../sgTask/sgtask_led.h"
#include "../sgTask/sgtask_qrcode.h"


#include <opencv2\opencv.hpp>
using namespace cv;

// 要求：保存的设备元素照
string ShanghaiEleSavePath = "设备元素照片/";

// 要求：有电显示器图片保存路径
string ShanghaiYoudian = "有电显示器/";

/**
*	@Method		taskDistributeWithStruct
*
*	@Brief		结构体方式任务分发.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg
*
*				const TaskInfo task：任务类型
*
*	@Para [OUT]	ResultInfo * result：返回值，结构体方式传递
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		注意指针返回值需要先申请内存
*
*	@Create		2018-03-25
*
*	@Checked	2018-05-27
*/
int taskDistributeWithStruct(const Mat srcImg, const TaskInfo taskinfo, ResultInfo & resultinfo)
{
	LOG(INFO) << "函数：taskDistributeWithStruct（任务分发接口）， 进入";

	int resp = sg_OK;

	// 1. 图像判空
	
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： taskDisfromStruct" << "  图像为空";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 任务分发
	switch (taskinfo.type)
	{
	case sg_task_analog:
		// 针对模拟指示器，subtype表示模拟指示器的类型
		if (sg_analog_type_circles == taskinfo.subtype || sg_analog_type_twoPanels == taskinfo.subtype ||
			sg_analog_type_onePanel == taskinfo.subtype || sg_analog_type_lights == taskinfo.subtype)
		{
			LOG(INFO) << "函数： taskDisfromStruct" << "  任务分发至：模拟指示器检测";
			resp = Detect_analog(srcImg, taskinfo.subtype, resultinfo.vectorResult);	//多个返回结果在result数组中
			if (resp != sg_OK)
			{
				LOG(ERROR) << "函数： taskDisfromStruct" << "  模拟指示器检测出错";
				return resp;
			}
		}
		else
		{
			LOG(ERROR) << "函数： taskDisfromStruct" << "  任务编码出错，模拟指示器类别不在列表中";
			resp = sg_ERROR;
			return resp;
		}
		break;

	case sg_task_knob:
		// 针对旋钮，subtype应该表示表示旋钮的类型
		if ((sg_knob_type_Square == taskinfo.subtype || sg_knob_type_Rectangle == taskinfo.subtype || sg_knob_type_Circle == taskinfo.subtype))
		{
			LOG(INFO) << "函数： taskDisfromStruct" << "  任务分发至：旋钮检测";
			int resultINT;
			resp = Detect_knob(srcImg, taskinfo.subtype, resultINT);
			if (resp != sg_OK)
			{
				LOG(ERROR) << "函数： taskDisfromStruct" << "  旋钮检测出错";
				return resp;
			}
			resultinfo.result = double(resultINT);
			resultinfo.vectorResult[0] = resultINT;
		}
		else
		{
			LOG(ERROR) << "函数： taskDisfromStruct" << "  任务编码出错，旋钮类别不在列表中";
			resp = sg_ERROR;
			return resp;
		}
		break;

	case sg_task_pointer:
		// 针对指针式仪表，不需要输入参数
		LOG(INFO) << "函数： taskDisfromStruct" << "  任务分发至：指针仪表检测";
		double resultDOUBLE;

		resp = Detect_pointer(srcImg, resultDOUBLE);
		if (resp != sg_OK)
		{
			LOG(ERROR) << "函数： taskDisfromStruct" << "  指针仪表检测出错";
			return resp;
		}
		resultinfo.result = resultDOUBLE;
		resultinfo.vectorResult[0] = (int)resultDOUBLE;

		break;

	case sg_task_led:
		// 针对指示灯
		if (sg_led_type_benderZongCha == taskinfo.subtype || sg_led_type_benderBaoHu == taskinfo.subtype || sg_led_type_benderTongXun == taskinfo.subtype || sg_led_type_YouDian == taskinfo.subtype)
		{
			LOG(INFO) << "函数： taskDisfromStruct" << "  任务分发至：指示灯检测";

			resp = Detect_led(srcImg, taskinfo.subtype, resultinfo.vectorResult);
			if (resp != sg_OK)
			{
				LOG(ERROR) << "函数： taskDisfromStruct" << "  指示灯检测出错";
				return resp;
			}
		}
		else
		{
			LOG(ERROR) << "函数： taskDistribute" << "  任务编码出错，指示灯类别不在列表中";
			resp = sg_ERROR;
			return resp;
		}
		break;

	default:
		LOG(ERROR) << "函数： taskDisfromStruct" << "  任务编码出错，第一位不在列表中";
		resp = sg_ERROR;
		return resp;

		break;
	}


	LOG(INFO) << "函数：taskDistributeWithStruct（任务分发接口）， 退出";

	return resp;
}




/**
*	@Method		detectTask
*
*	@Brief		检测识别任务交互接口,非DLL接口，工程内部接口.
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
*	@Create		2018-05-23
*
*	@Checked	2018-05-27
*/
int detectTask(const Mat srcImg, const ROIInfo roi, const TaskInfo taskinfo, ResultInfo & resultinfo)
{
	LOG(INFO) << "函数：detectTask（检测识别任务交互接口，分发前申请内存） ， 进入";

	int resp = sg_OK;

	// 1. 入参判空
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：detectTask " << "图像入参为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}


	// 2. 取ROI区域进行处理

	// 2.1 对ROI进行区域判断，防止过大
	if ((roi.startX+ roi.width) > srcImg.cols || (roi.startY + roi.height) > srcImg.rows)
	{
		LOG(ERROR) << "函数：detectTask " << "ROI取值出错，" << "图像大小，宽： " << srcImg.cols <<", 高： " << srcImg.rows;
		LOG(ERROR) << "函数：detectTask " << "ROI取值出错，" << "ROI信息，左上角（" << roi.startX << "," << roi.startY << "), 宽：" << roi.width << "，高：" << roi.height;
		resp = sg_ERROR;
		return resp;
	}

	// 2.2 ROI操作
	resp = checkRectInside(srcImg, Rect(roi.startX, roi.startY, roi.width, roi.height));
	if (resp != sg_OK)
	{
		LOG(ERROR) << "ROI取值出错！";
		return sg_ERROR;
	}
	Mat image = srcImg(Rect(roi.startX, roi.startY, roi.width, roi.height));

	// 3. 如果是多值结果的，申请内存
	//if (sg_task_analog == taskinfo.type || sg_task_led == taskinfo.type)
	//{
	//	resultinfo.arrayResult = (int *)calloc(taskinfo.number, sizeof(int));
	//}

	// 4. 调用任务分发接口进行检测
	resp = taskDistributeWithStruct(image, taskinfo, resultinfo);
	if (resp != sg_OK)
	{
		LOG(INFO) << "函数：detectTask（检测识别任务交互接口） ，调用任务分发接口出错,退出函数";
		return resp;
	}


	LOG(INFO) << "函数：detectTask（检测识别任务交互接口，分发前申请内存） ， 退出";
	return resp;
}




/**
*	@Method		processXMLTask
*
*	@Brief		从XML中进行XML解析，同时进行检测
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath：XML配置文件路径
*
*				const Mat srcImg: 待处理图像
*
*	@Para [OUT]	string & result：检测结果(检测结果组成的字符串数组)
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		二维码内容即代表需要检测的柜面，二维码其实应当与XML是匹配的
*
*	@Create		2018-05-23
*/
int processXMLTask(const Mat srcImg, const string xmlPath, vector<string> & resultArr, const int DevNum, const int updown)
{
	LOG(INFO) << "函数：processXMLTask（从XML中进行XML解析，同时进行检测） ， 进入";

	int resp = sg_OK;

	// 1. 入参判空
	if (xmlPath.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：processXMLTask " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：processXMLTask " << "图像入参为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 获取XML中的校正选项
	int cameraType = sg_Camera_NoOption;
	resp = getCameraOptionFromXML(xmlPath, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask  " << "没有找到正确的校正选项";
		return resp;
	}

	// 3. 畸变校正
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "畸变校正步骤出错，退出函数";
		return resp;
	}

	// 4. 解析XML文件，获取配置时二维码的坐标及大小，以及二维码内容
	QRCodePos qrPosOrigin;
	string QRContent;
	resp = getQRPosOriginFromXML(xmlPath, qrPosOrigin, QRContent);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "没有找到二维码内容，退出函数";
		return resp;
	}

	// 5. 根据指定二维码内存搜索图中区域
	QRCodePos QRPosNow;
	resp = Search_qrcode(UndistortImg, QRContent, QRPosNow);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "没有找到指定二维码，退出函数";
		return resp;
	}

	// 6. 解析XML文件，获取任务序列
	vector<DetectInfo> detectList;

	resp = getDetectListFromXML(xmlPath, detectList);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "XML解析失败，退出函数";
		return resp;
	}

	// 7. 根据任务序列，更新ROI信息（直接获取或者根据二维码换算，两种类型）
	resp = getROIArrayandUpdate(detectList, true, QRPosNow, qrPosOrigin);	// 记得打开二维码转换开关
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "获取ROI数组时失败，退出函数";
		return resp;
	}

	// 8. 绘制ROI数组（该步骤可跳过）和 保存各个ROI区域
	Mat drawROIImg = UndistortImg.clone();
	resp = drawROIArray(drawROIImg, detectList);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask " << "绘制ROI数组时失败，退出函数";
		return resp;
	}
	string ROISaveName = ShanghaiEleSavePath + "Dev" + to_string(DevNum) + "_" + to_string(updown) + "ROI" + ".jpg";
	imwrite(ROISaveName, drawROIImg);

	 //8.1 保存元素图片，注意序号，模拟指示器有特殊需求
	resp = saveElementROIimg(detectList, UndistortImg, DevNum);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask  " << "保存元素图片出错";
		return resp;
	}

	// 9. 获取XML中电柜数目（定义数组供后续保存结果）
	int eleNum = 0;
	resp = getEleNumOptionFromXML(xmlPath, eleNum);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：processXMLTask  " << "没有找到正确的开关柜元素数目";
		return resp;
	}

	vector<string> resultArray(eleNum + 1);	//定义为字符串数组，结果按照order(第0个，没有)保存

	// 10. 遍历执行任务序列
	for (size_t i = 0; i < detectList.size(); i++)
	{
		ROIInfo roiinfo = detectList[i].roiinfo;
		TaskInfo taskinfo = detectList[i].taskinfo;
		detectList[i].resultinfo.vectorResult = vector<int>(taskinfo.number);	//使用vectorResult作为结果存储

		// TODO：此处涉及resultinfo的内存申请，注意释放
		resp = detectTask(UndistortImg, roiinfo, taskinfo, detectList[i].resultinfo);

		if (resp != sg_OK)
		{
			if (sg_task_analog == taskinfo.type)
			{
				for (int j = 0; j <taskinfo.number; j++)	// 模拟指示器结果保存，按元素分别保存
				{
					resultArray[taskinfo.order + j] = "检测失败"; // 按顺序保存
				}
			}
			else
			{
				resultArray[taskinfo.order] = "检测失败";
			}

			continue;	// 检测失败则跳过此次检测
		}

		ResultInfo resultinfo = detectList[i].resultinfo;


		if (taskinfo.type == sg_task_pointer)	// 指针结果保存
		{
			string resultStr = to_string(resultinfo.result);

			resultArray[taskinfo.order] = resultStr;

			LOG(INFO) << "指针检测结果为：" << resultStr;
		}
		else if (taskinfo.type == sg_task_analog)
		{
			for (int j = 0; j < taskinfo.number; j++)	// 模拟指示器结果保存，按元素分别保存
			{
				string resultStr = resultinfo.vectorResult[j] == sg_analog_Connect ? "接入" : "断开";
				resultArray[taskinfo.order + j] = resultStr; // 按顺序保存

				LOG(INFO) << "模拟指示器检测结果为：" << resultStr;
			}
		}
		else if (taskinfo.type == sg_task_knob)	// 旋钮结果保存，按元素分别保存
		{
			string result = detectList[i].getKnobInfo();

			resultArray[taskinfo.order] = result;

			LOG(INFO) << "旋钮的检测结果为： " << result;

		}
		else if (taskinfo.type == sg_task_led)	// 指示灯结果保存
		{
			// 此处会造成内存泄漏
			char* result = new char[taskinfo.number+1];	//TODO: 注意内存释放

			for (size_t j = 0; j < taskinfo.number; j++)
			{
				char str = (resultinfo.vectorResult[j] == sg_led_open ? '1' : '0');
				result[j] = str;
				LOG(INFO) << "指示灯检测结果为：" << resultinfo.vectorResult[j];
				LOG(INFO) << "指示灯检测结果为：" << (resultinfo.vectorResult[j] == sg_led_open ? "亮" : "灭");
			}

			result[taskinfo.number] = '\0';
			resultArray[taskinfo.order] = string(result);	

			delete[] result;	// 释放内存
		}

	}


	// 赋给返回变量
	resultArr = resultArray;

	LOG(INFO) << "函数：processXMLTask（从XML中进行XML解析，同时进行检测） ， 退出";
	return resp;
}




/**
*	@Method		saveElementROIimg
*
*	@Brief		根据任务列表进行元素的保存
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	vector<DetectInfo> & detectList：任务序列
*
*				const Mat srcImg：待处理原图
*
*				const int DevNum：柜子编号，用于命名
*
*	@Para [OUT]	None.
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-06-04
*/
int saveElementROIimg(const vector<DetectInfo> detectList, const Mat srcImg, const int DevNum)
{
	int resp = sg_OK;

	// 1. 入参判断
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：saveElementROIimg " << "图像入参为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	if (detectList.size() == 0)	// 任务序列为0，则返回错误
	{
		LOG(ERROR) << "函数：saveElementROIimg " << "XML解析的任务序列长度为0！，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 遍历绘图并保存
	for (size_t i = 0; i < detectList.size(); i++)
	{
		Rect saveRoi = Rect(detectList[i].roiinfo.startX, detectList[i].roiinfo.startY, detectList[i].roiinfo.width, detectList[i].roiinfo.height);

		// 非模拟指示器保存这个元素
		if (detectList[i].taskinfo.type != sg_task_analog)	
		{
			string saveName = ShanghaiEleSavePath + "Dev_" + to_string(DevNum) + "_" + to_string(detectList[i].taskinfo.order) + ".jpg";
			imwrite(saveName, srcImg(saveRoi));
		}
		else  // 模拟指示器进行每个元素的绘框
		{
			vector<Rect> rectlist(4);
			rectlist[0] = Rect(68, 13, 130, 115);
			rectlist[1] = Rect(64, 66, 147, 115);
			rectlist[2] = Rect(10, 164, 111, 106);
			rectlist[3] = Rect(74, 42, 129, 116);
			Mat img = srcImg(saveRoi);
			resize(img, img, Size(220, 400));
			if (detectList[i].taskinfo.number == 1)
			{
				Mat draw = img.clone();
				rectangle(draw, rectlist[3], Scalar(0, 0, 255), 7);
				string saveName = ShanghaiEleSavePath + "Dev_" + to_string(DevNum) + "_" + to_string(detectList[i].taskinfo.order) + ".jpg";
				imwrite(saveName, draw);
			}
			else
			{
				for (size_t j = 0; j < detectList[i].taskinfo.number; j++)
				{
					Mat draw = img.clone();
					rectangle(draw, rectlist[j], Scalar(0, 0, 255), 7);
					string saveName = ShanghaiEleSavePath + "Dev_" + to_string(DevNum) + "_" + to_string(detectList[i].taskinfo.order + j) + ".jpg";
					imwrite(saveName, draw);
				}
			}
		}
	}

	return resp;
}


/**
*	@Method		getROIArrayandUpdate
*
*	@Brief		从任务列表中获取ROI信息，如要使用二维码定位则进行换算
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	list<DetectInfo> & detectList：任务序列
*
*				bool withQR: 是否需要根据二维码进行换算ROI
*
*				QRCodePos qrPos：二维码的坐标及大小
*
*	@Para [OUT]	list<DetectInfo> & detectList： 如需根据ROI换算，则任务序列中的ROI也进行对应换算
*
*				ROIInfo *roiarray：ROI数组
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-25
*
*	@Updated	2018-05-30: 改用相对位置计算
*/
int getROIArrayandUpdate(vector<DetectInfo> & detectList, bool withQR, QRCodePos qrPosNow, QRCodePos qrPosOrigin)
{
	LOG(INFO) << "函数：getROIArrayandUpdate（任务列表中获取和更新ROI数组） ， 进入";

	int resp = sg_OK;

	if (detectList.size() == 0)	// 任务序列为0，则返回错误
	{
		LOG(ERROR) << "函数：getROIArray " << "XML解析的任务序列长度为0！，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	if (withQR)	// 根据二维码来重新确认ROI信息
	{
		//以左上角为基准的
		//是否利用放大缩小比例
		double widthscale = qrPosNow.width * 1.0 / qrPosOrigin.width; //获取倍数
		double heightscale = qrPosNow.height * 1.0 / qrPosOrigin.height; //获取倍数

		//不利用二维码缩放比
		widthscale = 1.0;
		heightscale = 1.0;


		for (size_t i = 0; i < detectList.size(); i++)
		{
			//int distXOrigin = detectList[i].roiinfo.startX - qrPosOrigin.startX;
			//int distYOrigin = detectList[i].roiinfo.startY - qrPosOrigin.startY;
			int distXOrigin = detectList[i].roiinfo.distX;
			int distYOrigin = detectList[i].roiinfo.distY;

			int newDistX = (int)(distXOrigin * widthscale);
			int newDistY = (int)(distYOrigin * heightscale);

			int newstartX = qrPosNow.startX + newDistX;
			int newstartY = qrPosNow.startY + newDistY;

			int newheight = (int)(detectList[i].roiinfo.height * heightscale);
			int newwidth = (int)(detectList[i].roiinfo.width * widthscale);


			ROIInfo tempROI = ROIInfo(newstartX,newstartY, newDistX, newDistY, newwidth, newheight);

			// 同时更新到任务序列中
			detectList[i].roiinfo = tempROI;
		}
	}

	LOG(INFO) << "函数：getROIArrayandUpdate（任务列表中获取和更新ROI数组） ， 退出";
	return sg_OK;
}






/**
*	@Method		ReleaseMemoryINT
*
*	@Brief		在C++端释放int数组内存.
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

bool ReleaseMemoryINT(int* buf)
{
	if (buf == NULL)
		return false;

	free(buf);
	buf = NULL;
	return true;
}




/**
*	@Method		drawROIListWithXML
*
*	@Brief		根据XML配置文件对任务序列的ROI进行查看，确认ROI无误.
*
*	@Para [IN]	const Mat srcImg： 待处理图像.
*
*				const string xmlPath： XML文件路径
*
*	@Para [OUT]	Mat & resultImg： 绘制完成的图像
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/

int drawROIListWithXML(const Mat srcImg, const string xmlPath, Mat & resultImg)
{
	LOG(INFO) << "函数：drawROIListWithXML（绘制ROI方框进行查看对不对），进入";

	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "图片路径不对，读图失败，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 获取XML中的校正选项
	int cameraType = sg_Camera_NoOption;
	resp = getCameraOptionFromXML(xmlPath, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML  " << "没有找到正确的校正选项";
		return resp;
	}


	// 3. 畸变校正
	resultImg = srcImg.clone();

	resp = undistortImg(srcImg, resultImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "畸变校正步骤出错，退出函数";
		return resp;
	}

	// 4. 解析XML文件，获取配置时二维码的坐标及大小，以及二维码内容
	QRCodePos qrPosOrigin;
	string QRContent;
	resp = getQRPosOriginFromXML(xmlPath, qrPosOrigin, QRContent);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "没有找到二维码内容，退出函数";
		return resp;
	}

	// 5. 根据指定二维码内存搜索图中区域
	QRCodePos QRPosNow;
	resp = Search_qrcode(resultImg, QRContent, QRPosNow);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "没有找到指定二维码，退出函数";
		return resp;
	}

	// 6. 解析XML文件，获取任务序列
	vector<DetectInfo> detectList;
	resp = getDetectListFromXML(xmlPath, detectList);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "XML解析失败，退出函数";
		return resp;
	}

	// 7. 根据任务序列，获取ROI数组（直接获取或者根据二维码换算，两种类型）
	vector<ROIInfo> ROIArray(detectList.size());
	resp = getROIArrayandUpdate(detectList, true, QRPosNow, qrPosOrigin);	// 记得打开二维码转换开关
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "获取ROI数组时失败，退出函数";
		return resp;
	}

	// 8. 绘制ROI数组
	resp = drawROIArray(resultImg, detectList);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：drawROIListWithXML " << "绘制ROI数组时失败，退出函数";
		return resp;
	}

	LOG(INFO) << "函数：drawROIListWithXML（绘制ROI方框进行查看对不对），退出";
	return resp;
}