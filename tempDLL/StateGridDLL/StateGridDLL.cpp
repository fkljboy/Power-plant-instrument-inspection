/*
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	StateGridDLL.cpp
*
* 	@Brief	����DLLӦ�ó���ĵ�������.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15 
*
*	@MethodList
*			1.	���ʶ�����񽻻��ӿ�
*			1.	DllExport int DetectTask(const char* filename, const ROIInfo roi, const TaskInfo taskinfo , const char* processedName, ResultInfo & resultinfo)
*
*			2.	����ROI������Ʒ��� DLL�ӿ�.
*			2.	DllExport int DrawROIArray(const char* filename, const ROIInfo ROIArray[], const char* processedName)
*
*			3.	��ʼ��glog��־ϵͳ
*			3.	DllExport void GoogleGlogInit(char* exefilename)
*
*			4.	�ر�glog��־ϵͳ
*			4.	DllExport void GoogleGlogShutdown()
*			
*			5.	��C++���ͷ��ڴ�.
*			5.	DllExport bool ReleaseMemoryFromC(unsigned char* buf)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		Created
*	2.0		3/28		SHEN		���������ӿڳ���
*	3.0		5/27		SHEN		�½ӿ�����
*
*/ 


//���嵼��DLL��д
#define DllExport extern "C" __declspec(dllexport)

#include "sgApplication/sgApplication.h"

#include "sgcore/sgcore_def.h"
#include "sgCore/sgcore_log.h"

#include "sgTask/sgtask_qrcode.h"
#include "sgFunction/sgfunc_transform.h"
#include "sgFunction/sgfunc_file.h"

#include <opencv2\opencv.hpp>
using namespace cv;


const char* glogLogDir = "Ѳ����־/ʶ����־";

/**
*	@Method		GoogleGlogInit
*
*	@Brief		��ʼ��glog��־ϵͳ.
*
*	@Para [IN]	char* exefilename�� ���г�����
*
*				const char* glogDir�� ��־����·��
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		������־�ļ�����Ŀ¼�����Ŀ¼�������Ѿ����ڵģ�������������־�ļ���
*
*				�����ڳ�ʼ����֮ǰ���á�
*
*				���·���������Debug��.exe�����·��
*
*	@Create		2018-03-15
*
*	@Checked	2018-05-26
*/
DllExport void GoogleGlogInit(const char* exefilename, const char* glogDir)
{
	LOG(INFO) << "����DLL�ӿڣ�GoogleGlogInit��Glog��־ϵͳ��ʼ��)�� ����";

	glogInit(exefilename, glogDir);

	LOG(INFO) << "����DLL�ӿڣ�GoogleGlogInit��Glog��־ϵͳ��ʼ��)�� �˳�";
}


/**
*	@Method		GoogleGlogShutdown
*
*	@Brief		�ر�glog��־ϵͳ��־ϵͳ.
*
*	@Para [IN]	None.
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		�������н���ʱ������ر�glog�⣬������ڴ����.
*
*	@Create		2018-03-15
*
*	@Checked	2018-05-26
*/
DllExport void GoogleGlogShutdown()
{
	LOG(INFO) << "����DLL�ӿڣ�GoogleGlogShutdown��Glog��־ϵͳ��������)�� ����";

	glogShutdown();

	LOG(INFO) << "����DLL�ӿڣ�GoogleGlogShutdown��Glog��־ϵͳ��������)�� �˳�";

	
}



/**
*	@Method		GoogleGlogInitShanghai
*
*	@Brief		��ʼ��glog��־ϵͳ.�̶����·��.
*
*	@Para [IN]	char* exefilename�� ���г�����
*
*	@Para [OUT]	None.
*
*	@Return		None
*
*  	@Note		�������н���ʱ������ر�glog�⣬������ڴ����.
*
*	@Create		2018-05-31
*/
DllExport void GoogleGlogInitShanghai(const char* exefilename)
{
	glogInit(exefilename, glogLogDir);

	LOG(INFO) << "����DLL�ӿڣ�GoogleGlogInit��Glog��־ϵͳ��ʼ��)";
}



/**
*	@Method		ReleaseMemoryFromC
*
*	@Brief		��C++���ͷ��ڴ�.
*
*	@Para [IN]	unsigned char* buf��	ImageInfo.data����.
*
*	@Para [OUT]	None.
*
*	@Return		bool:
*				- true:		�ɹ�
*				- false:	ʧ��
*
*  	@Note		C#���÷�ʽ��
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
*	@Method		DLL: DrawROIArray����������ԣ�
*
*	@Brief		����ROI������Ʒ��� DLL�ӿ�.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename�� ����ͼ��·��
*
*				const ROIInfo ROIArray[] �� ROI����
*
*				const char* processedName������ͼ�񱣴�·��
*
*	@Para [OUT]	��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-24
*
*	@Desperated	2018-06-03	ִ�й�����ʵ����ROI�Ļ�ͼ��
*/
DllExport int DrawROIArray(const char* filename, const ROIInfo ROIArray[], const int num, const char* processedName, QRCodeInfo & qrcodeinfo, int cameraType)
{
	LOG(INFO) << "����DLL�ӿڣ�DrawROIArray������ROI������Ʒ��� DLL�ӿ�)�� ����";

	int resp = sg_OK;

	// 1. ��ͼ����μ��
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "������DrawROIArray " << "ͼƬ·�����ԣ���ͼʧ��";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ����У��
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������DrawROIArray " << "����У���������";
		return resp;
	}

	// 3. �����������ROI
	for (int i = 0; i < num; i++)
	{
		rectangle(UndistortImg, Rect(ROIArray[i].startX,ROIArray[i].startY,ROIArray[i].width,ROIArray[i].height), Scalar(0, 0, 255), 7);
	}

	// 4. ������ָ��·��
	imwrite(processedName, UndistortImg);
	LOG(INFO) << "����DLL�ӿڣ�DrawROIArray���ѱ�����·����" << processedName;

	LOG(INFO) << "����DLL�ӿڣ�DrawROIArray������ROI������Ʒ��� DLL�ӿ�)�� �˳�";
	return resp;
}



/**
*	@Method		DLL: QRCodePositionMulti
*
*	@Brief		��ȡ��ά��λ�ã������
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename: ������ͼ��·��
*

*
*	@Para [OUT]	int * x����ά������x����
*
*				int * y����ά������y����
*
*				int * height����ά��߶�����
*
*				int * width����ά��������
*
*				char* qrContent��ƴ�Ӷ��ɵ��ַ���,�ԡ�;��Ϊ�ָ�����ע���ʼ��ʱ�ṩ�㹻����ַ����ռ�
*
*				int & qrNum����ά����Ŀ
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-16
*
*	@Checked	2018-05-26
*/
DllExport int QRCodePositionMulti(const char* filename, int * x, int * y, int * height, int * width, char* qrContent, int & qrNum, int cameraType)
{
	LOG(INFO) << "����DLL�ӿڣ�QRCodePositionMulti�������ά����)�� ����";
	int resp = sg_OK;

	// 1. ����ͼ��·�����ж�ͼ
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "������QRCodePositionMulti " << "ͼƬ·�����ԣ���ͼʧ��";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ���ǰ��ͼ�����У��
	Mat UndistortImg = srcImg.clone();
	
	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������QRCodePositionMulti " << "����У���������";
		return resp;
	}

	// 3. ����ͼ���еĶ�ά����
	vector<QRCodePos> posList;
	vector<string> contentList;

	qrNum = 0;	// ��ʼ����ά������ĿΪ��

	resp = Detect_qrcode_multi(UndistortImg, posList, contentList);	// ���ýӿڽ��м��
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������QRCodePositionMulti " << "��ά���ⲽ�����";
		return resp;
	}

	qrNum = posList.size();	// ���¶�ά������Ŀ

	string content = "";
	for (size_t i = 0; i < qrNum; i++)
	{
		x[i] = posList[i].startX;
		y[i] = posList[i].startY;
		height[i] = posList[i].height;
		width[i] = posList[i].width;
		content = content + contentList[i] + ";";
	}

	// ���Ƶ����ص��ַ���������
	int buffMaxsize = 200;	// strcpy_s ���峤��
	strcpy_s(qrContent, buffMaxsize, content.c_str());


	LOG(INFO) << "����DLL�ӿڣ�QRCodePositionMulti�������ά����)���˳�";
	return sg_OK;
}



/**
*	@Method		DetectTask����������ԣ�
*
*	@Brief		���ʶ�����񽻻��ӿ�.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename��������ͼ��·��
*
*				const ROIInfo roi������������ROI
*
*				const TaskInfo taskinfo: ������Ϣ
*
*				int cameraType�����У��ѡ��
*
*	@Para [OUT]	ResultInfo & resultinfo�������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		�ڵ��Խ���ˣ���Ҫ�ڵõ����֮���������ڴ�����ͷ�
*
*	@Create		2018-03-25
*
*	@Desperated	2018-06-04 Ŀǰ����������ͼ���Ȼ�󷵻�����ͼ�ļ����
*/
DllExport int DetectTask(const char* filename, const ROIInfo roi, const TaskInfo taskinfo , const char* processedName, ResultInfo & resultinfo, int cameraType)
{
	LOG(INFO) << "����DLL�ӿڣ�DetectTask�����ʶ��ӿ�)������";

	int resp = sg_OK;

	// 1. �п�
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "������DetectTask " << "ͼƬ·�����ԣ���ͼʧ��";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ���ǰ��ͼ�����У��
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������DetectTask " << "����У���������";
		return resp;
	}


	// 3. ȡROI������д���
	Mat image = UndistortImg(Rect(roi.startX, roi.startY, roi.width, roi.height));
	

	// 5. ��������ַ��ӿڽ��м�⣬ͬʱ���ؽ��
	resp = taskDistributeWithStruct(image,taskinfo,resultinfo);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������DetectTask " << "���õ�������ַ��ӿڽ��м�� " << "�ò������";
		return resp;
	}

	LOG(INFO) << "����DLL�ӿڣ�DetectTask�����ʶ��ӿ�)���˳�";
	return sg_OK;
}



/**
*	@Method		ImgUndistort
*
*	@Brief		У���ӿ�.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename��������ͼ��·��
*
*				const ROIInfo roi������������ROI
*
*				const TaskInfo taskinfo: ������Ϣ
*
*				const char* processedName��������ͼ��·������ʱû�У�
*
*	@Para [OUT]	ResultInfo & resultinfo�������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-25
*/
DllExport int ImgUndistort(const char* filename, const char* savePath, const int cameraType)
{
	LOG(INFO) << "����DLL�ӿڣ�ImgUndistort��ͼ�����У��)������";

	int resp = sg_OK;

	// 1. �п�
	Mat srcImg = imread(filename);
	if (srcImg.empty())
	{
		LOG(ERROR) << "������ImgUndistort " << "ͼƬ·�����ԣ���ͼʧ��";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ����У��
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������ImgUndistort " << "����У���������";
		return resp;
	}

	// 3. ������ָ��·��
	imwrite(savePath, UndistortImg);

	LOG(INFO) << "����DLL�ӿڣ�ImgUndistort��ͼ�����У��)���˳�";
	return resp;
}



/**
*	@Method		findQRcodeinRegion
*
*	@Brief		����ʱ��ָ������������ά�벢���������ý���
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename��������ͼ��·��
*
*				const int cameraType: ����ѡ��
*
*				ROIInfo searchArea: ָ���Ķ�ά����������
*
*	@Para [OUT]	QRCodeInfo & QRcode�� ��ά��������ͼ�е�λ��
*
*				char* qrContent��ָ�������ά�������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-27
*/
DllExport int findQRcodeinRegion(const char* filename, const int cameraType, ROIInfo searchArea, QRCodeInfo & QRcode, char* qrContent)
{
	LOG(INFO) << "����DLL�ӿڣ�findQRcodeinRegion�����������ڶ�ά�룩������";

	int resp = sg_OK;

	// 1. �п�
	Mat srcImg = imread(filename);	//ͼ���п�
	if (srcImg.empty())
	{
		LOG(ERROR) << "����DLL�ӿڣ�findQRcodeinRegion " << "ͼƬ·�����ԣ���ͼʧ�ܣ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ����У��
	Mat UndistortImg = srcImg.clone();

	resp = undistortImg(srcImg, UndistortImg, cameraType);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "��������DLL�ӿڣ�DetectOnece " << "����У����������˳�����";
		return resp;
	}

	// 3. ��ȡָ������ͼ��
	Mat image = UndistortImg(Rect(searchArea.startX, searchArea.startY, searchArea.width, searchArea.height));

	// 4. ����ͼ���еĶ�ά����
	vector<QRCodePos> posList;
	vector<string> contentList;

	resp = Detect_qrcode_multi(image, posList, contentList);	// ���ýӿڽ��м��
	if (resp != sg_OK)
	{
		LOG(ERROR) << "��������DLL�ӿڣ�DetectOnece  " << "��ά���ⲽ�����";
		return resp;
	}

	if (posList.size() != 1)
	{
		LOG(ERROR) << "��������DLL�ӿڣ�DetectOnece  " << "ָ���������ά��ʧ��,û��⵽������Ŀ����һ";
		resp = sg_ERROR;
		return resp;
	}

	// ��ά����ͼ�е�λ�� = ����λ�� + ��ά����������λ��
	QRcode.startX = posList[0].startX + searchArea.startX;
	QRcode.startY = posList[0].startY + searchArea.startY;
	QRcode.width = posList[0].width;
	QRcode.height = posList[0].height;

	// ���Ƶ����ص��ַ���������
	int buffMaxsize = 200;	// strcpy_s ���峤��
	strcpy_s(qrContent, buffMaxsize, contentList[0].c_str());

	LOG(INFO) << "����DLL�ӿڣ�findQRcodeinRegion�����������ڶ�ά�룩���˳�";
	return resp;
}



/**
*	@Method		drawROIwithXML
*
*	@Brief		����XML�����ļ����������е�ROI���в鿴��ȷ��ROI����.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename��������ͼ��·��
*
*				const char* xmlPath: �����ļ�·��
*
*				const char* savePath��ͼ�񱣴�·��
*
*	@Para [OUT]	None.
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
DllExport int drawROIwithXML(const char* filename, const char* xmlPath, const char* savePath)
{
	LOG(INFO) << "����DLL�ӿڣ�drawROIwithXML������ROI������в鿴�Բ��ԣ�������";

	int resp = sg_OK;

	// 1. �п�
	Mat srcImg = imread(filename);	//ͼ���п�
	if (srcImg.empty())
	{
		LOG(ERROR) << "������drawROIwithXML " << "ͼƬ·�����ԣ���ͼʧ�ܣ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ���ú������л�ͼ
	Mat resultImg;
	resp = drawROIListWithXML(srcImg, xmlPath, resultImg);
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������drawROIwithXML " << "����ROI����";
		return resp;
	}

	//3. ����ͼ��
	imwrite(savePath, resultImg);

	LOG(INFO) << "����DLL�ӿڣ�drawROIwithXML������ROI������в鿴�Բ��ԣ����˳�";
	return resp;
}



/**
*	@Method		detectWithXML
*
*	@Brief		����XML�ļ����м��
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const char* filename��	������ͼ��·��
*
*				const char* xmlPath��	�����ļ�·��
*
*				const int Devnum��		�豸���
*
*				const int updown��		1��ʾ�ϣ�2��ʾ��
*
*	@Para [OUT]	char* resultCOntent���������ַ���
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-30
*/
DllExport int detectWithXML(const char* filename, const char* xmlPath, char* resultCOntent, const int Devnum, const int updown)
{
	LOG(INFO) << "����DLL�ӿڣ�detectWithXML������ͼ���XML���м�⣩ �� ����";

	int resp = sg_OK;

	// 1. ����п�
	string pathXML = string(xmlPath);
	if (pathXML.empty())	// XML�ļ�·���п�
	{
		LOG(ERROR) << "������detectWithXML " << "XML�ļ�·��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	Mat srcImg = imread(filename, 1);
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������detectWithXML " << "ͼ�����Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ���ýӿڽ��м��
	vector<string> result(0);
	processXMLTask(srcImg, pathXML, result, Devnum, updown);

	// 3. ������ַ�������
	string content = "";

	// �˴���1��ʼ
	for (size_t i =1; i < result.size(); i++)
	{
		if (result[i] != "")
		{
			content = content + result[i] + ";";
		}
		//content = content + result[i] + ";";
	}

	// ���Ƶ����ص��ַ���������
	int buffMaxsize = 200;	// strcpy_s ���峤��
	strcpy_s(resultCOntent, buffMaxsize, content.c_str());

	LOG(INFO) << "����DLL�ӿڣ�detectWithXML������ͼ���XML���м�⣩ �� �Ƴ�";

	return resp;
}







#include <windows.h> 
#include <time.h>

DllExport int DetectWithResult(const char* filename, const char* xmlPath,  char* dllResult, const int DevNum)
{
	LOG(INFO) << "����DLL�ӿڣ�DetectWithResult���������ý�������� �� ����";

	int resp = sg_OK;

	// 1. ����п�
	string pathXML = string(xmlPath);
	if (pathXML.empty())	// XML�ļ�·���п�
	{
		LOG(ERROR) << "������detectWithXML " << "XML�ļ�·��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	Mat srcImg = imread(filename, 1);
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������detectWithXML " << "ͼ�����Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 1. ��ȡԪ�ظ���
	int eleNum = 0;
	resp = getEleNumOptionFromXML(xmlPath, eleNum);

	
	// 2. �������н����ȡ�ͻ���ROI��

	vector<string> resultContent(eleNum+1);

	Mat drawROIImg = srcImg.clone();

	// 2. ����XML�ļ�
	tinyxml2::XMLDocument docXml;
	tinyxml2::XMLError errXml = docXml.LoadFile(xmlPath);

	if (tinyxml2::XML_SUCCESS != errXml)	// XML����ʧ��
	{
		LOG(ERROR) << "������getDetectListFromXML: XML�ļ���ʧ�ܣ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 3. ��ȡ���ڵ���Ϣ
	tinyxml2::XMLElement *root = docXml.RootElement();

	// 4. ��device�ڵ���б���
	tinyxml2::XMLElement *device = root->FirstChildElement("device");

	while (device)
	{
		// 1. ��ȡ����
		tinyxml2::XMLElement *name = device->FirstChildElement("name");

		string deviceName(name->GetText());
		string deviceNameUTF8 = "";
		Convert(deviceName, deviceNameUTF8, CP_UTF8, CP_ACP);

		LOG(INFO) << "XML�������豸��Ϊ�� " << deviceNameUTF8;	// �����Ϣ����ֹXML�ṹ����

		tinyxml2::XMLElement *taskorder = device->FirstChildElement("order");
		int order = atoi(taskorder->GetText());

		tinyxml2::XMLElement *result = device->FirstChildElement("result");
		string resultStr(result->GetText());
		string resultUTF8 = "";
		Convert(resultStr, resultUTF8, CP_UTF8, CP_ACP);
		LOG(INFO) << "XML�����������Ϊ�� " << resultUTF8;	// �����Ϣ����ֹXML�ṹ����

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

		// 1. �����
		resultContent[order] = resultUTF8;

		// 2. ���Ʒ���
		rectangle(drawROIImg, Rect(startX, startY, width, height), Scalar(0, 0, 255), 7);

		// 6. ������һ���豸
		device = device->NextSiblingElement();
	}

	// 3. ������ַ�������
	string content = "";

	// �˴���1��ʼ
	for (size_t i = 1; i < resultContent.size(); i++)
	{
		if (resultContent[i] != "")
		{
			content = content + resultContent[i] + ";";
		}
		//content = content + result[i] + ";";
	}

	// ���Ƶ����ص��ַ���������
	int buffMaxsize = 200;	// strcpy_s ���峤��
	strcpy_s(dllResult, buffMaxsize, content.c_str());

	LOG(INFO) << "����DLL�ӿڣ�DetectWithResult������ͼ���XML���м�⣩ �� �Ƴ�";

	string ShanghaiEleSavePath = "�豸Ԫ����Ƭ/";
	string ROISaveName = ShanghaiEleSavePath  + to_string(DevNum) + "ROI" + ".jpg";
	imwrite(ROISaveName, drawROIImg);

	return resp;

}