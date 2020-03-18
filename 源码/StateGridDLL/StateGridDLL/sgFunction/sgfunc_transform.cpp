/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_transform.cpp
*
* 	@Brief	图像变换函数.
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
*	@Brief		线性变换图像改变对比度.
*
*	@Author		Lu Xin
*
*	@Para [IN]	const Mat srcImg：	输入源图
*
*				const float a：	变换系数
*
*				const int b：	变换偏置量
*
*	@Para [OUT]	Mat & resultImg：	变换后的图像
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		线性变换公式： y = a * x + b.
*
*	@Create		2018-03-17
*/

int Trans_linearTransform(const Mat srcImg, const float a, const int b, Mat & resultImg)
{
	// 1. 判空
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	// 2. 进行线性变换
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;

	Mat result = Mat::zeros(srcImg.size(), srcImg.type());

	// 对像素点三个通道的值进行线性变换
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

	// 3. 引用返回
	resultImg = result;
	return sg_OK;

}




/**
*	@Method		Trans_logTransform
*
*	@Brief		对数变换增大像素值较低的区域.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*				const int c
*
*	@Para [OUT]	Mat & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		对数变换公式：y = c * log(x)
*
*	@Create		2018-03-18
*/
int Trans_logTransform(const Mat srcImg, const int c, Mat & result)
{

	// 1. 判空
	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	// 2. 处理
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
*	@Brief		对图像进行畸变校正.
*
*	@Author		Shen Xiaohai
*
*	@Para [IN]	const Mat srcImg：	输入源图
*
*				string cameraData： 相机配置文件的路径
*
*	@Para [OUT]	Mat & resultImg：	变换后的图像
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		
*
*	@Create		2018-05-22
*/

int undistortImg(const Mat srcImg, Mat & resultImg, int cameraType)
{
	LOG(INFO) << "进入函数：undistortImg，畸变校正";

	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数（畸变校正）：undistortImg " << "待处理图像为空";
		resp = sg_ERROR;
		return	resp;
	}

	// 2.根据相机焦距选项，选择对应参数进行校正

	if (sg_Camera_Far == cameraType)	// 远侧
	{
		// 1. 获取相机内参
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

		// 2. 获取畸变系数
		Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		distCoeffs.at<double>(0, 0) = -0.2799;
		distCoeffs.at<double>(1, 0) = -0.4642;
		distCoeffs.at<double>(2, 0) = 4.9326e-04;
		distCoeffs.at<double>(3, 0) = 2.8743e-04;
		distCoeffs.at<double>(4, 0) = 0;

		// 3. 进行畸变校正
		undistort(srcImg, resultImg, cameraMatrix, distCoeffs);
	}
	else if (sg_Camera_Near == cameraType)	// 近侧
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

		// 凑出来的一对比较靠谱的数据
		//Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
		//distCoeffs.at<double>(0, 0) = -0.1843;
		//distCoeffs.at<double>(1, 0) = -0.5411;
		//distCoeffs.at<double>(2, 0) = -0.0079;
		//distCoeffs.at<double>(3, 0) = -0.0170;
		//distCoeffs.at<double>(4, 0) = 0;

		// 3. 进行畸变校正
		undistort(srcImg, resultImg, cameraMatrix, distCoeffs);
	}
	else
	{
		LOG(ERROR) << "函数（畸变校正）：undistortImg " << "没有对应畸变校正选项";
		resp = sg_Camera_NoOption;
		return	resp;
	}

	imgShowDebug(resultImg, "校正图像", false);

	LOG(INFO) << "退出函数：undistortImg，畸变校正";
	return resp;
}

