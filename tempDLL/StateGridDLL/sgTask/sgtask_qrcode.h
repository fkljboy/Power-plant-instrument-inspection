/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_qrcode.h
*
* 	@Brief	��ά���⺯��ͷ�ļ�.
*
* 	@Author	LU Xin
*
* 	@Create	2018-05-10
*
*	@MethodList
*		int Detect_qrcode(Mat image);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		5/10		LU   		created.
*
*/

#ifndef SGTASK_QRCODE_H
#define SGTASK_QRCODE_H

#include <opencv2\opencv.hpp>
using namespace cv;

#include "../sgCore/sgcore_def.h"

// ��ά������
int Detect_qrcode_multi(const Mat image, vector<QRCodePos> &  posList, vector<string> & contentList);

// ����ָ����ά����������λ��
int Search_qrcode(const Mat srcImg, const string content, QRCodePos & qrLocation);


#endif // !SGTASK_QRCODE_H
