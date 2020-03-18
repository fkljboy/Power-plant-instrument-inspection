/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_knob.cpp
*
* 	@Brief	旋钮检测函数.
*
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1.	int Detect_knob(const Mat srcImg, const unsigned int Knobtype, const unsigned int platetype, unsigned int & angle);
*
*		2.	int PanelDetect_knob(const Mat srcImg, const unsigned int platetype, Mat & panel);
*
*		3.	int AngleDetect_knob(const Mat srcImg, const unsigned int Knobtype, unsigned int & angle);
*
*		4.	int PanelAreaMaybe(const Mat srcImg, Mat & erodeImg, const unsigned int platetype,const vector<vector<Point>> contours, int & panelNum, vector<Rect> & boundRect);
*
*		5.	int BoundProjection(const Mat erodeImg, int * location);
*
*		6.	int PanelLocation(const Mat erodeImg, const vector<Rect> boundRect, const int panelNum, int * location);
*
*		7.	int removeFrame(const Mat knobImg_bin, const Mat knob_Img, Mat & result);
*
*		8.	int SquareHeadKnobDetection(const Mat srcImg, unsigned int & resultAngle);
*
*		9.	int angleOfMaxLine(const Mat edge, Mat & drawImg, int & angle);
*
*		10.	int link_gap(Mat &threImage);
*
*		11.	int extend_Bound(const Mat threMat, Mat & result);
*
*		12.	int cacBoundRectRandomDirection(const Mat srcMat, int & angle);
*
*		13.	int SharpHeadKnobDetection(const Mat srcImg, unsigned int & resultAngle);
*
*       14. int eraseSmallArea(Mat edge, Mat srcImg, Mat& mainAreaImg);
*
*       15. int CircleKnobDetection(const Mat srcImg, int & resultAngle);
*
*       16. int searchCircleKnob(Mat binImg, vector<Point>& knobContour);
*
*       17. int circleKnobAngleCalc(const Mat srcImg, const Mat otsuImg, vector<Point> knobContour, int& resultAngle);
*
*	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/15		SHEN		created.
*
*	2.0		3/17		SHEN		Add 12 Methods.
*
*/


#include "sgtask_knob.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_math.h"

#include "../sgFunction/sgfunc_transform.h"
#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"
#include "../sgFunction/sgfunc_imageio.h"

#include <opencv2\opencv.hpp>
using namespace cv;


/**
*	@Method		Detect_knob
*
*	@Brief		旋钮检测入口.
*
*	@Para [IN]	const Mat srcImg：	输入旋钮区域图像（经过ROI处理）
*
*				const unsigned int Knobtype:	旋钮头型：方头or尖头
*												1. 方头: sg_knob_type_Square
*												2. 尖头: sg_knob_type_Sharp
*
*				const unsigned int platetype：	旋钮表盘：方形or矩形
*												1. 方形:	sg_knobplate_type_Square
*												2. 矩形:	sg_knobplate_type_Rectangle
*
*	@Para [OUT]	unsigned int & angle：旋钮的角度（下一步，根据定义规则，确认旋钮角度对应旋钮档位）
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		None
*
*	@Author		Lu Xin
*
*	@Create		2018-03-15
*/

int Detect_knob(const Mat srcImg, const unsigned int Knobtype, int & angle)
{
	int resp = sg_OK;	// 错误类型返回
	// 1. 判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： Detect_knob  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	// 2. 表盘区域检测

	Mat plateArea;		//表盘区域

						// 如果是圆形就跳过表盘，使用了矩形和方形的参数
	if (Knobtype != sg_knob_type_Circle)
	{
		resp = PanelDetect_knob(srcImg, Knobtype, plateArea);
	}
	else
	{
		plateArea = srcImg;
	}


	// 3. 旋钮角度检测
	int angleDetc = 0;	//检测结果

	resp = AngleDetect_knob(plateArea, Knobtype, angleDetc);

	// 4. 返回结果
	angle = angleDetc;

	LOG(INFO) << "angle of knob:" << angle << endl;

	return sg_OK;
}


/**
*	@Method		PanelDetect
*
*	@Brief		旋钮表盘定位.
*
*	@Author		Lu Xin
*
*	@Para [IN]	const Mat srcImg： 待检测图像
*
*				const unsigned int platetype：	旋钮表盘：方形or矩形
*												1. 方形:	sg_knobplate_type_Square
*												2. 矩形:	sg_knobplate_type_Rectangle
*
*	@Para [OUT]	Mat & panel：返回旋钮表盘区域图像
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int PanelDetect_knob(const Mat srcImg, const unsigned int platetype, Mat & panel)
{
	int resp = sg_OK;	// 错误类型返回

	// 1. 判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： PanelDetect_knob  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}


	// 2. 对原图像进行resize操作
	Mat resizeImg;
	int col = srcImg.cols;
	int row = srcImg.rows;
	int len = col <= row ? col : row;
	float scale = 300.0 / len;
	resize(srcImg, resizeImg, Size(), scale, scale, CV_INTER_AREA);
	imgShowDebug(resizeImg, "resizeImg", 0);

	// 3. 线性变换增强旋钮和背景区域的对比度
	Mat linearImg;
	float trans_a = 1.25;
	int trans_b = 0;

	resp = Trans_linearTransform(resizeImg, trans_a, trans_b, linearImg);
	CHECKRESP(resp);
	imgShowDebug(linearImg, "linearImg", 0);

	// 4. 灰度化
	Mat grayImg;

	cvtColor(linearImg, grayImg, CV_BGR2GRAY);

	// 5. 自适应阈值二值化
	Mat binaryImg;
	double maxValue = 255;
	int blockSize = 25;
	double C = 10;
	adaptiveThreshold(grayImg, binaryImg, maxValue, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, blockSize, C);
	imgShowDebug(binaryImg, "binaryImg", 0);

	// 6. 图像腐蚀，消除连通域之间的粘连
	Mat element;
	element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	Mat erodeImage;
	erode(binaryImg, erodeImage, element);
	imgShowDebug(erodeImage, "erodeImg", 0);

	// 7.1 寻找连通域
	int panelNum = -1;
	vector<vector<Point>> contours;
	Mat erodeImg = erodeImage.clone();
	findContours(erodeImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	if (contours.size() == 0)
	{
		LOG(ERROR) << "函数： PanelDetect_knob  " << "sg_ERROR_knob_cacBound_NOCONTOUR";
		return sg_ERROR;
	}

	vector<Rect> boundRect(contours.size());

	resp = PanelAreaMaybe(resizeImg, erodeImg, platetype, contours, panelNum, boundRect);
	CHECKRESP(resp);

	// 7.2 扣取旋钮表盘区域
	Mat knobImg, knobImg_binary;
	resp = GetPanelArea(resizeImg, erodeImg, binaryImg, boundRect, panelNum, knobImg, knobImg_binary);
	imgShowDebug(knobImg, "knobImg", 0);
	CHECKRESP(resp);

	// 8. 剔除四周边框
	removeFrame(knobImg_binary, knobImg, panel);
	len = panel.cols <= panel.rows ? panel.cols : panel.rows;
	scale = 300.0 / len;
	resize(panel, panel, Size(), scale, scale, CV_INTER_AREA);
	imgShowDebug(panel, "panel", 0);

	return sg_OK;
}


/**
*	@Method		removeFrame
*
*	@Brief		剔除四周边框.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat knobImg_bin
*
*	@Para [OUT]	Mat & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int removeFrame(const Mat knobImg_bin, const Mat knob_Img, Mat & result)
{
	if (knobImg_bin.empty() || knob_Img.empty())
	{
		LOG(ERROR) << "函数： removeFrame  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	int location[4];

	int rows = knobImg_bin.rows;
	int cols = knobImg_bin.cols;
	int blackProjection;

	// location[0]存储起始行
	for (int i = 0; i < rows / 8; i++)
	{
		blackProjection = 0;
		for (int j = 0; j < cols; j++)
		{
			if (knobImg_bin.at<uchar>(i, j) == 0)
				blackProjection++;
		}
		location[0] = i;
		if (blackProjection < cols / 6.0)
			break;
	}
	cout << "blackProjection:" << blackProjection << endl;

	// location[1]存储终止行
	for (int i = rows - 1; i > rows * 7 / 8; i--)
	{
		blackProjection = 0;
		for (int j = 0; j < cols; j++)
		{
			if (knobImg_bin.at<uchar>(i, j) == 0)
				blackProjection++;
		}
		location[1] = i;
		if (blackProjection < cols / 6.0)
			break;
	}
	cout << "blackProjection:" << blackProjection << endl;

	// location[2]存储起始列
	for (int i = 0; i < cols / 8; i++)
	{
		blackProjection = 0;
		for (int j = 0; j < rows; j++)
		{
			if (knobImg_bin.at<uchar>(j, i) == 0)
				blackProjection++;
		}
		location[2] = i;
		if (blackProjection < rows / 6.0)
			break;
	}
	cout << "blackProjection:" << blackProjection << endl;

	// location[3]存储终止列
	for (int i = cols - 1; i > cols * 7 / 8; i--)
	{
		blackProjection = 0;
		for (int j = 0; j < rows; j++)
		{
			if (knobImg_bin.at<uchar>(j, i) == 0)
				blackProjection++;
		}
		location[3] = i;
		if (blackProjection < rows / 6.0)
			break;
	}
	cout << "blackProjection:" << blackProjection << endl;

	int height = location[1] - location[0] + 1;
	int width = location[3] - location[2] + 1;

	result = knob_Img(Rect(location[2], location[0], width, height));
	if (height < width*2.0 / 3.0 || width < height*2.0 / 3.0)
	{
		LOG(ERROR) << "函数： removeFrame  " << "旋钮未找到panel";
		return	sg_ERROR;
	}

	return sg_OK;
}




/**
*	@Method		PanelAreaMaybe
*
*	@Brief		对每个提取出来的连通域进行分析，返回表盘可能区域的连通域编号.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg：源图，绘图调试用
*
*				const Mat erodeImg：腐蚀图
*
*				const unsigned int platetype： panel类型
*
*
*	@Para [OUT]	int & panelNum
*
*				vector<Rect> & boundRect
*
*				Mat & erodeImgback
*
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int PanelAreaMaybe(const Mat srcImg, Mat & erodeImg, const unsigned int platetype, const vector<vector<Point>> contours, int & panelNum, vector<Rect> & boundRect)
{
	if (srcImg.empty() || erodeImg.empty())
	{
		LOG(ERROR) << "函数： PanelAreaMaybe  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	vector<vector<Point>> conPoint(contours.size());

	//Mat drawing = srcImg.clone();

	int nrows = srcImg.rows;
	int ncols = srcImg.cols;
	int min_boundRect = nrows*ncols;

	for (int k = 0; k < contours.size(); k++)
	{
		approxPolyDP(Mat(contours[k]), conPoint[k], 3, true);
		boundRect[k] = boundingRect(Mat(conPoint[k]));
		Scalar color = Scalar(0, 0, 255);

		// 用红色的矩形框标出检测出来的连通域
		//rectangle(drawing, boundRect[k].tl(), boundRect[k].br(), color, 2, 8, 0);

		int x0 = boundRect[k].x;
		int y0 = boundRect[k].y;
		int width = boundRect[k].width;
		int height = boundRect[k].height;
		float rate = 1.0*width / height;
		int x1 = x0 + width;
		int y1 = y0 + height;

		// 填充面积小于整幅图像百分之一的小区域，排除干扰
		if (boundRect[k].area()<nrows*ncols / 100)
		{
			for (int i = x0; i < x0 + width; i++)
			{
				for (int j = y0; j < y0 + height; j++)
				{
					erodeImg.at<uchar>(j, i) = 255;
				}
			}
		}

		/*求满足条件的最小矩形，排除外边界的干扰。在此对得到的旋钮roi图像有所要求：
		旋钮的长和宽介于图像尺寸的0.6到0.9之间；同时图像畸变后原来方形表盘的长宽比能够
		保持在0.85到1.15之间；表盘四个顶点到图像边界的距离均不超过图像宽（高）的1/3。*/
		if (width > 0.6*min(ncols, nrows) && width < 0.9*max(ncols, nrows) && height >
			0.6*min(ncols, nrows) && height < 0.9*max(ncols, nrows) && rate<1.15&& rate>0.85)
		{
			if (sg_knob_type_Square == platetype)
			{
				if (x0<ncols / 3 && y0<nrows / 3 && x1>ncols * 2 / 3 && y1>nrows * 2 / 3)
				{
					if (boundRect[k].area() < min_boundRect)
					{
						panelNum = k;// panelNum用于存储表盘所在连通域的编号
						min_boundRect = boundRect[k].area();
					}
				}
			}
			if (sg_knob_type_Rectangle == platetype)
			{
				if (boundRect[k].area() < min_boundRect)
				{
					panelNum = k;
					min_boundRect = boundRect[k].area();
				}
			}
		}
	}

	if (panelNum == -1)
	{
		LOG(INFO) << "函数： PanelAreaMaybe  " << "旋钮表盘区域未找到，下一步使用投影法进行查找";
	}

	return sg_OK;
}




/**
*	@Method		GetPanelArea
*
*	@Brief		抠出旋钮表盘区域.
*
*	@Author		Lu Xin
*
*	@Para [IN]	const Mat srcImg:
*
*				const Mat erodeImg:
*
*				const Mat binaryImg:
*
*				const vector<Rect> boundRect:
*
*				int panelNum:
*
*	@Para [OUT]	Mat & knobImg:
*
*				Mat & knobImg_bin:
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int GetPanelArea(const Mat srcImg, const Mat erodeImg, const Mat binaryImg, const vector<Rect> boundRect, int panelNum, Mat & knobImg, Mat & knobImg_bin)
{
	int resp = sg_OK;

	if (srcImg.empty() || erodeImg.empty() || binaryImg.empty())
	{
		LOG(ERROR) << "函数： GetPanelArea  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	int x0, x1, y0, y1;

	if (-1 == panelNum)	// 如果连通域法没有找到旋钮表盘，则用投影法进行补充
	{
		int location[4];

		// 根据投影选取四条边.
		resp = BoundProjection(erodeImg, location);
		CHECKRESP(resp);

		y0 = location[0];
		y1 = location[1];
		x0 = location[2];
		x1 = location[3];

		// 如果截取出来的表盘太小，则认为没有表盘
		if (abs(y1 - y0) < 0.4*min(srcImg.rows, srcImg.cols) || abs(x1 - x0) < 0.4*min(srcImg.rows, srcImg.cols))
		{
			LOG(ERROR) << "函数： GetPanelArea  " << "投影法表盘区域未找到";
			return sg_ERROR;
		}
	}
	else
	{
		int location[4];
		resp = PanelLocation(erodeImg, boundRect, panelNum, location);
		x0 = location[0];
		x1 = location[1];
		y0 = location[2];
		y1 = location[3];
	}

	int height = y1 - y0 + 1;
	int width = x1 - x0 + 1;

	knobImg = srcImg(Rect(x0, y0, width, height)).clone();
	knobImg_bin = binaryImg(Rect(x0, y0, width, height)).clone();
	if (knobImg.empty() || knobImg_bin.empty())
	{
		LOG(ERROR) << "函数： GetPanelArea  " << "sg_ERROR_knob_NO_rectArea";
		return	sg_ERROR;
	}

	return sg_OK;
}




/**
*	@Method		BoundProjection
*
*	@Brief		根据投影选取四条边.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat erodeImg:
*
*	@Para [OUT]	int * location:
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int BoundProjection(const Mat erodeImg, int * location)
{

	if (erodeImg.empty())
	{
		LOG(ERROR) << "函数： BoundProjection  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	Mat binaryImage = erodeImg.clone();
	int brows = binaryImage.rows;
	int bcols = binaryImage.cols;
	vector<int> row_black(brows), col_black(bcols);
	int max_row_black = 0, max_col_black = 0;

	/*投影法只针对距离边界1/6以内的点进行投影计算，找出黑色像素点最多的一行（列），
	作为旋钮表盘的边框。location[0]存储的是表盘上边框所在的行*/
	for (int m = 0; m < brows / 6; m++)
	{
		for (int n = 0; n < bcols; n++)
		{
			if (binaryImage.at<uchar>(m, n) == 0)
				row_black[m]++;
		}
		if (row_black[m] >= max_row_black)
		{
			max_row_black = row_black[m];
			location[0] = m;
		}
	}
	// location[1]存储的是表盘下边框所在的行
	max_row_black = 0;
	for (int m = location[0] + brows / 4.0; m < brows; m++)
	{
		for (int n = 0; n < bcols; n++)
		{
			if (binaryImage.at<uchar>(m, n) == 0)
				row_black[m]++;
		}
		if (row_black[m] >= max_row_black)
		{
			max_row_black = row_black[m];
			location[1] = m;
		}
	}
	// location[2]存储的是表盘左边框所在的列
	for (int m = 0; m < bcols / 6; m++)
	{
		col_black[m] = 0;
		for (int n = 0; n < brows; n++)
		{
			if (binaryImage.at<uchar>(n, m) == 0)
				col_black[m]++;
		}
		if (col_black[m] > max_col_black)
		{
			max_col_black = col_black[m];
			location[2] = m;
		}
	}
	// location[3]存储的是表盘有边框所在的列
	max_col_black = 0;
	for (int m = bcols - 1; m > bcols * 5 / 6; m--)
	{
		col_black[m] = 0;
		for (int n = 0; n < brows; n++)
		{
			if (binaryImage.at<uchar>(n, m) == 0)
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
*	@Method		PanelLocation
*
*	@Brief		得到旋钮表盘的顶点坐标.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat erodeImg:
*
*				const vector<Rect> boundRect:
*
*				const int panelNum:
*
*	@Para [OUT]	int * location:
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int PanelLocation(const Mat erodeImg, const vector<Rect> boundRect, const int panelNum, int * location)
{
	if (erodeImg.empty())
	{
		LOG(ERROR) << "函数： PanelLocation  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	Mat erodeImage = erodeImg.clone();

	int x0 = boundRect[panelNum].x;
	int y0 = boundRect[panelNum].y;

	int width = boundRect[panelNum].width;
	int height = boundRect[panelNum].height;

	int core_x = x0 + width / 2;
	int core_y = y0 + height / 2;

	int x1 = x0 + width;
	int y1 = y0 + height;

	int projection_x, projection_y, m, n, pixel;
	int erodeDis = 5;//缩进距离，防止边框与截取出来的roi之间存在真空

	// 填充旋钮的中心区域，为之后的截框做准备
	for (int i = x0 + width / 5; i < x0 + width / 5 * 4; i++)
	{
		for (int j = y0 + height / 5; j < y0 + height / 5 * 4; j++)
		{
			erodeImage.at<uchar>(j, i) = 255;
		}
	}

	// 对粗略定位出的表盘从内向外寻找边框，防止表盘与周围的区域出现粘连
	for (m = core_y; m >= y0; m--)
	{
		projection_x = 0;
		for (n = x0; n < x1; n++)
		{
			pixel = static_cast<int>(erodeImage.at<uchar>(m, n));
			if (pixel == 255)
				projection_x++;
		}
		// 如果投影小于表盘宽度的1/5，则跳出循环
		if (projection_x < 0.2*width)
			break;
	}
	y0 = m + erodeDis;
	location[2] = y0;

	for (m = core_y; m < y1; m++)
	{
		projection_x = 0;
		for (n = x0; n < x1; n++)
		{
			pixel = static_cast<int>(erodeImage.at<uchar>(m, n));
			if (pixel == 255)
				projection_x++;
		}
		if (projection_x < 0.2*width)
			break;
	}
	y1 = m - erodeDis;
	location[3] = y1;

	for (m = core_x; m >= x0; m--)
	{
		projection_y = 0;
		for (n = y0; n < y1; n++)
		{
			pixel = static_cast<int>(erodeImage.at<uchar>(n, m));
			if (pixel == 255)
				projection_y++;
		}
		if (projection_y < 0.2*height)
			break;
	}
	x0 = m + erodeDis;
	location[0] = x0;

	for (m = core_x; m < x1; m++)
	{
		projection_y = 0;
		for (n = y0; n < y1; n++)
		{
			pixel = static_cast<int>(erodeImage.at<uchar>(n, m));
			if (pixel == 255)
				projection_y++;
		}
		if (projection_y < 0.2*height)
			break;
	}
	x1 = m - erodeDis;
	location[1] = x1;

	return sg_OK;
}



/**
*	@Method		AngleDetect_knob
*
*	@Brief		旋钮角度识别.
*
*	@Author		Lu Xin
*
*	@Para [IN]	const Mat srcImg：	待检测图像（旋钮表盘区域）
*
*				const unsigned int Knobtype：	旋钮头型：方头or尖头
*												1. 方头: sg_knob_type_Square
*												2. 尖头: sg_knob_type_Sharp
*
*	@Para [OUT]	unsigned int & angle：检测结果（角度）
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int AngleDetect_knob(const Mat srcImg, const unsigned int Knobtype, int & angle)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： AngleDetect_knob  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	int resultAngle = 0;

	//if (sg_knob_type_Square == Knobtype)
	//{
	//	resp = SquareHeadKnobDetection(srcImg, resultAngle);
	//	CHECKRESP(resp);
	//}
	if (sg_knob_type_Circle != Knobtype)
	{
		resp = SharpHeadKnobDetection(srcImg, resultAngle);
		CHECKRESP(resp);
	}
	else
	{
		resp = CircleKnobDetection(srcImg, resultAngle);
		CHECKRESP(resp);
	}

	// 引用返回
	angle = resultAngle;
	return sg_OK;
}




/**
*	@Method		SharpHeadKnobDetection
*
*	@Brief		尖头旋钮角度识别处理流程.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	unsigned int & resultAngle
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int SharpHeadKnobDetection(const Mat srcImg, int & resultAngle)
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： SharpHeadKnobDetection  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	float a = 1.0;
	int b = 0;
	Mat linearTransform_image;
	resp = Trans_linearTransform(srcImg, a, b, linearTransform_image);

	Mat Transform_gray;
	cvtColor(linearTransform_image, Transform_gray, CV_BGR2GRAY);

	//大津法二值化
	Mat Img_Bw;
	threshold(Transform_gray, Img_Bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	//对图像进行闭操作，消除小区域以及旋钮与周边字符的粘连
	//二值化后的图像，旋钮为黑色而背景为白色
	Mat closed_image;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(Img_Bw, closed_image, MORPH_CLOSE, element);
	//imgShowDebug(closed_image, "closed_image", 0);

	//对图像进行边缘检测，方便找连通域
	Mat cannyImg;
	Canny(closed_image, cannyImg, 50, 150, 3);

	//消除小的连通域
	Mat mainAreaImg;
	eraseSmallArea(cannyImg, closed_image, mainAreaImg);
	CHECKRESP(resp);

	//连接旋钮内部的缝隙，使之成为一个完整的连通域
	resp = link_gap(mainAreaImg);
	CHECKRESP(resp);

	//扩展图像的大小确保其能容下倾斜矩形
	Mat extend_image;
	resp = extend_Bound(mainAreaImg, extend_image);
	CHECKRESP(resp);
	imgShowDebug(extend_image, "extend_image", 0);

	//计算旋钮角度
	int knobAngle;
	resp = cacBoundRectRandomDirection(extend_image, knobAngle);

	//引用返回结果
	resultAngle = knobAngle;
	waitKey(0);

	return sg_OK;
}



/**
*	@Method		SquareHeadKnobDetection
*
*	@Brief		方头旋钮识别.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	unsigned int & resultAngle
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int SquareHeadKnobDetection(const Mat srcImg, int & resultAngle)
{

	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： SquareHeadKnobDetection  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	Mat image;
	resize(srcImg, image, Size(300, 300));

	//对图像进行线性变换，增强旋钮与背景区域的对比度
	float a = 3.0;
	int b = 10;
	Mat linearTransform_image;

	resp = Trans_linearTransform(image, a, b, linearTransform_image);
	CHECKRESP(resp);

	Mat Transform_gray;
	cvtColor(linearTransform_image, Transform_gray, CV_BGR2GRAY);

	//大津法二值化
	Mat Img_Bw;
	threshold(Transform_gray, Img_Bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	//闭操作消除小区域干扰
	Mat closed_image;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(Img_Bw, closed_image, MORPH_CLOSE, element);

	//Canny算子边缘检测
	Mat edge;
	Canny(closed_image, edge, 0, 255);

	//寻找图像中的最长直线作为旋钮角度的参考线
	int knobAngle;
	Mat DrawImg = srcImg.clone();
	resp = angleOfMaxLine(edge, DrawImg, knobAngle);
	CHECKRESP(resp);

	resultAngle = knobAngle;
	return sg_OK;
}


/**
*	@Method		angleOfMaxLine
*
*	@Brief		图像中最长直线的角度.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat edge：
*
*	@Para [OUT]	Mat & drawImg：
*
*				int & angle：
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/

int angleOfMaxLine(const Mat edge, Mat & drawImg, int & angle)
{

	int resp = sg_OK;

	if (edge.empty())
	{
		LOG(ERROR) << "函数： angleOfMaxLine  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	Mat houghMat;
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 40, 50, 200);

	double longest_line = 0.0;

	int col = edge.cols;
	int row = edge.rows;

	int core_x = col / 2;
	int core_y = row / 2;

	double min_distance = col;

	int dx0, dx1, dx2, dy0, dy1, dy2;

	float l0, l1, l2, costheta, theta, distance;

	int x0, x1, y0, y1;

	// 设置远点和近点用于之后的角度识别
	Point far_point, close_point;
	if (0 == lines.size())
	{
		LOG(ERROR) << "函数： angleOfMaxLine  " << "sg_ERROR_knob_NO_lineSquare";
		return sg_ERROR;
	}

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		dx0 = abs(l[0] - l[2]);
		dy0 = abs(l[1] - l[3]);
		dx1 = abs(l[0] - core_x);
		dy1 = abs(l[1] - core_y);
		dx2 = abs(l[2] - core_x);
		dy2 = abs(l[3] - core_y);
		l0 = 1.0*sqrt(dx0*dx0 + dy0*dy0);
		l1 = 1.0*sqrt(dx1*dx1 + dy1*dy1);
		l2 = 1.0*sqrt(dx2*dx2 + dy2*dy2);
		costheta = (l0*l0 + l1*l1 - l2*l2) / (2 * l0*l1);
		theta = acos(costheta);
		distance = l1*sin(theta);
		//cout << "distance=" << distance << endl;
		if (distance < 160)
		{
			double length = sqrt(dx0*dx0 + dy0*dy0);
			if (length >= longest_line)
			{
				x0 = l[0];
				x1 = l[2];
				y0 = l[1];
				y1 = l[3];
				longest_line = length;
				far_point.x = l1 >= l2 ? l[0] : l[2];
				close_point.x = l1 < l2 ? l[0] : l[2];
				far_point.y = l1 >= l2 ? l[1] : l[3];
				close_point.y = l1 < l2 ? l[1] : l[3];
			}
		}
	}

	line(drawImg, Point(x0, y0), Point(x1, y1), Scalar(0, 0, 255), 2, CV_AA);
	// imshow("drawImg", drawImg);
	// imshow("drawImg", drawImg);
	imgShowDebug(drawImg, "drawImg", 0);

	int height, width;
	height = abs(y0 - y1);
	if (y0 <= y1)
		width = x0 - x1;
	else
		width = x1 - x0;
	angle = atan(height*1.0 / width) / M_PI * 180;
	if (angle >= 0)
	{
		if ((far_point.x < close_point.x&&far_point.y >= close_point.y) ||
			(far_point.x <= close_point.x&&far_point.y > close_point.y))
		{
			angle = angle;
		}
		else
		{
			angle = angle + 180;
		}
	}
	else
	{
		if (far_point.x > close_point.x&&far_point.y > close_point.y)
		{
			angle = angle + 180;
		}
		else
		{
			angle = angle + 360;
		}
	}

	return sg_OK;
}


/**
*	@Method		eraseSmallArea
*
*	@Brief		消除二值图像中小面积的连通域
*
*	@Author		LU Xin
*
*	@Para [IN]	Mat edge,Mat srcImg
*
*	@Para [OUT]	Mat &mainAreaImg
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-13
*/
int eraseSmallArea(Mat edge, Mat srcImg, Mat& mainAreaImg)
{
	int resp = sg_OK;

	if (srcImg.empty() || edge.empty())
	{
		LOG(ERROR) << "函数： eraseSmallArea  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(edge, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //定义外接矩形集合
	float area = (srcImg.cols*srcImg.rows) / 50.0;
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		if (boundRect[i].area() < area)
		{
			for (int m = 0; m < boundRect[i].height; m++)
			{
				for (int n = 0; n < boundRect[i].width; n++)
				{
					srcImg.at<uchar>(m + boundRect[i].y, n + boundRect[i].x) = 255;
				}
			}
		}
	}
	mainAreaImg = srcImg.clone();
	imgShowDebug(mainAreaImg, "mainAreaImg", 0);
	return sg_OK;
}

/**
*	@Method		link_gap
*
*	@Brief		连接旋钮区域断裂的部分，确保它能成为一个完整的连通域.
*				分别对二值图像的行和列进行遍历，对满足条件的缝隙区域进行像素填充
*
*	@Author		LU Xin
*
*	@Para [IN]	Mat &threImage
*
*	@Para [OUT]	Mat &threImage
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int link_gap(Mat &threImage)
{
	int resp = sg_OK;

	if (threImage.empty())
	{
		LOG(ERROR) << "函数： link_gap  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	struct color_gap
	{
		uchar pixel;
		int length;
		int head_place;
	};

	int cols = threImage.cols;
	int rows = threImage.rows;

	vector<vector<color_gap>> gapRowVec(rows, vector<color_gap>(20));

	for (int i = 0; i < rows; i++)
	{
		gapRowVec[i][0].pixel = threImage.at<uchar>(i, 0);
		int num = 0, sum = 0;
		gapRowVec[i][0].length = 0;
		gapRowVec[i][0].head_place = 0;
		for (int j = 0; j < cols; j++)
		{
			if (threImage.at<uchar>(i, j) != gapRowVec[i][num].pixel)
			{
				sum += gapRowVec[i][num].length;
				num++;
				gapRowVec[i][num].head_place = sum;
				gapRowVec[i][num].length = 0;
			}
			gapRowVec[i][num].pixel = threImage.at<uchar>(i, j);
			gapRowVec[i][num].length++;
		}
	}

	for (int m = 0; m < rows; m++)
	{
		for (int n = 0; n < 18; n++)
		{
			if (gapRowVec[m][n].pixel == 0 && gapRowVec[m][n].length > 20 && gapRowVec[m][n + 1].length < 40 && gapRowVec[m][n + 2].length > 20
				&& gapRowVec[m][n].head_place + gapRowVec[m][n].length < cols && gapRowVec[m][n + 1].head_place + gapRowVec[m][n + 1].length < cols)
			{
				for (int k = 0; k < gapRowVec[m][n + 1].length; k++)
				{
					threImage.at<uchar>(m, k + gapRowVec[m][n + 1].head_place) = 0;
				}
			}
		}
	}



	vector<vector<color_gap>> gapColVec(cols, vector<color_gap>(20));

	for (int j = 0; j < cols; j++)
	{
		gapColVec[j][0].pixel = threImage.at<uchar>(0, j);
		int num = 0, sum = 0;
		gapColVec[j][0].length = 0;
		gapColVec[j][0].head_place = 0;
		for (int i = 0; i < rows; i++)
		{
			if (threImage.at<uchar>(i, j) != gapColVec[j][num].pixel)
			{
				sum += gapColVec[j][num].length;
				num++;
				gapColVec[j][num].head_place = sum;
				gapColVec[j][num].length = 0;
			}
			gapColVec[j][num].pixel = threImage.at<uchar>(i, j);
			gapColVec[j][num].length++;
		}
	}
	for (int m = 0; m < cols; m++)
	{
		for (int n = 0; n < 18; n++)
		{
			if (gapColVec[m][n].pixel == 0 && gapColVec[m][n].length > 20 && gapColVec[m][n + 1].length < 40 && gapColVec[m][n + 2].length > 20
				&& gapColVec[m][n].head_place + gapColVec[m][n].length < rows && gapColVec[m][n + 1].head_place + gapColVec[m][n + 1].length < rows)
			{
				for (int k = 0; k < gapColVec[m][n + 1].length; k++)
				{
					for (int k = 0; k < gapColVec[m][n + 1].length; k++)
						threImage.at<uchar>(k + gapColVec[m][n + 1].head_place, m) = 0;
				}
			}
		}
	}

	return sg_OK;
}




/**
*	@Method		extend_Bound
*
*	@Brief		扩展旋钮图片并用白色像素点填充，确保能够容纳下矩形框.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat threMat
*
*	@Para [OUT]	Mat & result
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int extend_Bound(const Mat threMat, Mat & result)
{
	int resp = sg_OK;

	if (threMat.empty())
	{
		LOG(ERROR) << "函数： extend_Bound  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	int nRows = threMat.rows + 100;
	int nCols = threMat.cols + 100;
	Mat new_threMat(nRows, nCols, threMat.type());

	for (int m = 0; m < nRows; m++)
	{
		for (int n = 0; n < nCols; n++)
		{
			new_threMat.at<uchar>(m, n) = 255;
		}
	}

	int x = 0, y = 0;
	for (int i = 50; i < nRows - 50; i++)
	{
		for (int j = 50; j < nCols - 50; j++)
		{
			if (x < threMat.cols&&y < threMat.rows)
			{
				new_threMat.at<uchar>(i, j) = threMat.at<uchar>(y, x);
				x++;
			}
		}
		x = 0;
		y++;
	}

	result = new_threMat;
	return sg_OK;
}




/**
*	@Method		cacBoundRectRandomDirection
*
*	@Brief		找出旋钮的倾斜外接矩形，通过计算对角线的角度得到旋钮角度.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcMat
*
*	@Para [OUT]	int & angle
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int cacBoundRectRandomDirection(const Mat srcMat, int & angle)
{
	int resp = sg_OK;

	if (srcMat.empty())
	{
		LOG(ERROR) << "函数： cacBoundRectRandomDirection  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}

	Mat threMat = srcMat.clone();

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat new_threMat = threMat.clone();
	Mat resultMat(threMat.size(), CV_8UC3);

	findContours(new_threMat, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (contours.size() == 0)
	{
		LOG(ERROR) << "函数： cacBoundRectRandomDirection  " << "sg_ERROR_knob_cacBound_NOCONTOUR";
		return sg_ERROR;
	}

	vector<RotatedRect> minRect(contours.size());
	float theata;
	int rows = threMat.rows;
	int cols = threMat.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (threMat.at<uchar>(i, j) == 0)
			{
				resultMat.at<Vec3b>(i, j) = (0, 0, 0);
			}
			else if (threMat.at<uchar>(i, j) == 255)
			{
				for (int k = 0;k < 3;k++)
				{
					resultMat.at<Vec3b>(i, j)[k] = (255, 255, 255);
				}
			}
		}
	}

	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
	}

	for (int i = 0; i < contours.size(); i++)
	{
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		float width = minRect[i].size.width;
		float height = minRect[i].size.height;
		int point_num = 0, min_temp = 300;
		Point2f center_point = minRect[i].center;

		//计算旋钮角度，注意旋钮实际所指的区域在指针的对面
		if (width > 0.3*cols&&width<0.9*cols&&height>0.3*rows&&height < 0.9*rows)
		{
			int maxblackSum = 0;
			int blackSum[4];
			for (int k = 0; k < 4; k++)
			{
				Point left_up;
				left_up.x = rect_points[k].x - 15;
				left_up.x = left_up.x >= 0 ? left_up.x : 0;
				left_up.y = rect_points[k].y - 15;
				left_up.y = left_up.y >= 0 ? left_up.y : 0;
				line(resultMat, rect_points[k], rect_points[(k + 1) % 4], Scalar(0, 0, 255), 2, 8);
				blackSum[k] = 0;
				for (int m = 0; m < 30; m++)
				{
					for (int n = 0; n < 30; n++)
					{
						int areaPtX = left_up.x + m;
						areaPtX = areaPtX < threMat.cols ? areaPtX : threMat.cols - 1;
						int areaPtY = left_up.y + n;
						areaPtY = areaPtY < threMat.rows ? areaPtY : threMat.rows - 1;
						if (threMat.at<uchar>(areaPtY, areaPtX) == 0)
						{
							blackSum[k]++;
						}
					}
				}
				LOG(INFO) << "函数： cacBoundRectRandomDirection  blackSum[" << to_string(k) << "]" << blackSum[k];
				if (blackSum[k] > maxblackSum)
				{
					maxblackSum = blackSum[k];
					point_num = k;
				}
				//将统计区域用红色矩形框出
				Rect rect(left_up.x, left_up.y, 30, 30);
				rectangle(resultMat, rect, Scalar(0, 0, 255), 1, 8, 0);
			}
			if (!(maxblackSum > 8 * blackSum[(point_num + 1) % 4] && maxblackSum > 8 * blackSum[(point_num + 2) % 4]
				&& maxblackSum > 8 * blackSum[(point_num + 3) % 4]))
			{
				for (int j = 0; j < 4; j++)
				{
					float dx = rect_points[j].x - center_point.x;
					float dy = rect_points[j].y - center_point.y;

					int temp = 0;
					int point_x = 0, point_y = 0;
					float line_length = sqrt(dx*dx + dy*dy);
					float angle = atan(abs(dy / dx)) * 180 / M_PI;
					for (int m = 0; m < line_length; m++)
					{
						point_x = center_point.x + m*cos(angle*M_PI / 180)*(dx / abs(dx));
						point_y = center_point.y + m*sin(angle*M_PI / 180)*(dy / abs(dy));
						int pixel = static_cast<int>(threMat.at<uchar>(point_y, point_x));

						if (pixel == 255)
							temp++;
					}
					if (temp < min_temp)
					{
						point_num = j;
						min_temp = temp;
					}
				}
			}
			float det_x = rect_points[point_num].x - center_point.x;
			float det_y = rect_points[point_num].y - center_point.y;
			if (det_x == 0 && det_y > 0)
				theata = 270;
			else if (det_x == 0 && det_y < 0)
				theata = 90;
			else if (det_y == 0 && det_x > 0)
				theata = 180;
			else if (det_y == 0 && det_x < 0)
				theata = 0;
			else
			{
				theata = atan(abs(det_y / det_x)) * 180 / M_PI;
				if (rect_points[point_num].x < center_point.x&&rect_points[point_num].y < center_point.y)
					theata = 360 - theata;
				else if (rect_points[point_num].x > center_point.x&&rect_points[point_num].y < center_point.y)
					theata = 180 + theata;
				else if (rect_points[point_num].x < center_point.x&&rect_points[point_num].y > center_point.y)
					theata = theata;
				else
					theata = 180 - theata;
			}
			line(resultMat, rect_points[point_num], center_point, Scalar(0, 0, 255), 2, 8);
		}
	}
	imgShowDebug(resultMat, "resultMat", 0);
	angle = theata;
	return sg_OK;
}


/**
*	@Method		CircleKnobDetection
*
*	@Brief		圆形旋钮角度识别.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	unsigned int & resultAngle
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int CircleKnobDetection(const Mat srcImg, int & resultAngle)
{
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： CircleKnobDetection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}
	//对图像进行线性变换
	Mat linearTransImg;
	Trans_linearTransform(srcImg, 3.0, 10.0, linearTransImg);
	int cols = linearTransImg.cols;
	int rows = linearTransImg.rows;
	Mat grayImg;
	cvtColor(linearTransImg, grayImg, CV_BGR2GRAY);
	imgShowDebug(grayImg, "grayImg", 0);

	Mat otsuImg;
	threshold(grayImg, otsuImg, 0, 255, CV_THRESH_OTSU);
	imgShowDebug(otsuImg, "otsuImg", 0);

	vector<Point> knobContour;
	searchCircleKnob(otsuImg, knobContour);
	//计算旋钮角度
	circleKnobAngleCalc(srcImg, otsuImg, knobContour, resultAngle);

	return sg_OK;
}


/**
*	@Method		searchCircleKnob
*
*	@Brief		找出圆形旋钮所在的倾斜外接矩形.
*
*	@Author		LU Xin
*
*	@Para [IN]	Mat binImg
*
*	@Para [OUT]	vector<Point>& knobContour
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int searchCircleKnob(Mat binImg, vector<Point>& knobContour)
{
	if (binImg.empty())
	{
		LOG(ERROR) << "函数： searchCircleKnob  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binImg.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/*Mat image_binary(binaryImg.size(), binaryImg.type());
	image_binary = Scalar::all(0);
	drawContours(image_binary, contours, -1, Scalar::all(255));
	imshow("image_binary", image_binary);*/
	int cols = binImg.cols;
	int rows = binImg.rows;
	int imgArea = cols*rows;
	bool isContour = 0;
	vector<Rect> boundRect(contours.size());
	int maxContourArea = 0;//将面积最大的连通域找出来
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		int width = boundRect[i].width;
		int height = boundRect[i].height;
		int area = width*height;
		if (area > maxContourArea&&area < 0.5*imgArea)
		{
			maxContourArea = area;
			isContour = 1;
			knobContour = contours[i];
		}
	}
	if (isContour == 0)
	{
		LOG(ERROR) << "函数： searchCircleKnob  " << "sg_ERROR_knob_NO_contour";
		return sg_ERROR;
	}

	return sg_OK;
}


/**
*	@Method		circleKnobAngleCalc
*
*	@Brief		计算圆形旋钮的角度.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg, const Mat otsuImg, vector<Point> knobContour
*
*	@Para [OUT]	float& resultAngle
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-17
*/
int circleKnobAngleCalc(const Mat srcImg, const Mat otsuImg, vector<Point> knobContour, int& resultAngle)
{
	if (srcImg.empty() || otsuImg.empty())
	{
		LOG(ERROR) << "函数： circleKnobAngleCalc  " << "入参图像为空，退出函数";
		return	sg_ERROR;
	}
	if (knobContour.size() == 0)
	{
		LOG(ERROR) << "函数： circleKnobAngleCalc  " << "sg_ERROR_knob_NO_contour";
		return	sg_ERROR;
	}
	//找最小倾斜外接矩形
	RotatedRect minRect;
	minRect = minAreaRect(Mat(knobContour));
	Point2f rect_points[4];
	minRect.points(rect_points);
	float width = minRect.size.width;
	float height = minRect.size.height;
	Point2f center_point = minRect.center;
	Mat showRectImg = srcImg.clone();
	for (int k = 0; k < 4; k++)
	{
		line(showRectImg, rect_points[k], rect_points[(k + 1) % 4], Scalar(0, 0, 255), 2, 8);
	}
	imgShowDebug(showRectImg, "showRectImg", 0);

	//计算对角线上的黑色像素点个数
	Point vertex0, vertex1;
	int maxBlackSum = 0;
	float diagAngle;//旋钮指向角的角度
	for (int i = 0; i <= 1; i++)
	{
		vertex0 = rect_points[i].x >= rect_points[i + 2].x ? rect_points[i] : rect_points[i + 2];
		vertex1 = rect_points[i].x < rect_points[i + 2].x ? rect_points[i] : rect_points[i + 2];
		float dx = vertex0.x - vertex1.x;
		float dy = vertex0.y - vertex1.y;
		int diagBlackSum = 0;
		float lineLength = sqrt(pow(dx, 2) + pow(dy, 2));
		float angle;//对角线的倾斜角
		if (dx == 0 && dy > 0)
		{
			angle = M_PI / 2.0;
		}
		else if (dx == 0 && dy < 0)
		{
			angle = -M_PI / 2.0;
		}
		else
		{
			angle = atan(1.0*dy / dx);
		}
		for (int j = 0; j < lineLength; j++)
		{
			int ptX = vertex1.x + j*cos(angle);
			int ptY = vertex1.y + j*sin(angle);
			if (otsuImg.at<uchar>(ptY, ptX) == 0)
			{
				diagBlackSum++;
			}
		}
		if (diagBlackSum > maxBlackSum)
		{
			maxBlackSum = diagBlackSum;
			diagAngle = angle*180.0 / M_PI;
		}
	}
	resultAngle = diagAngle > 0 ? 180 - diagAngle : -diagAngle;
	LOG(INFO) << "函数： circleKnobAngleCalc  " << "resultAngle:" << resultAngle << endl;

	return sg_OK;
}
