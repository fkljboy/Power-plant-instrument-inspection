/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_log.h
*
* 	@Brief	使用Google Glog 日志库进行调试输出.
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



//所以如果#include <windows.h>后要添加#define GLOG_NO_ABBREVIATED_SEVERITIES，
//并且代码中要用google::GLOG_ERROR来代替原来的google::ERROR，相应的其他也改为：GLOG_INFO、GLOG_WARNING、GLOG_FATAL。
#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES


// 根据平台WIN32和X86选择配置
#ifdef WIN32

// 根据Debug/Release选择glog库文件
#ifdef _DEBUG
#pragma comment(lib,"../glog/glog_x86/lib/glogd.lib")
#else
#pragma comment(lib,"../glog/glog_x86/lib/glog.lib")
#endif // _DEBUG

// 配置头文件
#include "../../glog/glog_x86/include/logging.h"

#else

// 根据Debug/Release选择glog库文件
#ifdef _DEBUG
#pragma comment(lib,"../glog/glog_x64/lib/glogd.lib")
#else
#pragma comment(lib,"../glog/glog_x64/lib/glog.lib")
#endif // _DEBUG

// 配置头文件
#include "../../glog/glog_x64/include/logging.h"

#endif // WIN32

// google glog 命名空间
using namespace google;

#include <string>
using namespace std;


// glog初始化
void glogInit(const char* argv, string glogDir);

// glog关闭
void glogShutdown();

void glogTest();



#endif // !SGCORE_LOG_H

