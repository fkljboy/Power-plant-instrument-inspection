/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_def.h
*
* 	@Brief	项目需要用到的全局定义头文件.
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

// 宏定义返回错误变量
#define CHECKRESP(resp) if(sg_OK!=(resp)) return (resp)

// 内存传递图像方式结构体
struct ImageInfo
{
	unsigned char *data;
	int size;
};


// 任务信息结构体定义
// subtype用于个别任务需要多个输入参数的情况
struct TaskInfo
{
	int type;
	int subtype;	// 细分类别
	int number;	// 细分元素的数目
	int order;

	// 构造函数
	TaskInfo(int t = -1, int sub = -1, int num = -1,int ord = -1)
	{
		type = t;
		subtype = sub;
		number = num;
		order = ord ;
	}
};

// ROI结构体定义，便于C#/C++交互
struct ROIInfo
{
	int startX;
	int startY;
	int distX;
	int distY;
	int width;
	int height;

	// 默认构造函数
	ROIInfo()
	{
		startX = 0;
		startY = 0;
		distX = 0;
		distY = 0;
		width = 0;
		height = 0;
	}

	// 构造函数
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


// 定义旋钮档位的语义
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


// 返回结果结构体定义
// 主要分为多个值（数组）和单个值（Double吧）
struct ResultInfo
{

	//int * arrayResult = nullptr;	//实际使用的时候初始化内存再进行调用，防止内存泄漏，抛弃这种方式

	double result = 0.0;

	std::vector<int> vectorResult;	//实际使用时设置长度
};



// 返回结果二维码位置
// 
struct QRCodeInfo
{
	unsigned int startX;
	unsigned int startY;
	unsigned int width;
	unsigned int height;
};

// 二维码检测结构体
// 类型，内容，旋转角度，位置，长宽
struct QRCodePos
{
	int startX;
	int startY;
	int width;
	int height;
};


// 定义错误类型返回码1
static const int sg_OK = 0;
static const int sg_ERROR = 1;

// 定义二维码检测结果码9
static const int sg_qrcode_imgnull = 91;	// 二维码入参为空
static const int sg_qrcode_detectNone = 92;	// 没有检测到二维码
static const int sg_qrcode_detectError = 93;	// 二维码检测出错
static const int sg_qrcode_searchNone = 94;	// 搜索指定二维码失败
static const int sg_qrcode_searchContentNull = 95;	// 搜索指定二维码失败

// 定义畸变校正 12
// 类型
static const int sg_Camera_Far = 121;		// 远侧
static const int sg_Camera_Near = 122;		// 近侧
static const int sg_Camera_NoOption = 125;	//没有畸变校正选项

// 结果
static const int sg_Camera_OptionFail = 126;



// 定义任务类型码2
static const int sg_task_analog = 1;	//模拟指示器
static const int sg_task_knob = 2;		//旋钮
static const int sg_task_led = 3;		//指示灯
static const int sg_task_pointer = 4;		//指针
static const int sg_task_switch = 5;		//短接片

// 定义旋钮头型类型码8
static const int sg_knob_type_Square = 81;		//方形旋钮
static const int sg_knob_type_Rectangle = 82;	//矩形旋钮
static const int sg_knob_type_Circle = 83;		//圆形旋钮

// 定义模拟指示器 9
// 类型
static const int sg_analog_type_circles = 91;   //模拟指示器类型一：有圆无灯 3个灯
static const int sg_analog_type_twoPanels = 92; //模拟指示器类型二：两个方格 2个灯
static const int sg_analog_type_onePanel = 93;  //模拟指示器类型三：一个方格 1个灯
static const int sg_analog_type_lights = 94;	//模拟指示器类型四：有圆有灯 3个灯

// 结果
static const int sg_analog_Connect= 98;	    //模拟指示器 接入
static const int sg_analog_DisConnect = 99;	//模拟指示器 断开

// 定义指示灯类型码10
// 类型
static const int sg_led_type_benderZongCha = 101;	//继电保护器	纵差继电器 从上至下10位
static const int sg_led_type_benderBaoHu = 102;		//继电保护器	保护继电器 从左至右8位
static const int sg_led_type_benderTongXun = 103;	//继电保护器	通讯继电器 从左至右17位
static const int sg_led_type_YouDian = 104;			//闪烁灯		有电显示器 从左至右3位

// 结果
static const int sg_led_open = 105;	// 指示器灯 亮
static const int sg_led_close = 106;// 指示器灯 灭
static const int sg_led_UpCloseDownClose = 107;// 指示器灯 上灭下灭
static const int sg_led_UpOpenDownClose = 108;// 指示器灯 上亮下灭
static const int sg_led_UpCloseDownOpen = 109;// 指示器灯 上灭下亮
static const int sg_led_UpOpenDownOpen = 110;// 指示器灯 上亮下亮



#endif // !SGCORE_DEF_H
