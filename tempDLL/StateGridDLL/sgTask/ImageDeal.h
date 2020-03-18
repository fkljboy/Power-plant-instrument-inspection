#pragma once
#include "DealImageUtil.h"
class ImageDeal
{
public:

	ImageDeal();
	bool Detect(const Mat &src, Vec4i &result);

	vector<Rect> obj_pos;

	Mat tplMat;//模板图片

	Rect targRect; //目标矩形

	Mat targMat;//目标图片

	/// <summary>
	/// 计算图像的 mssim.
	/// </summary>
	/// <param name="_i1">The _i1.</param>
	/// <param name="_i2">The _i2.</param>
	/// <returns>double.</returns>
	static double getMSSIM(const Mat& _i1, const Mat& _i2);

	/// <summary>
	/// 查找目标区域的矩形
	/// </summary>
	/// <param name="src">The source.</param>
	/// <param name="tplMat">The TPL mat.</param>
	/// <param name="rectDst">The rect DST.</param>
	/// <returns>bool.</returns>
	static bool findTargRect(const Mat& src, const Mat& tplMat, Rect& rectDst);


	/// <summary>
	///区域校正
	/// </summary>
	/// <param name="src">The source.</param>
	/// <returns>cv.Mat.</returns>
	static Mat getTargRegion(const Mat& src);

	/// <summary>
	///获取红色的二值区域
	/// </summary>
	/// <param name="src">The source.</param>
	/// <returns>cv.Mat.</returns>
	static Mat getRedTarg(const Mat& src);
};
