using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace DetectGUIPlus
{
    class XMLProcess
    {
        // XML生成,路径指定
        // 新的XML生成
        public void generateXML(string xmlPath, string cabinName, string cabinType, string dev_Num, string side, string itemNum)
        {
            XDeclaration xdeca = new XDeclaration("1.0", "UTF-8", "yes");
            XDocument xdoc = new XDocument(xdeca);

            XElement root = new XElement("root");

            XElement info = new XElement("info");
            info.Add(   new XElement("cabinName", cabinName),
                        new XElement("cabinType", cabinType),
                        new XElement("dev_Num", dev_Num),
                        new XElement("side", side),
                        new XElement("itemNum",itemNum));
            root.Add(info);
            xdoc.Add(root);
            xdoc.Save(xmlPath);
        }


        // 增加仪表项
        // 现在变为计算相对位置
        public void appendDevice(string xmlPath, string deviveName, TaskInfo task, ROIInfo roi, string addtionText, string order, QRCodeInfo qrRefer)
        {
            XElement xdoc = XElement.Load(xmlPath);

            XElement xeDevice = new XElement("device");
            xeDevice.SetAttributeValue("type", task.type);

            // 增加一项名字
            XElement xeName = new XElement("name", deviveName);
            xeDevice.Add(xeName);

            XElement xeTask = new XElement("taskinfo");
            xeTask.Add( new XElement("type", task.type),
                        new XElement("subtype", task.subtype),
                        new XElement("number", task.number),
                        new XElement("order",order));   //增加序号供C++层返回结果

            xeDevice.Add(xeTask);

            XElement xeROI = new XElement("roiinfo");
            xeROI.Add(  new XElement("startX", roi.startX),
                        new XElement("startY", roi.startY),
                        new XElement("distX", roi.startX - qrRefer.startX),
                        new XElement("distY", roi.startY - qrRefer.startY),
                        new XElement("width", roi.width),
                        new XElement("height", roi.height));

            xeDevice.Add(xeROI);

            if (DLLDefine.sg_task_pointer == task.type)
            {
                XElement pointerInfo= new XElement("unitinfo");    //TODO 此处获取指针额外配置
                getElementFromText(addtionText, task.type,ref pointerInfo);
                xeDevice.Add(pointerInfo);
            }
            else if (DLLDefine.sg_task_knob == task.type)
            {
                XElement knobInfo = new XElement("unitinfo");   // TODO 此处解析旋钮额外配置
                getElementFromText(addtionText, task.type, ref knobInfo);
                xeDevice.Add(knobInfo);
            }
            

            xdoc.Add(xeDevice);

            xdoc.Save(xmlPath);
        }

        public void appendQRPosition(string xmlPath, QRCodeInfo qrROI, string qrContent)
        {
            XElement xdoc = XElement.Load(xmlPath);

            //XElement info = xdoc.Element("info");

            var qrinfo = xdoc.Elements("QRCODE");
            if (qrinfo != null)
            {
                xdoc.Elements("QRCODE").Remove();
            }

            XElement QR = new XElement("QRCODE");
            QR.Add(new XElement("startX", qrROI.startX),
                   new XElement("startY", qrROI.startY),
                   new XElement("width", qrROI.width),
                   new XElement("height", qrROI.height),
                   new XElement("content",qrContent));

            xdoc.AddFirst(QR);
            //xdoc.Add(QR);

            xdoc.Save(xmlPath);
        }

        public void GetQRregionorigin(string xmlpath, ref QRCodeInfo qrcodeorigin )
        {
            // 1. 加载XML文件
            XElement xe = XElement.Load(xmlpath);

            XElement QRCODE = xe.Element("QRCODE");

            int startX = Convert.ToInt16(QRCODE.Element("startX").Value);
            int startY = Convert.ToInt16(QRCODE.Element("startY").Value);
            int width = Convert.ToInt16(QRCODE.Element("width").Value);
            int height = Convert.ToInt16(QRCODE.Element("height").Value);
            qrcodeorigin.startX = startX;
            qrcodeorigin.startY = startY;
            qrcodeorigin.width = width;
            qrcodeorigin.height = height;
        }


        // 由XML文件生成检测任务序列
        public List<DetectInfo> xmlToTaskList(string xmlPath)
        {
            // 1. 加载XML文件
            XElement xe = XElement.Load(xmlPath);

            // 2. 获取XML Device 信息
            IEnumerable<XElement> devices =  xe.Elements("device");                                  

            // 3. 遍历并生成任务信息，同时添加到任务序列中
            List<DetectInfo> DetectList = new List<DetectInfo>();

            foreach(XElement element in devices)
            {
                XElement eleRoi = element.Element("roiinfo");
                int startX = Convert.ToInt16(eleRoi.Element("startX").Value);
                int startY = Convert.ToInt16(eleRoi.Element("startY").Value);
                int disX = Convert.ToInt16(eleRoi.Element("distX").Value);
                int disY = Convert.ToInt16(eleRoi.Element("distY").Value);
                int width = Convert.ToInt16(eleRoi.Element("width").Value);
                int height = Convert.ToInt16(eleRoi.Element("height").Value);
                ROIInfo roi = new ROIInfo(startX, startY, disX, disY, width, height);


                XElement eleTask = element.Element("taskinfo");
                int type = Convert.ToInt16(eleTask.Element("type").Value);
                int subtype = Convert.ToInt16(eleTask.Element("subtype").Value);
                int num = Convert.ToInt16(eleTask.Element("number").Value);
                TaskInfo task = new TaskInfo(type, subtype, num);

                XElement eleName = element.Element("name");
                string devicename = eleName.Value;

                // 此处添加参考信息，用以检测结果对应语义
                ReferInfo refer = new ReferInfo();
                XMLToTaskRefer(element, type, ref refer);

                DetectInfo detect = new DetectInfo(devicename, roi, task, refer);
                DetectList.Add(detect);
            }

            // 4. 返回任务序列
            return DetectList;
        }


        // 将任务信息中的单位参考信息拆出来
        public void XMLToTaskRefer(XElement xele, int type, ref ReferInfo refer)
        {
            if (DLLDefine.sg_task_pointer == type)
            {
                XElement eleunit = xele.Element("unitinfo");
                int min = Convert.ToInt16(eleunit.Element("rangeLow").Value);
                int max = Convert.ToInt16(eleunit.Element("rangeHigh").Value);
                string unit = eleunit.Element("unit").Value;
                refer.POINTER_REFER = new pointer_refer(min, max, unit);
            }
            else if (DLLDefine.sg_task_knob == type)
            {
                refer.KNOB_REFER = new knob_refer();
                IEnumerable<XElement> elestalls = xele.Element("unitinfo").Elements("stall");
                foreach (XElement item in elestalls)
                {
                    int min = Convert.ToInt16(item.Element("rangeLow").Value);
                    int max = Convert.ToInt16(item.Element("rangeHigh").Value);
                    string context = item.Element("context").Value;
                    refer.KNOB_REFER.knobs.Add(new knob_refer.knobStall(min, max, context));
                }
            }
            else if (DLLDefine.sg_task_analog == type)
            {
                refer.ANALOG_REFER = new analog_refer();
            }
            else if (DLLDefine.sg_task_led == type)
            {
                refer.LED_REFER = new led_refer();
            }
        }



        // 从XML文件中获取电柜信息
        public void XMLtoCabinInfo(string xmlPath,  ref string cabinName, ref string cabinType,ref string dev_Num, ref string side)
        {
            // 1. 加载XML文件
            XElement xe = XElement.Load(xmlPath);

            // 2. 提取相关信息，通过引用返回
            cabinName = xe.Element("info").Element("cabinName").Value;
            cabinType = xe.Element("info").Element("cabinType").Value;
            dev_Num = xe.Element("info").Element("dev_Num").Value;
            side = xe.Element("info").Element("side").Value;
        }


        private void getElementFromText(string text, int devicetype, ref XElement result)
        {
            if (DLLDefine.sg_task_pointer == devicetype)
            {
                string[] words = text.Split(',');
                result.Add(new XElement("rangeLow", words[0]),
                           new XElement("rangeHigh", words[1]),
                           new XElement("unit", words[2]));
            }
            else if (DLLDefine.sg_task_knob == devicetype)
            {
                string[] strings = text.Split(';');
                foreach (var item in strings)
                {
                    if (item.Equals(""))
                    {
                        return;
                    }
                    string[] words = item.Split(',');
                    XElement stall = new XElement("stall");
                    stall.Add(new XElement("rangeLow", words[0]),
                                new XElement("rangeHigh", words[1]),
                                new XElement("context", words[2]));
                    result.Add(stall);
                }
            }
        }

        internal void getCameraSide(string xmlPath, ref int cameraside)
        {
            // 1. 加载XML文件
            XElement xe = XElement.Load(xmlPath);

            // 2. 获取cameraSide信息
            string sideContent = xe.Element("info").Element("side").Value;
            if (sideContent == null)
            {
                cameraside = 0;
                return;
            }
            if (sideContent.Equals("FarFace"))
            {
                cameraside = DLLDefine.sg_Camera_Far;
            }
            else if (sideContent.Equals("NearFace"))
            {
                cameraside = DLLDefine.sg_Camera_Near;
            }
        }
    }
}
