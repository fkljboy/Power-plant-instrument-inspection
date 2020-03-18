// sgfunc_file.h����Ƶ������ͷ�ļ���


#ifndef SGFUNC_FILE_H
#define SGFUNC_FILE_H


#include <opencv2\opencv.hpp>
using namespace cv;

#include "tinyxml2.h"	// XML������tinyXML2ͷ�ļ�

#include "../sgCore/sgcore_taskinfo.h"

// ���������Ϣ���ļ�
int saveCameraInfo(const string filename, const Mat Intrix, const Mat  disCoeff, const string CameraName);

// ���ļ���ȡ�����Ϣ
int readCameraInfo(const string filename, Mat & Intrix, Mat  & disCoeff);

// ��XML�����������
int getDetectListFromXML(const string xmlPath, std::vector<DetectInfo> & detectList);

// ��XML��ȡ��ά����Ϣ
int getQRPosOriginFromXML(const string xmlPath, QRCodePos & QRPos, string & qrContent);

// ��XML�л�ȡУ��ѡ��
int getCameraOptionFromXML(const string xmlPath, int & cameraType);

// ��XML�л�ȡ���ع�Ԫ����Ŀ
int getEleNumOptionFromXML(const string xmlPath, int & elenum);

void Convert(const string stringIN, string & strinyOut, int sourceCodepage, int targetCodepage);

#endif // !SGFUNC_VIDEO_H