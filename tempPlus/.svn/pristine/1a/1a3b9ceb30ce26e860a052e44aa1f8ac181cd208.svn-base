using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DetectGUIPlus
{
    // 内存传递图像方式结构体
    public struct ImageInfo
    {
        public IntPtr data;
        public int size;
    }


    //ROI结构体定义，便于C#/C++交互
    public struct ROIInfo
    {
        public int startX;
        public int startY;
        public int distX;
        public int distY;
        public int width;
        public int height;

        public ROIInfo(int x, int y,int disx, int disy, int w, int h)
        {
            startX = x;
            startY = y;
            distX = disx;
            distY = disy;
            width = w;
            height = h;
        }
    };


    // 返回结果二维码位置
    // 
    public struct QRCodeInfo
    {
        public int startX;
        public int startY;
        public int width;
        public int height;
    };

    // 二维码检测结构体
    // 类型，内容，旋转角度，位置，长宽
    public struct QRCodeDetectInfo
    {
        public double angle;

        public int startX;
        public int startY;
        public int width;
        public int height;

        //string content;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string content;
    };



    // 任务信息结构体定义
    // subtype用于个别任务需要多个输入参数的情况
    public struct TaskInfo
    {
        public int type;

        public int subtype;

        public int number;

        public TaskInfo(int t = -1, int sub = -1, int num = -1)
        {
            type = t;
            subtype = sub;
            number = num;
        }

    };

    // C#与C++交互使用的结构体
    // 主要分为多个值（数组）和单个值（Double吧）
    //int数组不好传，因此用IntPtr指针获取算法库的运行结果
    public struct ResultTemp
    {
        public IntPtr arrayResult;

        public double result;
    };

    // C#客户端中数据传输的结构体
    public struct ResultInfo
    {
        public int[] arrayResult;

        public double result;
    };


    //  定义旋钮的语义
    public class knob_refer
    {
        // 定义旋钮档位的语义
        public struct knobStall
        {
            public int min_angle;
            public int max_angle;
            public string context;

            public knobStall(int min, int max, string s)
            {
                this.min_angle = min;
                this.max_angle = max;
                this.context = s;
            }
        };

        public List<knobStall> knobs;

        public knob_refer()
        {
            this.knobs = new List<knobStall>();
        }

        public string getContextWithAngle(double angle)
        {
            foreach (var item in knobs)
            {
                if (angle >= item.min_angle && angle < item.max_angle)
                {
                    return item.context;
                }
            }
            return "检测错误";
        }
    }

    // 定义指针语义
    public class pointer_refer
    {
        private int min;
        private int max;
        private string unit;

        public pointer_refer(int minmin, int maxmax, string unitunit)
        {
            this.min = minmin;
            this.max = maxmax;
            this.unit = unitunit;
        }

        public double getValueWithAngle(double angle)
        {
            return (angle / 90) * max;
        }

        public string getContextWithAngle(double angle)
        {
            return getValueWithAngle(angle).ToString("0.00") + unit;
        }
    }

    // 定义模拟指示器语义
    public class analog_refer
    {
        public struct analogItem
        {
            public int resultType;
            public string resultContext;

            public analogItem(int reT, string reCon)
            {
                this.resultType = reT;
                this.resultContext = reCon;
            }
        }

        public List<analogItem> anlogList;

        public analog_refer()   // 语义直接初始化的时候定义，如果有必要的话可以进行XML配置读取的定义
        {
            this.anlogList = new List<analogItem>();
            this.anlogList.Add(new analogItem( DLLDefine.sg_analog_Connect, "接入"));
            this.anlogList.Add(new analogItem( DLLDefine.sg_analog_DisConnect, "断开"));
        }

        public string getContextWithValue(int resultType)
        {
            foreach (var item in anlogList)
            {
                if (resultType == item.resultType)
                {
                    return item.resultContext;
                }
            }
            return "检测错误";
        }

        public string getContextWithValueArray(int[] resultArr)
        {
            string stringTogether = null;
            for (int i = 0; i < resultArr.Length; i++)
            { 
                foreach (var item in anlogList)
                {
                    if (resultArr[i] == item.resultType)
                    {
                        stringTogether += (i+1) + "." + item.resultContext + " ";
                    }
                }
            }
            return stringTogether;
        }
    }

    public class led_refer
    {
        public struct ledItem
        {
            public int resultType;
            public string resultContext;

            public ledItem(int reT, string reCon)
            {
                this.resultType = reT;
                this.resultContext = reCon;
            }
        }

        public List<ledItem> ledList;

        public led_refer()    // 语义直接初始化的时候定义，如果有必要的话可以进行XML配置读取的定义
        {
            this.ledList = new List<ledItem>();

            this.ledList.Add(new ledItem(DLLDefine.sg_led_close, "灭"));
            this.ledList.Add(new ledItem(DLLDefine.sg_led_open, "亮"));

            this.ledList.Add(new ledItem(DLLDefine.sg_led_UpcloseDownClose, "上灭下灭"));
            this.ledList.Add(new ledItem(DLLDefine.sg_led_UpOpenDownClose, "上亮下灭"));

            this.ledList.Add(new ledItem(DLLDefine.sg_led_UpCloseDownOpen, "上灭下亮"));
            this.ledList.Add(new ledItem(DLLDefine.sg_led_UpOpenDownOpen, "上亮下亮"));
        }

        public string getContextWithValue(int resultType)
        {
            foreach (var item in ledList)
            {
                if (resultType == item.resultType)
                {
                    return item.resultContext;
                }
            }
            return "检测错误";
        }

        public string getContextWithValueArray(int[] resultArr)
        {
            string stringTogether = null;
            for (int i = 0; i < resultArr.Length; i++)
            {
                foreach (var item in ledList)
                {
                    if (resultArr[i] == item.resultType)
                    {
                        stringTogether += (i + 1) + "." + item.resultContext + " ";
                    }
                }
            }
            return stringTogether;
        }
    }

    // 语义转换换算类
    public class ReferInfo
    {
        public knob_refer KNOB_REFER;
        public pointer_refer POINTER_REFER;
        public analog_refer ANALOG_REFER;
        public led_refer LED_REFER;
    }


    // 定义检测任务类
    public class DetectInfo
    {
        public string deviceName;

        public ROIInfo ROIINFO;

        public TaskInfo TASKINFO;

        public ResultInfo RESULTINFO;

        public ReferInfo REFERINFO;

        public DetectInfo(string devicename, ROIInfo roi, TaskInfo task, ReferInfo refer)
        {
            this.deviceName = devicename;
            this.ROIINFO = roi;
            this.TASKINFO = task;
            this.REFERINFO = refer;
        }

        // 转换数据，其实只是为了转换指针为数组
        public ResultInfo ResultTempToResultInfo(ResultTemp temp)
        {
            ResultInfo info = new ResultInfo();

            if (DLLDefine.sg_task_analog == TASKINFO.type)  //模拟指示器是数组形式
            {
                int[] resultarr = new int[TASKINFO.number];
                if (temp.arrayResult != IntPtr.Zero)
                {
                    Marshal.Copy(temp.arrayResult, resultarr, 0, TASKINFO.number);
                    info.arrayResult = resultarr;
                }
            }
            else if (DLLDefine.sg_task_knob == TASKINFO.type)
            {
                info.result = temp.result;
            }
            else if (DLLDefine.sg_task_pointer == TASKINFO.type)
            {
                info.result = temp.result;
            }
            else if (DLLDefine.sg_task_switch == TASKINFO.type)
            {
                info.result = temp.result;
            }
            else if (DLLDefine.sg_task_led == TASKINFO.type)    //指示灯是数组形式
            {
                int[] resultarr = new int[TASKINFO.number];
                if (temp.arrayResult != IntPtr.Zero)
                {
                    Marshal.Copy(temp.arrayResult, resultarr, 0, TASKINFO.number);
                    info.arrayResult = resultarr;
                }
            }
            return info;
        }


        public string GetResultWithRefer()
        {
            if (DLLDefine.sg_task_pointer == this.TASKINFO.type)
            {
                return this.REFERINFO.POINTER_REFER.getContextWithAngle(this.RESULTINFO.result);
            }
            else if (DLLDefine.sg_task_knob == this.TASKINFO.type)
            {
                return this.REFERINFO.KNOB_REFER.getContextWithAngle(this.RESULTINFO.result);
            }
            else if (DLLDefine.sg_task_analog == this.TASKINFO.type)
            {
                return this.REFERINFO.ANALOG_REFER.getContextWithValueArray(this.RESULTINFO.arrayResult);
            }else if (DLLDefine.sg_task_led == this.TASKINFO.type)
            {
                return this.REFERINFO.LED_REFER.getContextWithValueArray(this.RESULTINFO.arrayResult);
            }
            return null;
        }

        public string GetDetectClass()
        {
            if (DLLDefine.sg_task_pointer == this.TASKINFO.type)
            {
                return "仪表读数";
            }
            else if (DLLDefine.sg_task_knob == this.TASKINFO.type)
            {
                return "档位判断";
            }
            else if (DLLDefine.sg_task_analog == this.TASKINFO.type)
            {
                return "符号识别";
            }
            else if (DLLDefine.sg_task_switch == this.TASKINFO.type)
            {
                return "开关判断";
            }
            else if (DLLDefine.sg_task_led == this.TASKINFO.type)
            {
                return "开关判断";
            }
            return null;
        }
    }



    public class DLLDefine
    {
        // C#工程需要用到的路径

        public const string XMLFolder = "配置文件/";

        public const string ImgDBFolder = "图像缓存/";

        public const string DeviceImgFolder = "设备图片/";

        public const string ElementImgFolder = "设备元素图片/";

        // 定义错误类型返回码1
        public const int sg_OK = 0;
        public const int sg_ERROR = 1;
        public const int sg_String_Null = 2;
        public const int sg_Mat_Null = 3;
        public const int sg_XML_LoadFail = 4;
        public const int sg_XML_TaskListZero = 5;
        public const int sg_XML_NoQrCode = 6;
        public const int sg_XML_ROIArrayNone = 7;
        public const int sg_XML_PathNULL = 8;
        public const int sg_ROI_WrongSize = 9;
        public const int sg_TASK_typeisWrong = 10;

        public const int sg_knob_panel_notFound = -1;
        public const int sg_ERROR_img_null = 2;
        public const int sg_ERROR_knob_NO_panel = 3;
        public const int sg_ERROR_knob_NO_rectArea = 4;
        public const int sg_ERROR_knob_NO_lineSquare = 5;
        public const int sg_ERROR_knob_cacBound_NOCONTOUR = 7;
        public const int sg_ERROR_switch_NO_switchArea = 8;
        public const int sg_ERROR_pointer_NO_baseLine = 9;
        public const int sg_ERROR_pointer_NO_pointer = 10;
        public const int sg_ERROR_analog_circleNotEqual = 11;
        public const int sg_ERROR_analog_circleSizeZero = 12;
        public const int sg_ERROR_pointer_NO_AreaDetected = 13;
        public const int sg_ERROR_Draw_ROIsize_Wrong = 14;

        public const int sg_ERROR_TaskID_IS_WRONG = 15;
        public const int sg_ERROR_TaskID_analog_IS_WRONG = 16;
        public const int sg_ERROR_TaskID_knob_IS_WRONG = 17;
        public const int sg_ERROR_TaskID_switch_IS_WRONG = 18;
        public const int sg_ERROR_TaskID_led_IS_WRONG = 19;

        public const int sg_ERROR_led_circle_notFound = 20;
        public const int sg_ERROR_led_bender_num_wrong = 21;

        // 定义畸变校正 12
        public const int sg_Camera_Far = 121;   // 远侧
        public const int sg_Camera_Near = 122;  // 近侧
        public const int sg_Camera_NoOption = 125;	//没有畸变校正选项

        // 定义任务类型码
        public const int sg_task_analog = 1;    //模拟指示器
        public const int sg_task_knob = 2;      //旋钮
        public const int sg_task_led = 3;       //指示灯
        public const int sg_task_pointer = 4;       //指针
        public const int sg_task_switch = 5;        //短接片
        public const int sg_task_none = -1;

        public const int sg_subtype_none = -1;
        public const int sg_taskNum_none = 1;

        // 定义旋钮 8
        // 类型
        public const int sg_knob_type_Square = 81;      //方形旋钮
        public const int sg_knob_type_Rectangle = 82;   //矩形旋钮
        public const int sg_knob_type_Circle = 83;      //圆形旋钮

        // 定义模拟指示器 9
        // 类型
        public const int sg_analog_type_circles = 91;   //模拟指示器类型一：有圆无灯
        public const int sg_analog_type_twoPanels = 92; //模拟指示器类型二：两个方格
        public const int sg_analog_type_onePanel = 93;  //模拟指示器类型三：一个方格
        public const int sg_analog_type_lights = 94;    //模拟指示器类型四：有圆有灯
                                                        // 结果
        public const int sg_analog_Connect = 98;        //模拟指示器 接入
        public const int sg_analog_DisConnect = 99;	//模拟指示器 断开

        // 定义指示灯类型码10
        // 类型
        public const int sg_led_type_benderZongCha = 101;   //继电保护器	纵差继电器 从上至下10位
        public const int sg_led_type_benderBaoHu = 102;     //继电保护器	保护继电器 从左至右8位
        public const int sg_led_type_benderTongXun = 103;   //继电保护器	通讯继电器 从左至右17位
        public const int sg_led_type_YouDian = 104;         //闪烁灯		有电显示器 从左至右3位
                                                            // 结果
        public const int sg_led_open = 105; // 指示器灯 亮
        public const int sg_led_close = 106;// 指示器灯 灭
        public const int sg_led_UpcloseDownClose = 107;// 指示器灯 上灭下灭
        public const int sg_led_UpOpenDownClose = 108;// 指示器灯 上亮下灭
        public const int sg_led_UpCloseDownOpen = 109;// 指示器灯 上灭下亮
        public const int sg_led_UpOpenDownOpen = 110;// 指示器灯 上亮下亮



    }
}