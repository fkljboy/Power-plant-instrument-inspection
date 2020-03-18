using System;
using System.Windows.Forms;

namespace DetectGUIPlus
{
    partial class MainWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabHome = new System.Windows.Forms.TabPage();
            this.panelResult = new System.Windows.Forms.Panel();
            this.tabControlResult = new System.Windows.Forms.TabControl();
            this.tabResultData = new System.Windows.Forms.TabPage();
            this.dataGridViewDetect = new System.Windows.Forms.DataGridView();
            this.id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.time = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.device = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.result = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.alert = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tabResultMatter = new System.Windows.Forms.TabPage();
            this.dataGridViewDetail = new System.Windows.Forms.DataGridView();
            this.ColumDetailNO = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumDetailTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumDetailLevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumDetailInfo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tabResultAlarm = new System.Windows.Forms.TabPage();
            this.dataGridViewAlarm = new System.Windows.Forms.DataGridView();
            this.CloumAlertNO = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertDevice = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertLevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertContent = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumAlertConfirm = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.imageListx32 = new System.Windows.Forms.ImageList(this.components);
            this.panelStatus = new System.Windows.Forms.Panel();
            this.panelProcess = new System.Windows.Forms.Panel();
            this.panelstatusDetect = new System.Windows.Forms.Panel();
            this.dataGridViewStatus = new System.Windows.Forms.DataGridView();
            this.ColumDetectName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumDetectValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.labelbarprocess = new System.Windows.Forms.Label();
            this.circularProgressBarprocess = new CircularProgressBar.CircularProgressBar();
            this.labelProcess = new System.Windows.Forms.Label();
            this.pictureBoxProcess = new System.Windows.Forms.PictureBox();
            this.panelLocation = new System.Windows.Forms.Panel();
            this.panelLocationDetail = new System.Windows.Forms.Panel();
            this.labelCab = new System.Windows.Forms.Label();
            this.labelRom = new System.Windows.Forms.Label();
            this.labelFac = new System.Windows.Forms.Label();
            this.pictureBoxCab = new System.Windows.Forms.PictureBox();
            this.pictureBoxRom = new System.Windows.Forms.PictureBox();
            this.pictureBoxFac = new System.Windows.Forms.PictureBox();
            this.circularProgressBarLocation = new CircularProgressBar.CircularProgressBar();
            this.labelLoca = new System.Windows.Forms.Label();
            this.pictureBoxlocation = new System.Windows.Forms.PictureBox();
            this.panelImagearea = new System.Windows.Forms.Panel();
            this.panelvideoPlayer = new System.Windows.Forms.Panel();
            this.videoSourcePlayer = new AForge.Controls.VideoSourcePlayer();
            this.panelCameraOperate = new System.Windows.Forms.Panel();
            this.buttonIPcamera = new System.Windows.Forms.Button();
            this.buttonvideoCap = new System.Windows.Forms.Button();
            this.buttonCapture = new System.Windows.Forms.Button();
            this.buttonRefreshCameras = new System.Windows.Forms.Button();
            this.buttonCloseCamera = new System.Windows.Forms.Button();
            this.buttonopenCamera = new System.Windows.Forms.Button();
            this.comboBoxCameraChoose = new System.Windows.Forms.ComboBox();
            this.panelImgProcess = new System.Windows.Forms.Panel();
            this.pictureBoxProcessed = new System.Windows.Forms.PictureBox();
            this.panelImgSource = new System.Windows.Forms.Panel();
            this.pictureBoxSource = new System.Windows.Forms.PictureBox();
            this.tabChart = new System.Windows.Forms.TabPage();
            this.tabControlDatabase = new System.Windows.Forms.TabControl();
            this.tabPageDBadvanced = new System.Windows.Forms.TabPage();
            this.panel1 = new System.Windows.Forms.Panel();
            this.dataGridViewAdvancedSQL = new System.Windows.Forms.DataGridView();
            this.roomName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CabinName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DeviceName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DeviceClass = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DetectResult = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DetectAlarm = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DetectDateTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.paneldevicetree = new System.Windows.Forms.Panel();
            this.treeViewAdvanced = new System.Windows.Forms.TreeView();
            this.paneldate = new System.Windows.Forms.Panel();
            this.labeladvancedDate = new System.Windows.Forms.Label();
            this.dateTimePickeradvancedStop = new System.Windows.Forms.DateTimePicker();
            this.dateTimePickerAdvancedStart = new System.Windows.Forms.DateTimePicker();
            this.tabPageDBDevicequery = new System.Windows.Forms.TabPage();
            this.tabPageDBSelfAlarm = new System.Windows.Forms.TabPage();
            this.imageListDB = new System.Windows.Forms.ImageList(this.components);
            this.tabSetting = new System.Windows.Forms.TabPage();
            this.panelXMLConfig = new System.Windows.Forms.Panel();
            this.panelXML = new System.Windows.Forms.Panel();
            this.buttonQR = new System.Windows.Forms.Button();
            this.paneldata = new System.Windows.Forms.Panel();
            this.panelfordatause = new System.Windows.Forms.Panel();
            this.bunifuImageButtonRefresh = new Bunifu.Framework.UI.BunifuImageButton();
            this.panelforgridview = new System.Windows.Forms.Panel();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.panelAdd = new System.Windows.Forms.Panel();
            this.panelknob = new System.Windows.Forms.Panel();
            this.richTextBoxKnobitem = new System.Windows.Forms.RichTextBox();
            this.labelknobLow = new System.Windows.Forms.Label();
            this.labelKnobHigh = new System.Windows.Forms.Label();
            this.numericUpDownknobLow = new System.Windows.Forms.NumericUpDown();
            this.textBoxKnobContext = new System.Windows.Forms.TextBox();
            this.numericUpDownKnobHigh = new System.Windows.Forms.NumericUpDown();
            this.buttonknobAddItem = new System.Windows.Forms.Button();
            this.panelpointer = new System.Windows.Forms.Panel();
            this.labelpointerunit = new System.Windows.Forms.Label();
            this.labelpointerhigh = new System.Windows.Forms.Label();
            this.labelpointerLow = new System.Windows.Forms.Label();
            this.textBoxpointerUnit = new System.Windows.Forms.TextBox();
            this.numericUpDownPointerhigh = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownpointerLow = new System.Windows.Forms.NumericUpDown();
            this.textBoxgetname = new System.Windows.Forms.TextBox();
            this.bunifuCustomLabelheight = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelwidth = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelY = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.buttonAppend = new System.Windows.Forms.Button();
            this.numericUpDownnum = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownheight = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownStartY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownwidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownStartX = new System.Windows.Forms.NumericUpDown();
            this.comboBoxsub2 = new System.Windows.Forms.ComboBox();
            this.comboBoxsub1 = new System.Windows.Forms.ComboBox();
            this.comboBoxType = new System.Windows.Forms.ComboBox();
            this.bunifuCustomLabelNum = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelSub2 = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelname = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelSub1 = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabelX = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.bunifuCustomLabeltype = new Bunifu.Framework.UI.BunifuCustomLabel();
            this.panelCreate = new System.Windows.Forms.Panel();
            this.bunifuTextboxCabin = new Bunifu.Framework.UI.BunifuTextbox();
            this.bunifuTextboxRoom = new Bunifu.Framework.UI.BunifuTextbox();
            this.bunifuTextboxFactory = new Bunifu.Framework.UI.BunifuTextbox();
            this.buttonCreateXML = new System.Windows.Forms.Button();
            this.panelxmlpath = new System.Windows.Forms.Panel();
            this.labelpath = new System.Windows.Forms.Label();
            this.buttonxmlOpen = new System.Windows.Forms.Button();
            this.textBoxXMLpath = new System.Windows.Forms.TextBox();
            this.buttonxmlCreate = new System.Windows.Forms.Button();
            this.panelROI = new System.Windows.Forms.Panel();
            this.panelSmallROIInfo = new System.Windows.Forms.Panel();
            this.buttonSmallROIROIchoose = new System.Windows.Forms.Button();
            this.buttonSmallROIImgChoose = new System.Windows.Forms.Button();
            this.panelSmallROIROIInfo = new System.Windows.Forms.Panel();
            this.labelROIInfoStopYValue = new System.Windows.Forms.Label();
            this.labelROIInfoStopY = new System.Windows.Forms.Label();
            this.labelROIInfoStopXValue = new System.Windows.Forms.Label();
            this.labelROIInfoStopX = new System.Windows.Forms.Label();
            this.labelROIInfoStartYValue = new System.Windows.Forms.Label();
            this.labelROIInfoStartY = new System.Windows.Forms.Label();
            this.labelROIInfoStartXValue = new System.Windows.Forms.Label();
            this.labelROIInfoStart = new System.Windows.Forms.Label();
            this.labelROIInfoTitle = new System.Windows.Forms.Label();
            this.pictureBoxROIInfo = new System.Windows.Forms.PictureBox();
            this.panelSmallROIMove = new System.Windows.Forms.Panel();
            this.labelChangInfoScaletimes = new System.Windows.Forms.Label();
            this.labelImgnowwidthvalue = new System.Windows.Forms.Label();
            this.labelImgnowheightvalue = new System.Windows.Forms.Label();
            this.labelChangeInfoScale = new System.Windows.Forms.Label();
            this.labelImgnowheight = new System.Windows.Forms.Label();
            this.labelImgnowwidth = new System.Windows.Forms.Label();
            this.labelChangeInfo = new System.Windows.Forms.Label();
            this.pictureBoxChangeInfo = new System.Windows.Forms.PictureBox();
            this.panelSmallROIImgInfo = new System.Windows.Forms.Panel();
            this.labelSrcImgInfoWidth = new System.Windows.Forms.Label();
            this.labelSrcImgInfoHeight = new System.Windows.Forms.Label();
            this.labelSrcImgInfoWidthTitle = new System.Windows.Forms.Label();
            this.labelSrcImgInfoHeightTitle = new System.Windows.Forms.Label();
            this.labelImgInfoTitle = new System.Windows.Forms.Label();
            this.pictureBoxSrcImgInfo = new System.Windows.Forms.PictureBox();
            this.panelSmallROI = new System.Windows.Forms.Panel();
            this.pictureBoxSmallROI = new System.Windows.Forms.PictureBox();
            this.tabInfo = new System.Windows.Forms.TabPage();
            this.tabDebug = new System.Windows.Forms.TabPage();
            this.imageListTab = new System.Windows.Forms.ImageList(this.components);
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.保存SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.打印PToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打印预览VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.ExitXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编辑EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.撤消UToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.重复RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.剪切TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.复制CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粘贴PToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.全选AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.工具TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.选项OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.xMLConfigurePlusToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.内容CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.索引IToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.搜索SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.关于AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panelSide = new System.Windows.Forms.Panel();
            this.panelLog = new System.Windows.Forms.Panel();
            this.labelJournal = new System.Windows.Forms.Label();
            this.pictureBoxLog = new System.Windows.Forms.PictureBox();
            this.panelJournal = new System.Windows.Forms.Panel();
            this.buttonToImage = new System.Windows.Forms.Button();
            this.buttonGototakephoto = new System.Windows.Forms.Button();
            this.buttonTest = new System.Windows.Forms.Button();
            this.labelschedule = new System.Windows.Forms.Label();
            this.pictureBoxjournal = new System.Windows.Forms.PictureBox();
            this.panelClock = new System.Windows.Forms.Panel();
            this.labelDate = new System.Windows.Forms.Label();
            this.labelWeek = new System.Windows.Forms.Label();
            this.labelSecond = new System.Windows.Forms.Label();
            this.labelTime = new System.Windows.Forms.Label();
            this.timerClock = new System.Windows.Forms.Timer(this.components);
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.contextMenuStripDataGrid = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItemDelete = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl.SuspendLayout();
            this.tabHome.SuspendLayout();
            this.panelResult.SuspendLayout();
            this.tabControlResult.SuspendLayout();
            this.tabResultData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDetect)).BeginInit();
            this.tabResultMatter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDetail)).BeginInit();
            this.tabResultAlarm.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAlarm)).BeginInit();
            this.panelStatus.SuspendLayout();
            this.panelProcess.SuspendLayout();
            this.panelstatusDetect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxProcess)).BeginInit();
            this.panelLocation.SuspendLayout();
            this.panelLocationDetail.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCab)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxRom)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxFac)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxlocation)).BeginInit();
            this.panelImagearea.SuspendLayout();
            this.panelvideoPlayer.SuspendLayout();
            this.panelCameraOperate.SuspendLayout();
            this.panelImgProcess.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxProcessed)).BeginInit();
            this.panelImgSource.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSource)).BeginInit();
            this.tabChart.SuspendLayout();
            this.tabControlDatabase.SuspendLayout();
            this.tabPageDBadvanced.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAdvancedSQL)).BeginInit();
            this.paneldevicetree.SuspendLayout();
            this.paneldate.SuspendLayout();
            this.tabSetting.SuspendLayout();
            this.panelXMLConfig.SuspendLayout();
            this.panelXML.SuspendLayout();
            this.paneldata.SuspendLayout();
            this.panelfordatause.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bunifuImageButtonRefresh)).BeginInit();
            this.panelforgridview.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.panelAdd.SuspendLayout();
            this.panelknob.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownknobLow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKnobHigh)).BeginInit();
            this.panelpointer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPointerhigh)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownpointerLow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownnum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownheight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStartY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownwidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStartX)).BeginInit();
            this.panelCreate.SuspendLayout();
            this.panelxmlpath.SuspendLayout();
            this.panelROI.SuspendLayout();
            this.panelSmallROIInfo.SuspendLayout();
            this.panelSmallROIROIInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxROIInfo)).BeginInit();
            this.panelSmallROIMove.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxChangeInfo)).BeginInit();
            this.panelSmallROIImgInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSrcImgInfo)).BeginInit();
            this.panelSmallROI.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSmallROI)).BeginInit();
            this.menuStrip.SuspendLayout();
            this.panelSide.SuspendLayout();
            this.panelLog.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLog)).BeginInit();
            this.panelJournal.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxjournal)).BeginInit();
            this.panelClock.SuspendLayout();
            this.contextMenuStripDataGrid.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl.Controls.Add(this.tabHome);
            this.tabControl.Controls.Add(this.tabChart);
            this.tabControl.Controls.Add(this.tabSetting);
            this.tabControl.Controls.Add(this.tabInfo);
            this.tabControl.Controls.Add(this.tabDebug);
            this.tabControl.ImageList = this.imageListTab;
            this.tabControl.ItemSize = new System.Drawing.Size(48, 96);
            this.tabControl.Location = new System.Drawing.Point(258, 28);
            this.tabControl.Name = "tabControl";
            this.tabControl.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(1662, 1048);
            this.tabControl.TabIndex = 2;
            // 
            // tabHome
            // 
            this.tabHome.BackColor = System.Drawing.Color.Transparent;
            this.tabHome.Controls.Add(this.panelResult);
            this.tabHome.Controls.Add(this.panelStatus);
            this.tabHome.Controls.Add(this.panelImagearea);
            this.tabHome.ImageIndex = 2;
            this.tabHome.Location = new System.Drawing.Point(4, 100);
            this.tabHome.Name = "tabHome";
            this.tabHome.Padding = new System.Windows.Forms.Padding(3);
            this.tabHome.Size = new System.Drawing.Size(1654, 944);
            this.tabHome.TabIndex = 0;
            // 
            // panelResult
            // 
            this.panelResult.BackColor = System.Drawing.Color.LightGray;
            this.panelResult.Controls.Add(this.tabControlResult);
            this.panelResult.Location = new System.Drawing.Point(552, 529);
            this.panelResult.Name = "panelResult";
            this.panelResult.Size = new System.Drawing.Size(1099, 412);
            this.panelResult.TabIndex = 2;
            // 
            // tabControlResult
            // 
            this.tabControlResult.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControlResult.Controls.Add(this.tabResultData);
            this.tabControlResult.Controls.Add(this.tabResultMatter);
            this.tabControlResult.Controls.Add(this.tabResultAlarm);
            this.tabControlResult.ImageList = this.imageListx32;
            this.tabControlResult.ItemSize = new System.Drawing.Size(82, 32);
            this.tabControlResult.Location = new System.Drawing.Point(-3, 0);
            this.tabControlResult.Name = "tabControlResult";
            this.tabControlResult.SelectedIndex = 0;
            this.tabControlResult.Size = new System.Drawing.Size(1102, 419);
            this.tabControlResult.TabIndex = 0;
            // 
            // tabResultData
            // 
            this.tabResultData.BackColor = System.Drawing.Color.LightGray;
            this.tabResultData.Controls.Add(this.dataGridViewDetect);
            this.tabResultData.ImageKey = "Data Sheet_32px.png";
            this.tabResultData.Location = new System.Drawing.Point(4, 36);
            this.tabResultData.Name = "tabResultData";
            this.tabResultData.Padding = new System.Windows.Forms.Padding(3);
            this.tabResultData.Size = new System.Drawing.Size(1094, 379);
            this.tabResultData.TabIndex = 0;
            this.tabResultData.Text = "巡检数据";
            // 
            // dataGridViewDetect
            // 
            this.dataGridViewDetect.AllowUserToAddRows = false;
            this.dataGridViewDetect.AllowUserToDeleteRows = false;
            this.dataGridViewDetect.AllowUserToOrderColumns = true;
            this.dataGridViewDetect.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewDetect.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.id,
            this.time,
            this.device,
            this.result,
            this.alert});
            this.dataGridViewDetect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewDetect.Location = new System.Drawing.Point(3, 3);
            this.dataGridViewDetect.Name = "dataGridViewDetect";
            this.dataGridViewDetect.ReadOnly = true;
            this.dataGridViewDetect.RowHeadersVisible = false;
            this.dataGridViewDetect.RowTemplate.Height = 23;
            this.dataGridViewDetect.Size = new System.Drawing.Size(1088, 373);
            this.dataGridViewDetect.TabIndex = 0;
            // 
            // id
            // 
            this.id.HeaderText = "序号";
            this.id.Name = "id";
            this.id.ReadOnly = true;
            // 
            // time
            // 
            this.time.HeaderText = "时间";
            this.time.Name = "time";
            this.time.ReadOnly = true;
            this.time.Width = 250;
            // 
            // device
            // 
            this.device.HeaderText = "设备名称";
            this.device.Name = "device";
            this.device.ReadOnly = true;
            this.device.Width = 350;
            // 
            // result
            // 
            this.result.HeaderText = "检测结果";
            this.result.Name = "result";
            this.result.ReadOnly = true;
            this.result.Width = 260;
            // 
            // alert
            // 
            this.alert.HeaderText = "报警类型";
            this.alert.Name = "alert";
            this.alert.ReadOnly = true;
            this.alert.Width = 110;
            // 
            // tabResultMatter
            // 
            this.tabResultMatter.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.tabResultMatter.Controls.Add(this.dataGridViewDetail);
            this.tabResultMatter.ImageKey = "Activity History_32px.png";
            this.tabResultMatter.Location = new System.Drawing.Point(4, 36);
            this.tabResultMatter.Name = "tabResultMatter";
            this.tabResultMatter.Padding = new System.Windows.Forms.Padding(3);
            this.tabResultMatter.Size = new System.Drawing.Size(1094, 379);
            this.tabResultMatter.TabIndex = 1;
            this.tabResultMatter.Text = "事项";
            // 
            // dataGridViewDetail
            // 
            this.dataGridViewDetail.AllowUserToOrderColumns = true;
            this.dataGridViewDetail.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewDetail.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumDetailNO,
            this.ColumDetailTime,
            this.ColumDetailLevel,
            this.ColumDetailInfo});
            this.dataGridViewDetail.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewDetail.Location = new System.Drawing.Point(3, 3);
            this.dataGridViewDetail.Name = "dataGridViewDetail";
            this.dataGridViewDetail.RowHeadersVisible = false;
            this.dataGridViewDetail.RowTemplate.Height = 23;
            this.dataGridViewDetail.Size = new System.Drawing.Size(1088, 373);
            this.dataGridViewDetail.TabIndex = 0;
            // 
            // ColumDetailNO
            // 
            this.ColumDetailNO.HeaderText = "序号";
            this.ColumDetailNO.Name = "ColumDetailNO";
            // 
            // ColumDetailTime
            // 
            this.ColumDetailTime.HeaderText = "时间";
            this.ColumDetailTime.Name = "ColumDetailTime";
            this.ColumDetailTime.Width = 250;
            // 
            // ColumDetailLevel
            // 
            this.ColumDetailLevel.HeaderText = "级别";
            this.ColumDetailLevel.Name = "ColumDetailLevel";
            this.ColumDetailLevel.Width = 130;
            // 
            // ColumDetailInfo
            // 
            this.ColumDetailInfo.HeaderText = "信息";
            this.ColumDetailInfo.Name = "ColumDetailInfo";
            this.ColumDetailInfo.Width = 550;
            // 
            // tabResultAlarm
            // 
            this.tabResultAlarm.BackColor = System.Drawing.Color.LightGray;
            this.tabResultAlarm.Controls.Add(this.dataGridViewAlarm);
            this.tabResultAlarm.ImageKey = "Alert_32px.png";
            this.tabResultAlarm.Location = new System.Drawing.Point(4, 36);
            this.tabResultAlarm.Name = "tabResultAlarm";
            this.tabResultAlarm.Padding = new System.Windows.Forms.Padding(3);
            this.tabResultAlarm.Size = new System.Drawing.Size(1094, 379);
            this.tabResultAlarm.TabIndex = 2;
            this.tabResultAlarm.Text = "报警信息";
            // 
            // dataGridViewAlarm
            // 
            this.dataGridViewAlarm.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAlarm.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.CloumAlertNO,
            this.ColumAlertTime,
            this.ColumAlertDevice,
            this.ColumAlertType,
            this.ColumAlertValue,
            this.ColumAlertLevel,
            this.ColumAlertContent,
            this.ColumAlertConfirm});
            this.dataGridViewAlarm.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewAlarm.Location = new System.Drawing.Point(3, 3);
            this.dataGridViewAlarm.Name = "dataGridViewAlarm";
            this.dataGridViewAlarm.RowHeadersVisible = false;
            this.dataGridViewAlarm.RowTemplate.Height = 23;
            this.dataGridViewAlarm.Size = new System.Drawing.Size(1088, 373);
            this.dataGridViewAlarm.TabIndex = 0;
            // 
            // CloumAlertNO
            // 
            this.CloumAlertNO.HeaderText = "序号";
            this.CloumAlertNO.Name = "CloumAlertNO";
            this.CloumAlertNO.Width = 60;
            // 
            // ColumAlertTime
            // 
            this.ColumAlertTime.HeaderText = "时间";
            this.ColumAlertTime.Name = "ColumAlertTime";
            this.ColumAlertTime.Width = 150;
            // 
            // ColumAlertDevice
            // 
            this.ColumAlertDevice.HeaderText = "设备名称";
            this.ColumAlertDevice.Name = "ColumAlertDevice";
            this.ColumAlertDevice.Width = 200;
            // 
            // ColumAlertType
            // 
            this.ColumAlertType.HeaderText = "报警类型";
            this.ColumAlertType.Name = "ColumAlertType";
            // 
            // ColumAlertValue
            // 
            this.ColumAlertValue.HeaderText = "报警数值";
            this.ColumAlertValue.Name = "ColumAlertValue";
            this.ColumAlertValue.Width = 90;
            // 
            // ColumAlertLevel
            // 
            this.ColumAlertLevel.HeaderText = "报警级别";
            this.ColumAlertLevel.Name = "ColumAlertLevel";
            // 
            // ColumAlertContent
            // 
            this.ColumAlertContent.HeaderText = "报警内容";
            this.ColumAlertContent.Name = "ColumAlertContent";
            this.ColumAlertContent.Width = 270;
            // 
            // ColumAlertConfirm
            // 
            this.ColumAlertConfirm.HeaderText = "确认状态";
            this.ColumAlertConfirm.Name = "ColumAlertConfirm";
            // 
            // imageListx32
            // 
            this.imageListx32.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListx32.ImageStream")));
            this.imageListx32.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListx32.Images.SetKeyName(0, "Data Sheet_32px.png");
            this.imageListx32.Images.SetKeyName(1, "Activity History_32px.png");
            this.imageListx32.Images.SetKeyName(2, "Alert_32px.png");
            this.imageListx32.Images.SetKeyName(3, "Console_32px.png");
            this.imageListx32.Images.SetKeyName(4, "Full Image_32px.png");
            // 
            // panelStatus
            // 
            this.panelStatus.BackColor = System.Drawing.Color.Silver;
            this.panelStatus.Controls.Add(this.panelProcess);
            this.panelStatus.Controls.Add(this.panelLocation);
            this.panelStatus.Location = new System.Drawing.Point(3, 529);
            this.panelStatus.Name = "panelStatus";
            this.panelStatus.Size = new System.Drawing.Size(543, 412);
            this.panelStatus.TabIndex = 1;
            // 
            // panelProcess
            // 
            this.panelProcess.BackColor = System.Drawing.Color.WhiteSmoke;
            this.panelProcess.Controls.Add(this.panelstatusDetect);
            this.panelProcess.Controls.Add(this.labelbarprocess);
            this.panelProcess.Controls.Add(this.circularProgressBarprocess);
            this.panelProcess.Controls.Add(this.labelProcess);
            this.panelProcess.Controls.Add(this.pictureBoxProcess);
            this.panelProcess.Location = new System.Drawing.Point(3, 149);
            this.panelProcess.Name = "panelProcess";
            this.panelProcess.Size = new System.Drawing.Size(537, 260);
            this.panelProcess.TabIndex = 1;
            // 
            // panelstatusDetect
            // 
            this.panelstatusDetect.Controls.Add(this.dataGridViewStatus);
            this.panelstatusDetect.Location = new System.Drawing.Point(110, 3);
            this.panelstatusDetect.Name = "panelstatusDetect";
            this.panelstatusDetect.Size = new System.Drawing.Size(424, 254);
            this.panelstatusDetect.TabIndex = 4;
            // 
            // dataGridViewStatus
            // 
            this.dataGridViewStatus.AllowUserToAddRows = false;
            this.dataGridViewStatus.AllowUserToDeleteRows = false;
            this.dataGridViewStatus.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewStatus.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumDetectName,
            this.ColumDetectValue});
            this.dataGridViewStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewStatus.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewStatus.Name = "dataGridViewStatus";
            this.dataGridViewStatus.ReadOnly = true;
            this.dataGridViewStatus.RowHeadersVisible = false;
            this.dataGridViewStatus.RowTemplate.Height = 23;
            this.dataGridViewStatus.Size = new System.Drawing.Size(424, 254);
            this.dataGridViewStatus.TabIndex = 0;
            this.toolTip.SetToolTip(this.dataGridViewStatus, "当前电柜的检测结果");
            // 
            // ColumDetectName
            // 
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.TopCenter;
            this.ColumDetectName.DefaultCellStyle = dataGridViewCellStyle1;
            this.ColumDetectName.HeaderText = "仪表名称";
            this.ColumDetectName.Name = "ColumDetectName";
            this.ColumDetectName.ReadOnly = true;
            this.ColumDetectName.Width = 200;
            // 
            // ColumDetectValue
            // 
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.TopCenter;
            this.ColumDetectValue.DefaultCellStyle = dataGridViewCellStyle2;
            this.ColumDetectValue.HeaderText = "检测结果";
            this.ColumDetectValue.Name = "ColumDetectValue";
            this.ColumDetectValue.ReadOnly = true;
            this.ColumDetectValue.Width = 200;
            // 
            // labelbarprocess
            // 
            this.labelbarprocess.AutoSize = true;
            this.labelbarprocess.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelbarprocess.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelbarprocess.Location = new System.Drawing.Point(9, 228);
            this.labelbarprocess.Name = "labelbarprocess";
            this.labelbarprocess.Size = new System.Drawing.Size(95, 17);
            this.labelbarprocess.TabIndex = 5;
            this.labelbarprocess.Text = "检测进度：1/10";
            // 
            // circularProgressBarprocess
            // 
            this.circularProgressBarprocess.AnimationFunction = WinFormAnimation.KnownAnimationFunctions.Liner;
            this.circularProgressBarprocess.AnimationSpeed = 500;
            this.circularProgressBarprocess.BackColor = System.Drawing.Color.Transparent;
            this.circularProgressBarprocess.Font = new System.Drawing.Font("微软雅黑", 20F, System.Drawing.FontStyle.Bold);
            this.circularProgressBarprocess.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.circularProgressBarprocess.InnerColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.circularProgressBarprocess.InnerMargin = -1;
            this.circularProgressBarprocess.InnerWidth = -1;
            this.circularProgressBarprocess.Location = new System.Drawing.Point(9, 135);
            this.circularProgressBarprocess.MarqueeAnimationSpeed = 500;
            this.circularProgressBarprocess.Name = "circularProgressBarprocess";
            this.circularProgressBarprocess.OuterColor = System.Drawing.Color.Gray;
            this.circularProgressBarprocess.OuterMargin = -15;
            this.circularProgressBarprocess.OuterWidth = 10;
            this.circularProgressBarprocess.ProgressColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.circularProgressBarprocess.ProgressWidth = 6;
            this.circularProgressBarprocess.SecondaryFont = new System.Drawing.Font("宋体", 15F);
            this.circularProgressBarprocess.Size = new System.Drawing.Size(90, 90);
            this.circularProgressBarprocess.StartAngle = -90;
            this.circularProgressBarprocess.SubscriptColor = System.Drawing.Color.FromArgb(((int)(((byte)(166)))), ((int)(((byte)(166)))), ((int)(((byte)(166)))));
            this.circularProgressBarprocess.SubscriptMargin = new System.Windows.Forms.Padding(10, -35, 0, 0);
            this.circularProgressBarprocess.SubscriptText = "";
            this.circularProgressBarprocess.SuperscriptColor = System.Drawing.Color.FromArgb(((int)(((byte)(166)))), ((int)(((byte)(166)))), ((int)(((byte)(166)))));
            this.circularProgressBarprocess.SuperscriptMargin = new System.Windows.Forms.Padding(10, 35, 0, 0);
            this.circularProgressBarprocess.SuperscriptText = "";
            this.circularProgressBarprocess.TabIndex = 0;
            this.circularProgressBarprocess.Text = "0%";
            this.circularProgressBarprocess.TextMargin = new System.Windows.Forms.Padding(8, 8, 0, 0);
            this.circularProgressBarprocess.Value = 68;
            // 
            // labelProcess
            // 
            this.labelProcess.AutoSize = true;
            this.labelProcess.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelProcess.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelProcess.Location = new System.Drawing.Point(7, 102);
            this.labelProcess.Name = "labelProcess";
            this.labelProcess.Size = new System.Drawing.Size(92, 27);
            this.labelProcess.TabIndex = 2;
            this.labelProcess.Text = "检测状态";
            // 
            // pictureBoxProcess
            // 
            this.pictureBoxProcess.BackColor = System.Drawing.Color.Transparent;
            this.pictureBoxProcess.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxProcess.Image")));
            this.pictureBoxProcess.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxProcess.Name = "pictureBoxProcess";
            this.pictureBoxProcess.Size = new System.Drawing.Size(96, 96);
            this.pictureBoxProcess.TabIndex = 1;
            this.pictureBoxProcess.TabStop = false;
            // 
            // panelLocation
            // 
            this.panelLocation.BackColor = System.Drawing.Color.WhiteSmoke;
            this.panelLocation.Controls.Add(this.panelLocationDetail);
            this.panelLocation.Controls.Add(this.circularProgressBarLocation);
            this.panelLocation.Controls.Add(this.labelLoca);
            this.panelLocation.Controls.Add(this.pictureBoxlocation);
            this.panelLocation.Location = new System.Drawing.Point(3, 3);
            this.panelLocation.Name = "panelLocation";
            this.panelLocation.Size = new System.Drawing.Size(537, 140);
            this.panelLocation.TabIndex = 0;
            // 
            // panelLocationDetail
            // 
            this.panelLocationDetail.Controls.Add(this.labelCab);
            this.panelLocationDetail.Controls.Add(this.labelRom);
            this.panelLocationDetail.Controls.Add(this.labelFac);
            this.panelLocationDetail.Controls.Add(this.pictureBoxCab);
            this.panelLocationDetail.Controls.Add(this.pictureBoxRom);
            this.panelLocationDetail.Controls.Add(this.pictureBoxFac);
            this.panelLocationDetail.Location = new System.Drawing.Point(384, 3);
            this.panelLocationDetail.Name = "panelLocationDetail";
            this.panelLocationDetail.Size = new System.Drawing.Size(150, 134);
            this.panelLocationDetail.TabIndex = 3;
            // 
            // labelCab
            // 
            this.labelCab.AutoSize = true;
            this.labelCab.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelCab.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelCab.Location = new System.Drawing.Point(43, 104);
            this.labelCab.Name = "labelCab";
            this.labelCab.Size = new System.Drawing.Size(96, 27);
            this.labelCab.TabIndex = 5;
            this.labelCab.Text = "36号电柜";
            // 
            // labelRom
            // 
            this.labelRom.AutoSize = true;
            this.labelRom.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelRom.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelRom.Location = new System.Drawing.Point(43, 54);
            this.labelRom.Name = "labelRom";
            this.labelRom.Size = new System.Drawing.Size(64, 27);
            this.labelRom.TabIndex = 4;
            this.labelRom.Text = "1号间";
            // 
            // labelFac
            // 
            this.labelFac.AutoSize = true;
            this.labelFac.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelFac.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelFac.Location = new System.Drawing.Point(42, 9);
            this.labelFac.Name = "labelFac";
            this.labelFac.Size = new System.Drawing.Size(64, 27);
            this.labelFac.TabIndex = 3;
            this.labelFac.Text = "5号站";
            // 
            // pictureBoxCab
            // 
            this.pictureBoxCab.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxCab.Image")));
            this.pictureBoxCab.Location = new System.Drawing.Point(3, 99);
            this.pictureBoxCab.Name = "pictureBoxCab";
            this.pictureBoxCab.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxCab.TabIndex = 2;
            this.pictureBoxCab.TabStop = false;
            // 
            // pictureBoxRom
            // 
            this.pictureBoxRom.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxRom.Image")));
            this.pictureBoxRom.Location = new System.Drawing.Point(4, 51);
            this.pictureBoxRom.Name = "pictureBoxRom";
            this.pictureBoxRom.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxRom.TabIndex = 1;
            this.pictureBoxRom.TabStop = false;
            // 
            // pictureBoxFac
            // 
            this.pictureBoxFac.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxFac.Image")));
            this.pictureBoxFac.Location = new System.Drawing.Point(4, 4);
            this.pictureBoxFac.Name = "pictureBoxFac";
            this.pictureBoxFac.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxFac.TabIndex = 0;
            this.pictureBoxFac.TabStop = false;
            // 
            // circularProgressBarLocation
            // 
            this.circularProgressBarLocation.AnimationFunction = WinFormAnimation.KnownAnimationFunctions.Liner;
            this.circularProgressBarLocation.AnimationSpeed = 200;
            this.circularProgressBarLocation.BackColor = System.Drawing.Color.Transparent;
            this.circularProgressBarLocation.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold);
            this.circularProgressBarLocation.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.circularProgressBarLocation.InnerColor = System.Drawing.Color.White;
            this.circularProgressBarLocation.InnerMargin = -1;
            this.circularProgressBarLocation.InnerWidth = -1;
            this.circularProgressBarLocation.Location = new System.Drawing.Point(178, 2);
            this.circularProgressBarLocation.MarqueeAnimationSpeed = 5000;
            this.circularProgressBarLocation.Name = "circularProgressBarLocation";
            this.circularProgressBarLocation.OuterColor = System.Drawing.Color.Gray;
            this.circularProgressBarLocation.OuterMargin = -15;
            this.circularProgressBarLocation.OuterWidth = 10;
            this.circularProgressBarLocation.ProgressColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.circularProgressBarLocation.ProgressWidth = 10;
            this.circularProgressBarLocation.SecondaryFont = new System.Drawing.Font("宋体", 10F);
            this.circularProgressBarLocation.Size = new System.Drawing.Size(135, 135);
            this.circularProgressBarLocation.StartAngle = 60;
            this.circularProgressBarLocation.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
            this.circularProgressBarLocation.SubscriptColor = System.Drawing.Color.FromArgb(((int)(((byte)(166)))), ((int)(((byte)(166)))), ((int)(((byte)(166)))));
            this.circularProgressBarLocation.SubscriptMargin = new System.Windows.Forms.Padding(10, -35, 0, 0);
            this.circularProgressBarLocation.SubscriptText = "";
            this.circularProgressBarLocation.SuperscriptColor = System.Drawing.Color.FromArgb(((int)(((byte)(166)))), ((int)(((byte)(166)))), ((int)(((byte)(166)))));
            this.circularProgressBarLocation.SuperscriptMargin = new System.Windows.Forms.Padding(10, 35, 0, 0);
            this.circularProgressBarLocation.SuperscriptText = "";
            this.circularProgressBarLocation.TabIndex = 2;
            this.circularProgressBarLocation.Text = "移动中......";
            this.circularProgressBarLocation.TextMargin = new System.Windows.Forms.Padding(8, 8, 0, 0);
            this.circularProgressBarLocation.Value = 50;
            // 
            // labelLoca
            // 
            this.labelLoca.AutoSize = true;
            this.labelLoca.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelLoca.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelLoca.Location = new System.Drawing.Point(7, 102);
            this.labelLoca.Name = "labelLoca";
            this.labelLoca.Size = new System.Drawing.Size(92, 27);
            this.labelLoca.TabIndex = 1;
            this.labelLoca.Text = "定位状态";
            // 
            // pictureBoxlocation
            // 
            this.pictureBoxlocation.BackColor = System.Drawing.Color.Transparent;
            this.pictureBoxlocation.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxlocation.Image")));
            this.pictureBoxlocation.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxlocation.Name = "pictureBoxlocation";
            this.pictureBoxlocation.Size = new System.Drawing.Size(96, 96);
            this.pictureBoxlocation.TabIndex = 0;
            this.pictureBoxlocation.TabStop = false;
            // 
            // panelImagearea
            // 
            this.panelImagearea.BackColor = System.Drawing.Color.Gainsboro;
            this.panelImagearea.Controls.Add(this.panelvideoPlayer);
            this.panelImagearea.Controls.Add(this.panelImgProcess);
            this.panelImagearea.Controls.Add(this.panelImgSource);
            this.panelImagearea.Location = new System.Drawing.Point(0, 0);
            this.panelImagearea.Name = "panelImagearea";
            this.panelImagearea.Size = new System.Drawing.Size(1654, 526);
            this.panelImagearea.TabIndex = 0;
            // 
            // panelvideoPlayer
            // 
            this.panelvideoPlayer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelvideoPlayer.Controls.Add(this.videoSourcePlayer);
            this.panelvideoPlayer.Controls.Add(this.panelCameraOperate);
            this.panelvideoPlayer.Location = new System.Drawing.Point(3, 3);
            this.panelvideoPlayer.Name = "panelvideoPlayer";
            this.panelvideoPlayer.Size = new System.Drawing.Size(820, 520);
            this.panelvideoPlayer.TabIndex = 1;
            // 
            // videoSourcePlayer
            // 
            this.videoSourcePlayer.Location = new System.Drawing.Point(72, 27);
            this.videoSourcePlayer.Name = "videoSourcePlayer";
            this.videoSourcePlayer.Size = new System.Drawing.Size(654, 489);
            this.videoSourcePlayer.TabIndex = 2;
            this.videoSourcePlayer.Text = "videoSourcePlayer1";
            this.videoSourcePlayer.VideoSource = null;
            this.videoSourcePlayer.NewFrame += new AForge.Controls.VideoSourcePlayer.NewFrameHandler(this.videoSourcePlayer_NewFrame);
            // 
            // panelCameraOperate
            // 
            this.panelCameraOperate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelCameraOperate.Controls.Add(this.buttonIPcamera);
            this.panelCameraOperate.Controls.Add(this.buttonvideoCap);
            this.panelCameraOperate.Controls.Add(this.buttonCapture);
            this.panelCameraOperate.Controls.Add(this.buttonRefreshCameras);
            this.panelCameraOperate.Controls.Add(this.buttonCloseCamera);
            this.panelCameraOperate.Controls.Add(this.buttonopenCamera);
            this.panelCameraOperate.Controls.Add(this.comboBoxCameraChoose);
            this.panelCameraOperate.Location = new System.Drawing.Point(2, 2);
            this.panelCameraOperate.Name = "panelCameraOperate";
            this.panelCameraOperate.Size = new System.Drawing.Size(813, 25);
            this.panelCameraOperate.TabIndex = 1;
            // 
            // buttonIPcamera
            // 
            this.buttonIPcamera.Location = new System.Drawing.Point(442, 0);
            this.buttonIPcamera.Name = "buttonIPcamera";
            this.buttonIPcamera.Size = new System.Drawing.Size(75, 23);
            this.buttonIPcamera.TabIndex = 5;
            this.buttonIPcamera.Text = "网络摄像头";
            this.buttonIPcamera.UseVisualStyleBackColor = true;
            this.buttonIPcamera.Click += new System.EventHandler(this.buttonIPcamera_Click);
            // 
            // buttonvideoCap
            // 
            this.buttonvideoCap.Location = new System.Drawing.Point(692, -1);
            this.buttonvideoCap.Name = "buttonvideoCap";
            this.buttonvideoCap.Size = new System.Drawing.Size(75, 23);
            this.buttonvideoCap.TabIndex = 4;
            this.buttonvideoCap.Text = "开始录像";
            this.buttonvideoCap.UseVisualStyleBackColor = true;
            this.buttonvideoCap.Click += new System.EventHandler(this.buttonvideoCap_Click);
            // 
            // buttonCapture
            // 
            this.buttonCapture.Location = new System.Drawing.Point(611, 0);
            this.buttonCapture.Name = "buttonCapture";
            this.buttonCapture.Size = new System.Drawing.Size(75, 23);
            this.buttonCapture.TabIndex = 3;
            this.buttonCapture.Text = "抓取";
            this.buttonCapture.UseVisualStyleBackColor = true;
            this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
            // 
            // buttonRefreshCameras
            // 
            this.buttonRefreshCameras.Location = new System.Drawing.Point(280, -1);
            this.buttonRefreshCameras.Name = "buttonRefreshCameras";
            this.buttonRefreshCameras.Size = new System.Drawing.Size(75, 23);
            this.buttonRefreshCameras.TabIndex = 2;
            this.buttonRefreshCameras.Text = "检索设备";
            this.buttonRefreshCameras.UseVisualStyleBackColor = true;
            this.buttonRefreshCameras.Click += new System.EventHandler(this.buttonRefreshCameras_Click);
            // 
            // buttonCloseCamera
            // 
            this.buttonCloseCamera.Location = new System.Drawing.Point(523, -2);
            this.buttonCloseCamera.Name = "buttonCloseCamera";
            this.buttonCloseCamera.Size = new System.Drawing.Size(82, 27);
            this.buttonCloseCamera.TabIndex = 1;
            this.buttonCloseCamera.Text = "关闭摄像头";
            this.buttonCloseCamera.UseVisualStyleBackColor = true;
            this.buttonCloseCamera.Click += new System.EventHandler(this.buttonCloseCamera_Click);
            // 
            // buttonopenCamera
            // 
            this.buttonopenCamera.Location = new System.Drawing.Point(361, -1);
            this.buttonopenCamera.Name = "buttonopenCamera";
            this.buttonopenCamera.Size = new System.Drawing.Size(75, 23);
            this.buttonopenCamera.TabIndex = 1;
            this.buttonopenCamera.Text = "打开摄像头";
            this.buttonopenCamera.UseVisualStyleBackColor = true;
            this.buttonopenCamera.Click += new System.EventHandler(this.buttonopenCamera_Click);
            // 
            // comboBoxCameraChoose
            // 
            this.comboBoxCameraChoose.Font = new System.Drawing.Font("宋体", 12F);
            this.comboBoxCameraChoose.FormattingEnabled = true;
            this.comboBoxCameraChoose.Location = new System.Drawing.Point(-1, -1);
            this.comboBoxCameraChoose.Name = "comboBoxCameraChoose";
            this.comboBoxCameraChoose.Size = new System.Drawing.Size(275, 24);
            this.comboBoxCameraChoose.TabIndex = 0;
            // 
            // panelImgProcess
            // 
            this.panelImgProcess.Controls.Add(this.pictureBoxProcessed);
            this.panelImgProcess.Location = new System.Drawing.Point(831, 3);
            this.panelImgProcess.Name = "panelImgProcess";
            this.panelImgProcess.Size = new System.Drawing.Size(820, 520);
            this.panelImgProcess.TabIndex = 1;
            // 
            // pictureBoxProcessed
            // 
            this.pictureBoxProcessed.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxProcessed.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBoxProcessed.Location = new System.Drawing.Point(0, 0);
            this.pictureBoxProcessed.Name = "pictureBoxProcessed";
            this.pictureBoxProcessed.Size = new System.Drawing.Size(820, 520);
            this.pictureBoxProcessed.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxProcessed.TabIndex = 0;
            this.pictureBoxProcessed.TabStop = false;
            // 
            // panelImgSource
            // 
            this.panelImgSource.Controls.Add(this.pictureBoxSource);
            this.panelImgSource.Location = new System.Drawing.Point(3, 3);
            this.panelImgSource.Name = "panelImgSource";
            this.panelImgSource.Size = new System.Drawing.Size(820, 520);
            this.panelImgSource.TabIndex = 0;
            // 
            // pictureBoxSource
            // 
            this.pictureBoxSource.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxSource.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBoxSource.Location = new System.Drawing.Point(0, 0);
            this.pictureBoxSource.Name = "pictureBoxSource";
            this.pictureBoxSource.Size = new System.Drawing.Size(820, 520);
            this.pictureBoxSource.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxSource.TabIndex = 0;
            this.pictureBoxSource.TabStop = false;
            this.pictureBoxSource.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSource_MouseDoubleClick);
            // 
            // tabChart
            // 
            this.tabChart.BackColor = System.Drawing.Color.Gainsboro;
            this.tabChart.Controls.Add(this.tabControlDatabase);
            this.tabChart.ImageKey = "Combo Chart_96px.png";
            this.tabChart.Location = new System.Drawing.Point(4, 100);
            this.tabChart.Name = "tabChart";
            this.tabChart.Padding = new System.Windows.Forms.Padding(3);
            this.tabChart.Size = new System.Drawing.Size(1654, 944);
            this.tabChart.TabIndex = 1;
            // 
            // tabControlDatabase
            // 
            this.tabControlDatabase.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.tabControlDatabase.Controls.Add(this.tabPageDBadvanced);
            this.tabControlDatabase.Controls.Add(this.tabPageDBDevicequery);
            this.tabControlDatabase.Controls.Add(this.tabPageDBSelfAlarm);
            this.tabControlDatabase.ImageList = this.imageListDB;
            this.tabControlDatabase.Location = new System.Drawing.Point(3, 3);
            this.tabControlDatabase.Multiline = true;
            this.tabControlDatabase.Name = "tabControlDatabase";
            this.tabControlDatabase.SelectedIndex = 0;
            this.tabControlDatabase.Size = new System.Drawing.Size(1648, 941);
            this.tabControlDatabase.TabIndex = 0;
            // 
            // tabPageDBadvanced
            // 
            this.tabPageDBadvanced.BackColor = System.Drawing.Color.Gainsboro;
            this.tabPageDBadvanced.Controls.Add(this.panel1);
            this.tabPageDBadvanced.Controls.Add(this.paneldevicetree);
            this.tabPageDBadvanced.Controls.Add(this.paneldate);
            this.tabPageDBadvanced.ImageIndex = 0;
            this.tabPageDBadvanced.Location = new System.Drawing.Point(71, 4);
            this.tabPageDBadvanced.Name = "tabPageDBadvanced";
            this.tabPageDBadvanced.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageDBadvanced.Size = new System.Drawing.Size(1573, 933);
            this.tabPageDBadvanced.TabIndex = 0;
            this.tabPageDBadvanced.ToolTipText = "高级查询";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.dataGridViewAdvancedSQL);
            this.panel1.Location = new System.Drawing.Point(374, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1193, 924);
            this.panel1.TabIndex = 5;
            // 
            // dataGridViewAdvancedSQL
            // 
            this.dataGridViewAdvancedSQL.AllowUserToAddRows = false;
            this.dataGridViewAdvancedSQL.AllowUserToDeleteRows = false;
            this.dataGridViewAdvancedSQL.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAdvancedSQL.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.roomName,
            this.CabinName,
            this.DeviceName,
            this.DeviceClass,
            this.DetectResult,
            this.DetectAlarm,
            this.DetectDateTime});
            this.dataGridViewAdvancedSQL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewAdvancedSQL.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewAdvancedSQL.Name = "dataGridViewAdvancedSQL";
            this.dataGridViewAdvancedSQL.ReadOnly = true;
            this.dataGridViewAdvancedSQL.RowHeadersVisible = false;
            this.dataGridViewAdvancedSQL.RowTemplate.Height = 23;
            this.dataGridViewAdvancedSQL.Size = new System.Drawing.Size(1193, 924);
            this.dataGridViewAdvancedSQL.TabIndex = 5;
            // 
            // roomName
            // 
            this.roomName.HeaderText = "房间名";
            this.roomName.Name = "roomName";
            this.roomName.ReadOnly = true;
            this.roomName.Width = 120;
            // 
            // CabinName
            // 
            this.CabinName.HeaderText = "电柜名";
            this.CabinName.Name = "CabinName";
            this.CabinName.ReadOnly = true;
            this.CabinName.Width = 120;
            // 
            // DeviceName
            // 
            this.DeviceName.HeaderText = "设备名";
            this.DeviceName.Name = "DeviceName";
            this.DeviceName.ReadOnly = true;
            this.DeviceName.Width = 200;
            // 
            // DeviceClass
            // 
            this.DeviceClass.HeaderText = "检测项";
            this.DeviceClass.Name = "DeviceClass";
            this.DeviceClass.ReadOnly = true;
            this.DeviceClass.Width = 200;
            // 
            // DetectResult
            // 
            this.DetectResult.HeaderText = "检测结果";
            this.DetectResult.Name = "DetectResult";
            this.DetectResult.ReadOnly = true;
            this.DetectResult.Width = 150;
            // 
            // DetectAlarm
            // 
            this.DetectAlarm.HeaderText = "报警信息";
            this.DetectAlarm.Name = "DetectAlarm";
            this.DetectAlarm.ReadOnly = true;
            this.DetectAlarm.Width = 200;
            // 
            // DetectDateTime
            // 
            this.DetectDateTime.HeaderText = "检测时间";
            this.DetectDateTime.Name = "DetectDateTime";
            this.DetectDateTime.ReadOnly = true;
            this.DetectDateTime.Width = 200;
            // 
            // paneldevicetree
            // 
            this.paneldevicetree.Controls.Add(this.treeViewAdvanced);
            this.paneldevicetree.Location = new System.Drawing.Point(3, 53);
            this.paneldevicetree.Name = "paneldevicetree";
            this.paneldevicetree.Size = new System.Drawing.Size(367, 874);
            this.paneldevicetree.TabIndex = 4;
            // 
            // treeViewAdvanced
            // 
            this.treeViewAdvanced.Location = new System.Drawing.Point(3, 4);
            this.treeViewAdvanced.Name = "treeViewAdvanced";
            this.treeViewAdvanced.Size = new System.Drawing.Size(361, 867);
            this.treeViewAdvanced.TabIndex = 0;
            this.treeViewAdvanced.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewAdvanced_AfterSelect);
            // 
            // paneldate
            // 
            this.paneldate.Controls.Add(this.labeladvancedDate);
            this.paneldate.Controls.Add(this.dateTimePickeradvancedStop);
            this.paneldate.Controls.Add(this.dateTimePickerAdvancedStart);
            this.paneldate.Location = new System.Drawing.Point(3, 3);
            this.paneldate.Name = "paneldate";
            this.paneldate.Size = new System.Drawing.Size(367, 45);
            this.paneldate.TabIndex = 3;
            // 
            // labeladvancedDate
            // 
            this.labeladvancedDate.AutoSize = true;
            this.labeladvancedDate.Location = new System.Drawing.Point(19, 17);
            this.labeladvancedDate.Name = "labeladvancedDate";
            this.labeladvancedDate.Size = new System.Drawing.Size(29, 12);
            this.labeladvancedDate.TabIndex = 0;
            this.labeladvancedDate.Text = "日期";
            // 
            // dateTimePickeradvancedStop
            // 
            this.dateTimePickeradvancedStop.Location = new System.Drawing.Point(228, 11);
            this.dateTimePickeradvancedStop.Name = "dateTimePickeradvancedStop";
            this.dateTimePickeradvancedStop.Size = new System.Drawing.Size(136, 21);
            this.dateTimePickeradvancedStop.TabIndex = 2;
            // 
            // dateTimePickerAdvancedStart
            // 
            this.dateTimePickerAdvancedStart.Location = new System.Drawing.Point(68, 11);
            this.dateTimePickerAdvancedStart.Name = "dateTimePickerAdvancedStart";
            this.dateTimePickerAdvancedStart.Size = new System.Drawing.Size(127, 21);
            this.dateTimePickerAdvancedStart.TabIndex = 1;
            // 
            // tabPageDBDevicequery
            // 
            this.tabPageDBDevicequery.ImageIndex = 1;
            this.tabPageDBDevicequery.Location = new System.Drawing.Point(71, 4);
            this.tabPageDBDevicequery.Name = "tabPageDBDevicequery";
            this.tabPageDBDevicequery.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageDBDevicequery.Size = new System.Drawing.Size(1573, 933);
            this.tabPageDBDevicequery.TabIndex = 1;
            this.tabPageDBDevicequery.ToolTipText = "设备查询";
            this.tabPageDBDevicequery.UseVisualStyleBackColor = true;
            // 
            // tabPageDBSelfAlarm
            // 
            this.tabPageDBSelfAlarm.ImageIndex = 2;
            this.tabPageDBSelfAlarm.Location = new System.Drawing.Point(71, 4);
            this.tabPageDBSelfAlarm.Name = "tabPageDBSelfAlarm";
            this.tabPageDBSelfAlarm.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageDBSelfAlarm.Size = new System.Drawing.Size(1573, 933);
            this.tabPageDBSelfAlarm.TabIndex = 2;
            this.tabPageDBSelfAlarm.ToolTipText = "本机报警查询.";
            this.tabPageDBSelfAlarm.UseVisualStyleBackColor = true;
            // 
            // imageListDB
            // 
            this.imageListDB.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListDB.ImageStream")));
            this.imageListDB.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListDB.Images.SetKeyName(0, "Google Web Search_96px.png");
            this.imageListDB.Images.SetKeyName(1, "Product_96px.png");
            this.imageListDB.Images.SetKeyName(2, "Siren_96px.png");
            // 
            // tabSetting
            // 
            this.tabSetting.BackColor = System.Drawing.Color.Gainsboro;
            this.tabSetting.Controls.Add(this.panelXMLConfig);
            this.tabSetting.ImageIndex = 5;
            this.tabSetting.Location = new System.Drawing.Point(4, 100);
            this.tabSetting.Name = "tabSetting";
            this.tabSetting.Padding = new System.Windows.Forms.Padding(3);
            this.tabSetting.Size = new System.Drawing.Size(1654, 944);
            this.tabSetting.TabIndex = 2;
            // 
            // panelXMLConfig
            // 
            this.panelXMLConfig.Controls.Add(this.panelXML);
            this.panelXMLConfig.Controls.Add(this.panelROI);
            this.panelXMLConfig.Location = new System.Drawing.Point(3, 3);
            this.panelXMLConfig.Name = "panelXMLConfig";
            this.panelXMLConfig.Size = new System.Drawing.Size(1648, 539);
            this.panelXMLConfig.TabIndex = 0;
            // 
            // panelXML
            // 
            this.panelXML.Controls.Add(this.buttonQR);
            this.panelXML.Controls.Add(this.paneldata);
            this.panelXML.Controls.Add(this.panelAdd);
            this.panelXML.Controls.Add(this.panelCreate);
            this.panelXML.Controls.Add(this.panelxmlpath);
            this.panelXML.Location = new System.Drawing.Point(750, 4);
            this.panelXML.Name = "panelXML";
            this.panelXML.Size = new System.Drawing.Size(895, 528);
            this.panelXML.TabIndex = 2;
            // 
            // buttonQR
            // 
            this.buttonQR.Location = new System.Drawing.Point(3, 182);
            this.buttonQR.Name = "buttonQR";
            this.buttonQR.Size = new System.Drawing.Size(75, 23);
            this.buttonQR.TabIndex = 11;
            this.buttonQR.Text = "二维码确认";
            this.buttonQR.UseVisualStyleBackColor = true;
            this.buttonQR.Click += new System.EventHandler(this.buttonQR_Click);
            // 
            // paneldata
            // 
            this.paneldata.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.paneldata.Controls.Add(this.panelfordatause);
            this.paneldata.Controls.Add(this.panelforgridview);
            this.paneldata.Location = new System.Drawing.Point(3, 251);
            this.paneldata.Name = "paneldata";
            this.paneldata.Size = new System.Drawing.Size(892, 269);
            this.paneldata.TabIndex = 10;
            // 
            // panelfordatause
            // 
            this.panelfordatause.Controls.Add(this.bunifuImageButtonRefresh);
            this.panelfordatause.Location = new System.Drawing.Point(839, 1);
            this.panelfordatause.Name = "panelfordatause";
            this.panelfordatause.Size = new System.Drawing.Size(49, 263);
            this.panelfordatause.TabIndex = 5;
            // 
            // bunifuImageButtonRefresh
            // 
            this.bunifuImageButtonRefresh.BackColor = System.Drawing.Color.LightGray;
            this.bunifuImageButtonRefresh.Image = ((System.Drawing.Image)(resources.GetObject("bunifuImageButtonRefresh.Image")));
            this.bunifuImageButtonRefresh.ImageActive = null;
            this.bunifuImageButtonRefresh.Location = new System.Drawing.Point(1, 2);
            this.bunifuImageButtonRefresh.Name = "bunifuImageButtonRefresh";
            this.bunifuImageButtonRefresh.Size = new System.Drawing.Size(45, 47);
            this.bunifuImageButtonRefresh.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.bunifuImageButtonRefresh.TabIndex = 8;
            this.bunifuImageButtonRefresh.TabStop = false;
            this.bunifuImageButtonRefresh.Zoom = 10;
            this.bunifuImageButtonRefresh.Click += new System.EventHandler(this.bunifuImageButtonRefresh_Click);
            // 
            // panelforgridview
            // 
            this.panelforgridview.Controls.Add(this.dataGridView);
            this.panelforgridview.Location = new System.Drawing.Point(-1, -1);
            this.panelforgridview.Name = "panelforgridview";
            this.panelforgridview.Size = new System.Drawing.Size(839, 269);
            this.panelforgridview.TabIndex = 0;
            // 
            // dataGridView
            // 
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView.Location = new System.Drawing.Point(0, 0);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.Size = new System.Drawing.Size(839, 269);
            this.dataGridView.TabIndex = 4;
            this.dataGridView.CellMouseDown += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView_CellMouseDown);
            // 
            // panelAdd
            // 
            this.panelAdd.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelAdd.Controls.Add(this.panelknob);
            this.panelAdd.Controls.Add(this.panelpointer);
            this.panelAdd.Controls.Add(this.textBoxgetname);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelheight);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelwidth);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelY);
            this.panelAdd.Controls.Add(this.buttonAppend);
            this.panelAdd.Controls.Add(this.numericUpDownnum);
            this.panelAdd.Controls.Add(this.numericUpDownheight);
            this.panelAdd.Controls.Add(this.numericUpDownStartY);
            this.panelAdd.Controls.Add(this.numericUpDownwidth);
            this.panelAdd.Controls.Add(this.numericUpDownStartX);
            this.panelAdd.Controls.Add(this.comboBoxsub2);
            this.panelAdd.Controls.Add(this.comboBoxsub1);
            this.panelAdd.Controls.Add(this.comboBoxType);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelNum);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelSub2);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelname);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelSub1);
            this.panelAdd.Controls.Add(this.bunifuCustomLabelX);
            this.panelAdd.Controls.Add(this.bunifuCustomLabeltype);
            this.panelAdd.Location = new System.Drawing.Point(439, 2);
            this.panelAdd.Name = "panelAdd";
            this.panelAdd.Size = new System.Drawing.Size(453, 245);
            this.panelAdd.TabIndex = 9;
            // 
            // panelknob
            // 
            this.panelknob.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelknob.Controls.Add(this.richTextBoxKnobitem);
            this.panelknob.Controls.Add(this.labelknobLow);
            this.panelknob.Controls.Add(this.labelKnobHigh);
            this.panelknob.Controls.Add(this.numericUpDownknobLow);
            this.panelknob.Controls.Add(this.textBoxKnobContext);
            this.panelknob.Controls.Add(this.numericUpDownKnobHigh);
            this.panelknob.Controls.Add(this.buttonknobAddItem);
            this.panelknob.Location = new System.Drawing.Point(123, 164);
            this.panelknob.Name = "panelknob";
            this.panelknob.Size = new System.Drawing.Size(308, 76);
            this.panelknob.TabIndex = 16;
            this.toolTip.SetToolTip(this.panelknob, "旋钮档位设定");
            // 
            // richTextBoxKnobitem
            // 
            this.richTextBoxKnobitem.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.richTextBoxKnobitem.Location = new System.Drawing.Point(140, 3);
            this.richTextBoxKnobitem.Name = "richTextBoxKnobitem";
            this.richTextBoxKnobitem.Size = new System.Drawing.Size(160, 69);
            this.richTextBoxKnobitem.TabIndex = 14;
            this.richTextBoxKnobitem.Text = "";
            // 
            // labelknobLow
            // 
            this.labelknobLow.AutoSize = true;
            this.labelknobLow.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelknobLow.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelknobLow.Location = new System.Drawing.Point(3, 8);
            this.labelknobLow.Name = "labelknobLow";
            this.labelknobLow.Size = new System.Drawing.Size(30, 16);
            this.labelknobLow.TabIndex = 13;
            this.labelknobLow.Text = "下限";
            // 
            // labelKnobHigh
            // 
            this.labelKnobHigh.AutoSize = true;
            this.labelKnobHigh.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelKnobHigh.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelKnobHigh.Location = new System.Drawing.Point(3, 30);
            this.labelKnobHigh.Name = "labelKnobHigh";
            this.labelKnobHigh.Size = new System.Drawing.Size(30, 16);
            this.labelKnobHigh.TabIndex = 13;
            this.labelKnobHigh.Text = "上限";
            // 
            // numericUpDownknobLow
            // 
            this.numericUpDownknobLow.Location = new System.Drawing.Point(39, 3);
            this.numericUpDownknobLow.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.numericUpDownknobLow.Name = "numericUpDownknobLow";
            this.numericUpDownknobLow.Size = new System.Drawing.Size(46, 21);
            this.numericUpDownknobLow.TabIndex = 11;
            // 
            // textBoxKnobContext
            // 
            this.textBoxKnobContext.Font = new System.Drawing.Font("微软雅黑", 8F);
            this.textBoxKnobContext.Location = new System.Drawing.Point(6, 51);
            this.textBoxKnobContext.Name = "textBoxKnobContext";
            this.textBoxKnobContext.Size = new System.Drawing.Size(79, 22);
            this.textBoxKnobContext.TabIndex = 11;
            this.textBoxKnobContext.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // numericUpDownKnobHigh
            // 
            this.numericUpDownKnobHigh.Location = new System.Drawing.Point(39, 27);
            this.numericUpDownKnobHigh.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.numericUpDownKnobHigh.Name = "numericUpDownKnobHigh";
            this.numericUpDownKnobHigh.Size = new System.Drawing.Size(46, 21);
            this.numericUpDownKnobHigh.TabIndex = 12;
            // 
            // buttonknobAddItem
            // 
            this.buttonknobAddItem.Font = new System.Drawing.Font("微软雅黑", 8F);
            this.buttonknobAddItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonknobAddItem.Location = new System.Drawing.Point(91, 3);
            this.buttonknobAddItem.Name = "buttonknobAddItem";
            this.buttonknobAddItem.Size = new System.Drawing.Size(30, 68);
            this.buttonknobAddItem.TabIndex = 2;
            this.buttonknobAddItem.Text = "添加";
            this.buttonknobAddItem.UseVisualStyleBackColor = true;
            this.buttonknobAddItem.Click += new System.EventHandler(this.buttonknobAddItem_Click);
            // 
            // panelpointer
            // 
            this.panelpointer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelpointer.Controls.Add(this.labelpointerunit);
            this.panelpointer.Controls.Add(this.labelpointerhigh);
            this.panelpointer.Controls.Add(this.labelpointerLow);
            this.panelpointer.Controls.Add(this.textBoxpointerUnit);
            this.panelpointer.Controls.Add(this.numericUpDownPointerhigh);
            this.panelpointer.Controls.Add(this.numericUpDownpointerLow);
            this.panelpointer.Location = new System.Drawing.Point(10, 164);
            this.panelpointer.Name = "panelpointer";
            this.panelpointer.Size = new System.Drawing.Size(93, 76);
            this.panelpointer.TabIndex = 15;
            this.toolTip.SetToolTip(this.panelpointer, "指针量程和单位设定");
            // 
            // labelpointerunit
            // 
            this.labelpointerunit.AutoSize = true;
            this.labelpointerunit.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelpointerunit.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelpointerunit.Location = new System.Drawing.Point(6, 52);
            this.labelpointerunit.Name = "labelpointerunit";
            this.labelpointerunit.Size = new System.Drawing.Size(30, 16);
            this.labelpointerunit.TabIndex = 13;
            this.labelpointerunit.Text = "单位";
            // 
            // labelpointerhigh
            // 
            this.labelpointerhigh.AutoSize = true;
            this.labelpointerhigh.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelpointerhigh.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelpointerhigh.Location = new System.Drawing.Point(6, 27);
            this.labelpointerhigh.Name = "labelpointerhigh";
            this.labelpointerhigh.Size = new System.Drawing.Size(30, 16);
            this.labelpointerhigh.TabIndex = 13;
            this.labelpointerhigh.Text = "上限";
            // 
            // labelpointerLow
            // 
            this.labelpointerLow.AutoSize = true;
            this.labelpointerLow.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelpointerLow.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelpointerLow.Location = new System.Drawing.Point(6, 3);
            this.labelpointerLow.Name = "labelpointerLow";
            this.labelpointerLow.Size = new System.Drawing.Size(30, 16);
            this.labelpointerLow.TabIndex = 13;
            this.labelpointerLow.Text = "下限";
            // 
            // textBoxpointerUnit
            // 
            this.textBoxpointerUnit.Location = new System.Drawing.Point(42, 52);
            this.textBoxpointerUnit.Name = "textBoxpointerUnit";
            this.textBoxpointerUnit.Size = new System.Drawing.Size(46, 21);
            this.textBoxpointerUnit.TabIndex = 11;
            this.textBoxpointerUnit.Text = "V";
            // 
            // numericUpDownPointerhigh
            // 
            this.numericUpDownPointerhigh.Location = new System.Drawing.Point(42, 27);
            this.numericUpDownPointerhigh.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.numericUpDownPointerhigh.Name = "numericUpDownPointerhigh";
            this.numericUpDownPointerhigh.Size = new System.Drawing.Size(46, 21);
            this.numericUpDownPointerhigh.TabIndex = 12;
            // 
            // numericUpDownpointerLow
            // 
            this.numericUpDownpointerLow.Location = new System.Drawing.Point(42, 3);
            this.numericUpDownpointerLow.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.numericUpDownpointerLow.Name = "numericUpDownpointerLow";
            this.numericUpDownpointerLow.Size = new System.Drawing.Size(46, 21);
            this.numericUpDownpointerLow.TabIndex = 11;
            // 
            // textBoxgetname
            // 
            this.textBoxgetname.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBoxgetname.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.textBoxgetname.Location = new System.Drawing.Point(264, 91);
            this.textBoxgetname.Name = "textBoxgetname";
            this.textBoxgetname.Size = new System.Drawing.Size(167, 29);
            this.textBoxgetname.TabIndex = 14;
            this.textBoxgetname.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // bunifuCustomLabelheight
            // 
            this.bunifuCustomLabelheight.AutoSize = true;
            this.bunifuCustomLabelheight.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelheight.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelheight.Location = new System.Drawing.Point(334, 64);
            this.bunifuCustomLabelheight.Name = "bunifuCustomLabelheight";
            this.bunifuCustomLabelheight.Size = new System.Drawing.Size(20, 20);
            this.bunifuCustomLabelheight.TabIndex = 13;
            this.bunifuCustomLabelheight.Text = "H";
            // 
            // bunifuCustomLabelwidth
            // 
            this.bunifuCustomLabelwidth.AutoSize = true;
            this.bunifuCustomLabelwidth.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelwidth.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelwidth.Location = new System.Drawing.Point(208, 64);
            this.bunifuCustomLabelwidth.Name = "bunifuCustomLabelwidth";
            this.bunifuCustomLabelwidth.Size = new System.Drawing.Size(23, 20);
            this.bunifuCustomLabelwidth.TabIndex = 13;
            this.bunifuCustomLabelwidth.Text = "W";
            // 
            // bunifuCustomLabelY
            // 
            this.bunifuCustomLabelY.AutoSize = true;
            this.bunifuCustomLabelY.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelY.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelY.Location = new System.Drawing.Point(334, 15);
            this.bunifuCustomLabelY.Name = "bunifuCustomLabelY";
            this.bunifuCustomLabelY.Size = new System.Drawing.Size(17, 20);
            this.bunifuCustomLabelY.TabIndex = 12;
            this.bunifuCustomLabelY.Text = "Y";
            // 
            // buttonAppend
            // 
            this.buttonAppend.Font = new System.Drawing.Font("微软雅黑", 15F);
            this.buttonAppend.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonAppend.Location = new System.Drawing.Point(237, 126);
            this.buttonAppend.Name = "buttonAppend";
            this.buttonAppend.Size = new System.Drawing.Size(194, 32);
            this.buttonAppend.TabIndex = 2;
            this.buttonAppend.Text = "添加";
            this.buttonAppend.UseVisualStyleBackColor = true;
            this.buttonAppend.Click += new System.EventHandler(this.buttonAppend_Click);
            // 
            // numericUpDownnum
            // 
            this.numericUpDownnum.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownnum.Location = new System.Drawing.Point(77, 133);
            this.numericUpDownnum.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownnum.Name = "numericUpDownnum";
            this.numericUpDownnum.Size = new System.Drawing.Size(111, 25);
            this.numericUpDownnum.TabIndex = 8;
            this.numericUpDownnum.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDownnum.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numericUpDownheight
            // 
            this.numericUpDownheight.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownheight.Location = new System.Drawing.Point(360, 59);
            this.numericUpDownheight.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownheight.Name = "numericUpDownheight";
            this.numericUpDownheight.Size = new System.Drawing.Size(71, 25);
            this.numericUpDownheight.TabIndex = 8;
            // 
            // numericUpDownStartY
            // 
            this.numericUpDownStartY.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownStartY.Location = new System.Drawing.Point(360, 13);
            this.numericUpDownStartY.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownStartY.Name = "numericUpDownStartY";
            this.numericUpDownStartY.Size = new System.Drawing.Size(71, 25);
            this.numericUpDownStartY.TabIndex = 8;
            // 
            // numericUpDownwidth
            // 
            this.numericUpDownwidth.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownwidth.Location = new System.Drawing.Point(237, 59);
            this.numericUpDownwidth.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownwidth.Name = "numericUpDownwidth";
            this.numericUpDownwidth.Size = new System.Drawing.Size(71, 25);
            this.numericUpDownwidth.TabIndex = 8;
            // 
            // numericUpDownStartX
            // 
            this.numericUpDownStartX.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownStartX.Location = new System.Drawing.Point(237, 13);
            this.numericUpDownStartX.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownStartX.Name = "numericUpDownStartX";
            this.numericUpDownStartX.Size = new System.Drawing.Size(71, 25);
            this.numericUpDownStartX.TabIndex = 8;
            // 
            // comboBoxsub2
            // 
            this.comboBoxsub2.FormattingEnabled = true;
            this.comboBoxsub2.Location = new System.Drawing.Point(77, 101);
            this.comboBoxsub2.Name = "comboBoxsub2";
            this.comboBoxsub2.Size = new System.Drawing.Size(111, 20);
            this.comboBoxsub2.TabIndex = 11;
            // 
            // comboBoxsub1
            // 
            this.comboBoxsub1.FormattingEnabled = true;
            this.comboBoxsub1.Location = new System.Drawing.Point(76, 59);
            this.comboBoxsub1.Name = "comboBoxsub1";
            this.comboBoxsub1.Size = new System.Drawing.Size(111, 20);
            this.comboBoxsub1.TabIndex = 11;
            // 
            // comboBoxType
            // 
            this.comboBoxType.FormattingEnabled = true;
            this.comboBoxType.Location = new System.Drawing.Point(76, 13);
            this.comboBoxType.Name = "comboBoxType";
            this.comboBoxType.Size = new System.Drawing.Size(111, 20);
            this.comboBoxType.TabIndex = 11;
            this.comboBoxType.SelectedIndexChanged += new System.EventHandler(this.comboBoxType_SelectedIndexChanged);
            // 
            // bunifuCustomLabelNum
            // 
            this.bunifuCustomLabelNum.AutoSize = true;
            this.bunifuCustomLabelNum.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelNum.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelNum.Location = new System.Drawing.Point(6, 138);
            this.bunifuCustomLabelNum.Name = "bunifuCustomLabelNum";
            this.bunifuCustomLabelNum.Size = new System.Drawing.Size(65, 20);
            this.bunifuCustomLabelNum.TabIndex = 8;
            this.bunifuCustomLabelNum.Text = "元素数目";
            // 
            // bunifuCustomLabelSub2
            // 
            this.bunifuCustomLabelSub2.AutoSize = true;
            this.bunifuCustomLabelSub2.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelSub2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelSub2.Location = new System.Drawing.Point(6, 101);
            this.bunifuCustomLabelSub2.Name = "bunifuCustomLabelSub2";
            this.bunifuCustomLabelSub2.Size = new System.Drawing.Size(59, 20);
            this.bunifuCustomLabelSub2.TabIndex = 8;
            this.bunifuCustomLabelSub2.Text = "子类别2";
            // 
            // bunifuCustomLabelname
            // 
            this.bunifuCustomLabelname.AutoSize = true;
            this.bunifuCustomLabelname.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelname.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelname.Location = new System.Drawing.Point(208, 96);
            this.bunifuCustomLabelname.Name = "bunifuCustomLabelname";
            this.bunifuCustomLabelname.Size = new System.Drawing.Size(37, 20);
            this.bunifuCustomLabelname.TabIndex = 8;
            this.bunifuCustomLabelname.Text = "命名";
            this.toolTip.SetToolTip(this.bunifuCustomLabelname, "区分同一电柜的不同仪表\r\n属于同一电柜不可重名\r\n属于不同电柜可以重名");
            // 
            // bunifuCustomLabelSub1
            // 
            this.bunifuCustomLabelSub1.AutoSize = true;
            this.bunifuCustomLabelSub1.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelSub1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelSub1.Location = new System.Drawing.Point(6, 61);
            this.bunifuCustomLabelSub1.Name = "bunifuCustomLabelSub1";
            this.bunifuCustomLabelSub1.Size = new System.Drawing.Size(59, 20);
            this.bunifuCustomLabelSub1.TabIndex = 8;
            this.bunifuCustomLabelSub1.Text = "子类别1";
            // 
            // bunifuCustomLabelX
            // 
            this.bunifuCustomLabelX.AutoSize = true;
            this.bunifuCustomLabelX.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabelX.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabelX.Location = new System.Drawing.Point(208, 15);
            this.bunifuCustomLabelX.Name = "bunifuCustomLabelX";
            this.bunifuCustomLabelX.Size = new System.Drawing.Size(18, 20);
            this.bunifuCustomLabelX.TabIndex = 8;
            this.bunifuCustomLabelX.Text = "X";
            // 
            // bunifuCustomLabeltype
            // 
            this.bunifuCustomLabeltype.AutoSize = true;
            this.bunifuCustomLabeltype.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bunifuCustomLabeltype.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.bunifuCustomLabeltype.Location = new System.Drawing.Point(6, 13);
            this.bunifuCustomLabeltype.Name = "bunifuCustomLabeltype";
            this.bunifuCustomLabeltype.Size = new System.Drawing.Size(65, 20);
            this.bunifuCustomLabeltype.TabIndex = 8;
            this.bunifuCustomLabeltype.Text = "仪器类别";
            // 
            // panelCreate
            // 
            this.panelCreate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelCreate.Controls.Add(this.bunifuTextboxCabin);
            this.panelCreate.Controls.Add(this.bunifuTextboxRoom);
            this.panelCreate.Controls.Add(this.bunifuTextboxFactory);
            this.panelCreate.Controls.Add(this.buttonCreateXML);
            this.panelCreate.Location = new System.Drawing.Point(3, 108);
            this.panelCreate.Name = "panelCreate";
            this.panelCreate.Size = new System.Drawing.Size(433, 62);
            this.panelCreate.TabIndex = 8;
            // 
            // bunifuTextboxCabin
            // 
            this.bunifuTextboxCabin.BackColor = System.Drawing.Color.Silver;
            this.bunifuTextboxCabin.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxCabin.BackgroundImage")));
            this.bunifuTextboxCabin.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.bunifuTextboxCabin.ForeColor = System.Drawing.Color.SeaGreen;
            this.bunifuTextboxCabin.Icon = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxCabin.Icon")));
            this.bunifuTextboxCabin.Location = new System.Drawing.Point(223, 10);
            this.bunifuTextboxCabin.Name = "bunifuTextboxCabin";
            this.bunifuTextboxCabin.Size = new System.Drawing.Size(104, 39);
            this.bunifuTextboxCabin.TabIndex = 0;
            this.bunifuTextboxCabin.text = "36号柜";
            // 
            // bunifuTextboxRoom
            // 
            this.bunifuTextboxRoom.BackColor = System.Drawing.Color.Silver;
            this.bunifuTextboxRoom.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxRoom.BackgroundImage")));
            this.bunifuTextboxRoom.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.bunifuTextboxRoom.ForeColor = System.Drawing.Color.SeaGreen;
            this.bunifuTextboxRoom.Icon = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxRoom.Icon")));
            this.bunifuTextboxRoom.Location = new System.Drawing.Point(113, 10);
            this.bunifuTextboxRoom.Name = "bunifuTextboxRoom";
            this.bunifuTextboxRoom.Size = new System.Drawing.Size(104, 39);
            this.bunifuTextboxRoom.TabIndex = 0;
            this.bunifuTextboxRoom.text = "1号间";
            // 
            // bunifuTextboxFactory
            // 
            this.bunifuTextboxFactory.BackColor = System.Drawing.Color.Silver;
            this.bunifuTextboxFactory.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxFactory.BackgroundImage")));
            this.bunifuTextboxFactory.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.bunifuTextboxFactory.ForeColor = System.Drawing.Color.SeaGreen;
            this.bunifuTextboxFactory.Icon = ((System.Drawing.Image)(resources.GetObject("bunifuTextboxFactory.Icon")));
            this.bunifuTextboxFactory.Location = new System.Drawing.Point(3, 10);
            this.bunifuTextboxFactory.Name = "bunifuTextboxFactory";
            this.bunifuTextboxFactory.Size = new System.Drawing.Size(104, 39);
            this.bunifuTextboxFactory.TabIndex = 0;
            this.bunifuTextboxFactory.text = "5号站";
            // 
            // buttonCreateXML
            // 
            this.buttonCreateXML.Font = new System.Drawing.Font("微软雅黑", 10F, System.Drawing.FontStyle.Bold);
            this.buttonCreateXML.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonCreateXML.Location = new System.Drawing.Point(348, 9);
            this.buttonCreateXML.Name = "buttonCreateXML";
            this.buttonCreateXML.Size = new System.Drawing.Size(80, 45);
            this.buttonCreateXML.TabIndex = 2;
            this.buttonCreateXML.Text = "创建";
            this.buttonCreateXML.UseVisualStyleBackColor = true;
            this.buttonCreateXML.Click += new System.EventHandler(this.buttonCreateXML_Click);
            // 
            // panelxmlpath
            // 
            this.panelxmlpath.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelxmlpath.Controls.Add(this.labelpath);
            this.panelxmlpath.Controls.Add(this.buttonxmlOpen);
            this.panelxmlpath.Controls.Add(this.textBoxXMLpath);
            this.panelxmlpath.Controls.Add(this.buttonxmlCreate);
            this.panelxmlpath.Location = new System.Drawing.Point(3, 3);
            this.panelxmlpath.Name = "panelxmlpath";
            this.panelxmlpath.Size = new System.Drawing.Size(433, 99);
            this.panelxmlpath.TabIndex = 4;
            // 
            // labelpath
            // 
            this.labelpath.AutoSize = true;
            this.labelpath.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelpath.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelpath.Location = new System.Drawing.Point(3, 10);
            this.labelpath.Name = "labelpath";
            this.labelpath.Size = new System.Drawing.Size(106, 21);
            this.labelpath.TabIndex = 1;
            this.labelpath.Text = "配置文件路径";
            // 
            // buttonxmlOpen
            // 
            this.buttonxmlOpen.Font = new System.Drawing.Font("微软雅黑", 20F);
            this.buttonxmlOpen.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonxmlOpen.Location = new System.Drawing.Point(182, 38);
            this.buttonxmlOpen.Name = "buttonxmlOpen";
            this.buttonxmlOpen.Size = new System.Drawing.Size(238, 52);
            this.buttonxmlOpen.TabIndex = 2;
            this.buttonxmlOpen.Text = "打开文件";
            this.buttonxmlOpen.UseVisualStyleBackColor = true;
            this.buttonxmlOpen.Click += new System.EventHandler(this.buttonxmlOpen_Click);
            // 
            // textBoxXMLpath
            // 
            this.textBoxXMLpath.Font = new System.Drawing.Font("Gadugi", 10F);
            this.textBoxXMLpath.Location = new System.Drawing.Point(115, 7);
            this.textBoxXMLpath.Name = "textBoxXMLpath";
            this.textBoxXMLpath.Size = new System.Drawing.Size(305, 25);
            this.textBoxXMLpath.TabIndex = 0;
            // 
            // buttonxmlCreate
            // 
            this.buttonxmlCreate.Font = new System.Drawing.Font("微软雅黑", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.buttonxmlCreate.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonxmlCreate.Location = new System.Drawing.Point(3, 40);
            this.buttonxmlCreate.Name = "buttonxmlCreate";
            this.buttonxmlCreate.Size = new System.Drawing.Size(119, 52);
            this.buttonxmlCreate.TabIndex = 2;
            this.buttonxmlCreate.Text = "创建";
            this.buttonxmlCreate.UseVisualStyleBackColor = true;
            this.buttonxmlCreate.Click += new System.EventHandler(this.buttonxmlCreate_Click);
            // 
            // panelROI
            // 
            this.panelROI.Controls.Add(this.panelSmallROIInfo);
            this.panelROI.Controls.Add(this.panelSmallROI);
            this.panelROI.Location = new System.Drawing.Point(3, 3);
            this.panelROI.Name = "panelROI";
            this.panelROI.Size = new System.Drawing.Size(744, 528);
            this.panelROI.TabIndex = 1;
            // 
            // panelSmallROIInfo
            // 
            this.panelSmallROIInfo.Controls.Add(this.buttonSmallROIROIchoose);
            this.panelSmallROIInfo.Controls.Add(this.buttonSmallROIImgChoose);
            this.panelSmallROIInfo.Controls.Add(this.panelSmallROIROIInfo);
            this.panelSmallROIInfo.Controls.Add(this.panelSmallROIMove);
            this.panelSmallROIInfo.Controls.Add(this.panelSmallROIImgInfo);
            this.panelSmallROIInfo.Location = new System.Drawing.Point(539, 1);
            this.panelSmallROIInfo.Name = "panelSmallROIInfo";
            this.panelSmallROIInfo.Size = new System.Drawing.Size(202, 525);
            this.panelSmallROIInfo.TabIndex = 2;
            // 
            // buttonSmallROIROIchoose
            // 
            this.buttonSmallROIROIchoose.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.buttonSmallROIROIchoose.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonSmallROIROIchoose.Location = new System.Drawing.Point(111, 454);
            this.buttonSmallROIROIchoose.Name = "buttonSmallROIROIchoose";
            this.buttonSmallROIROIchoose.Size = new System.Drawing.Size(89, 69);
            this.buttonSmallROIROIchoose.TabIndex = 3;
            this.buttonSmallROIROIchoose.Text = "ROI选择";
            this.buttonSmallROIROIchoose.UseVisualStyleBackColor = true;
            this.buttonSmallROIROIchoose.Click += new System.EventHandler(this.buttonSmallROIROIchoose_Click);
            // 
            // buttonSmallROIImgChoose
            // 
            this.buttonSmallROIImgChoose.BackColor = System.Drawing.Color.Transparent;
            this.buttonSmallROIImgChoose.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.buttonSmallROIImgChoose.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonSmallROIImgChoose.Location = new System.Drawing.Point(0, 451);
            this.buttonSmallROIImgChoose.Name = "buttonSmallROIImgChoose";
            this.buttonSmallROIImgChoose.Size = new System.Drawing.Size(96, 73);
            this.buttonSmallROIImgChoose.TabIndex = 3;
            this.buttonSmallROIImgChoose.Text = "选取图片";
            this.buttonSmallROIImgChoose.UseVisualStyleBackColor = false;
            this.buttonSmallROIImgChoose.Click += new System.EventHandler(this.buttonSmallROIImgChoose_Click);
            // 
            // panelSmallROIROIInfo
            // 
            this.panelSmallROIROIInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStopYValue);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStopY);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStopXValue);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStopX);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStartYValue);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStartY);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStartXValue);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoStart);
            this.panelSmallROIROIInfo.Controls.Add(this.labelROIInfoTitle);
            this.panelSmallROIROIInfo.Controls.Add(this.pictureBoxROIInfo);
            this.panelSmallROIROIInfo.Location = new System.Drawing.Point(3, 304);
            this.panelSmallROIROIInfo.Name = "panelSmallROIROIInfo";
            this.panelSmallROIROIInfo.Size = new System.Drawing.Size(197, 144);
            this.panelSmallROIROIInfo.TabIndex = 2;
            // 
            // labelROIInfoStopYValue
            // 
            this.labelROIInfoStopYValue.AutoSize = true;
            this.labelROIInfoStopYValue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStopYValue.ForeColor = System.Drawing.Color.Black;
            this.labelROIInfoStopYValue.Location = new System.Drawing.Point(93, 125);
            this.labelROIInfoStopYValue.Name = "labelROIInfoStopYValue";
            this.labelROIInfoStopYValue.Size = new System.Drawing.Size(15, 17);
            this.labelROIInfoStopYValue.TabIndex = 18;
            this.labelROIInfoStopYValue.Text = "0";
            // 
            // labelROIInfoStopY
            // 
            this.labelROIInfoStopY.AutoSize = true;
            this.labelROIInfoStopY.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStopY.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelROIInfoStopY.Location = new System.Drawing.Point(88, 97);
            this.labelROIInfoStopY.Name = "labelROIInfoStopY";
            this.labelROIInfoStopY.Size = new System.Drawing.Size(54, 17);
            this.labelROIInfoStopY.TabIndex = 17;
            this.labelROIInfoStopY.Text = "终点.Y：";
            // 
            // labelROIInfoStopXValue
            // 
            this.labelROIInfoStopXValue.AutoSize = true;
            this.labelROIInfoStopXValue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStopXValue.ForeColor = System.Drawing.Color.Black;
            this.labelROIInfoStopXValue.Location = new System.Drawing.Point(93, 70);
            this.labelROIInfoStopXValue.Name = "labelROIInfoStopXValue";
            this.labelROIInfoStopXValue.Size = new System.Drawing.Size(15, 17);
            this.labelROIInfoStopXValue.TabIndex = 16;
            this.labelROIInfoStopXValue.Text = "0";
            // 
            // labelROIInfoStopX
            // 
            this.labelROIInfoStopX.AutoSize = true;
            this.labelROIInfoStopX.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStopX.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelROIInfoStopX.Location = new System.Drawing.Point(88, 44);
            this.labelROIInfoStopX.Name = "labelROIInfoStopX";
            this.labelROIInfoStopX.Size = new System.Drawing.Size(55, 17);
            this.labelROIInfoStopX.TabIndex = 15;
            this.labelROIInfoStopX.Text = "终点.X：";
            // 
            // labelROIInfoStartYValue
            // 
            this.labelROIInfoStartYValue.AutoSize = true;
            this.labelROIInfoStartYValue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStartYValue.ForeColor = System.Drawing.Color.Black;
            this.labelROIInfoStartYValue.Location = new System.Drawing.Point(16, 125);
            this.labelROIInfoStartYValue.Name = "labelROIInfoStartYValue";
            this.labelROIInfoStartYValue.Size = new System.Drawing.Size(15, 17);
            this.labelROIInfoStartYValue.TabIndex = 14;
            this.labelROIInfoStartYValue.Text = "0";
            // 
            // labelROIInfoStartY
            // 
            this.labelROIInfoStartY.AutoSize = true;
            this.labelROIInfoStartY.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStartY.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelROIInfoStartY.Location = new System.Drawing.Point(4, 97);
            this.labelROIInfoStartY.Name = "labelROIInfoStartY";
            this.labelROIInfoStartY.Size = new System.Drawing.Size(54, 17);
            this.labelROIInfoStartY.TabIndex = 13;
            this.labelROIInfoStartY.Text = "起点.Y：";
            // 
            // labelROIInfoStartXValue
            // 
            this.labelROIInfoStartXValue.AutoSize = true;
            this.labelROIInfoStartXValue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStartXValue.ForeColor = System.Drawing.Color.Black;
            this.labelROIInfoStartXValue.Location = new System.Drawing.Point(16, 70);
            this.labelROIInfoStartXValue.Name = "labelROIInfoStartXValue";
            this.labelROIInfoStartXValue.Size = new System.Drawing.Size(15, 17);
            this.labelROIInfoStartXValue.TabIndex = 12;
            this.labelROIInfoStartXValue.Text = "0";
            // 
            // labelROIInfoStart
            // 
            this.labelROIInfoStart.AutoSize = true;
            this.labelROIInfoStart.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoStart.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelROIInfoStart.Location = new System.Drawing.Point(3, 44);
            this.labelROIInfoStart.Name = "labelROIInfoStart";
            this.labelROIInfoStart.Size = new System.Drawing.Size(55, 17);
            this.labelROIInfoStart.TabIndex = 10;
            this.labelROIInfoStart.Text = "起点.X：";
            // 
            // labelROIInfoTitle
            // 
            this.labelROIInfoTitle.AutoSize = true;
            this.labelROIInfoTitle.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelROIInfoTitle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelROIInfoTitle.Location = new System.Drawing.Point(37, 9);
            this.labelROIInfoTitle.Name = "labelROIInfoTitle";
            this.labelROIInfoTitle.Size = new System.Drawing.Size(71, 22);
            this.labelROIInfoTitle.TabIndex = 4;
            this.labelROIInfoTitle.Text = "ROI信息";
            // 
            // pictureBoxROIInfo
            // 
            this.pictureBoxROIInfo.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxROIInfo.Image")));
            this.pictureBoxROIInfo.Location = new System.Drawing.Point(-1, -1);
            this.pictureBoxROIInfo.Name = "pictureBoxROIInfo";
            this.pictureBoxROIInfo.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxROIInfo.TabIndex = 3;
            this.pictureBoxROIInfo.TabStop = false;
            // 
            // panelSmallROIMove
            // 
            this.panelSmallROIMove.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSmallROIMove.Controls.Add(this.labelChangInfoScaletimes);
            this.panelSmallROIMove.Controls.Add(this.labelImgnowwidthvalue);
            this.panelSmallROIMove.Controls.Add(this.labelImgnowheightvalue);
            this.panelSmallROIMove.Controls.Add(this.labelChangeInfoScale);
            this.panelSmallROIMove.Controls.Add(this.labelImgnowheight);
            this.panelSmallROIMove.Controls.Add(this.labelImgnowwidth);
            this.panelSmallROIMove.Controls.Add(this.labelChangeInfo);
            this.panelSmallROIMove.Controls.Add(this.pictureBoxChangeInfo);
            this.panelSmallROIMove.Location = new System.Drawing.Point(3, 154);
            this.panelSmallROIMove.Name = "panelSmallROIMove";
            this.panelSmallROIMove.Size = new System.Drawing.Size(197, 144);
            this.panelSmallROIMove.TabIndex = 1;
            // 
            // labelChangInfoScaletimes
            // 
            this.labelChangInfoScaletimes.AutoSize = true;
            this.labelChangInfoScaletimes.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelChangInfoScaletimes.ForeColor = System.Drawing.Color.Black;
            this.labelChangInfoScaletimes.Location = new System.Drawing.Point(93, 116);
            this.labelChangInfoScaletimes.Name = "labelChangInfoScaletimes";
            this.labelChangInfoScaletimes.Size = new System.Drawing.Size(15, 17);
            this.labelChangInfoScaletimes.TabIndex = 14;
            this.labelChangInfoScaletimes.Text = "0";
            // 
            // labelImgnowwidthvalue
            // 
            this.labelImgnowwidthvalue.AutoSize = true;
            this.labelImgnowwidthvalue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelImgnowwidthvalue.ForeColor = System.Drawing.Color.Black;
            this.labelImgnowwidthvalue.Location = new System.Drawing.Point(93, 83);
            this.labelImgnowwidthvalue.Name = "labelImgnowwidthvalue";
            this.labelImgnowwidthvalue.Size = new System.Drawing.Size(15, 17);
            this.labelImgnowwidthvalue.TabIndex = 13;
            this.labelImgnowwidthvalue.Text = "0";
            // 
            // labelImgnowheightvalue
            // 
            this.labelImgnowheightvalue.AutoSize = true;
            this.labelImgnowheightvalue.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelImgnowheightvalue.ForeColor = System.Drawing.Color.Black;
            this.labelImgnowheightvalue.Location = new System.Drawing.Point(93, 44);
            this.labelImgnowheightvalue.Name = "labelImgnowheightvalue";
            this.labelImgnowheightvalue.Size = new System.Drawing.Size(15, 17);
            this.labelImgnowheightvalue.TabIndex = 12;
            this.labelImgnowheightvalue.Text = "0";
            // 
            // labelChangeInfoScale
            // 
            this.labelChangeInfoScale.AutoSize = true;
            this.labelChangeInfoScale.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelChangeInfoScale.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelChangeInfoScale.Location = new System.Drawing.Point(3, 116);
            this.labelChangeInfoScale.Name = "labelChangeInfoScale";
            this.labelChangeInfoScale.Size = new System.Drawing.Size(68, 17);
            this.labelChangeInfoScale.TabIndex = 11;
            this.labelChangeInfoScale.Text = "缩放倍数：";
            // 
            // labelImgnowheight
            // 
            this.labelImgnowheight.AutoSize = true;
            this.labelImgnowheight.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelImgnowheight.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelImgnowheight.Location = new System.Drawing.Point(3, 83);
            this.labelImgnowheight.Name = "labelImgnowheight";
            this.labelImgnowheight.Size = new System.Drawing.Size(68, 17);
            this.labelImgnowheight.TabIndex = 10;
            this.labelImgnowheight.Text = "当前高度：";
            // 
            // labelImgnowwidth
            // 
            this.labelImgnowwidth.AutoSize = true;
            this.labelImgnowwidth.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelImgnowwidth.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelImgnowwidth.Location = new System.Drawing.Point(3, 44);
            this.labelImgnowwidth.Name = "labelImgnowwidth";
            this.labelImgnowwidth.Size = new System.Drawing.Size(68, 17);
            this.labelImgnowwidth.TabIndex = 9;
            this.labelImgnowwidth.Text = "当前宽度：";
            // 
            // labelChangeInfo
            // 
            this.labelChangeInfo.AutoSize = true;
            this.labelChangeInfo.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelChangeInfo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelChangeInfo.Location = new System.Drawing.Point(37, 9);
            this.labelChangeInfo.Name = "labelChangeInfo";
            this.labelChangeInfo.Size = new System.Drawing.Size(106, 22);
            this.labelChangeInfo.TabIndex = 3;
            this.labelChangeInfo.Text = "图像缩放移动";
            // 
            // pictureBoxChangeInfo
            // 
            this.pictureBoxChangeInfo.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxChangeInfo.Image")));
            this.pictureBoxChangeInfo.Location = new System.Drawing.Point(-1, -1);
            this.pictureBoxChangeInfo.Name = "pictureBoxChangeInfo";
            this.pictureBoxChangeInfo.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxChangeInfo.TabIndex = 2;
            this.pictureBoxChangeInfo.TabStop = false;
            // 
            // panelSmallROIImgInfo
            // 
            this.panelSmallROIImgInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSmallROIImgInfo.Controls.Add(this.labelSrcImgInfoWidth);
            this.panelSmallROIImgInfo.Controls.Add(this.labelSrcImgInfoHeight);
            this.panelSmallROIImgInfo.Controls.Add(this.labelSrcImgInfoWidthTitle);
            this.panelSmallROIImgInfo.Controls.Add(this.labelSrcImgInfoHeightTitle);
            this.panelSmallROIImgInfo.Controls.Add(this.labelImgInfoTitle);
            this.panelSmallROIImgInfo.Controls.Add(this.pictureBoxSrcImgInfo);
            this.panelSmallROIImgInfo.Location = new System.Drawing.Point(3, 3);
            this.panelSmallROIImgInfo.Name = "panelSmallROIImgInfo";
            this.panelSmallROIImgInfo.Size = new System.Drawing.Size(196, 145);
            this.panelSmallROIImgInfo.TabIndex = 0;
            // 
            // labelSrcImgInfoWidth
            // 
            this.labelSrcImgInfoWidth.AutoSize = true;
            this.labelSrcImgInfoWidth.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelSrcImgInfoWidth.ForeColor = System.Drawing.Color.Black;
            this.labelSrcImgInfoWidth.Location = new System.Drawing.Point(93, 83);
            this.labelSrcImgInfoWidth.Name = "labelSrcImgInfoWidth";
            this.labelSrcImgInfoWidth.Size = new System.Drawing.Size(15, 17);
            this.labelSrcImgInfoWidth.TabIndex = 6;
            this.labelSrcImgInfoWidth.Text = "0";
            // 
            // labelSrcImgInfoHeight
            // 
            this.labelSrcImgInfoHeight.AutoSize = true;
            this.labelSrcImgInfoHeight.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelSrcImgInfoHeight.ForeColor = System.Drawing.Color.Black;
            this.labelSrcImgInfoHeight.Location = new System.Drawing.Point(93, 50);
            this.labelSrcImgInfoHeight.Name = "labelSrcImgInfoHeight";
            this.labelSrcImgInfoHeight.Size = new System.Drawing.Size(15, 17);
            this.labelSrcImgInfoHeight.TabIndex = 5;
            this.labelSrcImgInfoHeight.Text = "0";
            // 
            // labelSrcImgInfoWidthTitle
            // 
            this.labelSrcImgInfoWidthTitle.AutoSize = true;
            this.labelSrcImgInfoWidthTitle.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelSrcImgInfoWidthTitle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelSrcImgInfoWidthTitle.Location = new System.Drawing.Point(3, 83);
            this.labelSrcImgInfoWidthTitle.Name = "labelSrcImgInfoWidthTitle";
            this.labelSrcImgInfoWidthTitle.Size = new System.Drawing.Size(68, 17);
            this.labelSrcImgInfoWidthTitle.TabIndex = 4;
            this.labelSrcImgInfoWidthTitle.Text = "源图宽度：";
            // 
            // labelSrcImgInfoHeightTitle
            // 
            this.labelSrcImgInfoHeightTitle.AutoSize = true;
            this.labelSrcImgInfoHeightTitle.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelSrcImgInfoHeightTitle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelSrcImgInfoHeightTitle.Location = new System.Drawing.Point(3, 50);
            this.labelSrcImgInfoHeightTitle.Name = "labelSrcImgInfoHeightTitle";
            this.labelSrcImgInfoHeightTitle.Size = new System.Drawing.Size(68, 17);
            this.labelSrcImgInfoHeightTitle.TabIndex = 3;
            this.labelSrcImgInfoHeightTitle.Text = "源图高度：";
            // 
            // labelImgInfoTitle
            // 
            this.labelImgInfoTitle.AutoSize = true;
            this.labelImgInfoTitle.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelImgInfoTitle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelImgInfoTitle.Location = new System.Drawing.Point(37, 9);
            this.labelImgInfoTitle.Name = "labelImgInfoTitle";
            this.labelImgInfoTitle.Size = new System.Drawing.Size(106, 22);
            this.labelImgInfoTitle.TabIndex = 2;
            this.labelImgInfoTitle.Text = "图像详细信息";
            // 
            // pictureBoxSrcImgInfo
            // 
            this.pictureBoxSrcImgInfo.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxSrcImgInfo.Image")));
            this.pictureBoxSrcImgInfo.Location = new System.Drawing.Point(-1, -1);
            this.pictureBoxSrcImgInfo.Name = "pictureBoxSrcImgInfo";
            this.pictureBoxSrcImgInfo.Size = new System.Drawing.Size(32, 32);
            this.pictureBoxSrcImgInfo.TabIndex = 1;
            this.pictureBoxSrcImgInfo.TabStop = false;
            // 
            // panelSmallROI
            // 
            this.panelSmallROI.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSmallROI.Controls.Add(this.pictureBoxSmallROI);
            this.panelSmallROI.Location = new System.Drawing.Point(0, 0);
            this.panelSmallROI.Name = "panelSmallROI";
            this.panelSmallROI.Size = new System.Drawing.Size(533, 525);
            this.panelSmallROI.TabIndex = 1;
            // 
            // pictureBoxSmallROI
            // 
            this.pictureBoxSmallROI.Location = new System.Drawing.Point(0, 0);
            this.pictureBoxSmallROI.Name = "pictureBoxSmallROI";
            this.pictureBoxSmallROI.Size = new System.Drawing.Size(531, 523);
            this.pictureBoxSmallROI.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxSmallROI.TabIndex = 0;
            this.pictureBoxSmallROI.TabStop = false;
            this.pictureBoxSmallROI.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBoxSmallROI_Paint);
            this.pictureBoxSmallROI.DoubleClick += new System.EventHandler(this.pictureBoxSmallROI_DoubleClick);
            this.pictureBoxSmallROI.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSmallROI_MouseDown);
            this.pictureBoxSmallROI.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSmallROI_MouseMove);
            this.pictureBoxSmallROI.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSmallROI_MouseUp);
            this.pictureBoxSmallROI.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.pictureBoxSmallROI_MouseWheel);
            // 
            // tabInfo
            // 
            this.tabInfo.BackColor = System.Drawing.Color.AliceBlue;
            this.tabInfo.ImageKey = "Info_96px.png";
            this.tabInfo.Location = new System.Drawing.Point(4, 100);
            this.tabInfo.Name = "tabInfo";
            this.tabInfo.Padding = new System.Windows.Forms.Padding(3);
            this.tabInfo.Size = new System.Drawing.Size(1654, 944);
            this.tabInfo.TabIndex = 3;
            // 
            // tabDebug
            // 
            this.tabDebug.BackColor = System.Drawing.Color.Transparent;
            this.tabDebug.ImageIndex = 0;
            this.tabDebug.Location = new System.Drawing.Point(4, 100);
            this.tabDebug.Name = "tabDebug";
            this.tabDebug.Padding = new System.Windows.Forms.Padding(3);
            this.tabDebug.Size = new System.Drawing.Size(1654, 944);
            this.tabDebug.TabIndex = 4;
            // 
            // imageListTab
            // 
            this.imageListTab.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListTab.ImageStream")));
            this.imageListTab.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListTab.Images.SetKeyName(0, "Code_96px.png");
            this.imageListTab.Images.SetKeyName(1, "Combo Chart_96px.png");
            this.imageListTab.Images.SetKeyName(2, "Home_96px.png");
            this.imageListTab.Images.SetKeyName(3, "Info_96px.png");
            this.imageListTab.Images.SetKeyName(4, "Search_96px.png");
            this.imageListTab.Images.SetKeyName(5, "Settings_96px.png");
            // 
            // menuStrip
            // 
            this.menuStrip.BackColor = System.Drawing.Color.DarkGray;
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.编辑EToolStripMenuItem,
            this.工具TToolStripMenuItem,
            this.帮助HToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(1920, 25);
            this.menuStrip.TabIndex = 3;
            this.menuStrip.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建NToolStripMenuItem,
            this.打开OToolStripMenuItem,
            this.toolStripSeparator,
            this.保存SToolStripMenuItem,
            this.另存为AToolStripMenuItem,
            this.toolStripSeparator1,
            this.打印PToolStripMenuItem,
            this.打印预览VToolStripMenuItem,
            this.toolStripSeparator2,
            this.ExitXToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(58, 21);
            this.文件FToolStripMenuItem.Text = "文件(&F)";
            // 
            // 新建NToolStripMenuItem
            // 
            this.新建NToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("新建NToolStripMenuItem.Image")));
            this.新建NToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.新建NToolStripMenuItem.Name = "新建NToolStripMenuItem";
            this.新建NToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.新建NToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.新建NToolStripMenuItem.Text = "新建(&N)";
            // 
            // 打开OToolStripMenuItem
            // 
            this.打开OToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("打开OToolStripMenuItem.Image")));
            this.打开OToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.打开OToolStripMenuItem.Name = "打开OToolStripMenuItem";
            this.打开OToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.打开OToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.打开OToolStripMenuItem.Text = "打开(&O)";
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(162, 6);
            // 
            // 保存SToolStripMenuItem
            // 
            this.保存SToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("保存SToolStripMenuItem.Image")));
            this.保存SToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.保存SToolStripMenuItem.Name = "保存SToolStripMenuItem";
            this.保存SToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.保存SToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.保存SToolStripMenuItem.Text = "保存(&S)";
            // 
            // 另存为AToolStripMenuItem
            // 
            this.另存为AToolStripMenuItem.Name = "另存为AToolStripMenuItem";
            this.另存为AToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.另存为AToolStripMenuItem.Text = "另存为(&A)";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(162, 6);
            // 
            // 打印PToolStripMenuItem
            // 
            this.打印PToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("打印PToolStripMenuItem.Image")));
            this.打印PToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.打印PToolStripMenuItem.Name = "打印PToolStripMenuItem";
            this.打印PToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.打印PToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.打印PToolStripMenuItem.Text = "打印(&P)";
            // 
            // 打印预览VToolStripMenuItem
            // 
            this.打印预览VToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("打印预览VToolStripMenuItem.Image")));
            this.打印预览VToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.打印预览VToolStripMenuItem.Name = "打印预览VToolStripMenuItem";
            this.打印预览VToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.打印预览VToolStripMenuItem.Text = "打印预览(&V)";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(162, 6);
            // 
            // ExitXToolStripMenuItem
            // 
            this.ExitXToolStripMenuItem.Name = "ExitXToolStripMenuItem";
            this.ExitXToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.ExitXToolStripMenuItem.Text = "退出(&X)";
            this.ExitXToolStripMenuItem.Click += new System.EventHandler(this.ExitXToolStripMenuItem_Click);
            // 
            // 编辑EToolStripMenuItem
            // 
            this.编辑EToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.撤消UToolStripMenuItem,
            this.重复RToolStripMenuItem,
            this.toolStripSeparator3,
            this.剪切TToolStripMenuItem,
            this.复制CToolStripMenuItem,
            this.粘贴PToolStripMenuItem,
            this.toolStripSeparator4,
            this.全选AToolStripMenuItem});
            this.编辑EToolStripMenuItem.Name = "编辑EToolStripMenuItem";
            this.编辑EToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.编辑EToolStripMenuItem.Text = "编辑(&E)";
            // 
            // 撤消UToolStripMenuItem
            // 
            this.撤消UToolStripMenuItem.Name = "撤消UToolStripMenuItem";
            this.撤消UToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.撤消UToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.撤消UToolStripMenuItem.Text = "撤消(&U)";
            // 
            // 重复RToolStripMenuItem
            // 
            this.重复RToolStripMenuItem.Name = "重复RToolStripMenuItem";
            this.重复RToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.重复RToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.重复RToolStripMenuItem.Text = "重复(&R)";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(158, 6);
            // 
            // 剪切TToolStripMenuItem
            // 
            this.剪切TToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("剪切TToolStripMenuItem.Image")));
            this.剪切TToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.剪切TToolStripMenuItem.Name = "剪切TToolStripMenuItem";
            this.剪切TToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.剪切TToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.剪切TToolStripMenuItem.Text = "剪切(&T)";
            // 
            // 复制CToolStripMenuItem
            // 
            this.复制CToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("复制CToolStripMenuItem.Image")));
            this.复制CToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
            this.复制CToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.复制CToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.复制CToolStripMenuItem.Text = "复制(&C)";
            // 
            // 粘贴PToolStripMenuItem
            // 
            this.粘贴PToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("粘贴PToolStripMenuItem.Image")));
            this.粘贴PToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.粘贴PToolStripMenuItem.Name = "粘贴PToolStripMenuItem";
            this.粘贴PToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.粘贴PToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.粘贴PToolStripMenuItem.Text = "粘贴(&P)";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(158, 6);
            // 
            // 全选AToolStripMenuItem
            // 
            this.全选AToolStripMenuItem.Name = "全选AToolStripMenuItem";
            this.全选AToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.全选AToolStripMenuItem.Text = "全选(&A)";
            // 
            // 工具TToolStripMenuItem
            // 
            this.工具TToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.选项OToolStripMenuItem,
            this.xMLConfigurePlusToolStripMenuItem});
            this.工具TToolStripMenuItem.Name = "工具TToolStripMenuItem";
            this.工具TToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.工具TToolStripMenuItem.Text = "工具(&T)";
            // 
            // 选项OToolStripMenuItem
            // 
            this.选项OToolStripMenuItem.Name = "选项OToolStripMenuItem";
            this.选项OToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.选项OToolStripMenuItem.Text = "选项(&O)";
            // 
            // xMLConfigurePlusToolStripMenuItem
            // 
            this.xMLConfigurePlusToolStripMenuItem.Name = "xMLConfigurePlusToolStripMenuItem";
            this.xMLConfigurePlusToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.xMLConfigurePlusToolStripMenuItem.Text = "XML配置工具(&P)";
            this.xMLConfigurePlusToolStripMenuItem.Click += new System.EventHandler(this.xMLConfigurePluasToolStripMenuItem_Click);
            // 
            // 帮助HToolStripMenuItem
            // 
            this.帮助HToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.内容CToolStripMenuItem,
            this.索引IToolStripMenuItem,
            this.搜索SToolStripMenuItem,
            this.toolStripSeparator5,
            this.关于AToolStripMenuItem});
            this.帮助HToolStripMenuItem.Name = "帮助HToolStripMenuItem";
            this.帮助HToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.帮助HToolStripMenuItem.Text = "帮助(&H)";
            // 
            // 内容CToolStripMenuItem
            // 
            this.内容CToolStripMenuItem.Name = "内容CToolStripMenuItem";
            this.内容CToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.内容CToolStripMenuItem.Text = "内容(&C)";
            // 
            // 索引IToolStripMenuItem
            // 
            this.索引IToolStripMenuItem.Name = "索引IToolStripMenuItem";
            this.索引IToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.索引IToolStripMenuItem.Text = "索引(&I)";
            // 
            // 搜索SToolStripMenuItem
            // 
            this.搜索SToolStripMenuItem.Name = "搜索SToolStripMenuItem";
            this.搜索SToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.搜索SToolStripMenuItem.Text = "搜索(&S)";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(122, 6);
            // 
            // 关于AToolStripMenuItem
            // 
            this.关于AToolStripMenuItem.Name = "关于AToolStripMenuItem";
            this.关于AToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.关于AToolStripMenuItem.Text = "关于(&A)...";
            // 
            // panelSide
            // 
            this.panelSide.BackColor = System.Drawing.Color.LightGray;
            this.panelSide.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSide.Controls.Add(this.panelLog);
            this.panelSide.Controls.Add(this.panelJournal);
            this.panelSide.Controls.Add(this.panelClock);
            this.panelSide.Location = new System.Drawing.Point(0, 28);
            this.panelSide.Name = "panelSide";
            this.panelSide.Size = new System.Drawing.Size(252, 1044);
            this.panelSide.TabIndex = 1;
            // 
            // panelLog
            // 
            this.panelLog.Controls.Add(this.labelJournal);
            this.panelLog.Controls.Add(this.pictureBoxLog);
            this.panelLog.Location = new System.Drawing.Point(3, 628);
            this.panelLog.Name = "panelLog";
            this.panelLog.Size = new System.Drawing.Size(244, 412);
            this.panelLog.TabIndex = 2;
            // 
            // labelJournal
            // 
            this.labelJournal.AutoSize = true;
            this.labelJournal.Font = new System.Drawing.Font("微软雅黑", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelJournal.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelJournal.Location = new System.Drawing.Point(105, 53);
            this.labelJournal.Name = "labelJournal";
            this.labelJournal.Size = new System.Drawing.Size(123, 36);
            this.labelJournal.TabIndex = 2;
            this.labelJournal.Text = "工作日志";
            // 
            // pictureBoxLog
            // 
            this.pictureBoxLog.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxLog.Image")));
            this.pictureBoxLog.Location = new System.Drawing.Point(0, 3);
            this.pictureBoxLog.Name = "pictureBoxLog";
            this.pictureBoxLog.Size = new System.Drawing.Size(96, 96);
            this.pictureBoxLog.TabIndex = 1;
            this.pictureBoxLog.TabStop = false;
            // 
            // panelJournal
            // 
            this.panelJournal.Controls.Add(this.buttonToImage);
            this.panelJournal.Controls.Add(this.buttonGototakephoto);
            this.panelJournal.Controls.Add(this.buttonTest);
            this.panelJournal.Controls.Add(this.labelschedule);
            this.panelJournal.Controls.Add(this.pictureBoxjournal);
            this.panelJournal.Location = new System.Drawing.Point(3, 160);
            this.panelJournal.Name = "panelJournal";
            this.panelJournal.Size = new System.Drawing.Size(244, 462);
            this.panelJournal.TabIndex = 1;
            // 
            // buttonToImage
            // 
            this.buttonToImage.Location = new System.Drawing.Point(76, 217);
            this.buttonToImage.Name = "buttonToImage";
            this.buttonToImage.Size = new System.Drawing.Size(75, 23);
            this.buttonToImage.TabIndex = 5;
            this.buttonToImage.Text = "手动模式";
            this.buttonToImage.UseVisualStyleBackColor = true;
            this.buttonToImage.Click += new System.EventHandler(this.buttonToImage_Click);
            // 
            // buttonGototakephoto
            // 
            this.buttonGototakephoto.Location = new System.Drawing.Point(76, 161);
            this.buttonGototakephoto.Name = "buttonGototakephoto";
            this.buttonGototakephoto.Size = new System.Drawing.Size(90, 35);
            this.buttonGototakephoto.TabIndex = 4;
            this.buttonGototakephoto.Text = "重新拍照";
            this.buttonGototakephoto.UseVisualStyleBackColor = true;
            this.buttonGototakephoto.Click += new System.EventHandler(this.buttonGototakephoto_Click);
            // 
            // buttonTest
            // 
            this.buttonTest.AutoSize = true;
            this.buttonTest.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.buttonTest.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.buttonTest.Location = new System.Drawing.Point(0, 118);
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Size = new System.Drawing.Size(244, 37);
            this.buttonTest.TabIndex = 3;
            this.buttonTest.Text = "打开XML进行测试";
            this.buttonTest.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolTip.SetToolTip(this.buttonTest, "手动进行测试，研究流程");
            this.buttonTest.UseVisualStyleBackColor = true;
            this.buttonTest.Click += new System.EventHandler(this.buttonTest_Click);
            // 
            // labelschedule
            // 
            this.labelschedule.AutoSize = true;
            this.labelschedule.Font = new System.Drawing.Font("微软雅黑", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelschedule.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelschedule.Location = new System.Drawing.Point(105, 49);
            this.labelschedule.Name = "labelschedule";
            this.labelschedule.Size = new System.Drawing.Size(123, 36);
            this.labelschedule.TabIndex = 1;
            this.labelschedule.Text = "巡检计划";
            // 
            // pictureBoxjournal
            // 
            this.pictureBoxjournal.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxjournal.Image")));
            this.pictureBoxjournal.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxjournal.Name = "pictureBoxjournal";
            this.pictureBoxjournal.Size = new System.Drawing.Size(96, 96);
            this.pictureBoxjournal.TabIndex = 0;
            this.pictureBoxjournal.TabStop = false;
            // 
            // panelClock
            // 
            this.panelClock.BackColor = System.Drawing.Color.Transparent;
            this.panelClock.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelClock.Controls.Add(this.labelDate);
            this.panelClock.Controls.Add(this.labelWeek);
            this.panelClock.Controls.Add(this.labelSecond);
            this.panelClock.Controls.Add(this.labelTime);
            this.panelClock.Location = new System.Drawing.Point(3, 3);
            this.panelClock.Name = "panelClock";
            this.panelClock.Size = new System.Drawing.Size(244, 151);
            this.panelClock.TabIndex = 0;
            // 
            // labelDate
            // 
            this.labelDate.AutoSize = true;
            this.labelDate.BackColor = System.Drawing.Color.Transparent;
            this.labelDate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelDate.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelDate.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelDate.Location = new System.Drawing.Point(120, 115);
            this.labelDate.Name = "labelDate";
            this.labelDate.Size = new System.Drawing.Size(121, 22);
            this.labelDate.TabIndex = 3;
            this.labelDate.Text = "0000-00-00";
            // 
            // labelWeek
            // 
            this.labelWeek.AutoSize = true;
            this.labelWeek.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelWeek.Font = new System.Drawing.Font("黑体", 25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelWeek.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelWeek.Location = new System.Drawing.Point(8, 101);
            this.labelWeek.Name = "labelWeek";
            this.labelWeek.Size = new System.Drawing.Size(119, 36);
            this.labelWeek.TabIndex = 2;
            this.labelWeek.Text = "星期一";
            // 
            // labelSecond
            // 
            this.labelSecond.AutoSize = true;
            this.labelSecond.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelSecond.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelSecond.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelSecond.Location = new System.Drawing.Point(181, 43);
            this.labelSecond.Name = "labelSecond";
            this.labelSecond.Size = new System.Drawing.Size(46, 33);
            this.labelSecond.TabIndex = 1;
            this.labelSecond.Text = "00";
            // 
            // labelTime
            // 
            this.labelTime.AutoSize = true;
            this.labelTime.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelTime.Font = new System.Drawing.Font("黑体", 60F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Pixel, ((byte)(134)));
            this.labelTime.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(110)))), ((int)(((byte)(80)))));
            this.labelTime.Location = new System.Drawing.Point(8, 14);
            this.labelTime.Name = "labelTime";
            this.labelTime.Size = new System.Drawing.Size(182, 62);
            this.labelTime.TabIndex = 0;
            this.labelTime.Text = "00:00";
            // 
            // timerClock
            // 
            this.timerClock.Enabled = true;
            this.timerClock.Interval = 1000;
            this.timerClock.Tick += new System.EventHandler(this.timerClock_Tick);
            // 
            // contextMenuStripDataGrid
            // 
            this.contextMenuStripDataGrid.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemDelete});
            this.contextMenuStripDataGrid.Name = "contextMenuStripDataGrid";
            this.contextMenuStripDataGrid.Size = new System.Drawing.Size(101, 26);
            // 
            // toolStripMenuItemDelete
            // 
            this.toolStripMenuItemDelete.Name = "toolStripMenuItemDelete";
            this.toolStripMenuItemDelete.Size = new System.Drawing.Size(100, 22);
            this.toolStripMenuItemDelete.Text = "删除";
            this.toolStripMenuItemDelete.Click += new System.EventHandler(this.toolStripMenuItemDelete_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(238)))), ((int)(((byte)(238)))), ((int)(((byte)(238)))));
            this.ClientSize = new System.Drawing.Size(1920, 1080);
            this.ControlBox = false;
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.panelSide);
            this.Controls.Add(this.menuStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainWindow";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MainWindow";
            this.Load += new System.EventHandler(this.MainWindowLoad);
            this.tabControl.ResumeLayout(false);
            this.tabHome.ResumeLayout(false);
            this.panelResult.ResumeLayout(false);
            this.tabControlResult.ResumeLayout(false);
            this.tabResultData.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDetect)).EndInit();
            this.tabResultMatter.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDetail)).EndInit();
            this.tabResultAlarm.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAlarm)).EndInit();
            this.panelStatus.ResumeLayout(false);
            this.panelProcess.ResumeLayout(false);
            this.panelProcess.PerformLayout();
            this.panelstatusDetect.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxProcess)).EndInit();
            this.panelLocation.ResumeLayout(false);
            this.panelLocation.PerformLayout();
            this.panelLocationDetail.ResumeLayout(false);
            this.panelLocationDetail.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCab)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxRom)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxFac)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxlocation)).EndInit();
            this.panelImagearea.ResumeLayout(false);
            this.panelvideoPlayer.ResumeLayout(false);
            this.panelCameraOperate.ResumeLayout(false);
            this.panelImgProcess.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxProcessed)).EndInit();
            this.panelImgSource.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSource)).EndInit();
            this.tabChart.ResumeLayout(false);
            this.tabControlDatabase.ResumeLayout(false);
            this.tabPageDBadvanced.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAdvancedSQL)).EndInit();
            this.paneldevicetree.ResumeLayout(false);
            this.paneldate.ResumeLayout(false);
            this.paneldate.PerformLayout();
            this.tabSetting.ResumeLayout(false);
            this.panelXMLConfig.ResumeLayout(false);
            this.panelXML.ResumeLayout(false);
            this.paneldata.ResumeLayout(false);
            this.panelfordatause.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.bunifuImageButtonRefresh)).EndInit();
            this.panelforgridview.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.panelAdd.ResumeLayout(false);
            this.panelAdd.PerformLayout();
            this.panelknob.ResumeLayout(false);
            this.panelknob.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownknobLow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKnobHigh)).EndInit();
            this.panelpointer.ResumeLayout(false);
            this.panelpointer.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPointerhigh)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownpointerLow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownnum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownheight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStartY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownwidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownStartX)).EndInit();
            this.panelCreate.ResumeLayout(false);
            this.panelxmlpath.ResumeLayout(false);
            this.panelxmlpath.PerformLayout();
            this.panelROI.ResumeLayout(false);
            this.panelSmallROIInfo.ResumeLayout(false);
            this.panelSmallROIROIInfo.ResumeLayout(false);
            this.panelSmallROIROIInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxROIInfo)).EndInit();
            this.panelSmallROIMove.ResumeLayout(false);
            this.panelSmallROIMove.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxChangeInfo)).EndInit();
            this.panelSmallROIImgInfo.ResumeLayout(false);
            this.panelSmallROIImgInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSrcImgInfo)).EndInit();
            this.panelSmallROI.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxSmallROI)).EndInit();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.panelSide.ResumeLayout(false);
            this.panelLog.ResumeLayout(false);
            this.panelLog.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLog)).EndInit();
            this.panelJournal.ResumeLayout(false);
            this.panelJournal.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxjournal)).EndInit();
            this.panelClock.ResumeLayout(false);
            this.panelClock.PerformLayout();
            this.contextMenuStripDataGrid.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabChart;
        private System.Windows.Forms.TabPage tabSetting;
        private System.Windows.Forms.TabPage tabInfo;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem 文件FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新建NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开OToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripMenuItem 保存SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存为AToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem 打印PToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打印预览VToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem ExitXToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 编辑EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 撤消UToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 重复RToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem 剪切TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 复制CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 粘贴PToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem 全选AToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 工具TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 选项OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 内容CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 索引IToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 搜索SToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem;
        private System.Windows.Forms.ImageList imageListTab;
        private System.Windows.Forms.TabPage tabHome;
        private System.Windows.Forms.Panel panelImagearea;
        private System.Windows.Forms.Panel panelImgProcess;
        private System.Windows.Forms.PictureBox pictureBoxProcessed;
        private System.Windows.Forms.Panel panelImgSource;
        private System.Windows.Forms.PictureBox pictureBoxSource;
        private System.Windows.Forms.Panel panelSide;
        private System.Windows.Forms.Panel panelClock;
        private System.Windows.Forms.Label labelTime;
        private System.Windows.Forms.Label labelWeek;
        private System.Windows.Forms.Label labelSecond;
        private System.Windows.Forms.Label labelDate;
        private System.Windows.Forms.Timer timerClock;
        private System.Windows.Forms.Panel panelJournal;
        private System.Windows.Forms.Panel panelResult;
        private System.Windows.Forms.TabControl tabControlResult;
        private System.Windows.Forms.TabPage tabResultData;
        private System.Windows.Forms.TabPage tabResultMatter;
        private System.Windows.Forms.TabPage tabResultAlarm;
        private System.Windows.Forms.Panel panelStatus;
        private System.Windows.Forms.TabPage tabDebug;
        private System.Windows.Forms.ImageList imageListx32;
        private System.Windows.Forms.DataGridView dataGridViewDetect;
        private System.Windows.Forms.DataGridView dataGridViewDetail;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumDetailNO;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumDetailTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumDetailLevel;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumDetailInfo;
        private System.Windows.Forms.DataGridView dataGridViewAlarm;
        private System.Windows.Forms.Panel panelProcess;
        private System.Windows.Forms.Panel panelLocation;
        private System.Windows.Forms.Label labelLoca;
        private System.Windows.Forms.PictureBox pictureBoxlocation;
        private System.Windows.Forms.Label labelProcess;
        private System.Windows.Forms.PictureBox pictureBoxProcess;
        private CircularProgressBar.CircularProgressBar circularProgressBarLocation;
        private System.Windows.Forms.Panel panelLocationDetail;
        private System.Windows.Forms.Label labelCab;
        private System.Windows.Forms.Label labelRom;
        private System.Windows.Forms.Label labelFac;
        private System.Windows.Forms.PictureBox pictureBoxCab;
        private System.Windows.Forms.PictureBox pictureBoxRom;
        private System.Windows.Forms.PictureBox pictureBoxFac;
        private CircularProgressBar.CircularProgressBar circularProgressBarprocess;
        private System.Windows.Forms.Panel panelstatusDetect;
        private System.Windows.Forms.Label labelbarprocess;
        private System.Windows.Forms.DataGridViewTextBoxColumn CloumAlertNO;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertDevice;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertType;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertLevel;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertContent;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumAlertConfirm;
        private System.Windows.Forms.DataGridView dataGridViewStatus;
        private System.Windows.Forms.Label labelschedule;
        private System.Windows.Forms.PictureBox pictureBoxjournal;
        private System.Windows.Forms.Panel panelLog;
        private System.Windows.Forms.Label labelJournal;
        private System.Windows.Forms.PictureBox pictureBoxLog;
        private Button buttonTest;
        private ToolStripMenuItem xMLConfigurePlusToolStripMenuItem;
        private ToolTip toolTip;
        private DataGridViewTextBoxColumn ColumDetectName;
        private DataGridViewTextBoxColumn ColumDetectValue;
        private TabControl tabControlDatabase;
        private TabPage tabPageDBadvanced;
        private TabPage tabPageDBDevicequery;
        private TabPage tabPageDBSelfAlarm;
        private ImageList imageListDB;
        private Label labeladvancedDate;
        private DateTimePicker dateTimePickeradvancedStop;
        private DateTimePicker dateTimePickerAdvancedStart;
        private Panel paneldevicetree;
        private TreeView treeViewAdvanced;
        private Panel paneldate;
        private Panel panel1;
        private DataGridView dataGridViewAdvancedSQL;
        private DataGridViewTextBoxColumn roomName;
        private DataGridViewTextBoxColumn CabinName;
        private DataGridViewTextBoxColumn DeviceName;
        private DataGridViewTextBoxColumn DeviceClass;
        private DataGridViewTextBoxColumn DetectResult;
        private DataGridViewTextBoxColumn DetectAlarm;
        private DataGridViewTextBoxColumn DetectDateTime;
        private Panel panelvideoPlayer;
        private AForge.Controls.VideoSourcePlayer videoSourcePlayer;
        private Panel panelCameraOperate;
        private Button buttonCloseCamera;
        private Button buttonopenCamera;
        private ComboBox comboBoxCameraChoose;
        private Button buttonRefreshCameras;
        private Button buttonCapture;
        private Button buttonGototakephoto;
        private Button buttonvideoCap;
        private DataGridViewTextBoxColumn id;
        private DataGridViewTextBoxColumn time;
        private DataGridViewTextBoxColumn device;
        private DataGridViewTextBoxColumn result;
        private DataGridViewTextBoxColumn alert;
        private Button buttonToImage;
        private Panel panelXMLConfig;
        private Panel panelROI;
        private Panel panelSmallROIInfo;
        private Button buttonSmallROIROIchoose;
        private Button buttonSmallROIImgChoose;
        private Panel panelSmallROIROIInfo;
        private Label labelROIInfoStopYValue;
        private Label labelROIInfoStopY;
        private Label labelROIInfoStopXValue;
        private Label labelROIInfoStopX;
        private Label labelROIInfoStartYValue;
        private Label labelROIInfoStartY;
        private Label labelROIInfoStartXValue;
        private Label labelROIInfoStart;
        private Label labelROIInfoTitle;
        private PictureBox pictureBoxROIInfo;
        private Panel panelSmallROIMove;
        private Label labelChangInfoScaletimes;
        private Label labelImgnowwidthvalue;
        private Label labelImgnowheightvalue;
        private Label labelChangeInfoScale;
        private Label labelImgnowheight;
        private Label labelImgnowwidth;
        private Label labelChangeInfo;
        private PictureBox pictureBoxChangeInfo;
        private Panel panelSmallROIImgInfo;
        private Label labelSrcImgInfoWidth;
        private Label labelSrcImgInfoHeight;
        private Label labelSrcImgInfoWidthTitle;
        private Label labelSrcImgInfoHeightTitle;
        private Label labelImgInfoTitle;
        private PictureBox pictureBoxSrcImgInfo;
        private Panel panelSmallROI;
        private PictureBox pictureBoxSmallROI;
        private Panel panelXML;
        private Panel paneldata;
        private Panel panelfordatause;
        private Bunifu.Framework.UI.BunifuImageButton bunifuImageButtonRefresh;
        private Panel panelforgridview;
        private DataGridView dataGridView;
        private Panel panelAdd;
        private Panel panelknob;
        private RichTextBox richTextBoxKnobitem;
        private Label labelknobLow;
        private Label labelKnobHigh;
        private NumericUpDown numericUpDownknobLow;
        private TextBox textBoxKnobContext;
        private NumericUpDown numericUpDownKnobHigh;
        private Button buttonknobAddItem;
        private Panel panelpointer;
        private Label labelpointerunit;
        private Label labelpointerhigh;
        private Label labelpointerLow;
        private TextBox textBoxpointerUnit;
        private NumericUpDown numericUpDownPointerhigh;
        private NumericUpDown numericUpDownpointerLow;
        private TextBox textBoxgetname;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelheight;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelwidth;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelY;
        private Button buttonAppend;
        private NumericUpDown numericUpDownnum;
        private NumericUpDown numericUpDownheight;
        private NumericUpDown numericUpDownStartY;
        private NumericUpDown numericUpDownwidth;
        private NumericUpDown numericUpDownStartX;
        private ComboBox comboBoxsub2;
        private ComboBox comboBoxsub1;
        private ComboBox comboBoxType;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelNum;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelSub2;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelname;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelSub1;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabelX;
        private Bunifu.Framework.UI.BunifuCustomLabel bunifuCustomLabeltype;
        private Panel panelCreate;
        private Bunifu.Framework.UI.BunifuTextbox bunifuTextboxCabin;
        private Bunifu.Framework.UI.BunifuTextbox bunifuTextboxRoom;
        private Bunifu.Framework.UI.BunifuTextbox bunifuTextboxFactory;
        private Button buttonCreateXML;
        private Panel panelxmlpath;
        private Label labelpath;
        private Button buttonxmlOpen;
        private TextBox textBoxXMLpath;
        private Button buttonxmlCreate;
        private ContextMenuStrip contextMenuStripDataGrid;
        private ToolStripMenuItem toolStripMenuItemDelete;
        private Button buttonIPcamera;
        private Button buttonQR;
        //private System.Windows.Forms.Panel panelImgSource;
        //private System.Windows.Forms.PictureBox pictureBoxSource;
        //private System.Windows.Forms.Panel panelImgProcess;
        //private System.Windows.Forms.PictureBox pictureBoxProcess;
    }
}

