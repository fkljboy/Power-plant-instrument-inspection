/**
*   =========================================================
*   Copyright (c) 2018 HOHAI UNIVERSITY. All rights reserved.
*   =========================================================
*	
*	@File	sgcore_log.cpp
*
* 	@Brief	This is a brief description.
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
#include "sgcore_log.h"

#include  <string>
using namespace std;


/**
*	@Method		glogInit
*
*	@Brief		glog日志框架初始化.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	char* argv ： main函数argv[0]程序名称
*
*	@Para [OUT]	无
*
*	@Return		void
*
*  	@Note		设置日志文件保存目录，这个目录必须是已经存在的，否则不能生成日志文件。
*
*				必须在初始化库之前调用。
*
*				相对路径是相对于Debug下.exe的相对路径
*
*	@Create		2018-03-23
*/
void glogInit(const char* argv, string glogDir)
{
	//string glogLogDir(glogDir);	// const char* 转 string
	string glogLogDir = glogDir;

	FLAGS_log_dir = glogLogDir;

	//初始化库，括号内为程序名
	InitGoogleLogging(argv);

	//设置特定严重级别的日志的输出目录和前缀。第一个参数为日志级别，第二个参数表示输出目录及日志文件名前缀
	string info_log = glogLogDir + "/INFO_";
	SetLogDestination(GLOG_INFO, info_log.c_str());

	string warning_log = glogLogDir + "/WARNING_";
	SetLogDestination(GLOG_WARNING, warning_log.c_str());

	string error_log = glogLogDir + "/ERROR_";
	SetLogDestination(GLOG_ERROR, error_log.c_str());

	string fatal_log = glogLogDir + "/FATAL_";
	SetLogDestination(GLOG_FATAL, fatal_log.c_str());

	//大于指定级别的日志都输出到标准输出
	SetStderrLogging(GLOG_INFO);

	//在日志文件名中级别后添加一个扩展名。适用于所有严重级别
	SetLogFilenameExtension("log_");

	//设置记录到标准输出的颜色消息（如果终端支持）
	FLAGS_colorlogtostderr = true; 

	//设置可以缓冲日志的最大秒数，0指实时输出
	FLAGS_logbufsecs = 0;

	//设置最大日志文件大小（以MB为单位）
	FLAGS_max_log_size = 1024; 

	//设置是否在磁盘已满时避免日志记录到磁盘
	FLAGS_stop_logging_if_full_disk = true;
}



/**
*	@Method		glogShutdown
*
*	@Brief		关闭glog日志框架，避免内存溢出
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	无
*
*	@Para [OUT]	无
*
*	@Return		void
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-23
*/
void glogShutdown()
{
	//当要结束glog时必须关闭库，否则会内存溢出
	ShutdownGoogleLogging();
}




/**
*	@Method		glogTest
*
*	@Brief		glog测试，用法案例.
*
*	@Author		SHEN Xiaohai
*
*	@Para [IN]	inArgName input argument description.type name:purpose(Range)
*
*	@Para [OUT]	outArgName output argument description.
*
*	@Return		void:description of the return value
*				- TRUE
*				- FALSE
*
*  	@Note		matters needing attention
*
*	@Create		2018-03-23
*/
void glogTest()
{
	//输出一个Info日志
	LOG(INFO) << "info test";

	//输出一个Warning日志
	LOG(WARNING) << "warning test";  

	//输出一个Error日志
	LOG(ERROR) << "error test"; 

	//输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序		
	//LOG(FATAL) << "fatal test"; 

	//当条件满足时输出日志
	int num_cookies = 11;
	LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";  

	//google::COUNTER 记录该语句被执行次数，从1开始，在第一次运行输出日志之后，每隔 10 次再输出一次日志信息
	for (int i=0;i<50;i++)
	{
		LOG_EVERY_N(INFO, 10) << "Got the " << COUNTER << "th cookie";
	}


	//上述两者的结合，不过要注意，是先每隔 10 次去判断条件是否满足，如果滞则输出日志；而不是当满足某条件的情况下，每隔 10 次输出一次日志信息
	
	for (int i = 0; i < 50; i++)
	{
		LOG_IF_EVERY_N(INFO, (num_cookies > 10), 10) << "Got the " << COUNTER << "th big cookie";
	}

	//当此语句执行的前 20 次都输出日志，然后不再输出
	LOG_FIRST_N(INFO, 20) << "Got the " << COUNTER << "th cookie";
}