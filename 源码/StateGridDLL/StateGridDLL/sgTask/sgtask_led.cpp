/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_led.cpp
*
* 	@Brief	ָʾ��ʶ����.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-16
*
*	@MethodList
*		1. int Detect_led(const Mat srcImg, const unsigned int ledtype, unsigned int lednum, unsigned int * valueArr)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/16		SHEN		Created.
*
*/

#include "sgtask_led.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"
#include "../sgCore/sgcore_math.h"
#include "../sgCore/sgcore_platform.h"

#include "../sgFunction/sgfunc_imageio.h"
#include "../sgFunction/sgfunc_feature.h"

#include "ImageDeal.h"

#include <opencv2\opencv.hpp>
using namespace cv;


//�ж����е���ķ���
static int arrange_row = 2;
static int arrange_col = 3;

//������״����
static int SHAPE_NONE = 0;
static int SHAPE_SQUARE = 1;

string YoudianPlate = "tpl.jpg";

// �ж������Ƿ���������
int ShapeDetect(vector<Point> mContour, vector<Point> &outContour);


/**
*	@Method		Detect_led
*
*	@Brief		ָʾ�Ƽ��ʶ�����.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg��	����̱�����ͼ�񣨾���ROI����
*
*				const unsigned int ledtype��	�̱����ͣ�3�֣�
*											1. �ݲ�̵��� ��������10λ��	sg_led_type_benderZongCha
*											2. �����̵��� ��������8λ��		sg_led_type_benderBaoHu
*											3. ͨѶ�̵��� ��������17λ��	sg_led_type_benderTongXun
*
*											4. �е���ʾ������˸�ƣ� ��������4λ��		sg_led_type_YouDian
*
*	@Para [OUT]	unsigned int * valueArr��	��������飨����ǰ�����ڴ棩
*				�����Ϊint���飬ÿ��Ԫ��Ϊ����������������մ��ϵ��£�������ԭ��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-16
*
*	@Checked	2018-05-29
*/

int Detect_led(const Mat srcImg, const int ledtype, vector<int> & valueArr)
{
	LOG(INFO) << "������Detect_led��ָʾ�Ʒַ��ӿڣ��� ����";

	int resp = sg_OK;

	// 1. ͼ���п�
	if (srcImg.empty())
	{
		LOG(ERROR) << "������ Detect_led" << "  ͼ��Ϊ��,�˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ����
	if (sg_led_type_benderZongCha == ledtype)	// �ݲ�̵��� ��������10λ
	{
		resp = led_Zongcha_detect(srcImg, valueArr);
		CHECKRESP(resp);
	}
	else if (sg_led_type_benderBaoHu == ledtype)	// �����̵��� ��������8λ
	{
		resp = led_Baohu_detect(srcImg, valueArr);
		//resp = led_bender_detect(srcImg, lednum, valueArr);
		CHECKRESP(resp);
	}
	else if (sg_led_type_benderTongXun == ledtype)	//ͨѶ�̵��� ��������17λ
	{
		resp = led_Tongxun_detect(srcImg, valueArr);
		CHECKRESP(resp);
	}
	else if (sg_led_type_YouDian == ledtype)
	{
		Mat templateImg = imread(YoudianPlate, 1);
		resp = led_flash_detect(srcImg, templateImg, valueArr);
		CHECKRESP(resp);
	}

	LOG(INFO) << "������Detect_led��ָʾ�Ʒַ��ӿڣ��� �˳�";
	return sg_OK;
}


/**
*	@Method		otsuThreshold
*
*	@Brief		�ų���ɫ���ص��Ӱ��ԻҶ�ͼ����д�򷨶�ֵ��
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat grayImage
*
*	@Para [OUT]	Mat& otsuImg
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-06-16
*/
int otsuThreshold(const Mat grayImage,Mat& otsuImg)
{
	int nCols = grayImage.cols;
	int nRows = grayImage.rows;
	int otsuThre = 0;
	// ��ʼ��ͳ�Ʋ���
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	// ͳ�ƻҶȼ���ÿ������������ͼ���еĸ��� 
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			int pixel = grayImage.at<uchar>(i, j);
			if (pixel != 0)
			{
				nSumPix[pixel]++;
			}
		}
	}
	// ����ÿ���Ҷȼ�ռͼ���еĸ��ʷֲ�
	for (int i = 1; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols * nRows);
	}
	// �����Ҷȼ�[0,255],����������䷽���µ���ֵ  
	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 1; i < 256; i++)
	{
		// ��ʼ����ز���
		w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;
		for (int j = 1; j < 256; j++)
		{
			//�������� 
			if (j <= i)
			{
				// ��ǰiΪ�ָ���ֵ����һ���ܵĸ���  
				w0 += nProDis[j];
				u0_temp += j * nProDis[j];
			}
			//ǰ������   
			else
			{
				// ��ǰiΪ�ָ���ֵ����һ���ܵĸ���
				w1 += nProDis[j];
				u1_temp += j * nProDis[j];
			}
		}
		// �ֱ��������ƽ���Ҷ� 
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		delta_temp = (float)(w0 *w1* pow((u0 - u1), 2));
		// �����ҵ������䷽���µ���ֵ    
		if (delta_temp > delta_max)
		{
			delta_max = delta_temp;
			otsuThre = i;
		}
	}

	threshold(grayImage, otsuImg, otsuThre, 255, CV_THRESH_BINARY);
	
	return sg_OK;
}

/**
*	@Method		led_Zongcha_detect
*
*	@Brief		�ݲ�̵���ָʾ�Ƽ��
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg��������ͼ��
*
*	@Para [OUT]	int * valueArr�� �������������ʽ����������10λ
*	                             1.sg_led_UpcloseDownClose = 107;// ָʾ���� ��������
*	                             2.sg_led_UpOpenDownClose = 108;// ָʾ���� ��������
*	                             3.sg_led_UpCloseDownOpen = 109;// ָʾ���� ��������
*	                             4.sg_led_UpOpenDownOpen = 110;// ָʾ���� ��������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Zongcha_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "������led_Zongcha_detect���ݲ�̵����� �� ����";
	int resp = sg_OK;

	// 1. �п�
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������led_flash_detect " << "������ͼ��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. TODO: �������
	Mat lampImg = srcImg.clone();
	Mat grayImg;
	cvtColor(lampImg, grayImg, CV_BGR2GRAY);
	Mat edgeImg;
	Canny(grayImg, edgeImg, 50, 150);
	// imshow("edgeImg", edgeImg);

	Mat otsuImg;
	resp = rotateCorrection(edgeImg, lampImg, grayImg, otsuImg, sg_led_type_benderZongCha);
	CHECKRESP(resp);
	int rows = lampImg.rows;
	int cols = lampImg.cols;

	Canny(grayImg, edgeImg, 50, 150);
	imgShowDebug(edgeImg, "edgeImg", 0);;

	vector<Point> coreEdge;
	resp = searchCore(edgeImg, coreEdge, 1 / 30.0, 1 / 50.0);
	CHECKRESP(resp);

	//�ҵ�λ��ͬһ�еĵ���
	vector<vector<Point>> pointColGroup;
	resp = searchPointSameCol(pointColGroup, coreEdge, edgeImg, 1 / 30.0);
	CHECKRESP(resp);

	//�ҳ���ͨ������һ��
	vector<Point> maxPointCol;
	resp = maxContourCol(pointColGroup, maxPointCol);
	CHECKRESP(resp);

	//����һ�еĵ㰴������������������
	resp = arrangePoint(maxPointCol, arrange_col);
	CHECKRESP(resp);

	//ѡ������֮���������ֵ��Ϊ��ļ������С©����������ĸ���
	float averDis;
	resp = maxPointDis(maxPointCol, averDis, cols, 1 / 60.0, sg_led_type_benderZongCha);
	CHECKRESP(resp);

	//�ҳ���־���м��Ϊ��λ�������
	vector<Point> signGroup;
	resp = searchAverDisRow(maxPointCol, averDis, edgeImg, 1 / 30.0, signGroup);
	CHECKRESP(resp);

	//����β֮��δ�ҵ��ı�־���в�ֵ
	resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderZongCha);
	CHECKRESP(resp);

	//�ݲ�̵�������β֮����в�ֵ
	resp = difInsertTopEndPt(signGroup, pointColGroup, averDis, edgeImg);
	CHECKRESP(resp);

	//��ÿһ�ν�ȡ������������
	vector<int> lightOrder;
	resp = difLightBlockAnalyse(signGroup, averDis, lampImg, valueArr);
	CHECKRESP(resp);

	LOG(INFO) << "������led_Zongcha_detect���ݲ�̵����� �� �˳�";

	return resp;
}


/**
*	@Method		led_Baohu_detect
*
*	@Brief		�����̵���ָʾ�Ƽ��
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg��������ͼ��
*
*	@Para [OUT]	int * valueArr�� �������������ʽ��	��������8λ
*								 1.sg_led_UpcloseDownClose = 107;// ָʾ���� ��������
*								 2.sg_led_UpOpenDownClose = 108;// ָʾ���� ��������
*								 3.sg_led_UpCloseDownOpen = 109;// ָʾ���� ��������
*								 4.sg_led_UpOpenDownOpen = 110;// ָʾ���� ��������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Baohu_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "������led_Baohu_detect�������̵����� �� ����";
	int resp = sg_OK;

	// 1. �п�
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������led_Baohu_detect " << "������ͼ��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}
	imgShowDebug(srcImg, "srcImg", 0);

	// 2. TODO: �������
	Mat lampImg = srcImg.clone();
	Mat grayImg;
	// cvtColor(lampImg, grayImg, CV_BGR2GRAY);

	Mat lampHsv;
	cvtColor(lampImg, lampHsv, CV_BGR2HSV);

	vector<Mat> hsvChannels;
	split(lampHsv, hsvChannels);
	grayImg = hsvChannels[2];
	// imgShowDebug(grayImg, "grayImg", 0);

	Mat edgeImg;
	Canny(grayImg, edgeImg, 20, 150);
	imgShowDebug(edgeImg, "edgeImg", 0);

	Mat otsuImg;
	resp = rotateCorrection(edgeImg, lampImg, grayImg, otsuImg, sg_led_type_benderBaoHu);
	CHECKRESP(resp);
	imgShowDebug(otsuImg, "otsuImg", 0);

	int location[4];
	resp = BoundProjection(otsuImg, location, 1.0 / 3);
	CHECKRESP(resp);
	int areaHeight = location[1] - location[0] + 1;
	int areaWidth = location[3] - location[2] + 1;
	Mat mainArea = lampImg(Rect(location[2], location[0], areaWidth, areaHeight));
	Mat mainOtsu = otsuImg(Rect(location[2], location[0], areaWidth, areaHeight));
	Mat mainEdge = edgeImg(Rect(location[2], location[0], areaWidth, areaHeight));
	int rows = mainArea.rows;
	int cols = mainArea.cols;
	imgShowDebug(mainArea, "mainArea", 0);
	imgShowDebug(mainOtsu, "mainOtsu", 0);
	imgShowDebug(mainEdge, "mainEdge", 0);

	Mat edgeHsv;
	resp = getHsvEdge(mainArea, edgeHsv);
	CHECKRESP(resp);

	vector<Point> coreMainOtsu;//�洢��ֵ��ͼ���е���ͨ��
	resp = searchCore(mainEdge, coreMainOtsu, 1 / 20.0, 1 / 20.0);
	CHECKRESP(resp);

	//�ҳ�ͬһ���ϵĵ�
	vector<vector<Point>> pointGroup;
	resp = searchPointSameRow(pointGroup, coreMainOtsu, rows, 1 / 30.0);
	CHECKRESP(resp);

	//�ҵ�������һ����������,�������ں�
	vector<Point>referRow;//�洢����������
	int upRow, downRow;
	resp = searchMostSilmilarRow(pointGroup, referRow, cols, upRow, downRow);
	CHECKRESP(resp);

	//�������и�����ĵ㰴��������ǰ��������
	resp = arrangePoint(referRow, arrange_row);
	CHECKRESP(resp);

	//ѡ������֮���������ֵ��Ϊ��ļ������С©����������ĸ���
	float averDis;
	resp = maxPointDis(referRow, averDis, cols, 1 / 50.0, sg_led_type_benderBaoHu);
	CHECKRESP(resp);

	//�����е�֮������д�ֱͶӰ������һ��Ϊ�ο���
	int maxProjectionCol;
	resp = maxVertProjection(mainOtsu, upRow, downRow, referRow, maxProjectionCol);
	CHECKRESP(resp);

	vector<Point> coreHsv;//�洢���е�����
	resp = searchCore(edgeHsv, coreHsv, 1 / 20.0, 1 / 20.0);
	CHECKRESP(resp);

	if (coreHsv.size() > 0)
	{
		int label[2];//�����洢ÿ�����λ����Ϣ
		resp = lightLocate(coreHsv, maxProjectionCol, averDis, label, upRow, downRow, valueArr);
		CHECKRESP(resp);
	}
	else
	{
		////�ҳ���־���м��Ϊ��λ�������
		//vector<Point> signGroup;
		//resp = searchAverDisCol(0, referRow, averDis, cols, 1 / 50.0, signGroup, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		////����β֮��δ�ҵ��ı�־���в�ֵ
		//resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		////�ڱ�־�е���β���в�ֵ
		//resp = comInsertTopEndPt(signGroup, maxProjectionCol, averDis, cols, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		LOG(ERROR) << "������ lightLocate  " << "sg_ERROR_led_NO_pointList";
		return sg_ERROR;
	}

	// 3. TODO: ���ؽ����ֵ
	LOG(INFO) << "������led_Baohu_detect�������̵����� �� �˳�";
	return resp;
}


/**
*	@Method		led_Tongxun_detect
*
*	@Brief		ͨѶ�̵���ָʾ�Ƽ��
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg��������ͼ��
*
*	@Para [OUT]	int * valueArr�� �������������ʽ��	��������17λ
*	                             1.sg_led_UpcloseDownClose = 107;// ָʾ���� ��������
*	                             2.sg_led_UpOpenDownClose = 108;// ָʾ���� ��������
*	                             3.sg_led_UpCloseDownOpen = 109;// ָʾ���� ��������
*	                             4.sg_led_UpOpenDownOpen = 110;// ָʾ���� ��������
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Tongxun_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "������led_Tongxun_detect��ͨѶ�̵����� �� ����";
	int resp = sg_OK;

	// 1. �п�
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������led_Tongxun_detect " << "������ͼ��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. TODO: �������
	Mat lampImg = srcImg.clone();
	Mat grayImg;
	cvtColor(lampImg, grayImg, CV_BGR2GRAY);
	Mat edgeImg;
	Canny(grayImg, edgeImg, 50, 150);

	Mat otsuImg;
	resp = rotateCorrection(edgeImg, lampImg, grayImg, otsuImg, sg_led_type_benderTongXun);
	CHECKRESP(resp);
	Canny(grayImg, edgeImg, 30, 100);

	int rows = lampImg.rows;
	int cols = lampImg.cols;
	int location[4];//�洢�ĸ����������
	resp = BoundProjection(edgeImg, location, 1.0 / 2);
	CHECKRESP(resp);
	int areaHeight = location[1] - location[0] + 1;
	int areaWidth = location[3] - location[2] + 1;
	Mat mainArea = lampImg(Rect(location[2], location[0], areaWidth, areaHeight));
	Mat mainEdge = edgeImg(Rect(location[2], location[0], areaWidth, areaHeight));
	imgShowDebug(mainArea, "mainArea", 0);
	imgShowDebug(mainEdge, "mainEdge", 0);
	Mat mainGray, mainBinary;
	cvtColor(mainArea, mainGray, CV_BGR2GRAY);
	threshold(mainGray, mainBinary, 0, 255, CV_THRESH_OTSU);
	imgShowDebug(mainBinary, "mainBinary", 0);

	vector<Point> coreMainEdge;
	resp = searchCore(mainEdge, coreMainEdge, 1 / 30.0, 1 / 10.0);
	CHECKRESP(resp);

	vector<vector<Point>> pointRowGroup;
	resp = searchPointSameRow(pointRowGroup, coreMainEdge, rows, 1 / 20.0);
	CHECKRESP(resp);

	//�ҳ���ͨ������һ��
	vector<Point> maxPointRow;
	resp = maxContourRow(pointRowGroup, maxPointRow);
	CHECKRESP(resp);

	//����һ�еĵ㰴��������ǰ��������
	resp = arrangePoint(maxPointRow, arrange_row);
	CHECKRESP(resp);

	//ѡ������֮���������ֵ��Ϊ��ļ������С©����������ĸ���
	float averDis;
	resp = maxPointDis(maxPointRow, averDis, cols, 1 / 60.0, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//�ҵ���ʶ�����ڵ�λ��
	vector<vector<Point>> pointColGroup;
	resp = searchSignCol(coreMainEdge, mainEdge, pointColGroup, 1 / 60.0);
	CHECKRESP(resp);

	//�ҳ���һ����������3����
	int signMaxRowNum = -1;
	int signColNum;//��־���������е�λ��
	int signCol;//��־���ڵ���
	resp = colMoreThanThree(pointColGroup, maxPointRow, mainEdge, averDis, signMaxRowNum, signColNum, signCol);
	CHECKRESP(resp);

	//�ҳ���־���м��Ϊ��λ�������
	vector<Point> signGroup;
	resp = searchAverDisCol(signMaxRowNum, maxPointRow, averDis, mainArea.cols, 1 / 80.0, signGroup, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//����β֮��δ�ҵ��ı�־���в�ֵ
	resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//�ڱ�־�е���β���в�ֵ
	resp = comInsertTopEndPt(signGroup, signCol, averDis, mainArea.cols, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//�ҵ�����С�����ĵ����ڵ���
	int lightRow[2] = { -1,-1 };//�洢�������ŵƵ�������
	resp = searchLightRows(lightRow, pointColGroup, signColNum, maxPointRow, signMaxRowNum);
	CHECKRESP(resp);

	//��ÿ�������ڵ�����ȡ������������
	resp = comLightBlockAnalyze(signGroup, averDis, mainArea, lightRow, valueArr);
	CHECKRESP(resp);


	LOG(INFO) << "������led_Tongxun_detect��ͨѶ�̵����� �� �˳�";

	return resp;
}




/**
*	@Method		led_flash_detect
*
*	@Brief		�����Ƽ�⣨�е���ʾ����
*
*	@Author		LI Wentao
*
*	@Para [IN]	const Mat srcImg��������ͼ��
*
*				const Mat templateImg: ģ��ͼ��
*
*	@Para [OUT]	int * valueArr�� �������������ʽ����������λ
*								��sg_led_open ��
*								��sg_led_close ��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_flash_detect(const Mat srcImg, const Mat templateImg, vector<int> &  valueArr)
{
	LOG(INFO) << "������led_flash_detect����˸�Ƽ��һ�Σ� �� ����";
	int resp = sg_OK;

	// 1. �п�
	if (srcImg.empty())		// ������ͼ���п�
	{
		LOG(ERROR) << "������led_flash_detect " << "������ͼ��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	if (templateImg.empty())		// ģ��ͼ���п�
	{
		LOG(ERROR) << "������led_flash_detect " << "ģ��ͼ��Ϊ�գ��˳�����";
		resp = sg_ERROR;
		return resp;
	}

	// 2. �������
	static ImageDeal imageDeal;
	if (imageDeal.tplMat.empty())
	{

		//ģ��ͼƬ
		imageDeal.tplMat = templateImg.clone();
	}

	Vec4i result(0);
	//����Ŀ�����----
	bool flage = imageDeal.Detect(srcImg, result);
	if (!flage)
	{
		return 0;//û�м�⵽���

	}


	// 3. ���ؽ����ֵ

	for (int i = 0; i < 4; i++)
	{
		valueArr[i] = result[i] == 1 ? sg_led_open : sg_led_close;
	}



	LOG(INFO) << "������led_flash_detect����˸�Ƽ��һ�Σ� �� �˳�";
	return resp;
}




Rect matchObj(Mat &src, Mat &temp)
{
	int width = src.cols - temp.cols + 1;//result���
	int height = src.rows - temp.rows + 1;//result�߶�

	Mat result(height, width, CV_32FC1);//�������ӳ��ͼ��
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF); //ƽ����ƥ�䷨(���ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF_NORMED); //��һ��ƽ����ƥ�䷨(���ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR); //���ƥ�䷨(�ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR_NORMED); //��һ�����ƥ�䷨(�ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCOEFF); //ϵ��ƥ�䷨(���ƥ��1)
	matchTemplate(src, temp, result, CV_TM_CCOEFF_NORMED);//�����ϵ��ƥ��,���ֵ1

	normalize(result, result, 0, 1, NORM_MINMAX, -1);//��һ����0-1��Χ

	double minValue, maxValue;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc);
	Rect rect;
	rect.x = maxLoc.x;
	rect.y = maxLoc.y;
	rect.width = temp.cols;
	rect.height = temp.rows;
	rectangle(src, maxLoc, Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), Scalar(0, 255, 0), 2, 8);
	return rect;
}

// �ж������Ƿ���������
int ShapeDetect(vector<Point> mContour, vector<Point> &outContour)
{
	int shape = SHAPE_NONE;
	double perimeter = arcLength(mContour, true);
	approxPolyDP(mContour, outContour, 0.03*perimeter, true);//�����������ɵ���0.01-0.05
	Rect mRect = boundingRect(outContour);
	float ar = (float)mRect.width / mRect.height;
	if ((ar >= 0.80) && (ar <= 1.15))
	{
		shape = SHAPE_SQUARE;
	}
	return shape;
}

/**
*	@Method		BoundProjection
*
*	@Brief		����ͶӰѡȡ������
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat Image, float scale
*
*	@Para [OUT]	int *location
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int BoundProjection(const Mat Image, int *location, float scale)
{
	int resp = sg_OK;

	if (Image.empty())
	{
		LOG(ERROR) << "������ BoundProjection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	Mat binaryImage = Image.clone();
	int brows = binaryImage.rows;
	int bcols = binaryImage.cols;
	vector<int> row_black(brows), col_black(bcols);
	int max_row_black = 0, max_col_black = 0;
	for (int m = 0; m < scale*brows; m++)
	{
		for (int n = 0; n < bcols; n++)
		{
			if (binaryImage.at<uchar>(m, n) == 255)
				row_black[m]++;
		}
		if (row_black[m] >= max_row_black)
		{
			max_row_black = row_black[m];
			location[0] = m;
		}
	}
	// location[1]�洢���Ǳ����±߿����ڵ���
	max_row_black = 0;
	for (int m = brows - 1; m > (1 - scale)*brows; m--)
	{
		for (int n = 0; n < bcols; n++)
		{
			if (binaryImage.at<uchar>(m, n) == 255)
				row_black[m]++;
		}
		if (row_black[m] >= max_row_black)
		{
			max_row_black = row_black[m];
			location[1] = m;
		}
	}
	// location[2]�洢���Ǳ�����߿����ڵ���
	for (int m = 0; m < scale*bcols; m++)
	{
		col_black[m] = 0;
		for (int n = 0; n < brows; n++)
		{
			if (binaryImage.at<uchar>(n, m) == 255)
				col_black[m]++;
		}
		if (col_black[m] > max_col_black)
		{
			max_col_black = col_black[m];
			location[2] = m;
		}
	}
	// location[3]�洢���Ǳ����ұ߿����ڵ���
	max_col_black = 0;
	for (int m = bcols - 1; m > 0.8*bcols; m--)
	{
		col_black[m] = 0;
		for (int n = 0; n < brows; n++)
		{
			if (binaryImage.at<uchar>(n, m) == 255)
				col_black[m]++;
		}
		if (col_black[m] > max_col_black)
		{
			max_col_black = col_black[m];
			location[3] = m;
		}
	}
	return sg_OK;
}


/**
*	@Method		 searchCore
*
*	@Brief		 ���Ҷ�ֵ��ͼ���е�����
*
*	@Author		 LU Xin
*
*	@Para [IN]	 Mat binaryImg, float colScale, float rowScale
*
*	@Para [OUT]	 vector<Point>& core
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchCore(Mat binaryImg, vector<Point>& core, float colScale, float rowScale)
{
	int resp = sg_OK;

	if (binaryImg.empty())
	{
		LOG(ERROR) << "������ searchCore  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryImg.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/*Mat image_binary(binaryImg.size(), binaryImg.type());
	image_binary = Scalar::all(0);
	drawContours(image_binary, contours, -1, Scalar::all(255));
	imshow("image_binary", image_binary);*/
	int core_x, core_y;
	int binCols = binaryImg.cols;
	int binRows = binaryImg.rows;
	vector<Rect> boundRect(contours.size());
	if (contours.size() == 0)
	{
		LOG(ERROR) << "������ searchCore  " << "sg_ERROR_led_NO_contour";
		return	sg_ERROR;
	}

	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		int width = boundRect[i].width;
		int height = boundRect[i].height;
		//����С����ͨ���޳���
		/*if ((width*height) < (binRows*binCols / 100.0))
		{
		continue;
		}*/
		int x = boundRect[i].x;
		int y = boundRect[i].y;
		core_x = x + width / 2.0;
		core_y = y + height / 2.0;
		core.push_back(Point(core_x, core_y));
	}
	//ȥ���ص��ĵ�
	for (int m = 0; m < core.size() - 1; m++)
	{
		for (int n = m + 1; n < core.size(); n++)
		{
			if (abs(core[m].x - core[n].x) < colScale*binCols
				&&abs(core[m].y - core[n].y) < rowScale*binRows)
			{
				//�����������ں�
				(core.begin() + n)->x = ((core.begin() + m)->x + (core.begin() + n)->x) / 2.0;
				(core.begin() + n)->y = ((core.begin() + m)->y + (core.begin() + n)->y) / 2.0;
				core.erase(core.begin() + m);
				m--;
				break;
			}
		}
	}
	LOG(INFO) << "The number of contours is:" << core.size();
	return sg_OK;
}


/**
*	@Method		 rotateCorrection
*
*	@Brief		 ��ͼ�������бУ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 int ledKind
*
*	@Para [OUT]	 Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int rotateCorrection(Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg, int ledKind)
{
	if (edgeImg.empty() || lampImg.empty() || grayImg.empty())
	{
		LOG(ERROR) << "������ rotateCorrection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}
	
	vector<Vec4i> lines;
	HoughLinesP(edgeImg, lines, 1, M_PI / 180, 20, 30, 5);

	if (lines.size() == 0)
	{
		LOG(ERROR) << "������ rotateCorrection  " << "sg_ERROR_Led_NO_line";
		return	sg_ERROR;
	}

	float maxLength = 0;//�ֱ�ߵĳ���
	float lampAngle;//�̵�������б�Ƕ�
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		int dx0 = l[0] - l[2];
		int dy0 = l[1] - l[3];
		float length = sqrt(pow(dx0, 2) + pow(dy0, 2));
		if (length > maxLength)
		{
			maxLength = length;
			lampAngle = atan(1.0*dy0 / dx0);
		}
	}
	if (ledKind == 102 || ledKind == 103)
	{
		lampAngle = lampAngle*180.0 / M_PI;
	}
	else if (ledKind == 101)
	{
		lampAngle = lampAngle*180.0 / M_PI;
		lampAngle = lampAngle > 0 ? lampAngle - 90.0 : lampAngle + 90.0;
	}

	LOG(INFO) << "lampAngle: " << lampAngle;

	int rows = lampImg.rows;
	int cols = lampImg.cols;
	Point2f center(cols / 2, rows / 2);
	Mat rot_mat = getRotationMatrix2D(center, lampAngle, 1.0);
	warpAffine(lampImg, lampImg, rot_mat, lampImg.size());

	Mat lampHsv;
	cvtColor(lampImg, lampHsv, CV_BGR2HSV);
	vector<Mat> hsvChannels;
	split(lampHsv, hsvChannels);
	grayImg = hsvChannels[2];
	otsuThreshold(grayImg, otsuImg);
	// imgShowDebug(otsuImg, "otsuImg", 0);
	Canny(grayImg, edgeImg, 20, 150);
	// imgShowDebug(edgeImg, "edgeImg", 0);
	imgShowDebug(lampImg, "lampImg_rotate", 0);

	return sg_OK;
}

/**
*	@Method		 getHsvEdge
*
*	@Brief		 ��ȡHsv�ռ��б�Ե�����ͼ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 Mat mainArea
*
*	@Para [OUT]	 Mat& edgeHsv
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int getHsvEdge(Mat mainArea, Mat& edgeHsv)
{
	if (mainArea.empty())
	{
		LOG(ERROR) << "������ getHsvEdge  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	//RGB��ɫ�ռ�ת����HSV��
	Mat hsvImg, hImg, sImg, vImg;
	cvtColor(mainArea, hsvImg, CV_BGR2HSV);
	vector<Mat> hsvChannels;
	split(hsvImg, hsvChannels);
	hImg = hsvChannels[0];
	sImg = hsvChannels[1];
	vImg = hsvChannels[2];
	imgShowDebug(hImg, "hImg", 0);
	imgShowDebug(sImg, "sImg", 0);
	imgShowDebug(vImg, "vImg", 0);
	//cout << hImg << " ";
	//waitKey(0);

	//˫��ֵ��ֵ��
	Mat binHsv;
	int maxVal = 255;
	int low_threshold = 100, high_threshold = 150;
	Mat dstTempImage1, dstTempImage2;
	threshold(hImg, dstTempImage1, low_threshold, maxVal, THRESH_BINARY);
	threshold(hImg, dstTempImage2, high_threshold, maxVal, THRESH_BINARY_INV);
	bitwise_and(dstTempImage1, dstTempImage2, binHsv);
	imgShowDebug(binHsv, "binHsv", 0);
	//waitKey(0);

	Canny(binHsv, edgeHsv, 50, 200);
	imgShowDebug(edgeHsv, "edgeHsv", 0);

	return sg_OK;
}


/**
*	@Method		 searchPointSameRow
*
*	@Brief		 �ҵ�λ��ͬһ�еĵ���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreMainOtsu, int rows, float rowScale
*
*	@Para [OUT]	 vector<vector<Point>>& pointGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchPointSameRow(vector<vector<Point>>& pointGroup, vector<Point>& coreMainOtsu,
	int rows, float rowScale)
{
	if (coreMainOtsu.size() == 0)
	{
		LOG(ERROR) << "������ searchPointSameRow  " << "sg_ERROR_led_NO_contour";
		return	sg_ERROR;
	}

	//�����������ϵ��£��������ҵ�˳������
	Point tempPoint;
	for (int i = 0;i < coreMainOtsu.size() - 1;i++)
	{
		for (int j = i + 1;j < coreMainOtsu.size();j++)
		{
			int coreDis = coreMainOtsu[i].y - coreMainOtsu[j].y;
			if (coreDis > rows / 10.0)
			{
				tempPoint.x = coreMainOtsu[j].x;
				tempPoint.y = coreMainOtsu[j].y;
				coreMainOtsu[j].x = coreMainOtsu[i].x;
				coreMainOtsu[j].y = coreMainOtsu[i].y;
				coreMainOtsu[i].x = tempPoint.x;
				coreMainOtsu[i].y = tempPoint.y;
			}
			else if (coreDis >= -rows / 10.0&&coreDis <= rows / 10.0
				&&coreMainOtsu[j].x < coreMainOtsu[i].x)
			{
				tempPoint.x = coreMainOtsu[j].x;
				tempPoint.y = coreMainOtsu[j].y;
				coreMainOtsu[j].x = coreMainOtsu[i].x;
				coreMainOtsu[j].y = coreMainOtsu[i].y;
				coreMainOtsu[i].x = tempPoint.x;
				coreMainOtsu[i].y = tempPoint.y;
			}
		}
	}

	for (int i = 0;i < coreMainOtsu.size();i++)
	{
		cout << coreMainOtsu[i] << " ";
	}
	cout << endl;

	vector<Point> lattice;//�洢ÿһ�еĵ���
	lattice.push_back(coreMainOtsu[0]);//����һ����ͨ������ڴ�
	pointGroup.push_back(lattice);
	//�����е㰴���������ϵ���δ���������
	for (int i = 1; i < coreMainOtsu.size(); i++)
	{
		int k = 0;//��ͬ�����������
		lattice.clear();
		for (; k < pointGroup.size(); k++)
		{
			if (abs(coreMainOtsu[i].y - pointGroup[k].back().y) < rows*rowScale)
			{
				int size = pointGroup[k].size();
				if (size == 1 || (size >= 2 && (abs(coreMainOtsu[i].y -
					pointGroup[k][size - 2].y) < rows*rowScale)))
				{
					pointGroup[k].push_back(coreMainOtsu[i]);//���õ���뵱ǰ����
					break;
				}
			}
		}
		//���֮ǰ����������߶ȵ��У��������pointGroup��
		if (k == pointGroup.size())
		{
			lattice.push_back(coreMainOtsu[i]);
			pointGroup.push_back(lattice);
		}
	}

	cout << "Point of same row: ";
	for (int m = 0;m < pointGroup.size();m++)
	{
		for (int n = 0;n < pointGroup[m].size();n++)
		{
			cout << pointGroup[m][n] << " ";
		}
		cout << endl;
	}

	return sg_OK;
}


/**
*	@Method		 searchMostSilmilarRow
*
*	@Brief		 �ҵ�������һ����������
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointGroup
*
*	@Para [OUT]	 vector<Point>& downPoint, int cols, int& upRow, int& downRow
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchMostSilmilarRow(const vector<vector<Point>> pointGroup,
	vector<Point>& downPoint, int cols, int& upRow, int& downRow)
{
	if (pointGroup.size() == 0)
	{
		LOG(ERROR) << "������ searchMostSilmilarRow  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxSameX = 0;
	for (int n = 0; n < pointGroup.size() - 1; n++)
	{
		for (int m = n + 1; m < pointGroup.size(); m++)
		{
			int count = 0;//�������к�������ͬ�ĵ�ĸ���
			int num0 = pointGroup[n].size();
			int num1 = pointGroup[m].size();
			for (int l = 0; l < num0; l++)
			{
				for (int k = 0; k < num1; k++)
				{
					if (abs(pointGroup[n][l].x - pointGroup[m][k].x) < cols / 50.0)
					{
						count++;
					}
				}
			}
			int upDownColDis = abs(pointGroup[n][0].y - pointGroup[m][0].y);
			if (count > maxSameX)
			{
				maxSameX = count;
				downRow = pointGroup[n][0].y>pointGroup[m][0].y ? pointGroup[n][0].y : pointGroup[m][0].y;
				upRow = pointGroup[n][0].y < pointGroup[m][0].y ? pointGroup[n][0].y : pointGroup[m][0].y;
				downPoint.clear();
				downPoint.insert(downPoint.begin(), pointGroup[n].begin(), pointGroup[n].end());
				downPoint.insert(downPoint.end(), pointGroup[m].begin(), pointGroup[m].end());
			}
		}
	}

	if (maxSameX == 0)
	{
		LOG(ERROR) << "������ searchMostSilmilarRow  " << "sg_ERROR_led_NO_similarRow";
		return	sg_ERROR;
	}

	LOG(INFO) << "upRow: " << upRow;
	LOG(INFO) << "downRow: " << downRow;

	return sg_OK;
}


/**
*	@Method		 arrangePoint
*
*	@Brief		 ��������������������е���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 vector<Point>& pointList
*
*	@Para [OUT]	 int rowOrCol
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int arrangePoint(vector<Point>& pointList, int rowOrCol)
{
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "������ arrangePoint  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	Point tempPoint;
	//������������
	if (rowOrCol == arrange_row)
	{
		for (int r = 0; r < pointList.size() - 1; r++)
		{
			for (int s = r + 1; s < pointList.size(); s++)
			{
				if (pointList[r].x > pointList[s].x)
				{
					tempPoint = pointList[r];
					pointList[r] = pointList[s];
					pointList[s] = tempPoint;
				}
			}
		}
	}

	if (rowOrCol == arrange_col)
	{
		for (int r = 0; r < pointList.size() - 1; r++)
		{
			for (int s = r + 1; s < pointList.size(); s++)
			{
				if (pointList[r].y > pointList[s].y)
				{
					Point tempPoint;
					tempPoint = pointList[r];
					pointList[r] = pointList[s];
					pointList[s] = tempPoint;
				}
			}
		}
	}

	cout << "The row of point after merge:" << endl;
	for (int n = 0;n < pointList.size();n++)
	{
		cout << pointList[n] << " ";
	}
	cout << endl;

	return sg_OK;
}


/**
*	@Method		 maxPointDis
*
*	@Brief		 ѡ������֮���������ֵ��Ϊ��ļ������С©����������ĸ���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point>pointList, int cols, float colScale, int knobKind
*
*	@Para [OUT]	 float& averDis
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxPointDis(const vector<Point>pointList, float& averDis, int cols, float colScale, int knobKind)
{
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "������ maxPointDis  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	vector<int> pointDis;
	vector<vector<int>> ptDisGroup;
	vector<int> ptSameDis;
	for (int i = 0; i < pointList.size() - 1; i++)
	{
		int pointListDis, pointAdvDis, pointRearDis;
		pointListDis = pointList[i + 1].x - pointList[i].x;
		pointAdvDis = i > 0 ? pointList[i].x - pointList[i - 1].x : 0;
		pointRearDis = i < pointList.size() - 2 ? pointList[i + 2].x - pointList[i + 1].x : 0;
		if (knobKind == sg_led_type_benderBaoHu && pointListDis > cols / 12.0)
		{
			if (pointAdvDis <= 3)
			{
				pointDis.push_back(pointListDis + pointAdvDis);
			}
			else if (pointRearDis <= 3)
			{
				pointDis.push_back(pointListDis + pointRearDis);
			}
			else
			{
				pointDis.push_back(pointListDis);
			}
		}
		else if (knobKind == sg_led_type_benderTongXun && pointListDis > cols / 60.0)
		{
			pointDis.push_back(pointListDis);
		}
		else if (knobKind == sg_led_type_benderZongCha)
		{
			pointListDis = pointList[i + 1].y - pointList[i].y;
			pointDis.push_back(pointListDis);
		}
	}

	if (pointDis.size() == 0)
	{
		return sg_ERROR;
	}
	ptSameDis.push_back(pointDis[0]);
	ptDisGroup.push_back(ptSameDis);
	for (int j = 1; j < pointDis.size(); j++)
	{
		int k = 0;
		ptSameDis.clear();
		for (; k < ptDisGroup.size(); k++)
		{
			if (abs(pointDis[j] - ptDisGroup[k][0]) < cols*colScale)
			{
				ptDisGroup[k].push_back(pointDis[j]);
				break;
			}
		}
		if (k == ptDisGroup.size())
		{
			ptSameDis.push_back(pointDis[j]);
			ptDisGroup.push_back(ptSameDis);
		}
	}
	int maxSameDisPoint = 0;
	float sumDis;

	for (int v = 0; v < ptDisGroup.size(); v++)
	{
		sumDis = 0;
		if (ptDisGroup[v].size()>maxSameDisPoint)
		{
			maxSameDisPoint = ptDisGroup[v].size();
			for (int u = 0; u < ptDisGroup[v].size(); u++)
			{
				sumDis += ptDisGroup[v][u];
			}
			averDis = sumDis*1.0 / ptDisGroup[v].size();
		}
	}
	LOG(INFO) << "averDis=" << averDis;

	return sg_OK;
}


/**
*	@Method		 maxVertProjection
*
*	@Brief		 �����е�֮������д�ֱͶӰ������һ��Ϊ�ο���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const Mat mainOtsu, const int upRow, const int downRow, const vector<Point> pointList
*
*	@Para [OUT]	 int& maxProjectionCol
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxVertProjection(const Mat mainOtsu, const int upRow, const int downRow,
	const vector<Point> pointList, int& maxProjectionCol)
{
	if (mainOtsu.empty())
	{
		LOG(ERROR) << "������ maxVertProjection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "������ maxVertProjection  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	int beginCol = mainOtsu.cols / 2.0;
	int endCol = mainOtsu.cols*4.0 / 5;
	int ptDisWidth = endCol - beginCol + 1;
	int maxProjection = 0;
	vector<int> vertProjection(ptDisWidth);
	for (int i = 0; i < ptDisWidth; i++)
	{
		vertProjection[i] = 0;
		for (int j = upRow; j < downRow; j++)
		{
			if (mainOtsu.at<uchar>(j, i + beginCol) == 255)
			{
				vertProjection[i]++;
			}
		}
		if (vertProjection[i] > maxProjection)
		{
			maxProjection = vertProjection[i];
			maxProjectionCol = i + beginCol;
		}
	}
	LOG(INFO) << "maxProjectionCol: " << maxProjectionCol;

	return sg_OK;
}


/**
*	@Method		 lightLocate
*
*	@Brief		 ȷ�������Ƶ�λ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 vector<Point> coreHsv, const int maxProjectionCol, const float averDis, int *label, const int upRow, const int downRow
*
*	@Para [OUT]	 int *valueArr
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int lightLocate(vector<Point> coreHsv, const int maxProjectionCol, const float averDis, int *label,
	const int upRow, const int downRow, vector<int> &  valueArr)
{
	if (coreHsv.size() == 0)
	{
		LOG(ERROR) << "������ lightLocate  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	//Ĭ�����е㶼��Ϩ���
	for (int i = 0; i < 8; i++)
	{
		valueArr[i] = sg_led_UpCloseDownClose;
	}
	for (int i = 0; i < coreHsv.size(); i++)
	{
		int num = abs(coreHsv[i].x - maxProjectionCol) / averDis;
		if (coreHsv[i].x < maxProjectionCol)
		{
			label[0] = 4 - num;
		}
		else
		{
			label[0] = 5 + num;
		}
		label[1] = abs(coreHsv[i].y - upRow) < abs(coreHsv[i].y - downRow) ? 0 : 1;

		if (label[0] < 0 || label[0] > 7)
		{
			return sg_ERROR;
		}
		valueArr[label[0]] = sg_led_open;

		/*if (label[1] == 0)
		{
		if (valueArr[label[0]] = sg_led_UpCloseDownClose)
		{
		valueArr[label[0]] = sg_led_UpOpenDownClose;
		}
		else if (valueArr[label[0]] = sg_led_UpCloseDownOpen)
		{
		valueArr[label[0]] = sg_led_UpOpenDownOpen;
		}
		}
		else if (label[1] == 1)
		{
		if (valueArr[label[0]] = sg_led_UpCloseDownClose)
		{
		valueArr[label[0]] = sg_led_UpCloseDownOpen;
		}
		else if (valueArr[label[0]] = sg_led_UpOpenDownClose)
		{
		valueArr[label[0]] = sg_led_UpOpenDownOpen;
		}
		}*/

		//LOG(INFO) << "The location of light:(" << coreHsv[i].x << "," << coreHsv[i].y << ")" << endl;
		LOG(INFO) << "The label of light: " << label[0] << label[1];
	}

	return sg_OK;
}



/**
*	@Method		 maxContourRow
*
*	@Brief		 �ҳ���ͨ������һ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointRowGroup
*
*	@Para [OUT]	 vector<Point>& maxPointRow
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxContourRow(const vector<vector<Point>> pointRowGroup, vector<Point>& maxPointRow)
{
	if (pointRowGroup.size() == 0)
	{
		LOG(ERROR) << "������ maxContourRow  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxElement = 0;
	int maxEleNum;//Ԫ���������������еı��
	for (int m = 0; m < pointRowGroup.size(); m++)
	{
		if (pointRowGroup[m].size()>maxElement)
		{
			maxEleNum = m;
			maxElement = pointRowGroup[m].size();
			maxPointRow.assign(pointRowGroup[m].begin(), pointRowGroup[m].end());
		}
	}
	LOG(INFO) << "Size of maxPointRow:" << maxPointRow.size();

	for (int i = 0;i < maxPointRow.size();i++)
	{
		cout << maxPointRow[i] << " ";
	}
	cout << endl;

	return sg_OK;
}


/**
*	@Method		 maxContourCol
*
*	@Brief		 �ҳ���ͨ������һ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointColGroup
*
*	@Para [OUT]	 vector<Point>& maxPointCol
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxContourCol(const vector<vector<Point>> pointColGroup, vector<Point>& maxPointCol)
{
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "������ maxContourCol  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxElement = 0;
	int maxEleNum;//Ԫ���������������еı��
	for (int m = 0; m < pointColGroup.size(); m++)
	{
		if (pointColGroup[m].size()>maxElement)
		{
			maxEleNum = m;
			maxElement = pointColGroup[m].size();
			maxPointCol.assign(pointColGroup[m].begin(), pointColGroup[m].end());
		}
	}
	LOG(INFO) << "Size of maxPointCol:" << maxPointCol.size();

	return sg_OK;
}



/**
*	@Method		 searchSignCol
*
*	@Brief		 �ҵ���ʶ�����ڵ�λ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreMainEdge, const Mat mainEdge, float colScale
*
*	@Para [OUT]	 vector<vector<Point>>& pointColGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchSignCol(const vector<Point> coreMainEdge, const Mat mainEdge,
	vector<vector<Point>>& pointColGroup, float colScale)
{
	if (coreMainEdge.size() == 0)
	{
		LOG(ERROR) << "������ searchSignCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (mainEdge.empty())
	{
		LOG(ERROR) << "������ searchSignCol  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	vector<Point> vertLat;//�洢ÿһ�еĵ���
	vertLat.push_back(coreMainEdge[0]);//����һ����ͨ������ڴ�
	pointColGroup.push_back(vertLat);
	//�����е㰴���������ϵ���δ���������
	for (int i = 1; i < coreMainEdge.size(); i++)
	{
		int k = 0;//��ͬ���������
		vertLat.clear();
		for (; k < pointColGroup.size(); k++)
		{
			if (abs(coreMainEdge[i].x - pointColGroup[k][0].x) <= mainEdge.cols*colScale
				&& pointColGroup[k][0].x > mainEdge.cols / 8.0)
			{
				pointColGroup[k].push_back(coreMainEdge[i]);//���õ���뵱ǰ����
				break;
			}
		}
		//���֮ǰ���������λ�õ��У��������pointGroup��
		if (k == pointColGroup.size())
		{
			vertLat.push_back(coreMainEdge[i]);
			pointColGroup.push_back(vertLat);
		}
	}

	//������ϰ��������ǰ������
	for (int i = 0; i < pointColGroup.size() - 1; i++)
	{
		for (int j = i + 1; j < pointColGroup.size(); j++)
		{
			vector<Point> tempPointCol;
			if (pointColGroup[i][0].x>pointColGroup[j][0].x)
			{
				pointColGroup[i].swap(pointColGroup[j]);
			}
		}
	}

	return sg_OK;
}


/**
*	@Method		 colMoreThanThree
*
*	@Brief		 �ҳ���һ����������3����
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> maxPointRow, const Mat mainEdge, const float averDis
*
*	@Para [OUT]	 const vector<vector<Point>>& pointColGroup, int& signMaxRowNum, int& signColNum, int& signCol
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int colMoreThanThree(const vector<vector<Point>>& pointColGroup, const vector<Point> maxPointRow,
	const Mat mainEdge, const float averDis, int& signMaxRowNum, int& signColNum, int& signCol)
{
	//imshow("mainEdge", mainEdge);
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "������ colMoreThanThree  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "������ colMoreThanThree  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (mainEdge.empty())
	{
		LOG(ERROR) << "������ colMoreThanThree  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	for (int m = 0; m < pointColGroup.size(); m++)
	{
		LOG(INFO) << "size of pointColGroup: " << pointColGroup[m].size();
		LOG(INFO) << pointColGroup[m];
		if (pointColGroup[m].size() >= 3)
		{
			//���ݵ�һ�е������ҳ������ڵ���
			for (int n = 0; n < maxPointRow.size(); n++)
			{
				if (abs(maxPointRow[n].x - pointColGroup[m][0].x) < mainEdge.cols / 80.0)
				{
					LOG(INFO) << "m = " << m << ",n = " << n;
					signMaxRowNum = n;
					signColNum = m;
					signCol = maxPointRow[n].x;
					break;
				}
			}
		}
		if (signMaxRowNum != -1)
		{
			LOG(INFO) << "The col of sign is:" << signCol;
			break;
		}
	}

	if (signMaxRowNum == -1)
	{
		LOG(ERROR) << "������ colMoreThanThree  " << "sg_ERROR_Led_NO_ThreeEleCol";
		return	sg_ERROR;
	}

	return sg_OK;
}


/**
*	@Method		 searchAverDisCol
*
*	@Brief		 �ҳ���־���м��Ϊ��λ�������
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signMaxRowNum, const vector<Point> maxPointRow, const float averDis, const Mat mainEdge, const float colScale
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchAverDisCol(const int signMaxRowNum, const vector<Point> maxPointRow,
	const float averDis, const float cols, const float colScale, vector<Point>& signGroup,int ledtype)
{
	if (signMaxRowNum == -1)
	{
		LOG(ERROR) << "������ searchAverDisCol  " << "sg_ERROR_Led_NO_ThreeEleCol";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "������ searchAverDisCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	
	if (sg_led_type_benderTongXun == ledtype)
	{
		for (int k = signMaxRowNum + 2; k < maxPointRow.size(); k++)
		{
			int nextPtDis = maxPointRow[k].x - maxPointRow[k - 1].x;
			if (abs(nextPtDis - averDis) < cols*colScale)
			{
				if (signGroup.size() == 0 || signGroup.back().x != maxPointRow[k - 1].x)
				{
					signGroup.push_back(maxPointRow[k - 1]);
				}
				signGroup.push_back(maxPointRow[k]);
			}
		}
	}
	else if (sg_led_type_benderBaoHu == ledtype)
	{
		for (int k = 1; k < maxPointRow.size(); k++)
		{
			int nextPtDis = maxPointRow[k].x - maxPointRow[k - 1].x;
			if (abs(nextPtDis - averDis) < cols*colScale)
			{
				if (signGroup.size() == 0 || signGroup.back().x != maxPointRow[k - 1].x)
				{
					signGroup.push_back(maxPointRow[k - 1]);
				}
				signGroup.push_back(maxPointRow[k]);
			}
		}
	}

	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ searchAverDisCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	LOG(INFO) << "The member of signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	return sg_OK;
}


/**
*	@Method		 searchAverDisRow
*
*	@Brief		 �ҳ���־���м��Ϊ��λ�������
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> maxPointCol, const float averDis, const Mat edgeImg, const float colScale
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchAverDisRow(const vector<Point> maxPointCol, const float averDis,
	const Mat edgeImg, const float colScale, vector<Point>& signGroup)
{
	if (maxPointCol.size() == 0)
	{
		LOG(ERROR) << "������ searchAverDisRow  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (edgeImg.empty())
	{
		LOG(ERROR) << "������ searchAverDisRow  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	for (int k = 1; k < maxPointCol.size(); k++)
	{
		int nextPtDis = maxPointCol[k].y - maxPointCol[k - 1].y;
		LOG(INFO) << "nextPtDis:" << nextPtDis;
		if (abs(nextPtDis - averDis) < edgeImg.rows / 60.0
			&&abs(maxPointCol[k].x - maxPointCol[k - 1].x) < edgeImg.cols*colScale)
		{
			LOG(INFO) << "nextPtDis-averDis=" << nextPtDis - averDis;
			if (signGroup.size() == 0 ||
				maxPointCol[k - 1].y - signGroup.back().y > averDis*3.0 / 4)
			{
				signGroup.push_back(maxPointCol[k - 1]);
			}
			signGroup.push_back(maxPointCol[k]);
		}
	}

	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ searchAverDisRow  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	LOG(INFO) << "The member of signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	return sg_OK;
}


/**
*	@Method		 insertMiddlePt
*
*	@Brief		 ����β֮��δ�ҵ��ı�־���в�ֵ
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const float averDis, const int ledKind
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int insertMiddlePt(vector<Point>& signGroup, const float averDis, const int ledbKind)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ insertMiddlePt  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	for (int i = 0; i < signGroup.size() - 1; i++)
	{
		//��������־��©���
		if (ledbKind == sg_led_type_benderTongXun || sg_led_type_benderBaoHu)
		{
			float adjSignDis = signGroup[i + 1].x - signGroup[i].x;
			if (adjSignDis > 1.5*averDis)
			{
				int insertPtNum = (int)(adjSignDis*1.0 / averDis + 0.5) - 1;//��������
				//���м����Ԫ��
				for (int j = 1; j <= insertPtNum; j++)
				{
					Point insertPt;
					insertPt.x = signGroup[i].x + j*averDis;
					insertPt.y = signGroup[i].y;
					signGroup.insert(signGroup.begin() + i + j, insertPt);
				}
			}
		}

		if (ledbKind == sg_led_type_benderZongCha)
		{
			float adjSignDis = signGroup[i + 1].y - signGroup[i].y;
			if (adjSignDis > 1.5*averDis)
			{
				int insertPtNum = (int)(adjSignDis*1.0 / averDis + 0.5) - 1;//��������
																			//���м����Ԫ��
				for (int j = 1; j <= insertPtNum; j++)
				{
					Point insertPt;
					insertPt.y = signGroup[i].y + j*averDis;
					insertPt.x = signGroup[i].x;
					signGroup.insert(signGroup.begin() + i + j, insertPt);
				}
			}
		}
	}

	LOG(INFO) << "The member of new signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	return sg_OK;
}


/**
*	@Method		 comInsertTopEndPt
*
*	@Brief		 ͨѶ�̵����ڱ�־�е���β���в�ֵ
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signCol, const float averDis, const Mat mainEdge
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int comInsertTopEndPt(vector<Point>& signGroup, const int signCol, const float averDis, float cols, int ledKind)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ comInsertTopEndPt  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (ledKind == sg_led_type_benderTongXun)
	{
		while (signGroup.size() != 17)
		{
			Point insertPt;
			if (signGroup[0].x - signCol > 1.5*averDis)
			{
				insertPt.x = signGroup[0].x - averDis;
				insertPt.y = signGroup[0].y;
				signGroup.insert(signGroup.begin(), insertPt);
			}
			else if (cols - signGroup.back().x > 1.5*averDis)
			{
				insertPt.x = signGroup.back().x + averDis;
				insertPt.y = signGroup.back().y;
				signGroup.push_back(insertPt);
			}
			else
			{
				return -1;
			}
		}
	}
	else if (ledKind == sg_led_type_benderBaoHu)
	{
		while (signGroup.size() != 8)
		{
			Point insertPt;
			if (signGroup[0].x > 1.5*averDis || abs(signGroup[0].x - signCol) < 4 * averDis)
			{
				insertPt.x = signGroup[0].x - averDis;
				insertPt.y = signGroup[0].y;
				signGroup.insert(signGroup.begin(), insertPt);
			}
			else if (cols - signGroup.back().x > 1.5*averDis || abs(signGroup.back().x - signCol) < 2 * averDis)
			{
				insertPt.x = signGroup.back().x + averDis;
				insertPt.y = signGroup.back().y;
				signGroup.push_back(insertPt);
			}
			else
			{
				return -1;
			}
		}
	}

	LOG(INFO) << "The member of new signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	LOG(INFO) << "The member of new signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	return sg_OK;
}


/**
*	@Method		 difInsertTopEndPt
*
*	@Brief		 �ݲ�̵����ڱ�־�е���β���в�ֵ����ɾ��
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointColGroup, const float averDis, const Mat edgeImg
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int difInsertTopEndPt(vector<Point>& signGroup, const vector<vector<Point>> pointColGroup,
	const float averDis, const Mat edgeImg)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ difInsertTopEndPt  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "������ difInsertTopEndPt  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (edgeImg.empty())
	{
		LOG(ERROR) << "������ difInsertTopEndPt  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	bool isPtInsert = 0;
	bool isPtErase = 0;
	while (signGroup.size() != 10)
	{
		//���Ԫ�ظ���С��10������в������
		isPtInsert = 0;//�ж��Ƿ��е���Բ���
		isPtErase = 0;//�ж��Ƿ�����е�ɾ��
		if (signGroup.size() < 10)
		{
			Point insertPt;
			for (int i = 0; i < pointColGroup.size(); i++)
			{
				for (int j = 0; j < pointColGroup[i].size(); j++)
				{
					int upPtDis = signGroup[0].y - pointColGroup[i][j].y;
					int downPtDis = pointColGroup[i][j].y - signGroup.back().y;
					if (abs(upPtDis - averDis) < edgeImg.rows / 40)
					{
						isPtInsert = 1;
						insertPt.x = signGroup[0].x;
						insertPt.y = pointColGroup[i][j].y;
						signGroup.insert(signGroup.begin(), insertPt);
					}
					if (abs(downPtDis - averDis) < edgeImg.rows / 40)
					{
						isPtInsert = 1;
						insertPt.x = signGroup.back().x;
						insertPt.y = pointColGroup[i][j].y;
						signGroup.push_back(insertPt);
					}
				}
			}
		}

		//���Ԫ�ظ�������10�������ɾ������
		else if (signGroup.size() > 10)
		{
			//�Ƚ�ǰ������ͺ�������֮��ľ��룬���������Ǹ���ɾ��
			int upPtxDis = signGroup[1].x - signGroup[0].x;
			int upPtyDis = signGroup[1].y - signGroup[0].y;
			float upPtDis = sqrt(pow(upPtxDis, 2) + pow(upPtyDis, 2));
			int downPtxDis = signGroup.back().x - signGroup[signGroup.size() - 2].x;
			int downPtyDis = signGroup.back().y - signGroup[signGroup.size() - 2].y;
			float downPtDis = sqrt(pow(downPtxDis, 2) + pow(downPtyDis, 2));
			if (upPtDis < downPtDis)
			{
				isPtErase = 1;
				signGroup.pop_back();
			}
			else if (upPtDis > downPtDis)
			{
				isPtErase = 1;
				signGroup.erase(signGroup.begin());
			}
			else if (upPtxDis < downPtxDis)
			{
				isPtErase = 1;
				signGroup.pop_back();
			}
			else if (upPtxDis > downPtxDis)
			{
				isPtErase = 1;
				signGroup.erase(signGroup.begin());
			}
			else
			{
				break;
			}
		}
		if (isPtInsert == 0 && isPtErase == 0)
		{
			LOG(ERROR) << "������ difInsertTopEndPt  " << "sg_ERROR_NO_InsertOrErase";
			return	sg_ERROR;
		}
	}

	LOG(INFO) << "The member of new signGroup: ";
	for (int t = 0; t < signGroup.size(); t++)
	{
		LOG(INFO) << signGroup[t] << " ";
	}

	return sg_OK;
}


/**
*	@Method		 searchLightRows
*
*	@Brief		 �ҵ�����С�����ĵ����ڵ���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signColNum, const vector<Point> maxPointRow, const int signMaxRowNum
*
*	@Para [OUT]	 int *lightRow, vector<vector<Point>>& pointColGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchLightRows(int *lightRow, vector<vector<Point>>& pointColGroup, const int signColNum,
	const vector<Point> maxPointRow, const int signMaxRowNum)
{
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "������ difInsertTopEndPt  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "������ searchLightRows  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	//����־�е����е㰴���ϵ��µ�˳������
	for (int m = 0; m < pointColGroup[signColNum].size() - 1; m++)
	{
		for (int n = m + 1; n < pointColGroup[signColNum].size(); n++)
		{
			Point tempPoint;
			if (pointColGroup[signColNum][m].y>pointColGroup[signColNum][n].y)
			{
				tempPoint = pointColGroup[signColNum][m];
				pointColGroup[signColNum][m] = pointColGroup[signColNum][n];
				pointColGroup[signColNum][n] = tempPoint;
			}
		}
	}
	for (int i = 0; i < pointColGroup[signColNum].size(); i++)
	{
		//�ҵ���־�кͱ�־�еĽ����
		if (pointColGroup[signColNum][i].y == maxPointRow[signMaxRowNum].y)
		{
			lightRow[0] = pointColGroup[signColNum][i + 1].y;
			lightRow[1] = pointColGroup[signColNum][i + 2].y;
		}
	}

	if (lightRow[0] == -1 || lightRow[1] == -1)
	{
		LOG(ERROR) << "������ searchLightRows  " << "sg_ERROR_led_NO_lightRow";
		return	sg_ERROR;
	}

	LOG(INFO) << "upLightRow,downLightRow:" << lightRow[0] << " " << lightRow[1];


	return sg_OK;
}


/**
*	@Method		 comLightBlockAnalyze
*
*	@Brief		 ��ͨѶ�̵���ÿ�������ڵ�����ȡ������������
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow,int *valueArr
*
*	@Para [OUT]
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int comLightBlockAnalyze(const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow, vector<int> &  valueArr)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ comLightBlockAnalyze  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	Mat lightBlockImg;
	int lightCount = 0;//���Ƶĸ���
	for (int i = 0; i < signGroup.size(); i++)
	{
		int blockBeginCol = signGroup[i].x - averDis / 2.0;
		Rect block = Rect(blockBeginCol, 0, averDis, mainArea.rows - 1);
		lightBlockImg = mainArea(block).clone();
		//imshow("block" + to_string(i), lightBlockImg);
		//RGB��ɫ�ռ�ת����HSV��
		Mat rectBlockMainArea = mainArea.clone();
		rectangle(rectBlockMainArea, block, Scalar(0, 0, 255), 1);
		Mat hsvImg, hImg, vImg, bImg;
		cvtColor(lightBlockImg, hsvImg, CV_RGB2HSV);
		vector<Mat> hsvChannels;
		split(hsvImg, hsvChannels);
		hImg = hsvChannels[0];
		vImg = hsvChannels[2];
		//imgShowDebug(hImg, "hImg", 0);
		//imgShowDebug(vImg, "vImg", 0);

		vector<Mat> rgbChannels;
		split(lightBlockImg, rgbChannels);
		bImg = rgbChannels[2];
		//imgShowDebug(bImg, "bImg", 0);

		Mat grayBlock;
		cvtColor(lightBlockImg, grayBlock, CV_BGR2GRAY);
		//imgShowDebug(grayBlock, "grayBlock", 0);

		//imgShowDebug(rectBlockMainArea, "rectBlockMainArea", 0);

		for (int m = 0; m < lightBlockImg.rows; m++)
		{
			for (int n = 0; n < lightBlockImg.cols; n++)
			{
				grayBlock.at<uchar>(m, n) = (vImg.at<uchar>(m, n) + bImg.at<uchar>(m, n)) / 2.0;
			}
		}

		//ͨ������h�ռ�Ķ�ֵͼ�����������ݱ������������
		Mat hBinary;
		threshold(hImg, hBinary, 20, 255, CV_THRESH_BINARY);
		imgShowDebug(hBinary, "hBinary", 0);
		//ͨ������v�ռ���b�ռ���ӵĻҶ�ͼ���������ݵ�����(����ʵ��ó�)
		Mat otsuBlock;
		threshold(grayBlock, otsuBlock, 0, 255, CV_THRESH_OTSU);
		imgShowDebug(otsuBlock, "otsuBlock", 0);

		//����ֵͼ���е�ÿ��С��������ȡ�������з���
		int squareRadius = averDis / 3.0;
		bool isLight = 0;
		//���ݵƵ������ÿ�����鸳ֵ
		valueArr[i] = sg_led_UpCloseDownClose;
		for (int k = 0; k < 2; k++)
		{
			Rect lightPt;
			Point leftUpPt;
			leftUpPt.x = averDis / 2.0 - squareRadius;
			leftUpPt.y = lightRow[k] - squareRadius;
			int squareWidth = 2 * squareRadius;
			int hBinWhiteArea = 0;
			int otsuWhiteArea = 0;

			//ͳ��hBianry�е�������İ�ɫ���ص����
			for (int u = 0; u < squareWidth; u++)
			{
				for (int v = 0; v < squareWidth; v++)
				{
					if (hBinary.at<uchar>(u + leftUpPt.y, v + leftUpPt.x) == 255)
					{
						hBinWhiteArea++;
					}
					if (otsuBlock.at<uchar>(u + leftUpPt.y, v + leftUpPt.x) == 255)
					{
						otsuWhiteArea++;
					}
				}
			}
			if (hBinWhiteArea > pow(squareWidth, 2) / 2.0&&
				otsuWhiteArea > pow(squareWidth, 2) / 3.0)
			{
				isLight = 1;
				lightCount++;
				LOG(INFO) << "The label of light: " << i << k;

				if (k == 0)
				{
					valueArr[i] = sg_led_UpOpenDownClose;
				}
				else if (k == 1 && valueArr[i] == sg_led_UpCloseDownClose)
				{
					valueArr[i] = sg_led_UpCloseDownOpen;
				}
				else if (k == 1 && valueArr[i] == sg_led_UpOpenDownClose)
				{
					valueArr[i] = sg_led_UpOpenDownOpen;
				}
			}
			//cout << "hBinWhiteArea=" << hBinWhiteArea << "otsuWhiteArea=" << otsuWhiteArea << endl;

		}
		//waitKey(0);
	}

	if (lightCount == 0)
	{
		LOG(INFO) << "None light bright.";
	}

	return sg_OK;
}


/**
*	@Method		 searchPointSameCol
*
*	@Brief		 �ҵ�λ��ͬһ�еĵ���
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreEdge, Mat edgeImg, float colScale
*
*	@Para [OUT]  vector<vector<Point>>& pointColGroup
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int searchPointSameCol(vector<vector<Point>>& pointColGroup, const vector<Point> coreEdge,
	Mat edgeImg, float colScale)
{
	if (coreEdge.size() == 0)
	{
		LOG(ERROR) << "������ searchPointSameCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	vector<Point> verLat;//�洢ÿһ�еĵ���
	verLat.push_back(coreEdge[0]);//����һ����ͨ������ڴ�
	pointColGroup.push_back(verLat);
	//�����е㰴�պ������ϵ���δ���������
	for (int i = 1; i < coreEdge.size(); i++)
	{
		int k = 0;//��ͬ�����������
		verLat.clear();
		for (; k < pointColGroup.size(); k++)
		{
			if (abs(coreEdge[i].x - pointColGroup[k][0].x) <= edgeImg.cols*colScale)
			{
				pointColGroup[k].push_back(coreEdge[i]);//���õ���뵱ǰ����
				break;
			}
		}
		//���֮ǰ�����������ȵ��У��������pointColGroup��
		if (k == pointColGroup.size())
		{
			verLat.push_back(coreEdge[i]);
			pointColGroup.push_back(verLat);
		}
	}

	for (int j = 0; j < pointColGroup.size(); j++)
	{
		LOG(INFO) << "pointColGroup" << to_string(j) << ":" << pointColGroup[j];
	}

	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "������ searchPointSameCol  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	return sg_OK;
}


/**
*	@Method		 difLightBlockAnalyse
*
*	@Brief		 ��ÿһ�ν�ȡ������������
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> signGroup, const float averDis, const Mat lampImg,int* valueArr
*
*	@Para [OUT]
*
*	@Return		 int���������ͷ����룬���sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int difLightBlockAnalyse(const vector<Point> signGroup, const float averDis, const Mat lampImg, vector<int> & valueArr)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "������ difLightBlockAnalyse  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (lampImg.empty())
	{
		LOG(ERROR) << "������ difLightBlockAnalyse  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	Mat lightBlockImg;
	int lightCount = 0;//���Ƶĸ���
	for (int i = 0; i < signGroup.size(); i++)
	{
		int blockBeginRow = signGroup[i].y - averDis / 2.0;
		int blockBeginCol = signGroup[i].x - 2 * averDis;
		blockBeginCol = blockBeginCol >= 0 ? blockBeginCol : 0;
		int blockEndCol = signGroup[i].x + 2 * averDis;
		blockEndCol = blockEndCol < lampImg.cols ? blockEndCol : lampImg.cols;
		int blockWidth = blockEndCol - blockBeginCol + 1;
		Rect block = Rect(blockBeginCol, blockBeginRow, blockWidth, int(averDis));
		lightBlockImg = lampImg(block).clone();
		//imshow("block" + to_string(i), lightBlockImg);
		//RGB��ɫ�ռ�ת����HSV��
		Mat rectBlocklampImg = lampImg.clone();
		rectangle(rectBlocklampImg, block, Scalar(0, 0, 255), 1);
		imgShowDebug(rectBlocklampImg, "rectBlocklampImg", 0);
		Mat hsvImg, hImg, sImg, vImg;
		cvtColor(lightBlockImg, hsvImg, CV_RGB2HSV);
		vector<Mat> hsvChannels;
		split(hsvImg, hsvChannels);
		vImg = hsvChannels[2];
		imgShowDebug(vImg, "vImg", 0);

		//ͨ������v�ռ�Ķ�ֵͼ�����������ݱ������������
		Mat vBinary;
		threshold(vImg, vBinary, 0, 255, CV_THRESH_OTSU);
		imgShowDebug(vBinary, "vBinary", 0);

		//����ֵͼ���е�ÿ��С��������ȡ�������з���
		int vBinWhiteArea = 0;
		int vBinBlackArea = 0;
		//ͳ��hBianry�е�������İ�ɫ���ص����
		for (int u = 0; u < int(averDis); u++)
		{
			for (int v = 0; v < blockWidth; v++)
			{
				if (vBinary.at<uchar>(u, v) == 255)
				{
					vBinWhiteArea++;
				}
				else if (vBinary.at<uchar>(u, v) == 0)
				{
					vBinBlackArea++;
				}
			}
		}
		if (vBinWhiteArea < vBinBlackArea)
		{
			lightCount++;
			valueArr[i] = sg_led_open;
			LOG(INFO) << "Light " << i << ":open" << endl;
		}
		else
		{
			valueArr[i] = sg_led_close;
			LOG(INFO) << "Light " << i << ":close" << endl;
		}
	}
	if (lightCount == 0)
	{
		LOG(INFO) << "None light bright." << endl;
	}

	return sg_OK;
}