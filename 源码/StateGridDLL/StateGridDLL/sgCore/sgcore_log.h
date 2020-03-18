/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_log.h
*
* 	@Brief	ʹ��Google Glog ��־����е������.
*	
* 	@Author	SHEN Xiaohai
*
* 	@Create	2018-03-23
*
*	@MethodList
*		1.
*
* 	Ver		Date		Author		WTChanged
* 	----------------------------------------------------------
*	1.0		3/23		SHEN		Created.
*
*/ 


#ifndef SGCORE_LOG_H
#define SGCORE_LOG_H



//�������#include <windows.h>��Ҫ���#define GLOG_NO_ABBREVIATED_SEVERITIES��
//���Ҵ�����Ҫ��google::GLOG_ERROR������ԭ����google::ERROR����Ӧ������Ҳ��Ϊ��GLOG_INFO��GLOG_WARNING��GLOG_FATAL��
#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES


// ����ƽ̨WIN32��X86ѡ������
#ifdef WIN32

// ����Debug/Releaseѡ��glog���ļ�
#ifdef _DEBUG
#pragma comment(lib,"../glog/glog_x86/lib/glogd.lib")
#else
#pragma comment(lib,"../glog/glog_x86/lib/glog.lib")
#endif // _DEBUG

// ����ͷ�ļ�
#include "../../glog/glog_x86/include/logging.h"

#else

// ����Debug/Releaseѡ��glog���ļ�
#ifdef _DEBUG
#pragma comment(lib,"../glog/glog_x64/lib/glogd.lib")
#else
#pragma comment(lib,"../glog/glog_x64/lib/glog.lib")
#endif // _DEBUG

// ����ͷ�ļ�
#include "../../glog/glog_x64/include/logging.h"

#endif // WIN32

// google glog �����ռ�
using namespace google;

#include <string>
using namespace std;


// glog��ʼ��
void glogInit(const char* argv, string glogDir);

// glog�ر�
void glogShutdown();

void glogTest();



#endif // !SGCORE_LOG_H

