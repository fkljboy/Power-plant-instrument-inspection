/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_transform.cpp
*
* 	@Brief	ͼ��任����.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-17
*
*	@MethodList
*		1.	int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg);
*
*		2.	int Trans_logTransform(const Mat srcImg, const int c, Mat & result);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/17		SHEN		Created.
*
*	2.0		3/18		SHEN		Add Log Function.
*
*/ 

#include "sgfunc_transform.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"

#include "../sgFunction/sgfunc_imageio.h"


#include <opencv2\opencv.hpp>
using namespace cv;

/**
*	@Method		Trans_linearTransform
*
*	@Brief		���Ա任ͼ��ı�Աȶ�.
*
*	@Author		Lu Xin
*
*	@Para [IN]	const Mat srcImg��	����Դͼ
*
*				const float a��	�任ϵ��
*
*				const int b��	�任ƫ����
*
*	@Para [OUT]	Mat & resultImg��	�任���ͼ��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		���Ա任��ʽ�� y = a * x + b.
*
*	@Create		2018-03-17
*/

int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg)
{
	// 1. �п�
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	// 2. �������Ա任
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;

	Mat result = Mat::zeros(srcImg.size(), srcImg.type());

	// �����ص�����ͨ����ֵ�������Ա任
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				result.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(a*(srcImg.at<Vec3b>(i, j)[c]) + b);
			}
		}
	}

	// 3. ���÷���
	resultImg = result;
	return sg_OK;

}




/**
*	@Method		Trans_logTransform
*
*	@Brief		�����任��������ֵ�ϵ͵�����.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*				const int c
*
*	@Para [OUT]	Mat & result
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		�����任��ʽ��y = c * log(x)
*
*	@Create		2018-03-18
*/
int Trans_logTransform(const Mat srcImg, const int c, Mat & result)
{

	// 1. �п�
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	// 2. ����
	Mat image = srcImg.clone();

	result = Mat::zeros(image.size(), image.type());

	add(image, Scalar(1.0, 1.0, 1.0), image);

	image.convertTo(image, CV_32F);

	log(image, result);

	result = c*result;

	normalize(result, result, 0, 255, NORM_MINMAX);

	convertScaleAbs(result, result);

	return sg_OK;
}



/**
*	@Method		undistortImg
*
*	@Brief		��ͼ����л���У��.
*
*	@Author		Shen Xiaohai
*
*	@Para [IN]	const Mat srcImg��	����Դͼ
*
*				string cameraData�� ��������ļ���·��
*
*	@Para [OUT]	Mat & resultImg��	�任���ͼ��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		
*
*	@Create		2018-05-22
*/

int undistortImg(const Mat srcImg, Mat & resultImg, int cameraType)
{
	LOG(INFO) << "���뺯����undistortImg������У��";

	int resp = sg_OK;

	// 1. �п�
	if (srcImg.empty())
	{
		LOG(ERROR) << "����������У������undistortImg " << "������ͼ��Ϊ��";
		resp = sg_ERROR;
		return	resp;
	}

	// 2.�����������ѡ�ѡ���Ӧ��������У��

	if (sg_Camera_Far == cameraType)	// Զ��
	{
		// 1. ��ȡ����ڲ�
		Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
		cameraMatrix.at<double>(0, 0) = 2.6710e+03;
		cameraMatrix.at<double>(0, 1) = -2.0644;
		cameraMatrix.at<double>(0, 2) = 966.6570;
		cameraMatrix.at<double>(1, 0) = 0;
		cameraMatrix.at<double>(1, 1) = 2.6724e+03;
		cameraMatrix.at<double>(1, 2) = 499.7752;
		cameraMatrix.at<double>(2, 0) = 0;
		cameraMatrix.at<double>(2, 1) = 0;
		cameraMatrix.at<double>(2, 2) = 1;

		// 2. ��ȡ����ϵ��
		Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		distCoeffs.at<double>(0, 0) = -0.2799;
		distCoeffs.at<double>(1, 0) = -0.4642;
		distCoeffs.at<double>(2, 0) = 4.9326e-04;
		distCoeffs.at<double>(3, 0) = 2.8743e-04;
		distCoeffs.at<double>(4, 0) = 0;

		// 3. ���л���У��
		undistort(srcImg, resultImg, cameraMatrix, distCoeffs);
	}
	else if (sg_Camera_Near == cameraType)	// ����
	{
		//Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
		//cameraMatrix.at<double>(0, 0) = 1.6739e+03;
		//cameraMatrix.at<double>(0, 1) = -0.6325;
		//cameraMatrix.at<double>(0, 2) = 963.5358;
		//cameraMatrix.at<double>(1, 0) = 0;
		//cameraMatrix.at<double>(1, 1) = 1.6758e+03;
		//cameraMatrix.at<double>(1, 2) = 525.2600;
		//cameraMatrix.at<double>(2, 0) = 0;
		//cameraMatrix.at<double>(2, 1) = 0;
		//cameraMatrix.at<double>(2, 2) = 1;

		//Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		//distCoeffs.at<double>(0, 0) = -0.3553;
		//distCoeffs.at<double>(1, 0) = 0.1097;
		//distCoeffs.at<double>(2, 0) = -1.1985e-05;
		//distCoeffs.at<double>(3, 0) = -1.6406e-04;
		//distCoeffs.at<double>(4, 0) = 0;
		Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
		cameraMatrix.at<double>(0, 0) = 1.4820e+03;
		cameraMatrix.at<double>(0, 1) = 8.1249;
		cameraMatrix.at<double>(0, 2) = 899.4933;
		cameraMatrix.at<double>(1, 0) = 0;
		cameraMatrix.at<double>(1, 1) = 1.4781e+03;
		cameraMatrix.at<double>(1, 2) = 478.4515;
		cameraMatrix.at<double>(2, 0) = 0;
		cameraMatrix.at<double>(2, 1) = 0;
		cameraMatrix.at<double>(2, 2) = 1;

		Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		distCoeffs.at<double>(0, 0) = -0.0643;
		distCoeffs.at<double>(1, 0) = -0.4411;
		distCoeffs.at<double>(2, 0) = -0.0079;
		distCoeffs.at<double>(3, 0) = -0.0170;
		distCoeffs.at<double>(4, 0) = 0;

		// �ճ�����һ�ԱȽϿ��׵�����
		//Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		//distCoeffs.at<double>(0, 0) = -0.1843;
		//distCoeffs.at<double>(1, 0) = -0.5411;
		//distCoeffs.at<double>(2, 0) = -0.0079;
		//distCoeffs.at<double>(3, 0) = -0.0170;
		//distCoeffs.at<double>(4, 0) = 0;

		// 3. ���л���У��
		undistort(srcImg, resultImg, cameraMatrix, distCoeffs);
	}
	else
	{
		LOG(ERROR) << "����������У������undistortImg " << "û�ж�Ӧ����У��ѡ��";
		resp = sg_Camera_NoOption;
		return	resp;
	}

	imgShowDebug(resultImg, "У��ͼ��", false);

	LOG(INFO) << "�˳�������undistortImg������У��";
	return resp;
}

