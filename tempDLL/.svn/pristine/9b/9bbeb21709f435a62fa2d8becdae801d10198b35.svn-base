/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_led.cpp
*
* 	@Brief	指示灯识别函数.
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


//判断排列点阵的方向
static int arrange_row = 2;
static int arrange_col = 3;

//轮廓形状编码
static int SHAPE_NONE = 0;
static int SHAPE_SQUARE = 1;

string YoudianPlate = "tpl.jpg";

// 判断轮廓是否是正方形
int ShapeDetect(vector<Point> mContour, vector<Point> &outContour);


/**
*	@Method		Detect_led
*
*	@Brief		指示灯检测识别入口.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg：	输入继保区域图像（经过ROI处理）
*
*				const unsigned int ledtype：	继保类型（3种）
*											1. 纵差继电器 从上至下10位：	sg_led_type_benderZongCha
*											2. 保护继电器 从左至右8位：		sg_led_type_benderBaoHu
*											3. 通讯继电器 从左至右17位：	sg_led_type_benderTongXun
*
*											4. 有电显示器（闪烁灯） 从左至右4位：		sg_led_type_YouDian
*
*	@Para [OUT]	unsigned int * valueArr：	检测结果数组（需提前开辟内存）
*				检测结果为int数组，每个元素为检测结果，数组排序按照从上到下，从左到右原则。
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-16
*
*	@Checked	2018-05-29
*/

int Detect_led(const Mat srcImg, const int ledtype, vector<int> & valueArr)
{
	LOG(INFO) << "函数：Detect_led（指示灯分发接口）， 进入";

	int resp = sg_OK;

	// 1. 图像判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： Detect_led" << "  图像为空,退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 分流
	if (sg_led_type_benderZongCha == ledtype)	// 纵差继电器 从上至下10位
	{
		resp = led_Zongcha_detect(srcImg, valueArr);
		CHECKRESP(resp);
	}
	else if (sg_led_type_benderBaoHu == ledtype)	// 保护继电器 从左至右8位
	{
		resp = led_Baohu_detect(srcImg, valueArr);
		//resp = led_bender_detect(srcImg, lednum, valueArr);
		CHECKRESP(resp);
	}
	else if (sg_led_type_benderTongXun == ledtype)	//通讯继电器 从左至右17位
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

	LOG(INFO) << "函数：Detect_led（指示灯分发接口）， 退出";
	return sg_OK;
}


/**
*	@Method		otsuThreshold
*
*	@Brief		排除黑色像素点的影响对灰度图像进行大津法二值化
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat grayImage
*
*	@Para [OUT]	Mat& otsuImg
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
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
	// 初始化统计参数
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	// 统计灰度级中每个像素在整幅图像中的个数 
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
	// 计算每个灰度级占图像中的概率分布
	for (int i = 1; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols * nRows);
	}
	// 遍历灰度级[0,255],计算出最大类间方差下的阈值  
	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 1; i < 256; i++)
	{
		// 初始化相关参数
		w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;
		for (int j = 1; j < 256; j++)
		{
			//背景部分 
			if (j <= i)
			{
				// 当前i为分割阈值，第一类总的概率  
				w0 += nProDis[j];
				u0_temp += j * nProDis[j];
			}
			//前景部分   
			else
			{
				// 当前i为分割阈值，第一类总的概率
				w1 += nProDis[j];
				u1_temp += j * nProDis[j];
			}
		}
		// 分别计算各类的平均灰度 
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		delta_temp = (float)(w0 *w1* pow((u0 - u1), 2));
		// 依次找到最大类间方差下的阈值    
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
*	@Brief		纵差继电器指示灯检测
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg：待处理图像
*
*	@Para [OUT]	int * valueArr： 检测结果（数组形式）从上至下10位
*	                             1.sg_led_UpcloseDownClose = 107;// 指示器灯 上灭下灭
*	                             2.sg_led_UpOpenDownClose = 108;// 指示器灯 上亮下灭
*	                             3.sg_led_UpCloseDownOpen = 109;// 指示器灯 上灭下亮
*	                             4.sg_led_UpOpenDownOpen = 110;// 指示器灯 上亮下亮
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Zongcha_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "函数：led_Zongcha_detect（纵差继电器） ， 进入";
	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：led_flash_detect " << "待处理图像为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. TODO: 处理过程
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

	//找到位于同一列的点阵
	vector<vector<Point>> pointColGroup;
	resp = searchPointSameCol(pointColGroup, coreEdge, edgeImg, 1 / 30.0);
	CHECKRESP(resp);

	//找出连通域最多的一列
	vector<Point> maxPointCol;
	resp = maxContourCol(pointColGroup, maxPointCol);
	CHECKRESP(resp);

	//将这一列的点按纵坐标由上往下排列
	resp = arrangePoint(maxPointCol, arrange_col);
	CHECKRESP(resp);

	//选择点与点之间距离最多的值作为点的间隔，减小漏检点和噪声点的干扰
	float averDis;
	resp = maxPointDis(maxPointCol, averDis, cols, 1 / 60.0, sg_led_type_benderZongCha);
	CHECKRESP(resp);

	//找出标志列中间隔为单位距离的行
	vector<Point> signGroup;
	resp = searchAverDisRow(maxPointCol, averDis, edgeImg, 1 / 30.0, signGroup);
	CHECKRESP(resp);

	//将首尾之间未找到的标志进行插值
	resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderZongCha);
	CHECKRESP(resp);

	//纵差继电器在首尾之间进行插值
	resp = difInsertTopEndPt(signGroup, pointColGroup, averDis, edgeImg);
	CHECKRESP(resp);

	//将每一段截取出来单独分析
	vector<int> lightOrder;
	resp = difLightBlockAnalyse(signGroup, averDis, lampImg, valueArr);
	CHECKRESP(resp);

	LOG(INFO) << "函数：led_Zongcha_detect（纵差继电器） ， 退出";

	return resp;
}


/**
*	@Method		led_Baohu_detect
*
*	@Brief		保护继电器指示灯检测
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg：待处理图像
*
*	@Para [OUT]	int * valueArr： 检测结果（数组形式）	从左至右8位
*								 1.sg_led_UpcloseDownClose = 107;// 指示器灯 上灭下灭
*								 2.sg_led_UpOpenDownClose = 108;// 指示器灯 上亮下灭
*								 3.sg_led_UpCloseDownOpen = 109;// 指示器灯 上灭下亮
*								 4.sg_led_UpOpenDownOpen = 110;// 指示器灯 上亮下亮
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Baohu_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "函数：led_Baohu_detect（保护继电器） ， 进入";
	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：led_Baohu_detect " << "待处理图像为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}
	imgShowDebug(srcImg, "srcImg", 0);

	// 2. TODO: 处理过程
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

	vector<Point> coreMainOtsu;//存储二值化图像中的连通域
	resp = searchCore(mainEdge, coreMainOtsu, 1 / 20.0, 1 / 20.0);
	CHECKRESP(resp);

	//找出同一行上的点
	vector<vector<Point>> pointGroup;
	resp = searchPointSameRow(pointGroup, coreMainOtsu, rows, 1 / 30.0);
	CHECKRESP(resp);

	//找到横坐标一致最多的两行,并将其融合
	vector<Point>referRow;//存储点个数多的行
	int upRow, downRow;
	resp = searchMostSilmilarRow(pointGroup, referRow, cols, upRow, downRow);
	CHECKRESP(resp);

	//将两行中个数多的点按横坐标由前往后排列
	resp = arrangePoint(referRow, arrange_row);
	CHECKRESP(resp);

	//选择点与点之间距离最多的值作为点的间隔，减小漏检点和噪声点的干扰
	float averDis;
	resp = maxPointDis(referRow, averDis, cols, 1 / 50.0, sg_led_type_benderBaoHu);
	CHECKRESP(resp);

	//找所有点之间的列中垂直投影最多的那一列为参考线
	int maxProjectionCol;
	resp = maxVertProjection(mainOtsu, upRow, downRow, referRow, maxProjectionCol);
	CHECKRESP(resp);

	vector<Point> coreHsv;//存储所有的亮点
	resp = searchCore(edgeHsv, coreHsv, 1 / 20.0, 1 / 20.0);
	CHECKRESP(resp);

	if (coreHsv.size() > 0)
	{
		int label[2];//用来存储每个点的位置信息
		resp = lightLocate(coreHsv, maxProjectionCol, averDis, label, upRow, downRow, valueArr);
		CHECKRESP(resp);
	}
	else
	{
		////找出标志行中间隔为单位距离的列
		//vector<Point> signGroup;
		//resp = searchAverDisCol(0, referRow, averDis, cols, 1 / 50.0, signGroup, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		////将首尾之间未找到的标志进行插值
		//resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		////在标志行的首尾进行插值
		//resp = comInsertTopEndPt(signGroup, maxProjectionCol, averDis, cols, sg_led_type_benderBaoHu);
		//CHECKRESP(resp);

		LOG(ERROR) << "函数： lightLocate  " << "sg_ERROR_led_NO_pointList";
		return sg_ERROR;
	}

	// 3. TODO: 返回结果赋值
	LOG(INFO) << "函数：led_Baohu_detect（保护继电器） ， 退出";
	return resp;
}


/**
*	@Method		led_Tongxun_detect
*
*	@Brief		通讯继电器指示灯检测
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg：待处理图像
*
*	@Para [OUT]	int * valueArr： 检测结果（数组形式）	从左至右17位
*	                             1.sg_led_UpcloseDownClose = 107;// 指示器灯 上灭下灭
*	                             2.sg_led_UpOpenDownClose = 108;// 指示器灯 上亮下灭
*	                             3.sg_led_UpCloseDownOpen = 109;// 指示器灯 上灭下亮
*	                             4.sg_led_UpOpenDownOpen = 110;// 指示器灯 上亮下亮
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_Tongxun_detect(const Mat srcImg, vector<int> &  valueArr)
{
	LOG(INFO) << "函数：led_Tongxun_detect（通讯继电器） ， 进入";
	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：led_Tongxun_detect " << "待处理图像为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. TODO: 处理过程
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
	int location[4];//存储四个顶点的坐标
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

	//找出连通域最多的一行
	vector<Point> maxPointRow;
	resp = maxContourRow(pointRowGroup, maxPointRow);
	CHECKRESP(resp);

	//将这一行的点按横坐标由前往后排列
	resp = arrangePoint(maxPointRow, arrange_row);
	CHECKRESP(resp);

	//选择点与点之间距离最多的值作为点的间隔，减小漏检点和噪声点的干扰
	float averDis;
	resp = maxPointDis(maxPointRow, averDis, cols, 1 / 60.0, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//找到标识列所在的位置
	vector<vector<Point>> pointColGroup;
	resp = searchSignCol(coreMainEdge, mainEdge, pointColGroup, 1 / 60.0);
	CHECKRESP(resp);

	//找出第一个个数大于3的列
	int signMaxRowNum = -1;
	int signColNum;//标志列在容器中的位置
	int signCol;//标志所在的列
	resp = colMoreThanThree(pointColGroup, maxPointRow, mainEdge, averDis, signMaxRowNum, signColNum, signCol);
	CHECKRESP(resp);

	//找出标志行中间隔为单位距离的列
	vector<Point> signGroup;
	resp = searchAverDisCol(signMaxRowNum, maxPointRow, averDis, mainArea.cols, 1 / 80.0, signGroup, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//将首尾之间未找到的标志进行插值
	resp = insertMiddlePt(signGroup, averDis, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//在标志行的首尾进行插值
	resp = comInsertTopEndPt(signGroup, signCol, averDis, mainArea.cols, sg_led_type_benderTongXun);
	CHECKRESP(resp);

	//找到两排小灯中心点所在的列
	int lightRow[2] = { -1,-1 };//存储上下两排灯的纵坐标
	resp = searchLightRows(lightRow, pointColGroup, signColNum, maxPointRow, signMaxRowNum);
	CHECKRESP(resp);

	//将每个灯所在的列提取出来单独讨论
	resp = comLightBlockAnalyze(signGroup, averDis, mainArea, lightRow, valueArr);
	CHECKRESP(resp);


	LOG(INFO) << "函数：led_Tongxun_detect（通讯继电器） ， 退出";

	return resp;
}




/**
*	@Method		led_flash_detect
*
*	@Brief		跳闪灯检测（有电显示器）
*
*	@Author		LI Wentao
*
*	@Para [IN]	const Mat srcImg：待处理图像
*
*				const Mat templateImg: 模板图像
*
*	@Para [OUT]	int * valueArr： 检测结果（数组形式）从左到右四位
*								：sg_led_open 亮
*								：sg_led_close 灭
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-28
*/
int led_flash_detect(const Mat srcImg, const Mat templateImg, vector<int> &  valueArr)
{
	LOG(INFO) << "函数：led_flash_detect（闪烁灯检测一次） ， 进入";
	int resp = sg_OK;

	// 1. 判空
	if (srcImg.empty())		// 待处理图像判空
	{
		LOG(ERROR) << "函数：led_flash_detect " << "待处理图像为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	if (templateImg.empty())		// 模板图像判空
	{
		LOG(ERROR) << "函数：led_flash_detect " << "模板图像为空，退出函数";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 处理过程
	static ImageDeal imageDeal;
	if (imageDeal.tplMat.empty())
	{

		//模板图片
		imageDeal.tplMat = templateImg.clone();
	}

	Vec4i result(0);
	//查找目标矩形----
	bool flage = imageDeal.Detect(srcImg, result);
	if (!flage)
	{
		return 0;//没有检测到结果

	}


	// 3. 返回结果赋值

	for (int i = 0; i < 4; i++)
	{
		valueArr[i] = result[i] == 1 ? sg_led_open : sg_led_close;
	}



	LOG(INFO) << "函数：led_flash_detect（闪烁灯检测一次） ， 退出";
	return resp;
}




Rect matchObj(Mat &src, Mat &temp)
{
	int width = src.cols - temp.cols + 1;//result宽度
	int height = src.rows - temp.rows + 1;//result高度

	Mat result(height, width, CV_32FC1);//创建结果映射图像
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF); //平方差匹配法(最好匹配0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF_NORMED); //归一化平方差匹配法(最好匹配0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR); //相关匹配法(最坏匹配0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR_NORMED); //归一化相关匹配法(最坏匹配0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCOEFF); //系数匹配法(最好匹配1)
	matchTemplate(src, temp, result, CV_TM_CCOEFF_NORMED);//化相关系数匹配,最佳值1

	normalize(result, result, 0, 1, NORM_MINMAX, -1);//归一化到0-1范围

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

// 判断轮廓是否是正方形
int ShapeDetect(vector<Point> mContour, vector<Point> &outContour)
{
	int shape = SHAPE_NONE;
	double perimeter = arcLength(mContour, true);
	approxPolyDP(mContour, outContour, 0.03*perimeter, true);//第三个参数可调，0.01-0.05
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
*	@Brief		根据投影选取四条边
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat Image, float scale
*
*	@Para [OUT]	int *location
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： BoundProjection  " << "sg_ERROR_img_null";
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
	// location[1]存储的是表盘下边框所在的行
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
	// location[2]存储的是表盘左边框所在的列
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
	// location[3]存储的是表盘右边框所在的列
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
*	@Brief		 查找二值化图像中的轮廓
*
*	@Author		 LU Xin
*
*	@Para [IN]	 Mat binaryImg, float colScale, float rowScale
*
*	@Para [OUT]	 vector<Point>& core
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchCore  " << "sg_ERROR_img_null";
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
		LOG(ERROR) << "函数： searchCore  " << "sg_ERROR_led_NO_contour";
		return	sg_ERROR;
	}

	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		int width = boundRect[i].width;
		int height = boundRect[i].height;
		//将过小的连通域剔除掉
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
	//去除重叠的点
	for (int m = 0; m < core.size() - 1; m++)
	{
		for (int n = m + 1; n < core.size(); n++)
		{
			if (abs(core[m].x - core[n].x) < colScale*binCols
				&&abs(core[m].y - core[n].y) < rowScale*binRows)
			{
				//将这两个点融合
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
*	@Brief		 对图像进行倾斜校正
*
*	@Author		 LU Xin
*
*	@Para [IN]	 int ledKind
*
*	@Para [OUT]	 Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int rotateCorrection(Mat& edgeImg, Mat& lampImg, Mat& grayImg, Mat& otsuImg, int ledKind)
{
	if (edgeImg.empty() || lampImg.empty() || grayImg.empty())
	{
		LOG(ERROR) << "函数： rotateCorrection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}
	
	vector<Vec4i> lines;
	HoughLinesP(edgeImg, lines, 1, M_PI / 180, 20, 30, 5);

	if (lines.size() == 0)
	{
		LOG(ERROR) << "函数： rotateCorrection  " << "sg_ERROR_Led_NO_line";
		return	sg_ERROR;
	}

	float maxLength = 0;//最长直线的长度
	float lampAngle;//继电器的倾斜角度
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
*	@Brief		 获取Hsv空间中边缘检测后的图像
*
*	@Author		 LU Xin
*
*	@Para [IN]	 Mat mainArea
*
*	@Para [OUT]	 Mat& edgeHsv
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int getHsvEdge(Mat mainArea, Mat& edgeHsv)
{
	if (mainArea.empty())
	{
		LOG(ERROR) << "函数： getHsvEdge  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	//RGB颜色空间转换到HSV中
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

	//双阈值二值化
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
*	@Brief		 找到位于同一行的点阵
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreMainOtsu, int rows, float rowScale
*
*	@Para [OUT]	 vector<vector<Point>>& pointGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchPointSameRow  " << "sg_ERROR_led_NO_contour";
		return	sg_ERROR;
	}

	//将轮廓按从上到下，从左往右的顺序排列
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

	vector<Point> lattice;//存储每一行的点阵
	lattice.push_back(coreMainOtsu[0]);//将第一个连通域放入内存
	pointGroup.push_back(lattice);
	//将所有点按照纵坐标关系依次存入容器中
	for (int i = 1; i < coreMainOtsu.size(); i++)
	{
		int k = 0;//不同横坐标的行数
		lattice.clear();
		for (; k < pointGroup.size(); k++)
		{
			if (abs(coreMainOtsu[i].y - pointGroup[k].back().y) < rows*rowScale)
			{
				int size = pointGroup[k].size();
				if (size == 1 || (size >= 2 && (abs(coreMainOtsu[i].y -
					pointGroup[k][size - 2].y) < rows*rowScale)))
				{
					pointGroup[k].push_back(coreMainOtsu[i]);//将该点计入当前行中
					break;
				}
			}
		}
		//如果之前不存在这个高度的行，则将其加入pointGroup中
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
*	@Brief		 找到横坐标一致最多的两行
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointGroup
*
*	@Para [OUT]	 vector<Point>& downPoint, int cols, int& upRow, int& downRow
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchMostSilmilarRow  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxSameX = 0;
	for (int n = 0; n < pointGroup.size() - 1; n++)
	{
		for (int m = n + 1; m < pointGroup.size(); m++)
		{
			int count = 0;//这两行中横坐标相同的点的个数
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
		LOG(ERROR) << "函数： searchMostSilmilarRow  " << "sg_ERROR_led_NO_similarRow";
		return	sg_ERROR;
	}

	LOG(INFO) << "upRow: " << upRow;
	LOG(INFO) << "downRow: " << downRow;

	return sg_OK;
}


/**
*	@Method		 arrangePoint
*
*	@Brief		 按横坐标或者纵坐标排列点阵
*
*	@Author		 LU Xin
*
*	@Para [IN]	 vector<Point>& pointList
*
*	@Para [OUT]	 int rowOrCol
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int arrangePoint(vector<Point>& pointList, int rowOrCol)
{
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "函数： arrangePoint  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	Point tempPoint;
	//按横坐标排列
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
*	@Brief		 选择点与点之间距离最多的值作为点的间隔，减小漏检点和噪声点的干扰
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point>pointList, int cols, float colScale, int knobKind
*
*	@Para [OUT]	 float& averDis
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxPointDis(const vector<Point>pointList, float& averDis, int cols, float colScale, int knobKind)
{
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "函数： maxPointDis  " << "sg_ERROR_led_NO_pointList";
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
*	@Brief		 找所有点之间的列中垂直投影最多的那一列为参考线
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const Mat mainOtsu, const int upRow, const int downRow, const vector<Point> pointList
*
*	@Para [OUT]	 int& maxProjectionCol
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： maxVertProjection  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}
	if (pointList.size() == 0)
	{
		LOG(ERROR) << "函数： maxVertProjection  " << "sg_ERROR_led_NO_pointList";
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
*	@Brief		 确定两个灯的位置
*
*	@Author		 LU Xin
*
*	@Para [IN]	 vector<Point> coreHsv, const int maxProjectionCol, const float averDis, int *label, const int upRow, const int downRow
*
*	@Para [OUT]	 int *valueArr
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： lightLocate  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	//默认所有点都是熄灭的
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
*	@Brief		 找出连通域最多的一行
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointRowGroup
*
*	@Para [OUT]	 vector<Point>& maxPointRow
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxContourRow(const vector<vector<Point>> pointRowGroup, vector<Point>& maxPointRow)
{
	if (pointRowGroup.size() == 0)
	{
		LOG(ERROR) << "函数： maxContourRow  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxElement = 0;
	int maxEleNum;//元素最多的行在容器中的编号
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
*	@Brief		 找出连通域最多的一列
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointColGroup
*
*	@Para [OUT]	 vector<Point>& maxPointCol
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int maxContourCol(const vector<vector<Point>> pointColGroup, vector<Point>& maxPointCol)
{
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "函数： maxContourCol  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	int maxElement = 0;
	int maxEleNum;//元素最多的行在容器中的编号
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
*	@Brief		 找到标识列所在的位置
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreMainEdge, const Mat mainEdge, float colScale
*
*	@Para [OUT]	 vector<vector<Point>>& pointColGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchSignCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (mainEdge.empty())
	{
		LOG(ERROR) << "函数： searchSignCol  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	vector<Point> vertLat;//存储每一列的点阵
	vertLat.push_back(coreMainEdge[0]);//将第一个连通域放入内存
	pointColGroup.push_back(vertLat);
	//将所有点按照纵坐标关系依次存入容器中
	for (int i = 1; i < coreMainEdge.size(); i++)
	{
		int k = 0;//不同纵坐标的列
		vertLat.clear();
		for (; k < pointColGroup.size(); k++)
		{
			if (abs(coreMainEdge[i].x - pointColGroup[k][0].x) <= mainEdge.cols*colScale
				&& pointColGroup[k][0].x > mainEdge.cols / 8.0)
			{
				pointColGroup[k].push_back(coreMainEdge[i]);//将该点计入当前列中
				break;
			}
		}
		//如果之前不存在这个位置的列，则将其加入pointGroup中
		if (k == pointColGroup.size())
		{
			vertLat.push_back(coreMainEdge[i]);
			pointColGroup.push_back(vertLat);
		}
	}

	//将列组合按横坐标从前往后排
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
*	@Brief		 找出第一个个数大于3的列
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> maxPointRow, const Mat mainEdge, const float averDis
*
*	@Para [OUT]	 const vector<vector<Point>>& pointColGroup, int& signMaxRowNum, int& signColNum, int& signCol
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： colMoreThanThree  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "函数： colMoreThanThree  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (mainEdge.empty())
	{
		LOG(ERROR) << "函数： colMoreThanThree  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	for (int m = 0; m < pointColGroup.size(); m++)
	{
		LOG(INFO) << "size of pointColGroup: " << pointColGroup[m].size();
		LOG(INFO) << pointColGroup[m];
		if (pointColGroup[m].size() >= 3)
		{
			//根据第一行的数据找出其所在的列
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
		LOG(ERROR) << "函数： colMoreThanThree  " << "sg_ERROR_Led_NO_ThreeEleCol";
		return	sg_ERROR;
	}

	return sg_OK;
}


/**
*	@Method		 searchAverDisCol
*
*	@Brief		 找出标志行中间隔为单位距离的列
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signMaxRowNum, const vector<Point> maxPointRow, const float averDis, const Mat mainEdge, const float colScale
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchAverDisCol  " << "sg_ERROR_Led_NO_ThreeEleCol";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "函数： searchAverDisCol  " << "sg_ERROR_led_NO_pointList";
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
		LOG(ERROR) << "函数： searchAverDisCol  " << "sg_ERROR_led_NO_pointList";
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
*	@Brief		 找出标志列中间隔为单位距离的行
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> maxPointCol, const float averDis, const Mat edgeImg, const float colScale
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchAverDisRow  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (edgeImg.empty())
	{
		LOG(ERROR) << "函数： searchAverDisRow  " << "sg_ERROR_img_null";
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
		LOG(ERROR) << "函数： searchAverDisRow  " << "sg_ERROR_led_NO_pointList";
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
*	@Brief		 将首尾之间未找到的标志进行插值
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const float averDis, const int ledKind
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int insertMiddlePt(vector<Point>& signGroup, const float averDis, const int ledbKind)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "函数： insertMiddlePt  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	for (int i = 0; i < signGroup.size() - 1; i++)
	{
		//如果横向标志有漏检的
		if (ledbKind == sg_led_type_benderTongXun || sg_led_type_benderBaoHu)
		{
			float adjSignDis = signGroup[i + 1].x - signGroup[i].x;
			if (adjSignDis > 1.5*averDis)
			{
				int insertPtNum = (int)(adjSignDis*1.0 / averDis + 0.5) - 1;//四舍五入
				//在中间插入元素
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
				int insertPtNum = (int)(adjSignDis*1.0 / averDis + 0.5) - 1;//四舍五入
																			//在中间插入元素
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
*	@Brief		 通讯继电器在标志行的首尾进行插值
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signCol, const float averDis, const Mat mainEdge
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int comInsertTopEndPt(vector<Point>& signGroup, const int signCol, const float averDis, float cols, int ledKind)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "函数： comInsertTopEndPt  " << "sg_ERROR_led_NO_pointList";
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
*	@Brief		 纵差继电器在标志行的首尾进行插值或者删除
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<vector<Point>> pointColGroup, const float averDis, const Mat edgeImg
*
*	@Para [OUT]	 vector<Point>& signGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： difInsertTopEndPt  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (pointColGroup.size() == 0)
	{
		LOG(ERROR) << "函数： difInsertTopEndPt  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (edgeImg.empty())
	{
		LOG(ERROR) << "函数： difInsertTopEndPt  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	bool isPtInsert = 0;
	bool isPtErase = 0;
	while (signGroup.size() != 10)
	{
		//如果元素个数小于10个则进行插入操作
		isPtInsert = 0;//判断是否有点可以插入
		isPtErase = 0;//判断是否可以有点删除
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

		//如果元素个数大于10个则进行删除操作
		else if (signGroup.size() > 10)
		{
			//比较前两个点和后两个点之间的距离，将距离大的那个点删除
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
			LOG(ERROR) << "函数： difInsertTopEndPt  " << "sg_ERROR_NO_InsertOrErase";
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
*	@Brief		 找到两排小灯中心点所在的列
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const int signColNum, const vector<Point> maxPointRow, const int signMaxRowNum
*
*	@Para [OUT]	 int *lightRow, vector<vector<Point>>& pointColGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： difInsertTopEndPt  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}
	if (maxPointRow.size() == 0)
	{
		LOG(ERROR) << "函数： searchLightRows  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	//将标志列的所有点按从上到下的顺序排列
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
		//找到标志行和标志列的交叉点
		if (pointColGroup[signColNum][i].y == maxPointRow[signMaxRowNum].y)
		{
			lightRow[0] = pointColGroup[signColNum][i + 1].y;
			lightRow[1] = pointColGroup[signColNum][i + 2].y;
		}
	}

	if (lightRow[0] == -1 || lightRow[1] == -1)
	{
		LOG(ERROR) << "函数： searchLightRows  " << "sg_ERROR_led_NO_lightRow";
		return	sg_ERROR;
	}

	LOG(INFO) << "upLightRow,downLightRow:" << lightRow[0] << " " << lightRow[1];


	return sg_OK;
}


/**
*	@Method		 comLightBlockAnalyze
*
*	@Brief		 将通讯继电器每个灯所在的列提取出来单独讨论
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow,int *valueArr
*
*	@Para [OUT]
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int comLightBlockAnalyze(const vector<Point> signGroup, const float averDis, const Mat mainArea, int *lightRow, vector<int> &  valueArr)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "函数： comLightBlockAnalyze  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	Mat lightBlockImg;
	int lightCount = 0;//亮灯的个数
	for (int i = 0; i < signGroup.size(); i++)
	{
		int blockBeginCol = signGroup[i].x - averDis / 2.0;
		Rect block = Rect(blockBeginCol, 0, averDis, mainArea.rows - 1);
		lightBlockImg = mainArea(block).clone();
		//imshow("block" + to_string(i), lightBlockImg);
		//RGB颜色空间转换到HSV中
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

		//通过分析h空间的二值图像来消除灯泡表面带来的误判
		Mat hBinary;
		threshold(hImg, hBinary, 20, 255, CV_THRESH_BINARY);
		imgShowDebug(hBinary, "hBinary", 0);
		//通过分析v空间与b空间叠加的灰度图来分析灯泡的亮灭(经过实验得出)
		Mat otsuBlock;
		threshold(grayBlock, otsuBlock, 0, 255, CV_THRESH_OTSU);
		imgShowDebug(otsuBlock, "otsuBlock", 0);

		//将二值图像中的每个小灯区域提取出来进行分析
		int squareRadius = averDis / 3.0;
		bool isLight = 0;
		//根据灯的亮灭对每个数组赋值
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

			//统计hBianry中灯泡区域的白色像素点个数
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
*	@Brief		 找到位于同一列的点阵
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> coreEdge, Mat edgeImg, float colScale
*
*	@Para [OUT]  vector<vector<Point>>& pointColGroup
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
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
		LOG(ERROR) << "函数： searchPointSameCol  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}

	vector<Point> verLat;//存储每一列的点阵
	verLat.push_back(coreEdge[0]);//将第一个连通域放入内存
	pointColGroup.push_back(verLat);
	//将所有点按照横坐标关系依次存入容器中
	for (int i = 1; i < coreEdge.size(); i++)
	{
		int k = 0;//不同横坐标的列数
		verLat.clear();
		for (; k < pointColGroup.size(); k++)
		{
			if (abs(coreEdge[i].x - pointColGroup[k][0].x) <= edgeImg.cols*colScale)
			{
				pointColGroup[k].push_back(coreEdge[i]);//将该点计入当前列中
				break;
			}
		}
		//如果之前不存在这个宽度的列，则将其加入pointColGroup中
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
		LOG(ERROR) << "函数： searchPointSameCol  " << "sg_ERROR_led_NO_pointGroup";
		return	sg_ERROR;
	}

	return sg_OK;
}


/**
*	@Method		 difLightBlockAnalyse
*
*	@Brief		 将每一段截取出来单独分析
*
*	@Author		 LU Xin
*
*	@Para [IN]	 const vector<Point> signGroup, const float averDis, const Mat lampImg,int* valueArr
*
*	@Para [OUT]
*
*	@Return		 int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		 matters needing attention
*
*	@Create		 2018-05-28
*/
int difLightBlockAnalyse(const vector<Point> signGroup, const float averDis, const Mat lampImg, vector<int> & valueArr)
{
	if (signGroup.size() == 0)
	{
		LOG(ERROR) << "函数： difLightBlockAnalyse  " << "sg_ERROR_led_NO_pointList";
		return	sg_ERROR;
	}
	if (lampImg.empty())
	{
		LOG(ERROR) << "函数： difLightBlockAnalyse  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}

	Mat lightBlockImg;
	int lightCount = 0;//亮灯的个数
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
		//RGB颜色空间转换到HSV中
		Mat rectBlocklampImg = lampImg.clone();
		rectangle(rectBlocklampImg, block, Scalar(0, 0, 255), 1);
		imgShowDebug(rectBlocklampImg, "rectBlocklampImg", 0);
		Mat hsvImg, hImg, sImg, vImg;
		cvtColor(lightBlockImg, hsvImg, CV_RGB2HSV);
		vector<Mat> hsvChannels;
		split(hsvImg, hsvChannels);
		vImg = hsvChannels[2];
		imgShowDebug(vImg, "vImg", 0);

		//通过分析v空间的二值图像来消除灯泡表面带来的误判
		Mat vBinary;
		threshold(vImg, vBinary, 0, 255, CV_THRESH_OTSU);
		imgShowDebug(vBinary, "vBinary", 0);

		//将二值图像中的每个小灯区域提取出来进行分析
		int vBinWhiteArea = 0;
		int vBinBlackArea = 0;
		//统计hBianry中灯泡区域的白色像素点个数
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