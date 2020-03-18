/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgfunc_file.cpp
*
* 	@Brief	文件相关.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-05-23
*
*	@MethodList
*		1. int saveCameraInfo(const string filename,const Mat Intrix, const Mat  disCoeff, const string CameraName)
*		
*		2. 
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		5/23		SHNE		Created.
*
*/
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <time.h>
#include "sgfunc_file.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"

#include "../sgCore/sgcore_taskinfo.h"


// 编码转换函数
// 可能会出现内存溢出问题
// 参考链接：http://rexyen.pixnet.net/blog/post/39515440-%E7%A8%8B%E5%BC%8F---%E4%B8%80%E4%BA%9B%E4%B8%8D%E5%A4%AA%E5%AE%B9%E6%98%93%E7%99%BC%E7%8F%BE%E7%9A%84-bug-....
void Convert(const string stringIN, string & strinyOut, int sourceCodepage, int targetCodepage)
{
	const char* strIn = stringIN.c_str();
	char *strOut = new char[200];

	int len = strlen(strIn);
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL);
	pTargetData = new BYTE[targetLen + 1];
	memset(pTargetData, 0, targetLen + 1);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL);

	strcpy_s(strOut,200, (char*)pTargetData);

	strinyOut = string(strOut);

	delete[] strOut;	// TODO: 此处可能会引发内存溢出错误 heap corruption，申请大小尽量定的大一些

	delete pUnicode;
	delete pTargetData;
}


/**
*	@Method		saveCameraInfo
*
*	@Brief		保存相机信息到文件
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string filename：yaml文件路径
*
*				const Mat Intrix：相机内参矩阵
*
*				const Mat  disCoeff：相机外参矩阵
*
*				const string CameraName：相机标志信息，便于文件查看
*
*	@Para [OUT]	无
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*/
int saveCameraInfo(const string filename,const Mat Intrix, const Mat  disCoeff, const string CameraName)
{
	LOG(INFO) << "函数：saveCameraInfo（保存畸变系数）， 进入";

	int resp = sg_OK;

	if (filename.empty())
	{
		LOG(ERROR) << "函数：saveCameraInfo: 文件名为空";
		resp = sg_ERROR;
		return resp;
	}
	if (Intrix.empty() || disCoeff.empty())
	{
		LOG(ERROR) << "函数：saveCameraInfo: 参数矩阵为空";
		resp = sg_ERROR;
		return resp;
	}

	

	// 写模式
	FileStorage fs(filename, FileStorage::WRITE);	

	// 写入相机信息
	fs << "CameraNameOrType" << CameraName;

	// 获取写入时间
	time_t rawtime;
	time(&rawtime);
	fs << "CalibrateDate" << asctime(localtime(&rawtime));


	// 写入内参和畸变系数
	fs << "CameraIntrixMatrix" << Intrix << "CameraDistortionCoeff" << disCoeff;

	// 释放文件指针
	fs.release();

	LOG(INFO) << "相机文件写入成功： " << CameraName << " ,路径： " << filename;

	LOG(INFO) << "函数：saveCameraInfo（保存畸变系数）， 退出";
	return resp;
}



/**
*	@Method		readCameraInfo
*
*	@Brief		从文件读取
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string filename：yaml文件路径
*
*	@Para [OUT]	Mat Intrix：相机内参矩阵
*
*				Mat  disCoeff：相机外参矩阵
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*/
int readCameraInfo(const string filename, Mat & Intrix, Mat  & disCoeff)
{
	LOG(INFO) << "函数：readCameraInfo（读取畸变系数）， 进入";

	int resp = sg_OK;

	if (filename.empty())
	{
		LOG(ERROR) << "函数：saveCameraInfo: 文件名为空";
		resp = sg_ERROR;
		return resp;
	}

	// 读模式
	FileStorage fs(filename, FileStorage::READ);

	// 写入内参和畸变系数
	fs["CameraIntrixMatrix"] >> Intrix;
	fs["CameraDistortionCoeff"] >> disCoeff;

	LOG(INFO) << "相机文件读取成功";
	LOG(INFO) << "CameraIntrixMatrix 相机内参" << Intrix;
	LOG(INFO) << "CameraDistortionCoeff 畸变系数" << Intrix;

	// 释放文件指针
	fs.release();

	LOG(INFO) << "函数：readCameraInfo（读取畸变系数）， 退出";
	return resp;
}



/**
*	@Method		getDetectListFromXML
*
*	@Brief		从XML文件分析任务队列
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath： XML配置文件路径
*
*	@Para [OUT]	list<DetectInfo> & detectList
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-24
*
*	@Checked	2018-05-26
*/
int getDetectListFromXML(const string xmlPath, vector<DetectInfo> & detectList)
{
	LOG(INFO) << "函数：getDetectListFromXML（从XML中获取任务队列）， 进入";

	int resp = sg_OK;

	// 1. 判空
	if (xmlPath.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：processXMLTask " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 加载XML文件
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath.c_str());

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
		string deviceNameUTF8="";
		Convert(deviceName, deviceNameUTF8, CP_UTF8, CP_ACP);

		//LOG(INFO) << "XML解析，设备名为： " << deviceName;	// 输出信息，防止XML结构出错
		LOG(INFO) << "XML解析，设备名为： " << deviceNameUTF8;	// 输出信息，防止XML结构出错

		// 2. taskinfo 
		tinyxml2::XMLElement *task = device->FirstChildElement("taskinfo");

		tinyxml2::XMLElement *tasktype = task->FirstChildElement("type");
		int type = atoi(tasktype->GetText());

		tinyxml2::XMLElement *tasksubtype = task->FirstChildElement("subtype");
		int subtype = atoi(tasksubtype->GetText());

		tinyxml2::XMLElement *tasknumber = task->FirstChildElement("number");
		int number = atoi(tasknumber->GetText());

		tinyxml2::XMLElement *taskorder = task->FirstChildElement("order");
		int order = atoi(taskorder->GetText());

		LOG(INFO) << "XML解析，任务信息为： " << "type: " << type << ", subtype: "<< subtype << ", number "<< number;	// 输出信息，防止XML结构出错

		TaskInfo taskinfo = TaskInfo(type, subtype, number,order);

		// 3. roiinfo 
		tinyxml2::XMLElement *roi = device->FirstChildElement("roiinfo");

		tinyxml2::XMLElement *roistartX = roi->FirstChildElement("startX");
		int startX = atoi(roistartX->GetText());

		tinyxml2::XMLElement *roistartY = roi->FirstChildElement("startY");
		int startY = atoi(roistartY->GetText());

		tinyxml2::XMLElement *roidisX = roi->FirstChildElement("distX");
		int disx = atoi(roidisX->GetText());

		tinyxml2::XMLElement *roidisY = roi->FirstChildElement("distY");
		int disy = atoi(roidisY->GetText());

		tinyxml2::XMLElement *roiwidth = roi->FirstChildElement("width");
		int width = atoi(roiwidth->GetText());

		tinyxml2::XMLElement *roiheight = roi->FirstChildElement("height");
		int height = atoi(roiheight->GetText());

		LOG(INFO) << "XML解析，ROI信息为： " << "startX: " << startX << ", startY: " << startY << "distX: " << disx << ", distY: " << disy <<  ", width" << width << ", height " << height;	// 输出信息，防止XML结构出错

		ROIInfo roiinfo = ROIInfo(startX, startY,disx, disy, width, height);

		

		// 5. 构造语义转换对象（针对旋钮）
		knob_refer KnobRefer = knob_refer();	//对于其他类别为空

		if (taskinfo.type == sg_task_knob)
		{
			tinyxml2::XMLElement *uintinfo = device->FirstChildElement("unitinfo");	// 找到unitinfo节点，然后遍历
			tinyxml2::XMLElement *stall = uintinfo->FirstChildElement("stall");
			while (stall)
			{
				tinyxml2::XMLElement *rangeLow = stall->FirstChildElement("rangeLow");
				int min = atoi(rangeLow->GetText());

				tinyxml2::XMLElement *rangeHigh = stall->FirstChildElement("rangeHigh");
				int max = atoi(rangeHigh->GetText());

				tinyxml2::XMLElement *context = stall->FirstChildElement("context");
				string contextStr = context->GetText();
				string contextStrUTF8 = "";
				Convert(contextStr, contextStrUTF8, CP_UTF8, CP_ACP);


				knobStall knobstall = knobStall(min, max, contextStrUTF8);
				KnobRefer.knobs.push_back(knobstall);

				stall = stall->NextSiblingElement();
			}
		}
		
		// 4. 构造DetectInfo
		DetectInfo detectinfo(deviceNameUTF8, roiinfo, taskinfo, KnobRefer);

		// 5. 新任务添入列表
		detectList.push_back(detectinfo);

		// 6. 遍历下一个设备
		device = device->NextSiblingElement();	
	}

	// 5. 判断任务队列是否为零
	if (detectList.size() == 0)
	{
		LOG(ERROR) << "函数：getDetectListFromXML " << "XML解析的任务序列长度为0！，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	LOG(INFO) << "函数：getDetectListFromXML（从XML中获取任务队列）， 退出";
	return resp;
}



/**
*	@Method		getQRPosOriginFromXML
*
*	@Brief		从XML文件找到配置时的二维码位置信息
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath： XML配置文件路径
*
*	@Para [OUT]	QRCodePos QRPos：二维码位置信息
*
*				string & qrContent: 二维码内容
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-25
*
*	@Checked	2018-05-26
*
*	@Modified	2018-05-30
*/
int getQRPosOriginFromXML(const string xmlPath, QRCodePos & QRPos, string & qrContent)
{
	LOG(INFO) << "函数：getDetectListFromXML（从XML中获取任务队列）， 进入";

	int resp = sg_OK;

	// 1. 判空
	if (xmlPath.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：processXMLTask " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 加载XML文件
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath.c_str());

	if (tinyxml2::XML_SUCCESS != errXml)	// XML加载失败
	{
		LOG(ERROR) << "函数：getDetectListFromXML: XML文件打开失败，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 3. 获取根节点信息
	tinyxml2::XMLElement *root = docXml.RootElement();

	// 4. 获取QRCODE节点（存有二维码内容）
	tinyxml2::XMLElement *qrcode = root->FirstChildElement("QRCODE");

	if (!qrcode)	// 如果没有该节点
	{
		LOG(ERROR) << "函数：getQRPosOriginFromXML: 配置文件中没有二维码相关信息，退出函数";
		resp = sg_ERROR;
		return resp;
	}
		
	// 5. 根据节点信息得到QRCodePos
	tinyxml2::XMLElement *roistartX = qrcode->FirstChildElement("startX");
	int startX = atoi(roistartX->GetText());

	tinyxml2::XMLElement *roistartY = qrcode->FirstChildElement("startY");
	int startY = atoi(roistartY->GetText());

	tinyxml2::XMLElement *roiwidth = qrcode->FirstChildElement("width");
	int width = atoi(roiwidth->GetText());

	tinyxml2::XMLElement *roiheight = qrcode->FirstChildElement("height");
	int height = atoi(roiheight->GetText());

	// 获取二维码内容
	tinyxml2::XMLElement *content = qrcode->FirstChildElement("content");
	qrContent = content->GetText();

	QRPos.startX = startX;
	QRPos.startY = startY;
	QRPos.width = width;
	QRPos.height = height;

	LOG(INFO) << "函数：getQRPosOriginFromXML: 配置时二维码区域为 x=" << startX << " y= " << startY << " width= " << width << " height= " << height;		// 输出信息，防止XML结构出错
	LOG(INFO) << "函数：getQRPosOriginFromXML: 配置时二维码内容为： " << qrContent;

	return resp;
}




/**
*	@Method		createXML
*
*	@Brief		创建XML文件
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath： XML配置文件路径
*
*	@Para [OUT] 
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-24
*/
int createXML(const string xmlPath)
{
	if (xmlPath.empty())
	{
		LOG(ERROR) << "函数：getDetectListFromXML: 文件名为空";
		return sg_ERROR;
	}

	int resp = sg_OK;

	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";

	tinyxml2::XMLDocument doc;

	doc.Parse(declaration);//会覆盖xml所有内容

	resp = doc.SaveFile(xmlPath.c_str());	//保存文件
	if (resp != tinyxml2::XML_SUCCESS)
	{
		LOG(ERROR) << "函数：createXML: 文件创建失败";
		return resp;
	}

	return resp;
}







/**
*	@Method		getCameraOptionFromXML
*
*	@Brief		从XML中获取校正选项
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath： XML配置文件路径
*
*	@Para [OUT]	int & cameraType: 相机配置选项
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
int getCameraOptionFromXML(const string xmlPath, int & cameraType)
{
	LOG(INFO) << "函数：getCameraOptionFromXML（从XML中获取校正选项）， 进入";

	int resp = sg_OK;

	// 1. 判空
	if (xmlPath.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：processXMLTask " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 加载XML文件
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath.c_str());

	if (tinyxml2::XML_SUCCESS != errXml)	// XML加载失败
	{
		LOG(ERROR) << "函数：getCameraOptionFromXML: XML中获取校正选项，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 3. 获取根节点信息
	tinyxml2::XMLElement *root = docXml.RootElement();

	// 4. 获取INFO节点（存有校正选项）
	tinyxml2::XMLElement *info = root->FirstChildElement("info");

	if (!info)	// 如果没有该节点
	{
		LOG(ERROR) << "函数：getCameraOptionFromXML: 配置文件中没有相关信息，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 5. 根据节点信息得到side信息
	tinyxml2::XMLElement *side = info->FirstChildElement("side");
	string sidestr = side->GetText();

	if (sidestr == "NearFace")
	{
		cameraType = sg_Camera_Near;
	}
	else if (sidestr == "FarFace")
	{
		cameraType = sg_Camera_Far;
	}
	else
	{
		cameraType = sg_Camera_NoOption;
		LOG(ERROR) << "函数：getCameraOptionFromXML: 没有找到正确配置，退出函数";
		resp = sg_Camera_OptionFail;
		return resp;
	}

	return resp;

}






/**
*	@Method		getEleNumOptionFromXML
*
*	@Brief		从XML中获取开关柜元素数目
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const string xmlPath： XML配置文件路径
*
*	@Para [OUT]	int & elenum: 开关柜元素数目
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
int getEleNumOptionFromXML(const string xmlPath, int & elenum)
{
	LOG(INFO) << "函数：getEleNumOptionFromXML（从XML中获取开关柜元素数目）， 进入";

	int resp = sg_OK;

	// 1. 判空
	if (xmlPath.empty())	// XML文件路径判空
	{
		LOG(ERROR) << "函数：getEleNumOptionFromXML " << "XML文件路径为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 加载XML文件
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath.c_str());

	if (tinyxml2::XML_SUCCESS != errXml)	// XML加载失败
	{
		LOG(ERROR) << "函数：getEleNumOptionFromXML: XML中获取校正选项，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 3. 获取根节点信息
	tinyxml2::XMLElement *root = docXml.RootElement();

	// 4. 获取INFO节点（存有校正选项）
	tinyxml2::XMLElement *info = root->FirstChildElement("info");

	if (!info)	// 如果没有该节点
	{
		LOG(ERROR) << "函数：getEleNumOptionFromXML: 配置文件中没有相关信息，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 5. 根据节点信息得到itemNum信息
	tinyxml2::XMLElement *elen = info->FirstChildElement("itemNum");
	if (!elen)	// 如果没有该节点
	{
		LOG(ERROR) << "函数：getEleNumOptionFromXML: 配置文件中没有开关柜元素数目，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	elenum = atoi(elen->GetText());
	LOG(INFO) << "函数：getEleNumOptionFromXML: 开关柜数目为：" << elenum;

	return resp;

}