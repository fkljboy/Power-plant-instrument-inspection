#include "DealImageUtil.h"

/// <summary>
/// 图像闭运算
/// </summary>
/// <param name="src">图</param>
/// <param name="size_w">尺寸大小</param>
/// <returns>cv.Mat.</returns>
Mat DealImageUtil::ImgClose(const Mat& src, int size_w)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size_w, size_w));

	Mat coloseMat;

	morphologyEx(src, coloseMat, MORPH_CLOSE, element, Point(-1, -1), 1, BORDER_CONSTANT, Scalar::all(0));
	return coloseMat;
}

/// <summary>
/// 开运算
/// </summary>
/// <param name="src">图</param>
/// <param name="size_w">尺寸大小</param>
/// <returns>cv.Mat.</returns>
Mat DealImageUtil::ImgOpen(const Mat& src, int size_w)
{
	Mat element = getStructuringElement(MORPH_RECT, Size(size_w, size_w));

	Mat open_mat;
	morphologyEx(src, open_mat, MORPH_OPEN, element, Point(-1, -1));
	return open_mat;
}

/// <summary>
/// 获取最大轮廓
/// </summary>
/// <param name="src">二值图</param>
/// <returns>最大的轮廓</returns>
vector<Point> DealImageUtil::getMaxCountour(const Mat& src)
{

	vector<vector<Point>> countous;
	Mat tempMat = src.clone();
	findContours(tempMat, countous, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if (countous.size() == 0)
		return vector<Point>();
	sort(countous.begin(), countous.end(), [](const vector<Point> &pts1, const vector<Point> &pts2)
	     {
		     return contourArea(pts1) > contourArea(pts2);
	     });
	return countous[0];
}

/// <summary>
///获取轮廓
/// </summary>
/// <param name="src">图 二值图</param>
/// <returns>从大到小排序后的图</returns>
vector<vector<Point>> DealImageUtil::getCountours(const Mat& src)
{

	vector<vector<Point>> countous;
	Mat tempMat = src.clone();
	findContours(tempMat, countous, RETR_LIST, CHAIN_APPROX_NONE);
	if (countous.size() == 0)
		return countous;
	sort(countous.begin(), countous.end(), [](const vector<Point> &pts1, const vector<Point> &pts2)
	     {
		     return contourArea(pts1) > contourArea(pts2);
	     });
	return countous;
}



/// <summary>
/// 高斯模糊
/// </summary>
/// <param name="src">输入图</param>
/// <param name="dst">输出</param>
/// <param name="k">核尺度大小</param>
void DealImageUtil::GaussianBlur(const Mat& src, Mat& dst, float k)
{
	double sigma = 0.3*(k / 2 - 1) + 0.8;
	cv::GaussianBlur(src, dst, Size(k, k), sigma, sigma);
}






vector<Point2f> DealImageUtil::getCountourEnd(const vector<Point>& countous)
{
	
	//轮廓边界
	Rect rect = cv::boundingRect(countous);
	Point tl = rect.tl();
	Point br = rect.br();

	vector<Point2f> coner;//角点
	coner.push_back(Point2f(tl.x, tl.y));
	coner.push_back(Point2f(br.x, tl.y));
	coner.push_back(Point2f(br.x, br.y));
	coner.push_back(Point2f(tl.x, br.y));

	vector<Point2f> ptEnd(4);
	vector<double> minDist(4, DBL_MAX);
	for(auto pt: countous)
	{
		Point2f ptf(pt.x, pt.y);
		for(int i=0;i<coner.size();i++)
		{
			double d = norm(ptf - coner[i]);
			if(d<minDist[i])
			{
				minDist[i] = d;
				ptEnd[i] = ptf;
			}
		}
	}

	return sortPoints(ptEnd);
}
/// <summary>
/// 点排序
/// </summary>
/// <param name="pts">The PTS.</param>
/// <returns>std.vector.Point2f</returns>
vector<Point2f> DealImageUtil::sortPoints(const vector<Point2f>& ptEnd)
{
		
	Rect rect = cv::boundingRect(ptEnd);
	//	vector<Point >hull;
	//排序
	convexHull(ptEnd, ptEnd);
	int minId = 0;
	double minDist = DBL_MAX;
	Point2f br(rect.br().x, rect.br().y);
	for (int i = 0; i < 4; i++)
	{
		double d2 = norm(ptEnd[(i + 2) % 4] - br);
		double d = norm(ptEnd[i]) + d2;

		if (d < minDist)
		{
			minDist = d;
			minId = i;
		}
	}
	vector<Point2f >hull(4);
	for (int i = 0; i < 4; i++)
	{
		hull[i] = ptEnd[(i + minId) % 4];
	}

	return hull;
}



/// <summary>
/// 透视变换
/// </summary>
/// <param name="src">The source.</param>
/// <param name="vertices">The vertices.</param>
/// <param name="dst">The DST.</param>
void DealImageUtil::getTransmitImg(const Mat& src, const std::vector<Point2f>& vertices, Mat& dst)
{

	std::vector<Point2f> dst_pt;

	float width_new = norm(vertices[3] - vertices[2]),
		hight_new = norm(vertices[3] - vertices[0]);//距离计算

	int th = 0;
	dst_pt.push_back(Point2f(th, th));
	dst_pt.push_back(Point2f(th + width_new, th));
	dst_pt.push_back(Point2f(th + width_new, th + hight_new));
	dst_pt.push_back(Point2f(th, hight_new));//新点映射
	Rect rect = boundingRect(vertices);
	std::vector<Point2f> tempPts;
	tempPts.reserve(vertices.size());
	Point2f tl = rect.tl();
	for (auto pt : vertices)
	{
		tempPts.push_back(pt - tl);
	}
	Mat temp = src(rect).clone();

	Mat transmtx1 = getPerspectiveTransform(tempPts, dst_pt);//仿射矩阵计算
	dst = Mat::zeros(hight_new, width_new, CV_8UC1);

	cv::warpPerspective(temp, dst, transmtx1, dst.size());//仿射

}


/// <summary>
/// 透视变换
/// </summary>
/// <param name="src">The source.</param>
/// <param name="vertices">The vertices.</param>
/// <param name="dst">The DST.</param>
void DealImageUtil::getTransmitImg(const Mat& src, const std::vector<Point2f>& vertices, Mat& dst, Size size)
{

	std::vector<Point2f> dst_pt;

	float width_new = size.width,
		hight_new = size.height;//距离计算

	int th = 0;
	dst_pt.push_back(Point2f(th, th));
	dst_pt.push_back(Point2f(th + width_new, th));
	dst_pt.push_back(Point2f(th + width_new, th + hight_new));
	dst_pt.push_back(Point2f(th, hight_new));//新点映射
	Rect rect = boundingRect(vertices);
	std::vector<Point2f> tempPts;
	tempPts.reserve(vertices.size());
	Point2f tl = rect.tl();
	double wX = double(size.width) / rect.width;
	double wY = double(size.height) / rect.height;
	for (auto pt : vertices)
	{
		pt = pt - tl;
		pt.x *= wX;
		pt.y *= wY;
		tempPts.push_back(pt);
	}
	Mat temp = src(rect).clone();
	resize(temp, temp, size);
	Mat transmtx1 = getPerspectiveTransform(tempPts, dst_pt);//仿射矩阵计算


	cv::warpPerspective(temp, dst, transmtx1, temp.size());//仿射

}



