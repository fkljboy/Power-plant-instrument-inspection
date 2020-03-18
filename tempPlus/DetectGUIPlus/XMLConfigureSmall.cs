using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace DetectGUIPlus
{
    public partial class XMLConfigureSmall : Form
    {
        XMLProcess xmlProcess = new XMLProcess();   //XML处理类
        VisionDLL visiondll = new VisionDLL();

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

        private string imgInBoxPath = "";   // pictureBox中的图像路径
        private int cameraside = 0; // 相框所属的位置
        private QRCodeInfo QRCodeRefer = new QRCodeInfo();

        public XMLConfigureSmall()
        {
            InitializeComponent();
            panelCreate.Hide();
        }

        private void XMLConfigurePlus_Load(object sender, EventArgs e)
        {
            pictureBoxSmallROI.Focus();

            // 1. 禁止使能添加按钮
            buttonAppend.Enabled = false;

            // 2. 添加任务类别下拉框
            comboxtypeGen();

            // 3. 不该显示的隐藏起来
            panelpointer.Hide();
            panelknob.Hide();
        }

        // 加载图片进行ROI选择操作
        private void buttonSmallROIImgChoose_Click(object sender, EventArgs e)
        {
            String fileName = "";

            OpenFileDialog openFileDialog = new OpenFileDialog();
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
            imgInBoxPath = fileName; //注意DLL同样进行畸变校正，所以不需要将校正后的图做后续使用。

            string undistortImgPath = null;

            if (cameraside != DLLDefine.sg_Camera_Far && cameraside != DLLDefine.sg_Camera_Near)
            {
                MessageBox.Show("尚未获取到关于远近侧信息,请确认");
                return;
            }

            visiondll.ImgUnDistort(fileName, ref undistortImgPath, cameraside); //传入Camera远近测信息

            bitmapROI = new Bitmap(undistortImgPath);
            

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
            //labelImgnowheightvalue.Text = pictureBoxSmallROI.Height.ToString();
            //labelImgnowwidthvalue.Text = pictureBoxSmallROI.Width.ToString();
            ROIScale = pictureBoxSmallROI.Width * 1.0 / bitmapROI.Width;
            //labelChangInfoScaletimes.Text = ROIScale.ToString();
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
        private string folderString = "";
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
                    folderString = folderDialog.SelectedPath;
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
                MessageBox.Show("文件不存在！");
                return;
            }

            XDocument xdoc = XDocument.Load(xmlPath);

            // 1. 获取远侧还是近侧
            xmlProcess.getCameraSide(xmlPath, ref cameraside);

            // 2. 加载表中数据
            var elements = from n in xdoc.Descendants("device")
                           select new
                           {
                               name = n.Element("name").Value,
                               type = n.Element("taskinfo").Element("type").Value,
                               subtype = n.Element("taskinfo").Element("subtype").Value,
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
            if (numericUpDownDev.Value == 0)
            {
                MessageBox.Show("请选择设备编号");
                return;
            }

            string xmlPath = textBoxXMLpath.Text;
            string cabinName = textBoxCabinName.Text;
            string cabinType = comboBoxCabinType.SelectedItem.ToString();
            string dev_Num = numericUpDownDev.Value.ToString();
            string Side = comboBoxSide.SelectedItem.ToString();
            string itemNum = numericUpDownitems.Value.ToString();
            xmlProcess.generateXML(xmlPath, cabinName, cabinType, dev_Num, Side, itemNum);//改为配置远侧近侧

            MessageBox.Show("配置创建成功");

            //// 此处对数据表进行加载，加载刚刚生的XML
            loadXML(xmlPath);

            panelCreate.Hide();
            buttonxmlCreate.Text = "创建";
        }

        //刷新按钮，即重新加载
        private void bunifuImageButtonRefresh_Click(object sender, EventArgs e)
        {
            string xmlPath = textBoxXMLpath.Text;
            loadXML(xmlPath);
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

            //将数据源的属性与ComboBox的属性对应
            comboBoxType.DisplayMember = "Text";        //显示
            comboBoxType.ValueMember = "Value";        //值
            comboBoxType.DataSource = typelist;
        }

        // 下拉框生成
        private void comboxsubGen(int type)
        {
            ArrayList typelistSub = new ArrayList();
            if (DLLDefine.sg_task_analog == type)
            {
                typelistSub.Add(new comBoxItem("模拟指示器类别", DLLDefine.sg_subtype_none));
                typelistSub.Add(new comBoxItem("有圆无灯", DLLDefine.sg_analog_type_circles));
                typelistSub.Add(new comBoxItem("两个方格", DLLDefine.sg_analog_type_twoPanels));
                typelistSub.Add(new comBoxItem("一个方格", DLLDefine.sg_analog_type_onePanel));
                typelistSub.Add(new comBoxItem("有圆有灯", DLLDefine.sg_analog_type_lights));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Hide();
            }
            else if (DLLDefine.sg_task_knob == type)
            {
                typelistSub.Add(new comBoxItem("旋钮类别", DLLDefine.sg_subtype_none));
                typelistSub.Add(new comBoxItem("方形", DLLDefine.sg_knob_type_Square));
                typelistSub.Add(new comBoxItem("矩形", DLLDefine.sg_knob_type_Rectangle));
                typelistSub.Add(new comBoxItem("圆形", DLLDefine.sg_knob_type_Circle));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Show();
            }
            else if (DLLDefine.sg_task_led == type)
            {
                typelistSub.Add(new comBoxItem("指示灯类别", DLLDefine.sg_subtype_none));

                typelistSub.Add(new comBoxItem("纵差继电器", DLLDefine.sg_led_type_benderZongCha));
                typelistSub.Add(new comBoxItem("保护继电器", DLLDefine.sg_led_type_benderBaoHu));
                typelistSub.Add(new comBoxItem("通讯继电器", DLLDefine.sg_led_type_benderTongXun));
                typelistSub.Add(new comBoxItem("有电显示器", DLLDefine.sg_led_type_YouDian));

                // 额外配置区域的显示设置
                panelpointer.Hide();
                panelknob.Hide();
            }
            else if (DLLDefine.sg_task_pointer == type)
            {
                typelistSub.Add(new comBoxItem("无需选择", DLLDefine.sg_subtype_none));

                // 额外配置区域的显示设置
                panelpointer.Show();
                panelknob.Hide();
            }

            comboBoxsub1.DisplayMember = "Text";        //显示
            comboBoxsub1.ValueMember = "Value";        //值
            comboBoxsub1.DataSource = typelistSub;
        }

        // 添加设备按钮
        private void buttonAppend_Click(object sender, EventArgs e)
        {
            comBoxItem comtype = (comBoxItem)comboBoxType.SelectedItem;
            comBoxItem comsub1 = (comBoxItem)comboBoxsub1.SelectedItem;
            TaskInfo task = new TaskInfo(comtype.Value, comsub1.Value, (int)numericUpDownnum.Value);

            ROIInfo roi = new ROIInfo((int)numericUpDownStartX.Value, (int)numericUpDownStartY.Value,0,0, (int)numericUpDownwidth.Value, (int)numericUpDownheight.Value);

            string devicename = textBoxgetname.Text;

            // 需要另外增添的文本
            string AddtitionCnotext = null;
            if (DLLDefine.sg_task_pointer == comtype.Value)
            {
                AddtitionCnotext = ((int)numericUpDownpointerLow.Value).ToString() + "," + ((int)numericUpDownPointerhigh.Value).ToString() + "," + textBoxpointerUnit.Text;
            }else if (DLLDefine.sg_task_knob == comtype.Value)
            {
                AddtitionCnotext = richTextBoxKnobitem.Text;
            }

            string order = numericUpDownOrder.Value.ToString();
            xmlProcess.appendDevice(textBoxXMLpath.Text, devicename, task, roi, AddtitionCnotext, order, QRCodeRefer);

            loadXML(textBoxXMLpath.Text);

            MessageBox.Show("添加成功");
        }

        // 更改type后清空后续下拉框
        private void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            comBoxItem select = (comBoxItem)comboBoxType.SelectedItem;

            comboBoxsub1.DataSource = null;
            comboBoxsub1.Items.Clear();
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


        // 确认添加二维码信息
        private void confirmQR_Click(object sender, EventArgs e)
        {
            ROIInfo roi = new ROIInfo((int)numericUpDownStartX.Value, (int)numericUpDownStartY.Value,0,0, (int)numericUpDownwidth.Value, (int)numericUpDownheight.Value);
            QRCodeInfo realQR = new QRCodeInfo();
            string QRcontent="";
            visiondll.searchQRwithregion(imgInBoxPath, roi, ref realQR, ref QRcontent,cameraside);

            MessageBox.Show("二维码的位置为：" + "(" + realQR.startX + "," + realQR.startY + "), w= " + realQR.width + ", h= " + realQR.height + "\n"
                            + "二维码的内容为： " + QRcontent + "\n"
                            + "已添加至配置表");

            QRCodeRefer = realQR;

            xmlProcess.appendQRPosition(textBoxXMLpath.Text, realQR, QRcontent);
        }

        private void pictureBoxSmallROI_Click(object sender, EventArgs e)
        {

        }

        private void bunifuCustomLabelSub1_Click(object sender, EventArgs e)
        {

        }


        // 根据数值动态更改文件名
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            string filename = "\\XML_DEV_" + numericUpDownDev.Value.ToString() + ".xml";
            textBoxXMLpath.Text = folderString + filename;
        }
    }
}
