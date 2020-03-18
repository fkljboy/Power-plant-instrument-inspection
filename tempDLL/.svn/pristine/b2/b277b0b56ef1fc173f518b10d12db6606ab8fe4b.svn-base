/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_safetyCheck.h
*
* 	@Brief	用来进行安全监测的代码头文件.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-06-03
*
*	@MethodList
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		6/03		SHEN		Created.
*
*/ 

#ifndef SGCORE_SAFETYCHECK_H
#define SGCORE_SAFETYCHECK_H


// 1. 检查内存泄漏
// 参考链接：http://www.cnblogs.com/phinecos/archive/2009/10/29/1592604.html
// 参考链接：https://www.zhihu.com/question/63946754

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define SG_CHECK_MEMORY_LEAKS_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new SG_CHECK_MEMORY_LEAKS_NEW
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//定义函数：  
//该函数可以放在主函数的任意位置，都能正确的触发内存泄露输出  
// 参考链接： https://blog.csdn.net/sinat_20265495/article/details/51763084
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}


// 3. 检查ROI的Rect是否取值正确
#include <opencv2\opencv.hpp>
using namespace cv;

int checkRectInside(const Mat srcImg, const Rect roiRect);


#endif // !SGCORE_SAFETYCHECK_H
