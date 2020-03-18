/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_qrcode.cpp
*
* 	@Brief	二维码检测函数.
*
* 	@Author	LU Xin
*
* 	@Create	2018-05-10
*
*	@MethodList
*		1. int Detect_qrcode(Mat image,Rect& qrcodeRoi);
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		5/10   		Lu		Created.
*
*/

#include "sgtask_qrcode.h"
#include "zbar.h"

#include "../sgCore/sgcore_def.h"
#include "../sgCore/sgcore_log.h"
#include "../sgFunction/sgfunc_imageio.h"

using namespace zbar;  //添加zbar名称空间


/**
*	@Method		Detect_qrcode_multi
*
*	@Brief		从图像中检测所有二维码的位置和内容
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg: 待处理图像			
*
*	@Para [OUT]	vector<QRCodePos> & posList：二维码位置列表
*
*				vector<string> & contentList：二维码内容列表
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*
*	@Checked	2018-05-26
*/
int Detect_qrcode_multi(const Mat srcImg, vector<QRCodePos> &  posList, vector<string> & contentList)
{
	LOG(INFO) << "函数：Detect_qrcode_multi（多二维码检测），进入";

	int resp = sg_OK;

	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	if (!srcImg.data)
	{
		LOG(ERROR) << "函数错误：Detect_qrcode_multi，待处理图像为空";
		resp = sg_ERROR;
		return	resp;
	}

	Mat imageGray;
	cvtColor(srcImg, imageGray, CV_RGB2GRAY);

	int width = imageGray.cols;
	int height = imageGray.rows;
	uchar *raw = (uchar *)imageGray.data;
	Image imageZbar(width, height, "Y800", raw, width * height);	//Y800或者GRAY

	int n = scanner.scan(imageZbar);	//扫描条码
										// n > 0检测成功
										// n = 0没有检测到
										// n < 0发生错误 
	if (0 == n)
	{
		LOG(ERROR) << "函数错误：Detect_qrcode_multi，没有检测到二维码";
		resp = sg_ERROR;
		return	resp;
	}
	if (-1 == n)
	{
		LOG(ERROR) << "函数错误：Detect_qrcode_multi，二维码检测出错";
		resp = sg_ERROR;
		return	resp;
	}

	Image::SymbolIterator symbol = imageZbar.symbol_begin();	// 二维码列表第一个

	if (symbol == imageZbar.symbol_end())
	{
		LOG(ERROR) << "函数错误：Detect_qrcode_multi，没有检测到二维码";
		resp = sg_ERROR;
		return	resp;
	}

	int count = 0; //二维码计数器

	// 遍历二维码
	for (;symbol != imageZbar.symbol_end();++symbol)
	{
		count++;

		QRCodePos qrcodepos;	//二维码区域
		string content;	// 二维码内容

		// 获取类型
		LOG(INFO) << "二维码检测：二维码类型： " << symbol->get_type_name();

		// 获取内容
		content = symbol->get_data();

		LOG(INFO) << "二维码检测：二维码内容： " << symbol->get_data();

		// 获取位置
		vector<Point> vp;
		int k = symbol->get_location_size();	//一般就是四个点
		LOG(INFO) << "二维码检测：二维码点集大小（正常为4）： " << k;

		for (int i = 0;i < k;i++)
		{
			vp.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		}

		RotatedRect rect = minAreaRect(vp);// 二维码的最小外接矩形

		// 获取角度
		LOG(INFO) << "二维码检测：二维码旋转角度： " << rect.angle;;

		Point2f pts[4];// 用于存放二维码的四个顶点
		rect.points(pts);
		int min_x = width;
		int min_y = height;

		for (int i = 0; i < 4; i++)
		{
			line(imageGray, pts[i], pts[(i + 1) % 4], Scalar(0, 0, 255), 2);	// 绘制
			if (pts[i].x <= min_x)
			{
				min_x = pts[i].x;
			}
			if (pts[i].y <= min_y)
			{
				min_y = pts[i].y;
			}
		}
		
		// 得出二维码的区域
		qrcodepos.startX = min_x;
		qrcodepos.startY = min_y;

		qrcodepos.height = abs(pts[3].y - pts[1].y + 1);
		qrcodepos.width = abs(pts[3].x - pts[1].x + 1);

		LOG(INFO) << "二维码检测：二维码位置： 左上角（" << qrcodepos.startX << "," << qrcodepos.startY << "），高= " << qrcodepos.height << ", 宽= " << qrcodepos.width;

		posList.push_back(qrcodepos);
		contentList.push_back(content);
	}
	
	imageZbar.set_data(NULL, 0);

	LOG(INFO) << "函数：Detect_qrcode_multi（多二维码检测），共检出 " << count << " 个为二维码";
	LOG(INFO) << "函数：Detect_qrcode_multi（多二维码检测），退出";

	return resp;
}



/**
*	@Method		Search_qrcode
*
*	@Brief		根据内容，搜索图像中对应二维码的区域位置
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg: 待处理图像
*
*				const string content: 指定寻找的二维码内容
*
*	@Para [OUT]	QRCodePos & qrLocation：二维码位置
*
*	@Return		int：错误类型返回码，详见sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*
*	@Checked	2018-05-26
*/

int Search_qrcode(const Mat srcImg, const string content, QRCodePos & qrLocation)
{
	LOG(INFO) << "函数：Search_qrcode（根据二维码内容搜索区域） ， 进入";

	int resp = sg_OK;

	// 1.判空
	if (srcImg.empty())
	{
		LOG(ERROR) << "函数：Search_qrcode " << "图像入参为空";
		resp = sg_ERROR;
		return resp;
	}
	if (content.empty())
	{
		LOG(ERROR) << "函数：Search_qrcode " << "指定内容字符串为空";
		resp = sg_ERROR;
		return resp;
	}

	// 2. 获取图像中所有的二维码内容和区域
	vector<QRCodePos> posList;
	vector<string> contentList;

	Mat processImg = srcImg.clone();

	resp = Detect_qrcode_multi(processImg, posList, contentList);	// 调用接口进行检测
	if (resp != sg_OK)
	{
		LOG(ERROR) << "函数：Search_qrcode " << "图像中没有检测到二维码";
		return resp;
	}

	// 3. 遍历二维码列表进行匹配
	for (size_t i = 0; i < posList.size(); i++)
	{
		if (!content.compare(contentList[i]))
		{
			LOG(INFO) << "函数：Search_qrcode " << "找到指定二维码";
			qrLocation = posList[i];
			resp = sg_OK;
			return resp;
		}
	}

	// 4. 遍历结束都没有找到，则返回错误
	LOG(ERROR) << "函数：Search_qrcode " << "图像中没有指定的二维码";
	resp = sg_qrcode_searchNone;

	LOG(INFO) << "函数：Search_qrcode（根据二维码内容搜索区域） ， 退出";
	return resp;
}
