using AForge.Video;
using AForge.Video.DirectShow;
using AForge.Video.FFMPEG;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace DetectGUIPlus
{
    public partial class MainWindow : Form
    {
        // 视频输入设备列表
        FilterInfoCollection cameraDevices;

        // 视频输入设备
        VideoCaptureDevice captureDevice;

        // 实例化一个DLL对象
        VisionDLL visiondll = new VisionDLL();

        // 实例化一个xml处理的对象
        XMLProcess xmlProcess = new XMLProcess();

        // 实例化一个ROI数组获取的对象
        DataFlow dataflow = new DataFlow();

        // 实例化一个数据库操作对象
        SQLInterface sqlProcess = new SQLInterface();
        
        // 待处理图像的路径
        private string imgPath;

        // 停止录像bool变量
        private bool stopREC = true;

        // 录像所需的帧率
        private int frameRate = 25; //默认帧率
        
        // 录像时先创建文件
        private bool createNewFile = true;

        // 写视频所需
        private VideoFileWriter videoWriter = null;

        // 巡检数据表自增序列编号
        private int detectCount = 0;

        // 事项数据表自增序列编号
        private int detailCount = 0;

        // 报警数据表自增序列编号
        private int alertCount = 0;

        // XML配置
        private Bitmap bitmapROI = null; //显示的图像
        private Point mouseDownPointROImove = new Point();  //记录拖拽过程中鼠标位置
        private Point mouseDownPointROIDrawStart = new Point();  //记录绘制中鼠标位置
        private Point mouseDownPointROIDrawStop = new Point();  //记录绘制中鼠标位置
        private Point RealROIStart = new Point();   //实际ROI区域起点
        private Point RealROIStop = new Point();   //实际ROI区域终点

        private bool isMoveROI = false; //判断鼠标在pictureBox上移动时，是否处于拖拽过程（鼠标左键是否按下）
        private float zoomStep = 0.1F;  //缩放步长
        private double ROIScale = 0;    //滚轮实现图片缩放 
        private bool ROISelect = false; //ROI选择按钮选项
        private bool boolROIDraw = false;

        private string xmlimagepath = null;

        private void MainWindowLoad(object sender, EventArgs e)
        {
            // 运行启动界面，此处直接等待，应使用多线程进行资源加载。
            WelcomeHohai myWelcome = new WelcomeHohai(500);
            myWelcome.ShowDialog();

            // Glog日志系统初始化
            visiondll.glogint(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName);
        }

        public MainWindow()
        {
            InitializeComponent();  //初始化所有组件
            
            panelLocationDetail.Hide(); //定位信息隐藏

            timerClock_Start(); //启动时钟

            sqlProcess.connectDatabase();   //连接数据库

            loadTree(); // 加载查询界面的设备列表

            panelImgSource.Hide();  //隐藏图像Panel
            panelvideoPlayer.Show();    //显示视频Panel

            loadCamera();   // 加载相机配置

            XMLConfigLoad();    // 配置界面的加载
        }





        // *******************************1.1 主界面菜单选项 ***************************************** 

        // 1.1.1 退出选项
        private void ExitXToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // 关闭摄像头
            if (videoSourcePlayer.IsRunning)
            {
                videoSourcePlayer.SignalToStop();
                videoSourcePlayer.WaitForStop();
            }

            // 关闭数据库连接
            sqlProcess.disconnectDatabase();

            // Glog日志系统关闭
            visiondll.glogshutdown();

            // 结束应用
            Application.Exit();
        }


        //1.1.2 XML配置
        private void xMLConfigurePluasToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XMLConfigure xmlconfigure = new XMLConfigure();
            xmlconfigure.ShowDialog();
        }



        //*********************1.2 主界面：相机相关********************************
        // 加载设备列表
        private void loadCamera()
        {
            try
            {
                // 获取视频输入设备列表
                cameraDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);

                if (cameraDevices.Count == 0)
                    throw new ApplicationException();

                // 填充至下拉框
                comboBoxCameraChoose.Items.Clear();
                foreach (FilterInfo device in cameraDevices)
                {
                    comboBoxCameraChoose.Items.Add(device.Name);
                }
                comboBoxCameraChoose.Items.Add("http://192.168.1.101:8080/video");    //添加IP摄像头

                comboBoxCameraChoose.SelectedIndex = 0;
            }
            catch (ApplicationException)
            {
                comboBoxCameraChoose.Items.Clear();
                comboBoxCameraChoose.Items.Add("没有检测到采集设备");
                comboBoxCameraChoose.SelectedIndex = 0;
                cameraDevices = null;
            }
        }

        // 打开摄像头
        private void buttonopenCamera_Click(object sender, EventArgs e)
        {
            // 1. 判断摄像头是否存在
            if (cameraDevices == null)
            {
                MessageBox.Show("没有检测到采集设备，请检查");
                return;
            }

            // 2. 判断是否已有摄像头在运行,先将摄像头关闭
            if (videoSourcePlayer.IsRunning)
            {
                videoSourcePlayer.SignalToStop();
                videoSourcePlayer.WaitForStop();
            }

            // 3. 打开选定摄像头
            captureDevice = new VideoCaptureDevice(cameraDevices[comboBoxCameraChoose.SelectedIndex].MonikerString);
            if (captureDevice.VideoCapabilities.Length > 10)
            {
                captureDevice.VideoResolution = captureDevice.VideoCapabilities[18];
            }
            else
            {
                captureDevice.VideoResolution = captureDevice.VideoCapabilities[5];
            }
            
            videoSourcePlayer.VideoSource = captureDevice;
            videoSourcePlayer.Start();


            
        }

        // 打开网络摄像头摄像头 // 820x461
        private void buttonIPcamera_Click(object sender, EventArgs e)
        {
            // 1. 判断是否已有摄像头在运行,先将摄像头关闭
            if (videoSourcePlayer.IsRunning)
            {
                videoSourcePlayer.SignalToStop();
                videoSourcePlayer.WaitForStop();
            }

            // 2. 获取IP并打开摄像头
            try
            {
                string URL = comboBoxCameraChoose.SelectedItem.ToString();
                MJPEGStream source = new MJPEGStream(URL);
                videoSourcePlayer.VideoSource = source;
                videoSourcePlayer.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show("网络摄像头异常,请重试： " + ex);
            }
            

            
        }

        // 关闭摄像头
        private void buttonCloseCamera_Click(object sender, EventArgs e)
        {
            // 1. 判断摄像头是否存在
            if (cameraDevices == null)
            {
                MessageBox.Show("没有检测到采集设备，请检查");
                return;
            }

            videoSourcePlayer.SignalToStop();
            videoSourcePlayer.WaitForStop();
        }

        // 更新检索摄像头
        private void buttonRefreshCameras_Click(object sender, EventArgs e)
        {
            comboBoxCameraChoose.Items.Clear();
            loadCamera();
        }

        // 抓拍实现
        private void buttonCapture_Click(object sender, EventArgs e)
        {
            // 1. 判断摄像头是否存在
            if (cameraDevices == null)
            {
                MessageBox.Show("没有检测到采集设备，请检查");
                return;
            }

            // 2. 抓拍实现
            try
            {
                if (videoSourcePlayer.IsRunning)
                {
                    Bitmap bmp = null;
                    bmp = videoSourcePlayer.GetCurrentVideoFrame(); //抓拍当前帧
                    if (bmp == null)
                    {
                        MessageBox.Show("捕获图像失败！", "提示");
                        return;
                    }

                    string bmpPath = DLLDefine.ImgDBFolder + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + "_Photo_" + ".jpg";
                    bmp.Save(bmpPath, System.Drawing.Imaging.ImageFormat.Jpeg);

                    imgPath = bmpPath;  // 切换加载的图片
                    pictureBoxSource.Image = Image.FromFile(imgPath);   //显示图片
                    displayROIImage(bmpPath);   // 在ROI配置界面设置

                    panelvideoPlayer.Hide();
                    panelImgSource.Show();
                }
                else
                {
                    MessageBox.Show("请打开摄像头！");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("摄像头异常： " + ex);
            }

            // 3. 直接调用XML进行分析
            //string xmlpath = "E:\\Documents\\SVN\\StateGrid\\XML\\513.xml";
            //processXML(xmlpath);
        }

        // 返回视频界面
        private void buttonGototakephoto_Click(object sender, EventArgs e)
        {
            panelImgSource.Hide();
            panelvideoPlayer.Show();
           
        }

        // 录像功能逻辑，录像功能主要在newFrame时间中
        private void buttonvideoCap_Click(object sender, EventArgs e)
        {
            // 1. 判断摄像头是否存在
            if (cameraDevices == null)
            {
                MessageBox.Show("没有检测到采集设备，请检查");
                return;
            }

            // 2. 录像开始与停止
            if (buttonvideoCap.Text == "开始录像")
            {
                stopREC = false;

                buttonvideoCap.Text = "停止录像";
            }
            else if (buttonvideoCap.Text == "停止录像")
            {
                stopREC = true;

                buttonvideoCap.Text = "开始录像";
            }
        }

        // videoSourcePlayer的newFrame事件
        // 备注：需要AForge的FFMPEG DLL文件，同时需要FFMPEG下的bin目录中的DLL文件
        private void videoSourcePlayer_NewFrame(object sender, ref Bitmap image)
        {
            //Graphics g = Graphics.FromImage(image);
            //SolidBrush drawBrush = new SolidBrush(Color.Yellow);
            //Font drawFont = new Font("Arial", 5, FontStyle.Bold, GraphicsUnit.Millimeter);
            //int xPos = 10;
            //int yPos = 10;

            ////写到屏幕上的时间
            //string drawDate = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");

            //g.DrawString(drawDate, drawFont, drawBrush, xPos, yPos);

            if (stopREC)
            {
                stopREC = true;
                createNewFile = true;  //这里要设置为true表示要创建新文件
                if (videoWriter != null)
                    videoWriter.Close();
            }
            else
            {
                //开始录像，第一帧先创建文件，后面保存到视频
                if (createNewFile)
                {
                    string videoFileName = DLLDefine.ImgDBFolder + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + "_Video_" + ".MP4";
                    createNewFile = false;
                    if (videoWriter != null)
                    {
                        videoWriter.Close();
                        videoWriter.Dispose();
                    }

                    videoWriter = new VideoFileWriter();
                    //这里必须是全路径，否则会默认保存到程序运行根据录下了
                    videoWriter.Open(videoFileName, image.Width, image.Height, frameRate, VideoCodec.MPEG4);
                    videoWriter.WriteVideoFrame(image);
                }
                else // 直接保存到视频
                {
                    videoWriter.WriteVideoFrame(image);
                }
            }


        }




        //*********************1.3 主界面：图像加载********************************
        // 1.3.1 文件方式加载图像
        private void pictureBoxSource_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = "E:\\3-研究生2017~2020\\6-项目\\2017-9-国家电网仪表识别项目-2018-3\\数据";
            openFileDialog.Filter = "图片文件(*.jpg,*.gif,*.bmp,*.png)|*.jpg;*.gif;*.bmp;*.png";
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FilterIndex = 1;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                String fileName = openFileDialog.FileName;
                pictureBoxSource.Image = Image.FromFile(fileName);
                imgPath = fileName;
            }
        }

        // 1.3.2 转到手动加载图像界面
        private void buttonToImage_Click(object sender, EventArgs e)
        {
            panelvideoPlayer.Hide();
            panelImgSource.Show();
        }




        //*********************1.4 主界面：XML运行并处理********************************
        //1.4.1 读取XML并进行分析：此处模仿整个流程：
        //      定位（没完成）-》读取XML(手动)-》分析任务序列-》提取ROI数组->绘制ROI-》遍历进行检测-》绘制数据
        private void buttonTest_Click(object sender, EventArgs e)
        {
            string xmlpath = null;

            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = DLLDefine.XMLFolder;
            openFileDialog.Filter = "配置文件(*.xml)|*.xml";
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FilterIndex = 1;

            // 1. 读取XML
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (openFileDialog.FileName.Equals(null))
                {
                    MessageBox.Show("文件路径为空");
                    //WarningDialog dialog = new WarningDialog("文件路径为空", DLLDefine.ImgDBFolder+ "File Delete_96px.png");
                    return;
                }
                xmlpath = openFileDialog.FileName;
            }
            else
            {
                MessageBox.Show("文件路径为空");
                //WarningDialog dialog = new WarningDialog("文件路径为空", DLLDefine.ImgDBFolder + "File Delete_96px.png");
                //dialog.ShowDialog();
                return;
            }
            processXML(xmlpath);

        }

        private void processXML(string xmlpath)
        {
            // 1. 获取电柜信息，更新到UI ,此处可以另开线程
            string house = null, cabin = null, side = null;
            xmlProcess.XMLtoCabinInfo(xmlpath, ref house, ref cabin, ref side);

            labelRom.Text = house;
            labelCab.Text = cabin;
            labelFac.Text = side;

            dataGridViewStatus.Rows.Clear();

            // 圆形进度条结束，定位信息显示
            panelLocationDetail.Show();
            circularProgressBarLocation.Value = 100;
            circularProgressBarLocation.Text = "定位成功......";
            circularProgressBarLocation.Style = ProgressBarStyle.Continuous;
            circularProgressBarLocation.MarqueeAnimationSpeed = 0;
            Delay(100); //delay是为了界面更新

            // 1.2 获取新的和旧的二维码位置
            //QRCodeInfo qrcode = new QRCodeInfo();
            //visiondll.GetQRregion(imgPath, ref qrcode);

            //QRCodeInfo qrcodeOrigin = new QRCodeInfo();
            //xmlProcess.GetQRregionorigin(xmlpath, ref qrcodeOrigin);

            // 1.2 
            int cameraSide = 0;
            if (side.Equals("远侧FarFace"))
            {
                cameraSide = DLLDefine.sg_Camera_Far;
            }
            else if (side.Equals("近侧NearFace"))
            {
                cameraSide = DLLDefine.sg_Camera_Near;
            }
            else
            {
                MessageBox.Show("相机远近侧参数确实，请确认！");
                return;
            }

            // 2. 分析任务序列
            List<DetectInfo> detectList = xmlProcess.xmlToTaskList(xmlpath);
            int detectSize = detectList.Count();


            // 2.01 根据任务序列绘制ROI数组,并显示图像
            ROIInfo[] roiarray = new ROIInfo[detectSize];
            string roiPath = null;
           dataflow.GetROIArrayFormDetectList(detectList,ref roiarray);    //获取ROI数组

            //dataflow.GetROIArrayFormDetectListwithQRCode(detectList, ref roiarray, qrcode, qrcodeOrigin); //获取换算之后的ROI数组,顺便把Detect的ROI也改了

            visiondll.ROIArrayDraw(imgPath, roiarray, ref roiPath, cameraSide);         //绘制ROI区域
            pictureBoxProcessed.Image = Image.FromFile(roiPath);            //显示绘制ROI后的图像
            Delay(200); //delay是为了界面更新

            // 2.1 分别进行检测，并更新界面进度信息
            int detectNow = 0;
            processUpdateUI(detectNow, detectSize); //重置UI

            foreach (DetectInfo item in detectList)
            {
                string procdpath = null;
                DetectInfo detect = item;

                visiondll.DetectTaskSend(imgPath, ref procdpath, ref detect, cameraSide);   //这一步得到检测结果，下一步应该是对检测结果进行一下数据的换算，需要从配置表中获取语义

                // UI 结果显示 小表格（仪表名称和检测结果），显示语义，调用自身类的转换功能实现数据到语义的转换
                dataGridViewStatus.Rows.Add(detect.deviceName, detect.GetResultWithRefer());

                // UI 结果显示 大表格（巡检数据结果），显示序号、时间、设备名称、检测结果、报警类型,并保存到数据库
                // TODO: 对检测结果进行报警判断
                detectResultSave(house, cabin, detect.deviceName, detect.GetResultWithRefer(), "正常", detect.GetDetectClass());

                // TODO 结果显示2. 大表格，大表格涉及到数据库的传入。暂不涉及

                // UI 进度更新
                detectNow = detectNow + 1;
                processUpdateUI(detectNow, detectSize); //更新UI

                Delay(500); //delay是为了界面更新
            }
        }

        //*********************1.5 主界面：时钟控件********************************
        private void timerClock_Tick(object sender, EventArgs e)
        {
            labelTime.Text = DateTime.Now.ToString("HH:mm");
            labelSecond.Text = DateTime.Now.ToString("ss");
            labelDate.Text = DateTime.Now.ToString("yyyy-MM-dd");
            labelWeek.Text = DateTime.Now.ToString("dddd");
        }

        public void timerClock_Start()
        {
            timerClock.Start();
        }

        public void timerClock_Stop()
        {
            timerClock.Stop();
        }




        //*********************1.5 主界面：检测进度百分比控件和进度信息标签********************************
        private void processUpdateUI(int detectNow, int detectSize)
        {
            circularProgressBarprocess.Value = (int)(detectNow * 1.0 / detectSize * 100);
            circularProgressBarprocess.Text = circularProgressBarprocess.Value.ToString() + "%";
            labelbarprocess.Text = "检测进度：" + detectNow.ToString() + " / " + detectSize.ToString();
        }




        //*********************1.6 主界面：巡检数据，事项，报警信息三个表添加新数据，并保存到相应数据库********************************
        // 1.6.1 巡检数据栏的表格添加
        private void detectResultSave(string room, string cabinet, string device, string result, string alert, string detectClass)
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");

            // 1. 填充至表格,并自动
            detectCount++;
            dataGridViewDetect.Rows.Add(detectCount, date, room + "-" + cabinet + "-" + device, result, alert);
            dataGridViewDetect.FirstDisplayedScrollingRowIndex = dataGridViewDetect.RowCount - 1;   // 自动显示最新的数据

            // 2. 保存至数据库
            sqlProcess.insertRecord(room, cabinet, device, detectClass, result, alert, date);
        }



        // 1.6.2 事项数据栏的表格添加
        private void detailItemsAdd(string level, string infomation)
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            detailCount++;

            // 1. 填充至表格
            dataGridViewDetail.Rows.Add(detailCount, date, level, infomation);
            dataGridViewDetail.FirstDisplayedScrollingRowIndex = dataGridViewDetail.RowCount - 1;   // 自动显示最新的数据

            // TODO 事项添加至数据库
        }



        // 1.6.3 报警信息数据栏的表格添加
        private void alertItemsAdd(string room, string cabinet, string device,string alertClass, string result, string alertLevel, string alertInfo, string confirm)
        {
            string date = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            alertCount++;

            // 1. 填充至表格
            dataGridViewAlarm.Rows.Add(alertCount, date, room + "-" + cabinet + "-" + device, alertClass, result, alertLevel, alertInfo, confirm);
            dataGridViewAlarm.FirstDisplayedScrollingRowIndex = dataGridViewAlarm.RowCount - 1;   // 自动显示最新的数据

            // TODO 报警添加至数据库
        }



        //************************2.1 查询界面：设备树状图***************************************
        // 2.1.1 设备树状图加载
        private void loadTree()
        {
            // 1. 判断数据库是否连接
            if (! sqlProcess.sqlIsReady())
            {
                MessageBox.Show("数据库连接有问题，请调试！");
                return;
            }

            // 2. 数据库查询
            List<string> roomNames = sqlProcess.readAllroom();
            foreach (string room in roomNames)
            {
                // 第一步，添加所有room
                TreeNode roomNode = new TreeNode(room);
                treeViewAdvanced.Nodes.Add(roomNode);

                // 数据库根据room查询所有Cabinet
                List<string> cabinetNames = sqlProcess.readCabinetByRoom(room);
                foreach (string cab in cabinetNames)
                {
                    // 第二步，添加所有cabinet
                    TreeNode cabNode = new TreeNode(cab);
                    roomNode.Nodes.Add(cabNode);

                    List<string> deviceNames = sqlProcess.readdeviceByRoomAndCabinet(room, cab);
                    foreach (string device in deviceNames)
                    {
                        // 第二步，添加所有cabinet
                        TreeNode deviceNode = new TreeNode(device);
                        cabNode.Nodes.Add(deviceNode);
                    }
                }
            }

            //展开所有节点
            treeViewAdvanced.ExpandAll();
        }




        //************************2.2 查询界面：查询结果显示*************************************** 
        // 2.2.1 根据选中域进行查询并显示
        private void treeViewAdvanced_AfterSelect(object sender, TreeViewEventArgs e)
        {
            // 1. 判断数据库是否连接
            if (!sqlProcess.sqlIsReady())
            {
                MessageBox.Show("数据库连接有问题，请调试！");
                return;
            }

            // 2. 获取时间上下限
            string DateStart = dateTimePickerAdvancedStart.Value.ToString("yyyy-MM-dd");
            string DateStop = dateTimePickeradvancedStop.Value.ToString("yyyy-MM-dd");

            // 3. 根据条件进行查询并进行展示
            if (treeViewAdvanced.SelectedNode.Parent == null)  // room节点
            {
                string roomName = treeViewAdvanced.SelectedNode.Text;
                List<detectRecords> records = sqlProcess.advanceQuery(roomName, DateStart, DateStop);
                dataGridViewAdvancedSQL.Rows.Clear();
                foreach (detectRecords record in records)
                {
                    dataGridViewAdvancedSQL.Rows.Add(roomName,
                                                     record.cabinetName,
                                                     record.deviceName,
                                                     record.detectClass,
                                                     record.detectResult,
                                                     record.detectAlarm,
                                                     record.detectDatetime);
                }
            }
            else if (treeViewAdvanced.SelectedNode.Parent.Parent == null)  // cabinet节点
            {
                string roomName = treeViewAdvanced.SelectedNode.Parent.Text;
                string cabinName = treeViewAdvanced.SelectedNode.Text;
                
                List<detectRecords> records = sqlProcess.advanceQuery(roomName, cabinName, DateStart, DateStop);
                dataGridViewAdvancedSQL.Rows.Clear();
                foreach (detectRecords record in records)
                {
                    dataGridViewAdvancedSQL.Rows.Add(roomName,
                                                     cabinName,
                                                     record.deviceName,
                                                     record.detectClass,
                                                     record.detectResult,
                                                     record.detectAlarm,
                                                     record.detectDatetime);
                }
            }
            else if (treeViewAdvanced.SelectedNode.Parent.Parent.Parent == null)  // device节点
            {
                string roomName = treeViewAdvanced.SelectedNode.Parent.Parent.Text;
                string cabinName = treeViewAdvanced.SelectedNode.Parent.Text;
                string deviceName = treeViewAdvanced.SelectedNode.Text;

                List<detectRecords> records = sqlProcess.advanceQuery(roomName, cabinName, deviceName, DateStart, DateStop);

                dataGridViewAdvancedSQL.Rows.Clear();

                foreach (detectRecords record in records)
                {
                    dataGridViewAdvancedSQL.Rows.Add(roomName, 
                                                     cabinName, 
                                                     record.deviceName, 
                                                     record.detectClass,
                                                     record.detectResult, 
                                                     record.detectAlarm,
                                                     record.detectDatetime);
                }
            }
        }




        //*************************10 第三方功能****************************************************************
        // 10.1 延时
        private void Delay(int mm)
        {
            DateTime current = DateTime.Now;
            while (current.AddMilliseconds(mm) > DateTime.Now)
            {
                Application.DoEvents();
            }
            return;
        }


        //************************3 配置界面：图像ROI选择*************************************** 
        private void buttonSmallROIImgChoose_Click(object sender, EventArgs e)
        {
            String fileName = "";

            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = DLLDefine.DatasetsFolder714Lab;
            openFileDialog.Filter = "图片文件(*.jpg,*.gif,*.bmp,*.png)|*.jpg;*.gif;*.bmp;*.png";
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                fileName = openFileDialog.FileName;
            }

            if (fileName == "")
            {
                return;
            }

            displayROIImage(fileName);
        }

        private void displayROIImage(string fileName)
        {
            bitmapROI = new Bitmap(fileName);

            xmlimagepath = fileName;

            if (bitmapROI == null)
            {
                return;
            }

            pictureBoxSmallROI.Image = bitmapROI;    //显示图片
            pictureBoxSmallROI.SizeMode = PictureBoxSizeMode.Zoom;   //设置pictureBox为缩放模式
            pictureBoxSmallROI.Width = bitmapROI.Width;  //pictureBox的大小设置成与图像的实际大小一致。
            pictureBoxSmallROI.Height = bitmapROI.Height;

            labelSrcImgInfoHeight.Text = bitmapROI.Height.ToString();
            labelSrcImgInfoWidth.Text = bitmapROI.Width.ToString();
        }

        private void XMLConfigLoad()
        {
            panelCreate.Hide();

            buttonAppend.Enabled = false;

            // 2. 添加任务类别下拉框
            comboxtypeGen();

            // 3. 不该显示的隐藏起来
            panelpointer.Hide();
            panelknob.Hide();
        }

        // 类型下拉框生成
        private void comboxtypeGen()
        {
            ArrayList typelist = new ArrayList();
            typelist.Add(new comBoxItem("请选择仪表类别", DLLDefine.sg_task_none));
            typelist.Add(new comBoxItem("模拟指示器", DLLDefine.sg_task_analog));
            typelist.Add(new comBoxItem("旋钮", DLLDefine.sg_task_knob));
            typelist.Add(new comBoxItem("指示灯", DLLDefine.sg_task_led));
            typelist.Add(new comBoxItem("指针仪表", DLLDefine.sg_task_pointer));
            typelist.Add(new comBoxItem("短接片", DLLDefine.sg_task_switch));
            //将数据源的属性与ComboBox的属性对应
            comboBoxType.DisplayMember = "Text";        //显示
            comboBoxType.ValueMember = "Value";        //值
            comboBoxType.DataSource = typelist;
        }

        // 下拉框生成
        private void comboxsubGen(int type)
        {
            ArrayList typelistSub1 = new ArrayList();
            ArrayList typelistSub2 = new ArrayList();
            if (DLLDefine.sg_task_analog == type)
            {
                typelistSub1.Add(new comBoxItem("模拟指示器类别", DLLDefine.sg_subtype1_none));
                typelistSub1.Add(new comBoxItem("circles", DLLDefine.sg_analog_type_circles));
                typelistSub1.Add(new comBoxItem("lights", DLLDefine.sg_analog_type_lights));
                typelistSub1.Add(new comBoxItem("squarelights", DLLDefine.sg_analog_type_squarelights));
                typelistSub2.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype2_none));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Hide();
            }
            else if (DLLDefine.sg_task_knob == type)
            {
                typelistSub1.Add(new comBoxItem("旋钮类别", DLLDefine.sg_subtype1_none));
                typelistSub1.Add(new comBoxItem("方头", DLLDefine.sg_knob_type_Square));
                typelistSub1.Add(new comBoxItem("尖头", DLLDefine.sg_knob_type_Sharp));
                typelistSub1.Add(new comBoxItem("圆形", DLLDefine.sg_knob_type_Circle));
                typelistSub2.Add(new comBoxItem("表盘类别", DLLDefine.sg_subtype2_none));
                typelistSub2.Add(new comBoxItem("方形", DLLDefine.sg_knobplate_type_Square));
                typelistSub2.Add(new comBoxItem("矩形", DLLDefine.sg_knobplate_type_Rectangle));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Show();
            }
            else if (DLLDefine.sg_task_led == type)
            {
                typelistSub1.Add(new comBoxItem("指示灯类别", DLLDefine.sg_subtype1_none));
                typelistSub1.Add(new comBoxItem("大灯", DLLDefine.sg_led_type_circle));
                typelistSub1.Add(new comBoxItem("继电保护器", DLLDefine.sg_led_type_bender));
                typelistSub1.Add(new comBoxItem("温湿度计", DLLDefine.sg_led_type_humiture));
                typelistSub2.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype2_none));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Hide();
            }
            else if (DLLDefine.sg_task_switch == type)
            {
                typelistSub1.Add(new comBoxItem("短接片类别", DLLDefine.sg_subtype1_none));
                typelistSub1.Add(new comBoxItem("单刀单掷", DLLDefine.sg_switch_type_single));
                typelistSub1.Add(new comBoxItem("单刀双掷", DLLDefine.sg_switch_type_dual));
                typelistSub2.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype2_none));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Hide();
            }
            else if (DLLDefine.sg_task_pointer == type)
            {
                typelistSub2.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype2_none));
                typelistSub1.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype1_none));

                // 额外配置区域的显示设置
                panelpointer.Show();
                panelknob.Hide();
            }

            comboBoxsub1.DisplayMember = "Text";        //显示
            comboBoxsub1.ValueMember = "Value";        //值
            comboBoxsub1.DataSource = typelistSub1;
            comboBoxsub2.DisplayMember = "Text";        //显示
            comboBoxsub2.ValueMember = "Value";        //值
            comboBoxsub2.DataSource = typelistSub2;
        }

        // comBoxItem用以生成下拉框选项
        public class comBoxItem : System.Object
        {
            private string _Text;
            private int _Value;

            public comBoxItem(string sText, int sValue)
            {
                this._Text = sText;
                this._Value = sValue;
            }

            public string Text
            {
                get
                {
                    return _Text;
                }
            }
            public int Value
            {
                get
                {
                    return _Value;
                }
            }
            public override string ToString()
            {
                return this.Text;
            }
        }

        // 鼠标左键按下事件：聚焦pictureBox，使能移动功能，获取鼠标坐标
        private void pictureBoxSmallROI_MouseDown(object sender, MouseEventArgs e)
        {
            if (bitmapROI == null)  //判空
            {
                return;
            }

            //非ROI选取时
            if (ROISelect == false)
            {
                if (e.Button == MouseButtons.Left)
                {
                    //如果按下去的是鼠标左键，把鼠标按下去的位置设定为鼠标当前位置
                    mouseDownPointROImove.X = Cursor.Position.X;
                    mouseDownPointROImove.Y = Cursor.Position.Y;

                    isMoveROI = true;   // 按下去后可以移动了
                    pictureBoxSmallROI.Focus();

                }
            }
            else
            {
                boolROIDraw = false; //拖拉框形图后点一下结束。
            }
        }

        // 鼠标按住移动时图像移动
        private void pictureBoxSmallROI_MouseMove(object sender, MouseEventArgs e)
        {
            if (bitmapROI == null)  //图像没加载或ROI选择时，不移动
            {
                return;
            }

            pictureBoxSmallROI.Focus();

            if (ROISelect == false) //非ROI选择时
            {
                if (isMoveROI)
                {
                    int x, y;
                    int moveX, moveY;

                    moveX = Cursor.Position.X - mouseDownPointROImove.X;    //X方向上的位移量
                    moveY = Cursor.Position.Y - mouseDownPointROImove.Y;    //Y方向上的位移量

                    x = pictureBoxSmallROI.Location.X + moveX;   //新的位置
                    y = pictureBoxSmallROI.Location.Y + moveY;

                    if (x < (panelSmallROI.Width - pictureBoxSmallROI.Width))  // 出现空白就把空白取消
                    {
                        x = panelSmallROI.Width - pictureBoxSmallROI.Width;
                    }

                    if (y < (panelSmallROI.Height - pictureBoxSmallROI.Height))    // 出现空白就把空白取消
                    {
                        y = panelSmallROI.Height - pictureBoxSmallROI.Height;
                    }

                    if (x > 0)  // 出现空白就把空白取消
                    {
                        x = 0;
                    }

                    if (y > 0)  // 出现空白就把空白取消
                    {
                        y = 0;
                    }

                    pictureBoxSmallROI.Location = new Point(x, y);
                    mouseDownPointROImove.X = Cursor.Position.X;
                    mouseDownPointROImove.Y = Cursor.Position.Y;
                }
            }
            else  //ROI选择,且双击绘图后
            {
                if (boolROIDraw == true)
                {
                    mouseDownPointROIDrawStop.X = e.X;
                    mouseDownPointROIDrawStop.Y = e.Y;

                    RealROIStop.X = (int)(mouseDownPointROIDrawStop.X / ROIScale);
                    RealROIStop.Y = (int)(mouseDownPointROIDrawStop.Y / ROIScale);

                    labelROIInfoStopXValue.Text = RealROIStop.X.ToString();
                    labelROIInfoStopYValue.Text = RealROIStop.Y.ToString();

                    pictureBoxSmallROI.Refresh();
                }
            }
        }

        // 鼠标左键释放事件：关掉图像移动功能
        private void pictureBoxSmallROI_MouseUp(object sender, MouseEventArgs e)
        {
            if (bitmapROI == null)  //图像没加载，不移动
            {
                return;
            }

            if (ROISelect == false)  //ROI非选择时
            {
                //左键释放后，图片就不需要再移动了。
                if (e.Button == MouseButtons.Left)
                {
                    isMoveROI = false;
                }
            }
        }

        // 鼠标滚轮事件：对图像进行缩放
        private void pictureBoxSmallROI_MouseWheel(object sender, MouseEventArgs e)
        {
            if (bitmapROI == null || ROISelect == true)  //图像没加载或ROI选择时，不缩放
            {
                return;
            }

            //缩放时滚轮所在位置
            int x = e.Location.X;
            int y = e.Location.Y;

            //缩放前pictureBox的大小
            int ow = pictureBoxSmallROI.Width;
            int oh = pictureBoxSmallROI.Height;

            int VX, VY;

            //计算缩放后的pictureBox大小
            if (e.Delta > 0)    // 滚轮向下
            {
                pictureBoxSmallROI.Width = (int)(pictureBoxSmallROI.Width * (1 + zoomStep));
                pictureBoxSmallROI.Height = (int)(pictureBoxSmallROI.Height * (1 + zoomStep));
                PropertyInfo pInfo = pictureBoxSmallROI.GetType().GetProperty("ImageRectangle", BindingFlags.Instance | BindingFlags.NonPublic);
                Rectangle rect = (Rectangle)pInfo.GetValue(pictureBoxSmallROI, null);
                pictureBoxSmallROI.Width = rect.Width;
                pictureBoxSmallROI.Height = rect.Height;
            }

            if (e.Delta < 0)    // 滚轮向上
            {
                if (pictureBoxSmallROI.Width < bitmapROI.Width / 10) //缩小至原来的十倍以下就不缩放了
                    return;
                pictureBoxSmallROI.Width = (int)(pictureBoxSmallROI.Width * (1 - zoomStep));
                pictureBoxSmallROI.Height = (int)(pictureBoxSmallROI.Height * (1 - zoomStep));
                PropertyInfo pInfo = pictureBoxSmallROI.GetType().GetProperty("ImageRectangle", BindingFlags.Instance | BindingFlags.NonPublic);
                Rectangle rect = (Rectangle)pInfo.GetValue(pictureBoxSmallROI, null);
                pictureBoxSmallROI.Width = rect.Width;
                pictureBoxSmallROI.Height = rect.Height;
            }

            // 计算偏移量
            VX = (int)((double)x * (ow - pictureBoxSmallROI.Width) / ow);
            VY = (int)((double)y * (oh - pictureBoxSmallROI.Height) / oh);
            pictureBoxSmallROI.Location = new Point(pictureBoxSmallROI.Location.X + VX, pictureBoxSmallROI.Location.Y + VY);

            // 如果小了重新定位到左上角
            x = pictureBoxSmallROI.Location.X;   //新的位置
            y = pictureBoxSmallROI.Location.Y;

            if (x < (panelSmallROI.Width - pictureBoxSmallROI.Width))  // 出现空白就把空白取消
            {
                x = panelSmallROI.Width - pictureBoxSmallROI.Width;
            }

            if (y < (panelSmallROI.Height - pictureBoxSmallROI.Height))    // 出现空白就把空白取消
            {
                y = panelSmallROI.Height - pictureBoxSmallROI.Height;
            }

            if (x > 0)  // 出现空白就把空白取消
            {
                x = 0;
            }

            if (y > 0)  // 出现空白就把空白取消
            {
                y = 0;
            }

            pictureBoxSmallROI.Location = new Point(x, y);

            // 计算缩放的倍数显示出来
            labelImgnowheightvalue.Text = pictureBoxSmallROI.Height.ToString();
            labelImgnowwidthvalue.Text = pictureBoxSmallROI.Width.ToString();
            ROIScale = pictureBoxSmallROI.Width * 1.0 / bitmapROI.Width;
            labelChangInfoScaletimes.Text = ROIScale.ToString();
        }

        //ROI区域选择
        private void buttonSmallROIROIchoose_Click(object sender, EventArgs e)
        {
            if (ROISelect == false)
            {
                ROISelect = true;
                buttonSmallROIROIchoose.Text = "选择完成";
            }
            else
            {
                ROISelect = false;
                buttonSmallROIROIchoose.Text = "ROI选择";

                // 此处将ROI数据拷贝到XML配置工具里
                Rectangle rect = getRectangle(RealROIStart, RealROIStop);
                numericUpDownStartX.Value = rect.X;
                numericUpDownStartY.Value = rect.Y;
                numericUpDownwidth.Value = rect.Width;
                numericUpDownheight.Value = rect.Height;
            }
        }

        // 绘制方框
        private void pictureBoxSmallROI_Paint(object sender, PaintEventArgs e)
        {
            if (boolROIDraw == true)
            {
                using (Pen pen = new Pen(Color.Red, 2))
                {
                    e.Graphics.DrawRectangle(pen, getRectangle(mouseDownPointROIDrawStart, mouseDownPointROIDrawStop));
                }
            }
        }

        // 返回由起始点和终止点决定的方框
        private Rectangle getRectangle(Point Start, Point Stop)
        {
            return new Rectangle(
                Math.Min(Start.X, Stop.X),
                Math.Min(Start.Y, Stop.Y),
                Math.Abs(Start.X - Stop.X),
                Math.Abs(Start.Y - Stop.Y));
        }

        // 双击开始选择方框
        private void pictureBoxSmallROI_DoubleClick(object sender, EventArgs e)
        {
            MouseEventArgs me = e as MouseEventArgs;

            if (ROISelect == true)
            {
                //计算鼠标相对于pictureBox(左上角0,0)的坐标,作为起始点
                mouseDownPointROIDrawStart.X = me.X;
                mouseDownPointROIDrawStart.Y = me.Y;
                RealROIStart.X = (int)(mouseDownPointROIDrawStart.X / ROIScale);
                RealROIStart.Y = (int)(mouseDownPointROIDrawStart.Y / ROIScale);
                labelROIInfoStartXValue.Text = RealROIStart.X.ToString();
                labelROIInfoStartYValue.Text = RealROIStart.Y.ToString();
                boolROIDraw = true;
            }
        }

        // 创建XML按钮
        private void buttonxmlCreate_Click(object sender, EventArgs e)
        {
            if ("创建" == buttonxmlCreate.Text)   //选择文件夹
            {
                //打开选择文件夹
                FolderBrowserDialog folderDialog = new FolderBrowserDialog();
                folderDialog.SelectedPath = DLLDefine.XMLFolder;
                if (DialogResult.OK == folderDialog.ShowDialog())
                {
                    textBoxXMLpath.Text = folderDialog.SelectedPath + "\\untitled.xml";
                }
                buttonxmlCreate.Text = "取消";
                panelCreate.Show();

            }
            else
            {
                panelCreate.Hide();
                buttonxmlCreate.Text = "创建";
            }
        }

        // TODO：这一块需要后期切换到XMLProcess类中
        // 加载XML
        public void loadXML(string xmlPath)
        {
            if (!System.IO.File.Exists(xmlPath))
            {
                WarningDialog resultNoExist = new WarningDialog("文件不存在", DLLDefine.IconFolder + "Error_96px.png");
                resultNoExist.ShowDialog();
                return;
            }

            XDocument xdoc = XDocument.Load(xmlPath);

            var elements = from n in xdoc.Descendants("device")
                           select new
                           {
                               name = n.Element("name").Value,
                               type = n.Element("taskinfo").Element("type").Value,
                               subtype1 = n.Element("taskinfo").Element("subtype1").Value,
                               subtype2 = n.Element("taskinfo").Element("subtype2").Value,
                               number = n.Element("taskinfo").Element("number").Value,
                               startX = n.Element("roiinfo").Element("startX").Value,
                               startY = n.Element("roiinfo").Element("startY").Value,
                               width = n.Element("roiinfo").Element("width").Value,
                               height = n.Element("roiinfo").Element("height").Value
                           };

            dataGridView.DataSource = elements.ToList();

            // 只有在XML加载的时候才能添加
            buttonAppend.Enabled = true;
        }

        // 打开XML配置文件和加载
        private void buttonxmlOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = DLLDefine.XMLFolder;
            openFileDialog.Filter = "配置文件(*.xml)|*.xml";
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FilterIndex = 1;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                String xmlPath = openFileDialog.FileName;

                loadXML(xmlPath);
                textBoxXMLpath.Text = xmlPath;
            }
        }

        // 创建XML过程中的保存按钮
        private void buttonCreateXML_Click(object sender, EventArgs e)
        {
            string xmlPath = textBoxXMLpath.Text;
            // TODO: 对路径进行可用性分析

            xmlProcess.generateXML(xmlPath, bunifuTextboxFactory.text, bunifuTextboxRoom.text, bunifuTextboxCabin.text);
            WarningDialog resultOK = new WarningDialog("配置创建成功");
            resultOK.ShowDialog();

            //// 此处对数据表进行加载，加载刚刚生的XML
            loadXML(xmlPath);

            panelCreate.Hide();
            buttonxmlCreate.Text = "创建";
        }

        // 刷新按钮，即重新加载
        private void bunifuImageButtonRefresh_Click(object sender, EventArgs e)
        {
            string xmlPath = textBoxXMLpath.Text;
            loadXML(xmlPath);
        }

        // 添加设备按钮
        private void buttonAppend_Click(object sender, EventArgs e)
        {
            comBoxItem comtype = (comBoxItem)comboBoxType.SelectedItem;
            comBoxItem comsub1 = (comBoxItem)comboBoxsub1.SelectedItem;
            comBoxItem comsub2 = (comBoxItem)comboBoxsub2.SelectedItem;
            TaskInfo task = new TaskInfo(comtype.Value, comsub1.Value, comsub2.Value, (int)numericUpDownnum.Value);

            ROIInfo roi = new ROIInfo((uint)numericUpDownStartX.Value, (uint)numericUpDownStartY.Value, (uint)numericUpDownwidth.Value, (uint)numericUpDownheight.Value);

            string devicename = textBoxgetname.Text;

            // 需要另外增添的文本
            string AddtitionCnotext = null;
            if (DLLDefine.sg_task_pointer == comtype.Value)
            {
                AddtitionCnotext = ((int)numericUpDownpointerLow.Value).ToString() + "," + ((int)numericUpDownPointerhigh.Value).ToString() + "," + textBoxpointerUnit.Text;
            }
            else if (DLLDefine.sg_task_knob == comtype.Value)
            {
                AddtitionCnotext = richTextBoxKnobitem.Text;
            }


            xmlProcess.appendDevice(textBoxXMLpath.Text, devicename, task, roi, AddtitionCnotext);

            loadXML(textBoxXMLpath.Text);
            WarningDialog resultOK = new WarningDialog("添加成功");
            resultOK.ShowDialog();
        }

        // 更改type后清空后续下拉框
        private void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            comBoxItem select = (comBoxItem)comboBoxType.SelectedItem;

            comboBoxsub1.DataSource = null;
            comboBoxsub1.Items.Clear();
            comboBoxsub2.DataSource = null;
            comboBoxsub2.Items.Clear();
            numericUpDownnum.Value = 1;

            comboxsubGen(select.Value);
        }

        // 点击添加旋钮档位并显示在富文本框中
        private void buttonknobAddItem_Click(object sender, EventArgs e)
        {
            int knobLow = (int)numericUpDownknobLow.Value;
            int knobHigh = (int)numericUpDownKnobHigh.Value;
            string knobcontext = textBoxKnobContext.Text;
            richTextBoxKnobitem.Text += knobLow.ToString() + "," + knobHigh.ToString() + "," + knobcontext + ";";
        }

        // 表格中：右键点击行时选中行，并弹出操作菜单
        private void dataGridView_CellMouseDown(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (e.RowIndex >= 0)
                {
                    //若行已是选中状态就不再进行设置
                    if (dataGridView.Rows[e.RowIndex].Selected == false)
                    {
                        dataGridView.ClearSelection();
                        dataGridView.Rows[e.RowIndex].Selected = true;
                    }
                    //只选中一行时设置活动单元格
                    if (dataGridView.SelectedRows.Count == 1)
                    {
                        dataGridView.CurrentCell = dataGridView.Rows[e.RowIndex].Cells[e.ColumnIndex];
                    }
                    //弹出操作菜单
                    contextMenuStripDataGrid.Show(MousePosition.X, MousePosition.Y);
                }
            }
        }

        // 右键删除选中行：获取DeviceName->操作XML,删除节点->重新加载XML
        private void toolStripMenuItemDelete_Click(object sender, EventArgs e)
        {
            // 1. 获取选中的Devicename
            Int32 rowToDelete = dataGridView.Rows.GetFirstRow(DataGridViewElementStates.Selected);
            string cellTitle = dataGridView.SelectedRows[0].Cells[0].Value.ToString();
            Console.WriteLine("********************************" + cellTitle);

            // 2. 加载XML文件
            XElement xe = XElement.Load(textBoxXMLpath.Text);
            IEnumerable<XElement> devices = xe.Elements("device");

            foreach (XElement item in devices)
            {
                if (cellTitle == item.Element("name").Value)
                {
                    item.Remove();
                }
            }
            xe.Save(textBoxXMLpath.Text);
            loadXML(textBoxXMLpath.Text);

            dataGridView.ClearSelection();
        }

        // 确认二维码位置 //用检测来做
        private void buttonQR_Click(object sender, EventArgs e)
        {
           

            QRCodeInfo qrcodeinfo = new QRCodeInfo();

            //visiondll.GetQRregion(xmlimagepath, ref qrcodeinfo);

            numericUpDownStartX.Value = qrcodeinfo.startX;
            numericUpDownStartY.Value = qrcodeinfo.startY;
            numericUpDownwidth.Value = qrcodeinfo.width;
            numericUpDownheight.Value = qrcodeinfo.height;

            ROIInfo roi = new ROIInfo((uint)numericUpDownStartX.Value, (uint)numericUpDownStartY.Value, (uint)numericUpDownwidth.Value, (uint)numericUpDownheight.Value);

            xmlProcess.appendQRPosition(textBoxXMLpath.Text, roi);
        }
    }



}
