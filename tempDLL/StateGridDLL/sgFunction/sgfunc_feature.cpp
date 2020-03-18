/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgfunc_feature.cpp
*
* 	@Brief	特征提取.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-18
*
*	@MethodList
*		1.	int getOTSUthresholdNoBlack(const Mat srcImg, int & thresh)
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/18		SHNE		Created.
*
*/ 
#define _CRT_SECURE_NO_WARNINGS

#include "sgfunc_feature.h"
#include "../sgCore/sgcore_log.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"

#include <opencv2\opencv.hpp>
using namespace cv;

#include <numeric>
#include <string>
using namespace std;

/**
*	@Method		getOTSUthresholdNoBlack
*
*	@Brief		计算图像中非零点区域类间方差对应的阈值.
*
*	@Author		LU Xin
*
*	@Para [IN]	const Mat srcImg
*
*	@Para [OUT]	int & thresh:阈值
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-18
*/

int getOTSUthresholdNoBlack(const Mat srcImg, int & thresh)
{

	int resp = sg_OK;

	if (srcImg.empty())
	{
		LOG(ERROR) << "函数： getOTSUthresholdNoBlack  " << "sg_ERROR_img_null";
		return	sg_ERROR;
	}


	Mat grayImg = srcImg.clone();

	int nCols = grayImg.cols;
	int nRows = grayImg.rows;
	int threshold = 0;
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
			int pixel = grayImg.at<uchar>(i, j);
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
			threshold = i;
		}
	}

	thresh = threshold;
	return sg_OK;
}







/**
*	@Method		detectColorWithPoints
*
*	@Brief		遍历像素点，检测是否匹配目标颜色.
*
*	@Author		TANG Xinyu
*
*	@Para [IN]	const Mat srcImg
*
*				Vec3b color
*
*				const int red
*
*				const int green
*
*				const int blue
*
*				const int minimum
*
*	@Para [OUT]	Mat & result
*
*				vector<vector<int>> & Points
*
*				int & figures
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-20
*/
int detectColorWithPoints(const Mat srcImg, Vec3b color, const int red, const int green, const int blue, const int minimum, Mat & result, vector<vector<int>> & Points, int & figures)//核心处理：遍历像素点，检测是否匹配目标颜色
{
	int resp = sg_OK;

	if (srcImg.empty())
	{
		return	sg_ERROR;
	}

	figures = 0;

	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			int pb = srcImg.at<Vec3b>(i, j)[0];
			int pg = srcImg.at<Vec3b>(i, j)[1];
			int pr = srcImg.at<Vec3b>(i, j)[2];
			int dis0 = abs(pb - color[0]);
			int dis1 = abs(pg - color[1]);
			int dis2 = abs(pr - color[2]);
			if (dis0 <= red && dis1 <= green && dis2 <= blue && sqrt(dis0 ^ 2 + dis1 ^ 2 + dis2 ^ 2) <= minimum)
			{
				result.at<Vec3b>(i, j)[0] = 255;//M中符合颜色检测条件的像素点设为白色
				result.at<Vec3b>(i, j)[1] = 255;
				result.at<Vec3b>(i, j)[2] = 255;

				Points[figures][0] = i;//存放符合颜色检测条件的像素点坐标
				Points[figures][1] = j;
				figures++;//统计符合颜色检测条件的像素点个数
			}
			else
			{
				result.at<Vec3b>(i, j)[0] = 0;//M中不符合颜色检测条件的像素点设为黑色
				result.at<Vec3b>(i, j)[1] = 0;
				result.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	return sg_OK;
}




// vector容器取平均
double vectorAvg(vector<int> vec)
{
	double sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
	double mean = sum / vec.size();
	return mean;
}

/**
*	@Method		imageMatch
*
*	@Brief		模板匹配返回匹配结果
*	s
*	@Author		LI Wentao
*
*	@Para [IN]	Mat srcImg：		输入原图
*					
*				Mat tempImg：	匹配模板
*
*				string flag:	检测结果语义定义
*
*				double minMatch：	匹配判断参数
*
*	@Para [OUT]	map<int, MatchPoint>* outLights：	检测结果
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-04-08
*/
int imageMatch(Mat srcImg, Mat tempImg, vector<MatchPoint> & outLights, int flag, string text, double minMatch)
{
	int resp = sg_OK;
	if (srcImg.empty() || tempImg.empty())
	{
		LOG(ERROR) << "函数： imageMatch " << "sg_ERROR_img_null";
		return sg_ERROR;
	}

	int width = srcImg.cols - tempImg.cols + 1;
	int height = srcImg.rows - tempImg.rows + 1;

	Mat resultImg(Size(width, height), CV_32FC1);

	matchTemplate(srcImg, tempImg, resultImg, CV_TM_CCOEFF_NORMED);//CV_TM_SQDIFF CV_TM_CCOEFF_NORMED

	normalize(resultImg, resultImg, 0, 1, NORM_MINMAX, -1);

	vector<int> columnList;

	map<int, MatchPoint>* lights = new map<int, MatchPoint>();

	columnList.push_back(0);

	MatchPoint maxMatch(0, 0, sg_ERROR, 0);

	char* prob = new char[10];

	int lastRow = 0;

	int index = 0;

	for (int i = 0; i < resultImg.rows; i++)
	{
		for (int j = 0; j < resultImg.cols; j++)
		{
			// 注意i为y,j为x
			double matchValue = resultImg.at<float>(i, j);
			if (matchValue > minMatch)
			{
				auto maxPosition = max_element(columnList.begin(), columnList.end());
				if (maxMatch.matchValue != 0.0 && i > (lastRow + 5))
				{
					lights->insert(pair<int, MatchPoint>(index++, maxMatch));
					maxMatch = MatchPoint(j, i, flag, matchValue);

					lastRow = i;
				}
				else
				{
					if (matchValue > maxMatch.matchValue)
					{
						maxMatch = MatchPoint(j, i, flag, matchValue);
					}
				}
			}
		}
	}

	int sum = 0;
	vector<vector<int>> groupCol;
	vector<int> tempGroupItem;
	for (map<int, MatchPoint>::iterator iter = lights->begin(); iter != lights->end(); ++iter)
	{
		int col = iter->second.point.x;
		sum += col;
		if (groupCol.size() == 0)
		{
			vector<int> tempGroupItem;
			tempGroupItem.push_back(col);
			groupCol.push_back(tempGroupItem);
		}
		else
		{
			bool existGroup = false;
			for (int i = 0; i < groupCol.size(); ++i)
			{
				if (abs(vectorAvg(groupCol[i]) - col) < 30)
				{
					existGroup = true;
					groupCol[i].push_back(col);
					break;
				}
			}
			if (!existGroup)
			{
				vector<int> tempGroupItem;
				tempGroupItem.push_back(col);
				groupCol.push_back(tempGroupItem);
			}
		}
	}

	int avgCol = 0;
	int maxSize = 0;
	for (int i = 0; i < groupCol.size(); ++i)
	{
		if (groupCol[i].size() > maxSize)
		{
			maxSize = groupCol[i].size();
			avgCol = vectorAvg(groupCol[i]);
		}
	}

	map<int, MatchPoint>::iterator iter = lights->begin();

	int lastRow1 = 0;
	for (; iter != lights->end();)
	{
		sprintf(prob, "%.2f", iter->second.matchValue);

		if (abs(iter->second.point.x - avgCol) > 10.0)
		{
			lights->erase(iter++);
		}
		else
		{
			if (lastRow1 == 0 || iter->second.point.y > lastRow1 + 15)
			{
				auto maxMatch = iter->second;
				rectangle(srcImg, Point(maxMatch.point.x, maxMatch.point.y), Point(maxMatch.point.x + tempImg.cols, maxMatch.point.y + tempImg.rows), Scalar(0, 255, 0), 1, 8);
				putText(srcImg, text, Point(maxMatch.point.x + 40, maxMatch.point.y + 15), 0, 0.8, Scalar(0, 0, 255));
				outLights.push_back(maxMatch);
			}
			lastRow1 = iter->second.point.y;
			++iter;
		}
	}
}