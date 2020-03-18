#pragma once
#include <opencv.hpp>


using namespace cv;
using namespace std;

/// <summary>
///图像处理静态类
/// </summary>
class DealImageUtil
{
public:

	/// <summary>
	/// 图像闭运算
	/// </summary>
	/// <param name="src">图</param>
	/// <param name="size_w">尺寸大小</param>
	/// <returns>cv.Mat.</returns>
	static Mat ImgClose(const Mat& src, int size_w);

	/// <summary>
	/// 开运算
	/// </summary>
	/// <param name="src">图</param>
	/// <param name="size_w">尺寸大小</param>
	/// <returns>cv.Mat.</returns>
	static Mat ImgOpen(const Mat& src, int size_w);

	/// <summary>
	/// 获取最大轮廓
	/// </summary>
	/// <param name="src">二值图</param>
	/// <returns>最大的轮廓</returns>
	static vector<Point> getMaxCountour(const Mat& src);

	/// <summary>
	///获取轮廓
	/// </summary>
	/// <param name="src">图 二值图</param>
	/// <returns>从大到小排序后的图</returns>
	static vector<vector<Point>> getCountours(const Mat& src);
	

	/// <summary>
	/// 高斯模糊
	/// </summary>
	/// <param name="src">输入图</param>
	/// <param name="dst">输出</param>
	/// <param name="k">核尺度大小</param>
	static void GaussianBlur(const Mat& src, Mat& dst, float k);

	
	/// <summary>
	/// 计算4角点
	/// </summary>
	/// <param name="countous"></param>
	/// <returns>std.vector.Vec4f</returns>
	static vector<Point2f> getCountourEnd(const vector<Point>& countous);

	/// <summary>
	/// 点排序
	/// </summary>
	/// <param name="pts">The PTS.</param>
	/// <returns>std.vector.Point2f</returns>
	static vector<Point2f> sortPoints(const vector<Point2f>& pts);

	/// <summary>
	/// 数据格式转换
	/// </summary>
	/// <param name="src">The source.</param>
	/// <param name="dst">The DST.</param>
	template <class SrcType, class DstType>
	static void convertVec(std::vector<SrcType>& src, std::vector<DstType>& dst) {
		dst.resize(src.size());
		std::copy(src.begin(), src.end(), dst.begin());
	}

	/// <summary>
	/// 透视变换
	/// </summary>
	/// <param name="src">The source.</param>
	/// <param name="vertices">The vertices.</param>
	/// <param name="dst">The DST.</param>
	static void getTransmitImg(const Mat& src, const std::vector<Point2f>& vertices, Mat& dst);
	static void getTransmitImg(const Mat& src, const std::vector<Point2f>& vertices, Mat& dst, Size size);

	enum RoateType {//顺时针旋转90 顺时针旋转180 顺时针旋转270 逆时针90°
		CLOCK90=0, CLOCK180, CLOCK270, ANTICLOCK90
	};


};

typedef  DealImageUtil DUtil;
