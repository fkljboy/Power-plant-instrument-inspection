/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgApplication.h
*
* 	@Brief	Ӧ�ò㺯��ͷ�ļ�
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

// �ṹ�巽ʽ����ַ�.
int taskDistributeWithStruct(const Mat srcImg, const TaskInfo taskinfo, ResultInfo & resultinfo);

// ���ʶ�����񽻻��ӿ�,��DLL�ӿڣ������ڲ��ӿ�.
int detectTask(const Mat srcImg, const ROIInfo roi, const TaskInfo taskinfo, ResultInfo & resultinfo);

// ��XML�н���XML������ͬʱ���м��
int processXMLTask(const Mat srcImg, const string xmlPath, vector<string> & resultArr, const int DevNum, const int updown);

// ���������б���Ԫ��ͼƬ
int saveElementROIimg(const vector<DetectInfo> detectList, const Mat srcImg, const int DevNum);

// �������б��л�ȡROI��Ϣ����Ҫʹ�ö�ά�붨λ����л���
int getROIArrayandUpdate(vector<DetectInfo> & detectList, bool withQR, QRCodePos qrPosNow, QRCodePos qrPosOrigin);

// ��C++���ͷ�int�����ڴ�.
bool ReleaseMemoryINT(int* buf);

// ����XML�����ļ����������е�ROI���в鿴��ȷ��ROI����
int drawROIListWithXML(const Mat srcImg, const string xmlPath, Mat & resultImg);
