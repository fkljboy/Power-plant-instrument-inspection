/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_safetyCheck.h
*
* 	@Brief	�������а�ȫ���Ĵ���ͷ�ļ�.
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


// 1. ����ڴ�й©
// �ο����ӣ�http://www.cnblogs.com/phinecos/archive/2009/10/29/1592604.html
// �ο����ӣ�https://www.zhihu.com/question/63946754

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
//���庯����  
//�ú������Է���������������λ�ã�������ȷ�Ĵ����ڴ�й¶���  
// �ο����ӣ� https://blog.csdn.net/sinat_20265495/article/details/51763084
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}


// 3. ���ROI��Rect�Ƿ�ȡֵ��ȷ
#include <opencv2\opencv.hpp>
using namespace cv;

int checkRectInside(const Mat srcImg, const Rect roiRect);


#endif // !SGCORE_SAFETYCHECK_H
