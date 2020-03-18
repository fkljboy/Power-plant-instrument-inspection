/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*
*	@File	sgtask_qrcode.cpp
*
* 	@Brief	��ά���⺯��.
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

using namespace zbar;  //���zbar���ƿռ�


/**
*	@Method		Detect_qrcode_multi
*
*	@Brief		��ͼ���м�����ж�ά���λ�ú�����
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg: ������ͼ��			
*
*	@Para [OUT]	vector<QRCodePos> & posList����ά��λ���б�
*
*				vector<string> & contentList����ά�������б�
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*
*	@Checked	2018-05-26
*/
int Detect_qrcode_multi(const Mat srcImg, vector<QRCodePos> &  posList, vector<string> & contentList)
{
	LOG(INFO) << "������Detect_qrcode_multi�����ά���⣩������";

	int resp = sg_OK;

	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	if (!srcImg.data)
	{
		LOG(ERROR) << "��������Detect_qrcode_multi��������ͼ��Ϊ��";
		resp = sg_ERROR;
		return	resp;
	}

	Mat imageGray;
	cvtColor(srcImg, imageGray, CV_RGB2GRAY);

	int width = imageGray.cols;
	int height = imageGray.rows;
	uchar *raw = (uchar *)imageGray.data;
	Image imageZbar(width, height, "Y800", raw, width * height);	//Y800����GRAY

	int n = scanner.scan(imageZbar);	//ɨ������
										// n > 0���ɹ�
										// n = 0û�м�⵽
										// n < 0�������� 
	if (0 == n)
	{
		LOG(ERROR) << "��������Detect_qrcode_multi��û�м�⵽��ά��";
		resp = sg_ERROR;
		return	resp;
	}
	if (-1 == n)
	{
		LOG(ERROR) << "��������Detect_qrcode_multi����ά�������";
		resp = sg_ERROR;
		return	resp;
	}

	Image::SymbolIterator symbol = imageZbar.symbol_begin();	// ��ά���б��һ��

	if (symbol == imageZbar.symbol_end())
	{
		LOG(ERROR) << "��������Detect_qrcode_multi��û�м�⵽��ά��";
		resp = sg_ERROR;
		return	resp;
	}

	int count = 0; //��ά�������

	// ������ά��
	for (;symbol != imageZbar.symbol_end();++symbol)
	{
		count++;

		QRCodePos qrcodepos;	//��ά������
		string content;	// ��ά������

		// ��ȡ����
		LOG(INFO) << "��ά���⣺��ά�����ͣ� " << symbol->get_type_name();

		// ��ȡ����
		content = symbol->get_data();

		LOG(INFO) << "��ά���⣺��ά�����ݣ� " << symbol->get_data();

		// ��ȡλ��
		vector<Point> vp;
		int k = symbol->get_location_size();	//һ������ĸ���
		LOG(INFO) << "��ά���⣺��ά��㼯��С������Ϊ4���� " << k;

		for (int i = 0;i < k;i++)
		{
			vp.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
		}

		RotatedRect rect = minAreaRect(vp);// ��ά�����С��Ӿ���

		// ��ȡ�Ƕ�
		LOG(INFO) << "��ά���⣺��ά����ת�Ƕȣ� " << rect.angle;;

		Point2f pts[4];// ���ڴ�Ŷ�ά����ĸ�����
		rect.points(pts);
		int min_x = width;
		int min_y = height;

		for (int i = 0; i < 4; i++)
		{
			line(imageGray, pts[i], pts[(i + 1) % 4], Scalar(0, 0, 255), 2);	// ����
			if (pts[i].x <= min_x)
			{
				min_x = pts[i].x;
			}
			if (pts[i].y <= min_y)
			{
				min_y = pts[i].y;
			}
		}
		
		// �ó���ά�������
		qrcodepos.startX = min_x;
		qrcodepos.startY = min_y;

		qrcodepos.height = abs(pts[3].y - pts[1].y + 1);
		qrcodepos.width = abs(pts[3].x - pts[1].x + 1);

		LOG(INFO) << "��ά���⣺��ά��λ�ã� ���Ͻǣ�" << qrcodepos.startX << "," << qrcodepos.startY << "������= " << qrcodepos.height << ", ��= " << qrcodepos.width;

		posList.push_back(qrcodepos);
		contentList.push_back(content);
	}
	
	imageZbar.set_data(NULL, 0);

	LOG(INFO) << "������Detect_qrcode_multi�����ά���⣩������� " << count << " ��Ϊ��ά��";
	LOG(INFO) << "������Detect_qrcode_multi�����ά���⣩���˳�";

	return resp;
}



/**
*	@Method		Search_qrcode
*
*	@Brief		�������ݣ�����ͼ���ж�Ӧ��ά�������λ��
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	const Mat srcImg: ������ͼ��
*
*				const string content: ָ��Ѱ�ҵĶ�ά������
*
*	@Para [OUT]	QRCodePos & qrLocation����ά��λ��
*
*	@Return		int���������ͷ����룬���sgcore_def.h
*
*  	@Note		matters needing attention
*
*	@Create		2018-05-23
*
*	@Checked	2018-05-26
*/

int Search_qrcode(const Mat srcImg, const string content, QRCodePos & qrLocation)
{
	LOG(INFO) << "������Search_qrcode�����ݶ�ά�������������� �� ����";

	int resp = sg_OK;

	// 1.�п�
	if (srcImg.empty())
	{
		LOG(ERROR) << "������Search_qrcode " << "ͼ�����Ϊ��";
		resp = sg_ERROR;
		return resp;
	}
	if (content.empty())
	{
		LOG(ERROR) << "������Search_qrcode " << "ָ�������ַ���Ϊ��";
		resp = sg_ERROR;
		return resp;
	}

	// 2. ��ȡͼ�������еĶ�ά�����ݺ�����
	vector<QRCodePos> posList;
	vector<string> contentList;

	Mat processImg = srcImg.clone();

	resp = Detect_qrcode_multi(processImg, posList, contentList);	// ���ýӿڽ��м��
	if (resp != sg_OK)
	{
		LOG(ERROR) << "������Search_qrcode " << "ͼ����û�м�⵽��ά��";
		return resp;
	}

	// 3. ������ά���б����ƥ��
	for (size_t i = 0; i < posList.size(); i++)
	{
		if (!content.compare(contentList[i]))
		{
			LOG(INFO) << "������Search_qrcode " << "�ҵ�ָ����ά��";
			qrLocation = posList[i];
			resp = sg_OK;
			return resp;
		}
	}

	// 4. ����������û���ҵ����򷵻ش���
	LOG(ERROR) << "������Search_qrcode " << "ͼ����û��ָ���Ķ�ά��";
	resp = sg_qrcode_searchNone;

	LOG(INFO) << "������Search_qrcode�����ݶ�ά�������������� �� �˳�";
	return resp;
}
