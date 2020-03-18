/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgtask_led.h
*
* 	@Brief	ָʾ��ʶ����ͷ�ļ�.
*	
* 	@Author	Author
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

#ifndef SGTASK_LED_H
#define SGTASK_LED_H


#include <opencv2\opencv.hpp>
using namespace cv;


// ָʾ�Ƽ��ʶ�����.
int Detect_led(const Mat srcImg, const int ledtype, vector<int> &  valueArr);

// �ų���ɫ���ص��Ӱ���ֵ��
int otsuThreshold(const Mat grayImage, Mat& otsuImg);

// �ݲ�̵���ָʾ�Ƽ��
int led_Zongcha_detect(const Mat srcImg, vector<int> &  valueArr);

// �����̵���ָʾ�Ƽ��
int led_Baohu_detect(const Mat srcImg, vector<int> &  valueArr);

// ͨѶ�̵���ָʾ�Ƽ��
int led_Tongxun_detect(const Mat srcImg, vector<int> &  valueArr);

// �����Ƽ��
int led_flash_detect(const Mat srcImg, const Mat templateImg, vector<int> &  valueArr);

// ����ͶӰѡȡ������
int BoundProjection(const Mat Image, int *location, float scale);

//���Ҷ�ֵ��ͼ���е�����
int searchCore(Mat binaryImg, vector<Point>& core, float colScale, float rowScale);

//��ͼ�������бУ��
int rotateCorrection(Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg, int ledKind);

//��ȡHsv�ռ��б�Ե�����ͼ��
int getHsvEdge(Mat mainArea, Mat& edgeHsv);

//�ҵ�λ��ͬһ�еĵ���
int searchPointSameRow(vector<vector<Point>>& pointGroup, vector<Point>& coreMainOtsu,
	int rows, float rowScale);

//�ҵ�������һ����������
int searchMostSilmilarRow(const vector<vector<Point>> pointGroup,
	vector<Point>& downPoint, int cols, int& upRow, int& downRow);

//��������������������е���
int arrangePoint(vector<Point>& pointList, int rowOrCol);


//ѡ������֮���������ֵ��Ϊ��ļ������С©����������ĸ���
int maxPointDis(const vector<Point>pointList, float& averDis, int cols, float colScale, int knobKind);

//�����е�֮������д�ֱͶӰ������һ��Ϊ�ο���
int maxVertProjection(const Mat mainOtsu, const int upRow, const int downRow,
	const vector<Point> pointList, int& maxProjectionCol);


//ȷ�������Ƶ�λ��
int lightLocate(vector<Point> coreHsv, const int maxProjectionCol, const float averDis, int *label,
	const int upRow, const int downRow, vector<int> &  valueArr);


//�ҳ���ͨ������һ��
int maxContourRow(const vector<vector<Point>> pointRowGroup, vector<Point>& maxPointRow);


//�ҳ���ͨ������һ��
int maxContourCol(const vector<vector<Point>> pointColGroup, vector<Point>& maxPointCol);


//�ҵ���ʶ�����ڵ�λ��
int searchSignCol(const vector<Point> coreMainEdge, const Mat mainEdge,
	vector<vector<Point>>& pointColGroup, float colScale);

//�ҳ���һ����������3����
int colMoreThanThree(const vector<vector<Point>>& pointColGroup, const vector<Point> maxPointRow,
	const Mat mainEdge, const float averDis, int& signMaxRowNum, int& signColNum, int& signCol);

//�ҳ���־���м��Ϊ��λ�������
int searchAverDisCol(const int signMaxRowNum, const vector<Point> maxPointRow,
	const float averDis, const float cols, const float colScale, vector<Point>& signGroup, int ledtype);

//�ҳ���־���м��Ϊ��λ�������
int searchAverDisRow(const vector<Point> maxPointCol, const float averDis,
	const Mat edgeImg, const float colScale, vector<Point>& signGroup);

//����β֮��δ�ҵ��ı�־���в�ֵ
int insertMiddlePt(vector<Point>& signGroup, const float averDis, const int ledbKind);

//ͨѶ�̵����ڱ�־�е���β���в�ֵ
int comInsertTopEndPt(vector<Point>& signGroup, const int signCol, const float averDis, float cols, int ledKind);

//�ݲ�̵����ڱ�־�е���β���в�ֵ����ɾ��
int difInsertTopEndPt(vector<Point>& signGroup, const vector<vector<Point>> pointColGroup,
	const float averDis, const Mat edgeImg);

//�ҵ�����С�����ĵ����ڵ���
int searchLightRows(int *lightRow, vector<vector<Point>>& pointColGroup, const int signColNum,
	const vector<Point> maxPointRow, const int signMaxRowNum);


//��ͨѶ�̵���ÿ�������ڵ�����ȡ������������
int comLightBlockAnalyze(const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow, vector<int> & valueArr);

//�ҵ�λ��ͬһ�еĵ���
int searchPointSameCol(vector<vector<Point>>& pointColGroup, const vector<Point> coreEdge,
	Mat edgeImg, float colScale);

//��ÿһ�ν�ȡ������������
int difLightBlockAnalyse(const vector<Point> signGroup, const float averDis, const Mat lampImg, vector<int> &  valueArr);

#endif // !SGTASK_LED_H
