#include "ImageDeal.h"

ImageDeal::ImageDeal()
{
	//位置定义
	obj_pos.push_back(Rect(Point(230, 30), Point(290, 80)));//左上
	obj_pos.push_back(Rect(Point(26, 110), Point(81, 160)));//1
	obj_pos.push_back(Rect(Point(94, 110), Point(143, 160)));//2
	obj_pos.push_back(Rect(Point(160, 110), Point(205, 160)));//3

}

bool ImageDeal::Detect(const Mat& src, Vec4i &result)
{
	//查找目标矩形
	bool flage = findTargRect(src, tplMat, targRect);

	if (!flage)
		return false;

	//目标图片
	targMat = src(targRect).clone();
	//获取目标区域校正后的
	targMat = getTargRegion(targMat);
	//颜色目标过滤
	Mat targMatHsv = getRedTarg(targMat);

	//结果处理
	vector<double> counts;
	for (auto rect : obj_pos)
	{
		long cd = cv::countNonZero(targMatHsv(rect));
		counts.push_back(cd);
	}

	result = Vec4i(0);
	if (counts[0] > 500)	// 亮的数目多的话就代表开关灯肯定是亮了
	{
		result[0] = 1;
		double maxValue = counts[1];

		//找到最大值
		for (int j = 2; j < 4; j++)
			maxValue = max(counts[j], maxValue);

		if (maxValue > 200)
		{
			for (int j = 1; j < 4; j++)
			{
				double r = counts[j] / maxValue;
				if (r > 0.5)
				{
					result[j] = 1;
				}
			}
		}
	}

	return true;
}

/// <summary>
/// 计算图像的 mssim.
/// </summary>
/// <param name="_i1">The _i1.</param>
/// <param name="_i2">The _i2.</param>
/// <returns>double.</returns>
double ImageDeal::getMSSIM(const Mat& _i1, const Mat& _i2)
{
	Mat i1, i2;
	cv::resize(_i1, i1, Size(200, 150));
	cv::resize(_i2, i2, Size(200, 150));

	const double C1 = 6.5025, C2 = 58.5225;
	/***************************** INITS **********************************/
	int d = CV_32F;

	Mat I1, I2;
	i1.convertTo(I1, d);           // cannot calculate on one byte large values
	i2.convertTo(I2, d);

	Mat I2_2 = I2.mul(I2);        // I2^2
	Mat I1_2 = I1.mul(I1);        // I1^2
	Mat I1_I2 = I1.mul(I2);        // I1 * I2

	/*************************** END INITS **********************************/

	Mat mu1, mu2;   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);

	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);

	Mat sigma1_2, sigma2_2, sigma12;

	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;

	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;

	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	///////////////////////////////// FORMULA ////////////////////////////////
	Mat t1, t2, t3;

	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

	Mat ssim_map;
	divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

	Scalar mssim = mean(ssim_map); // mssim = average of ssim map

	return mssim[0] + mssim[1] + mssim[2];
}


/// <summary>
/// 查找目标区域的矩形
/// </summary>
/// <param name="src">The source.</param>
/// <param name="tplMat">The TPL mat.</param>
/// <param name="rectDst">The rect DST.</param>
/// <returns>bool.</returns>
bool ImageDeal::findTargRect(const Mat& src, const Mat& tplMat, Rect& rectDst)
{
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);

	// 图像大小调整
	Mat resizeMat;

	Mat thImg;
	cv::threshold(gray, thImg, 80, 255, 1);
	thImg = DUtil::ImgClose(thImg, 10);

	thImg = DUtil::ImgOpen(thImg, 10);

	//	myshow("thImg", thImg);
	vector<vector<Point>> contous = DealImageUtil::getCountours(thImg);

	//没目标
	if (contous.size() == 0)
		return false;
	double arr = thImg.size().area();
	vector<Rect> rects;
	for (auto contou : contous)
	{
		Rect rect = cv::boundingRect(contou);
		double reArr = rect.area();
		double rate = reArr / arr;
		double rateWH = (double)rect.width / rect.height;

		//面积过滤
		if (rate > 0.95 || rate < 0.001 || rateWH < 1.5 || rateWH>2)
			continue;
		//if (rect.br().y > thImg.rows*0.8)
		//	continue;
		rects.push_back(rect);

	}
	//没有目标
	if (rects.size() == 0)
		return false;

	Rect targRect(0, 0, 0, 0);
	double maxConf = DBL_MIN;	//DBL_MIN为最小正值
	for (auto rect : rects)
	{
		// 计算结构相似度
		double  d = getMSSIM(tplMat, src(rect).clone());
		if (d > maxConf)
		{
			maxConf = d;
			targRect = rect;
		}
		//			cv::rectangle(image, rect, Scalar(0, 255, 0), 5);
	}
	if (maxConf > 1.3&&targRect.area() > 0)
	{
		rectDst = targRect;
		return true;
	}
	return false;
}

/// <summary>
///区域校正
/// </summary>
/// <param name="src">The source.</param>
/// <returns>cv.Mat.</returns>
Mat ImageDeal::getTargRegion(const Mat& src)
{
	Mat targMat = src.clone();
	cv::resize(targMat, targMat, Size(320, 200));
	Mat grayMat;
	cvtColor(targMat, grayMat, COLOR_BGR2GRAY);

	Mat thMat;
	cv::resize(grayMat, grayMat, Size(320, 200));

	//目标分割
	cv::threshold(grayMat, thMat, 50, 255, 1);
	//轮廓查找
	vector<Point> contous_S = DUtil::getMaxCountour(thMat);
	//端点查找
	vector<Point2f> ptend = DUtil::getCountourEnd(contous_S);

	Mat dst;
	DUtil::getTransmitImg(targMat, ptend, dst, Size(320, 200));

	return dst;
}

/// <summary>
///获取红色的二值区域
/// </summary>
/// <param name="src">The source.</param>
/// <returns>cv.Mat.</returns>
Mat ImageDeal::getRedTarg(const Mat& src)
{
	Mat hsvMat;
	cvtColor(src, hsvMat, COLOR_BGR2HSV);
	Mat targMatHsv1;
	Mat targMatHsv2;
	inRange(hsvMat, Scalar(0, 43, 46), Scalar(10, 255, 255), targMatHsv1);
	inRange(hsvMat, Scalar(156, 43, 46), Scalar(180, 255, 255), targMatHsv2);
	Mat targMatHsv = targMatHsv1 | targMatHsv2;
	return targMatHsv;
}
