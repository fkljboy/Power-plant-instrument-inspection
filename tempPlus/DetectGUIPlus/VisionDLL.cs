/********************************************************************
	created:	2018/03/16
	created:	16:3:2018   10:22
	filename: 	E:\Documents\Visual Studio 2015\Projects\DetectGUIPlus\DetectGUIPlus\VisionDLL.cs
	file path:	E:\Documents\Visual Studio 2015\Projects\DetectGUIPlus\DetectGUIPlus
	file base:	VisionDLL
	file ext:	cs
	author:		Shen Xiaohai
	
	purpose:	C++算法库的接口和调用函数
*********************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DetectGUIPlus
{
    public class VisionDLL
    {
        private bool glogInitiated = false;

        public const int sg_OK = 0;
        public const int sg_ERROR_img_null = 12;    // 图像路径为空
        public const int sg_qrcode_detectNone = 92;    // 没有检测到二维码
        public const int sg_qrcode_detectError = 93;    // 二维码检测出错

        public const int sg_Camera_Far = 121;   // 远侧
        public const int sg_Camera_Near = 122;	// 近侧

        /// <summary>
        ///   C++算法库DLL接口声明
        /// </summary>
        private class visionAlgorithm
        {
            // 初始化glog日志系统，已被抛弃
            [DllImport("StateGridDLL.dll", EntryPoint = "GoogleGlogInit", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GoogleGlogInit(string exefilename, string glogDir);

            // 初始化glog日志系统
            [DllImport("StateGridDLL.dll", EntryPoint = "GoogleGlogInitShanghai", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GoogleGlogInitShanghai(string exefilename);

            // 关闭glog日志系统
            [DllImport("StateGridDLL.dll", EntryPoint = "GoogleGlogShutdown", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GoogleGlogShutdown();

            // 检测识别任务交互接口，已被抛弃
            [DllImport("StateGridDLL.dll", EntryPoint = "DetectTask", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int DetectTask(string filename, ROIInfo roi, TaskInfo taskinfo, string processedName, ref ResultTemp resultTemp, int cameraType);

            // 根据ROI数组绘制方框，已被抛弃
            [DllImport("StateGridDLL.dll", EntryPoint = "DrawROIArray", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int DrawROIArray(string filename, ROIInfo[] ROIArray, int num, string processedName, ref QRCodeInfo qrcode, int cameraType);

            // 在C++端释放内存，已被抛弃
            [DllImport("StateGridDLL.dll", EntryPoint = "ReleaseMemoryFromC", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern bool ReleaseMemoryFromC(IntPtr buf);

            // 二维码位置检测多个
            [DllImport("StateGridDLL.dll", EntryPoint = "QRCodePositionMulti", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int QRCodePositionMulti(string filename,int[] x, int[] y,int[] height, int[] width, StringBuilder content, ref int qrNum, int cameraType);

            // 对图像进行畸变校正
            [DllImport("StateGridDLL.dll", EntryPoint = "ImgUndistort", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int ImgUndistort(string filename, string savePath, int cameraType);

            // 在指定区域搜索二维码
            [DllImport("StateGridDLL.dll", EntryPoint = "findQRcodeinRegion", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int findQRcodeinRegion(string filename, int cameraType, ROIInfo searchArea, ref QRCodeInfo QRcode, StringBuilder content);

            // 根据XML配置文件对任务序列的ROI进行查看，暂时未抛弃
            [DllImport("StateGridDLL.dll", EntryPoint = "drawROIwithXML", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int drawROIwithXML(string filename, string xmlpath, string savepath);

            // 根据XML配置文件对任务序列进行检测
            [DllImport("StateGridDLL.dll", EntryPoint = "detectWithXML", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
            public static extern int detectWithXML(string filename, string xmlpath, StringBuilder result, int Devnum, int updown);

        }


        /// <summary>
        /// 检测任务传递函数，抛弃
        /// </summary>
        /// <param name="srcPath"></param>
        /// <param name="PrcdPath"></param>
        /// <param name="detectinfo"></param>
        /// <returns></returns>
        public int DetectTaskSend(string srcPath, ref string PrcdPath, ref DetectInfo detectinfo, int cameraOption)
        {
            //处理结束的图像保存路径
            PrcdPath = DLLDefine.ImgDBFolder + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + "_Detect_" + ".jpg";

            TaskInfo task = detectinfo.TASKINFO;        //直接将Taskinfo输入，关于赋值是在解析配置文件时赋值

            ROIInfo roi = detectinfo.ROIINFO;           //直接将ROIinfo输入，关于赋值是在解析配置文件时赋值

            ResultTemp resultTemp = new ResultTemp();   //处理结果临时变量

            visionAlgorithm.DetectTask(srcPath, roi, task, PrcdPath, ref resultTemp, cameraOption);   //调用DLL接口进行图像处理

            // 数据转换
            detectinfo.RESULTINFO = detectinfo.ResultTempToResultInfo(resultTemp);

            // 释放内存，指针传值的地方(如果申请了内存)
            if (resultTemp.arrayResult != IntPtr.Zero)
            {
                visionAlgorithm.ReleaseMemoryFromC(resultTemp.arrayResult);
            }
                        
            return DLLDefine.sg_OK;
        }

        /// <summary>
        /// 检测图像中的二维码
        /// </summary>
        /// <param name="srcPath"></param>
        /// <param name="xarray"></param>
        /// <param name="yarray"></param>
        /// <param name="heightarray"></param>
        /// <param name="widtharray"></param>
        /// <param name="contentarray"></param>
        /// <param name="qrNum"></param>
        public void GetQRcodePositionMulti(string srcPath, ref int[] xarray, ref int[] yarray, ref int[] heightarray, ref int[] widtharray, ref string[] contentarray, ref int qrNum, int cameraOption)
        {
            StringBuilder wholeContent = new StringBuilder(200);    //Capacity 定义，内容大一些
            int resp =  visionAlgorithm.QRCodePositionMulti(srcPath, xarray, yarray, heightarray, widtharray, wholeContent, ref qrNum, cameraOption);
            if (resp != sg_OK)
            {
                if (resp == sg_ERROR_img_null)
                {
                    Console.WriteLine("路径为空");
                }
                if (resp == sg_qrcode_detectNone)
                {
                    Console.WriteLine("没有检测到二维码");
                }
                if (resp == sg_qrcode_detectError)
                {
                    Console.WriteLine("二维码检测出错");
                }
                return;
            }

            wholeContent.Remove(wholeContent.Length - 1, 1); //移除最后一个分隔符';'
            string wholestring = wholeContent.ToString();
            contentarray = wholestring.Split(';');  
        }


        /// <summary>
        /// glog日志系统初始化，外部调用
        /// </summary>
        public void glogint(string exefilename)
        {
            //visionAlgorithm.GoogleGlogInit(exefilename, "E:/Documents/SVN/StateGrid/Logs");
            visionAlgorithm.GoogleGlogInitShanghai(exefilename);
            
            this.glogInitiated = true;
        }


        /// <summary>
        /// glog日志系统关闭，外部调用
        /// </summary>
        public void glogshutdown()
        {
            if (this.glogInitiated)
            {
                visionAlgorithm.GoogleGlogShutdown();
            }
        }

        /// <summary>
        /// 图像畸变校正接口
        /// </summary>
        /// <param name="srcPath"></param>
        /// <param name="undistortPath"></param>
        public void ImgUnDistort(string srcPath, ref string undistortPath, int sideOption)
        {
            undistortPath = DLLDefine.ImgDBFolder + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + "_UNDISTORT_" + ".jpg";

            visionAlgorithm.ImgUndistort(srcPath, undistortPath, sideOption);
        }

        /// <summary>
        /// 寻找指定区域内的二维码
        /// </summary>
        /// <param name="srcPath"></param>
        /// <param name="searchArea"></param>
        /// <param name="qrcode"></param>
        /// <param name="qrcontent"></param>
        /// <param name="cameraOption"></param>
        public void searchQRwithregion(string srcPath, ROIInfo searchArea, ref QRCodeInfo qrcode, ref string qrcontent, int cameraOption)
        {
            StringBuilder CONTENT = new StringBuilder(20);
            int resp = visionAlgorithm.findQRcodeinRegion(srcPath, cameraOption, searchArea, ref qrcode, CONTENT);
            if (resp != DLLDefine.sg_OK)
            {
                Console.WriteLine("检测二维码出错");
                return;
            }

            qrcontent = CONTENT.ToString();
        }

        /// <summary>
        /// 绘制ROI进行查看，已被抛弃
        /// </summary>
        /// <param name="srcPath"></param>
        /// <param name="xmlPath"></param>
        /// <param name="savepath"></param>
        public void drawROIforCheck(string srcPath, string xmlPath, ref string savepath)
        {
            savepath = DLLDefine.ImgDBFolder + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + "_ROICheck_" + ".jpg";

            visionAlgorithm.drawROIwithXML(srcPath, xmlPath, savepath);
        }


        /// <summary>
        /// 指定柜号和上下，进行检测
        /// </summary>
        /// <param name="num"></param>
        /// <param name="contentarr"></param>
        /// <param name="updown"></param>
        public void DetectWithXML(int num, int updown, ref string[] contentarr)
        {
            StringBuilder CONTENT = new StringBuilder(200);
            string imgpath = DLLDefine.DeviceImgFolder + "Dev" + num.ToString() + "_" + updown.ToString() + ".jpg";
            string xmlpath = DLLDefine.XMLFolder + "XML_DEV_" + num.ToString() + "_" + updown.ToString() + ".xml";

            int resp = visionAlgorithm.detectWithXML(imgpath, xmlpath, CONTENT, num, updown);
            if (CONTENT.Length == 0)
            {
                string noanswer = "";
                contentarr = noanswer.Split(';'); 
                return;
            }
            CONTENT.Remove(CONTENT.Length - 1, 1); //移除最后一个分隔符';'
            string wholestring = CONTENT.ToString();

            contentarr = wholestring.Split(';');
        }
    }
}
