// sgfunc_file.h：视频处理函数头文件。


#ifndef SGFUNC_FILE_H
#define SGFUNC_FILE_H


#include <opencv2\opencv.hpp>
using namespace cv;

#include "tinyxml2.h"	// XML处理工具tinyXML2头文件

#include "../sgCore/sgcore_taskinfo.h"

// 保存相机信息到文件
int saveCameraInfo(const string filename, const Mat Intrix, const Mat  disCoeff, const string CameraName);

// 从文件读取相机信息
int readCameraInfo(const string filename, Mat & Intrix, Mat  & disCoeff);

// 从XML分析任务队列
int getDetectListFromXML(const string xmlPath, std::vector<DetectInfo> & detectList);

// 从XML获取二维码信息
int getQRPosOriginFromXML(const string xmlPath, QRCodePos & QRPos, string & qrContent);

// 从XML中获取校正选项
int getCameraOptionFromXML(const string xmlPath, int & cameraType);

// 从XML中获取开关柜元素数目
int getEleNumOptionFromXML(const string xmlPath, int & elenum);

void Convert(const string stringIN, string & strinyOut, int sourceCodepage, int targetCodepage);

#endif // !SGFUNC_VIDEO_H