/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_def.h
*
* 	@Brief	��Ŀ��Ҫ�õ���ȫ�ֶ���ͷ�ļ�.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-15
*
*	@MethodList
*		1.
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*/ 

#ifndef SGCORE_DEF_H
#define SGCORE_DEF_H

#include <string>
#include <vector>

// �궨�巵�ش������
#define CHECKRESP(resp) if(sg_OK!=(resp)) return (resp)

// �ڴ洫��ͼ��ʽ�ṹ��
struct ImageInfo
{
	unsigned char *data;
	int size;
};


// ������Ϣ�ṹ�嶨��
// subtype���ڸ���������Ҫ���������������
struct TaskInfo
{
	int type;
	int subtype;	// ϸ�����
	int number;	// ϸ��Ԫ�ص���Ŀ
	int order;

	// ���캯��
	TaskInfo(int t = -1, int sub = -1, int num = -1,int ord = -1)
	{
		type = t;
		subtype = sub;
		number = num;
		order = ord ;
	}
};

// ROI�ṹ�嶨�壬����C#/C++����
struct ROIInfo
{
	int startX;
	int startY;
	int distX;
	int distY;
	int width;
	int height;

	// Ĭ�Ϲ��캯��
	ROIInfo()
	{
		startX = 0;
		startY = 0;
		distX = 0;
		distY = 0;
		width = 0;
		height = 0;
	}

	// ���캯��
	ROIInfo(int x, int y, int disx, int disy,int w, int h)
	{
		startX = x;
		startY = y;
		distX = disx;
		distY = disy;
		width = w;
		height = h;
	}
};


// ������ť��λ������
struct knobStall
{
	int min_angle;
	int max_angle;
	std::string context;
	 
	knobStall(int min=-1, int max=-1, std::string s = "")
	{
		min_angle = min;
		max_angle = max;
		context = s;
	}
};


// ���ؽ���ṹ�嶨��
// ��Ҫ��Ϊ���ֵ�����飩�͵���ֵ��Double�ɣ�
struct ResultInfo
{

	//int * arrayResult = nullptr;	//ʵ��ʹ�õ�ʱ���ʼ���ڴ��ٽ��е��ã���ֹ�ڴ�й©���������ַ�ʽ

	double result = 0.0;

	std::vector<int> vectorResult;	//ʵ��ʹ��ʱ���ó���
};



// ���ؽ����ά��λ��
// 
struct QRCodeInfo
{
	unsigned int startX;
	unsigned int startY;
	unsigned int width;
	unsigned int height;
};

// ��ά����ṹ��
// ���ͣ����ݣ���ת�Ƕȣ�λ�ã�����
struct QRCodePos
{
	int startX;
	int startY;
	int width;
	int height;
};


// ����������ͷ�����1
static const int sg_OK = 0;
static const int sg_ERROR = 1;

// �����ά��������9
static const int sg_qrcode_imgnull = 91;	// ��ά�����Ϊ��
static const int sg_qrcode_detectNone = 92;	// û�м�⵽��ά��
static const int sg_qrcode_detectError = 93;	// ��ά�������
static const int sg_qrcode_searchNone = 94;	// ����ָ����ά��ʧ��
static const int sg_qrcode_searchContentNull = 95;	// ����ָ����ά��ʧ��

// �������У�� 12
// ����
static const int sg_Camera_Far = 121;		// Զ��
static const int sg_Camera_Near = 122;		// ����
static const int sg_Camera_NoOption = 125;	//û�л���У��ѡ��

// ���
static const int sg_Camera_OptionFail = 126;



// ��������������2
static const int sg_task_analog = 1;	//ģ��ָʾ��
static const int sg_task_knob = 2;		//��ť
static const int sg_task_led = 3;		//ָʾ��
static const int sg_task_pointer = 4;		//ָ��
static const int sg_task_switch = 5;		//�̽�Ƭ

// ������ťͷ��������8
static const int sg_knob_type_Square = 81;		//������ť
static const int sg_knob_type_Rectangle = 82;	//������ť
static const int sg_knob_type_Circle = 83;		//Բ����ť

// ����ģ��ָʾ�� 9
// ����
static const int sg_analog_type_circles = 91;   //ģ��ָʾ������һ����Բ�޵� 3����
static const int sg_analog_type_twoPanels = 92; //ģ��ָʾ�����Ͷ����������� 2����
static const int sg_analog_type_onePanel = 93;  //ģ��ָʾ����������һ������ 1����
static const int sg_analog_type_lights = 94;	//ģ��ָʾ�������ģ���Բ�е� 3����

// ���
static const int sg_analog_Connect= 98;	    //ģ��ָʾ�� ����
static const int sg_analog_DisConnect = 99;	//ģ��ָʾ�� �Ͽ�

// ����ָʾ��������10
// ����
static const int sg_led_type_benderZongCha = 101;	//�̵籣����	�ݲ�̵��� ��������10λ
static const int sg_led_type_benderBaoHu = 102;		//�̵籣����	�����̵��� ��������8λ
static const int sg_led_type_benderTongXun = 103;	//�̵籣����	ͨѶ�̵��� ��������17λ
static const int sg_led_type_YouDian = 104;			//��˸��		�е���ʾ�� ��������3λ

// ���
static const int sg_led_open = 105;	// ָʾ���� ��
static const int sg_led_close = 106;// ָʾ���� ��
static const int sg_led_UpCloseDownClose = 107;// ָʾ���� ��������
static const int sg_led_UpOpenDownClose = 108;// ָʾ���� ��������
static const int sg_led_UpCloseDownOpen = 109;// ָʾ���� ��������
static const int sg_led_UpOpenDownOpen = 110;// ָʾ���� ��������



#endif // !SGCORE_DEF_H
