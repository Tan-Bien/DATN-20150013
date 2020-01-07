namespace GiaoDienSRM
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btConnect = new System.Windows.Forms.Button();
            this.lvMonitor = new System.Windows.Forms.ListView();
            this.MntColumn1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MntColumn2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MntColumn3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.cbComPort = new System.Windows.Forms.ComboBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.lbRefw = new System.Windows.Forms.Label();
            this.tbRefw = new System.Windows.Forms.TextBox();
            this.btSave = new System.Windows.Forms.Button();
            this.btClear = new System.Windows.Forms.Button();
            this.btRefw = new System.Windows.Forms.Button();
            this.cbDisplay = new System.Windows.Forms.ComboBox();
            this.lbDisplay = new System.Windows.Forms.Label();
            this.btExit = new System.Windows.Forms.Button();
            this.lbBaudRate = new System.Windows.Forms.Label();
            this.lbPort = new System.Windows.Forms.Label();
            this.pbBar = new System.Windows.Forms.ProgressBar();
            this.cbBaudRate = new System.Windows.Forms.ComboBox();
            this.btZoom = new System.Windows.Forms.Button();
            this.btScroll = new System.Windows.Forms.Button();
            this.spCom = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.zgW = new ZedGraph.ZedGraphControl();
            this.zgPhaseW = new ZedGraph.ZedGraphControl();
            this.zgPhaseV = new ZedGraph.ZedGraphControl();
            this.zgPhaseU = new ZedGraph.ZedGraphControl();
            this.lbCTI = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(226, 3);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(78, 23);
            this.btConnect.TabIndex = 0;
            this.btConnect.Text = "Kết nối";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // lvMonitor
            // 
            this.lvMonitor.AllowDrop = true;
            this.lvMonitor.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.MntColumn1,
            this.MntColumn2,
            this.MntColumn3});
            this.lvMonitor.HideSelection = false;
            this.lvMonitor.Location = new System.Drawing.Point(15, 223);
            this.lvMonitor.Name = "lvMonitor";
            this.lvMonitor.Size = new System.Drawing.Size(315, 449);
            this.lvMonitor.TabIndex = 1;
            this.lvMonitor.UseCompatibleStateImageBehavior = false;
            this.lvMonitor.View = System.Windows.Forms.View.Details;
            this.lvMonitor.SelectedIndexChanged += new System.EventHandler(this.lvMonitor_SelectedIndexChanged);
            // 
            // MntColumn1
            // 
            this.MntColumn1.Text = "ColumnHeader";
            this.MntColumn1.Width = 102;
            // 
            // MntColumn2
            // 
            this.MntColumn2.Width = 111;
            // 
            // MntColumn3
            // 
            this.MntColumn3.Width = 88;
            // 
            // cbComPort
            // 
            this.cbComPort.FormattingEnabled = true;
            this.cbComPort.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM5"});
            this.cbComPort.Location = new System.Drawing.Point(81, 3);
            this.cbComPort.Name = "cbComPort";
            this.cbComPort.Size = new System.Drawing.Size(121, 21);
            this.cbComPort.TabIndex = 2;
            this.cbComPort.Text = "COM5";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.lbRefw);
            this.panel1.Controls.Add(this.tbRefw);
            this.panel1.Controls.Add(this.btSave);
            this.panel1.Controls.Add(this.btClear);
            this.panel1.Controls.Add(this.btRefw);
            this.panel1.Controls.Add(this.cbDisplay);
            this.panel1.Controls.Add(this.lbDisplay);
            this.panel1.Controls.Add(this.btExit);
            this.panel1.Controls.Add(this.lbBaudRate);
            this.panel1.Controls.Add(this.lbPort);
            this.panel1.Controls.Add(this.pbBar);
            this.panel1.Controls.Add(this.cbBaudRate);
            this.panel1.Controls.Add(this.btConnect);
            this.panel1.Controls.Add(this.cbComPort);
            this.panel1.Location = new System.Drawing.Point(12, 24);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(463, 145);
            this.panel1.TabIndex = 3;
            // 
            // lbRefw
            // 
            this.lbRefw.BackColor = System.Drawing.SystemColors.Control;
            this.lbRefw.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbRefw.Location = new System.Drawing.Point(3, 105);
            this.lbRefw.Name = "lbRefw";
            this.lbRefw.Size = new System.Drawing.Size(72, 32);
            this.lbRefw.TabIndex = 23;
            this.lbRefw.Text = "Tốc độ đặt (vòng/giây)";
            this.lbRefw.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tbRefw
            // 
            this.tbRefw.Location = new System.Drawing.Point(81, 112);
            this.tbRefw.Name = "tbRefw";
            this.tbRefw.Size = new System.Drawing.Size(121, 20);
            this.tbRefw.TabIndex = 22;
            // 
            // btSave
            // 
            this.btSave.Location = new System.Drawing.Point(219, 68);
            this.btSave.Name = "btSave";
            this.btSave.Size = new System.Drawing.Size(75, 23);
            this.btSave.TabIndex = 12;
            this.btSave.Text = "Lưu";
            this.btSave.UseVisualStyleBackColor = true;
            this.btSave.Click += new System.EventHandler(this.btSave_Click);
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(366, 68);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(75, 23);
            this.btClear.TabIndex = 11;
            this.btClear.Text = "Xóa";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // btRefw
            // 
            this.btRefw.Location = new System.Drawing.Point(219, 110);
            this.btRefw.Name = "btRefw";
            this.btRefw.Size = new System.Drawing.Size(75, 23);
            this.btRefw.TabIndex = 13;
            this.btRefw.Text = "Xác nhận";
            this.btRefw.UseVisualStyleBackColor = true;
            this.btRefw.Click += new System.EventHandler(this.btRefw_Click);
            // 
            // cbDisplay
            // 
            this.cbDisplay.FormattingEnabled = true;
            this.cbDisplay.Items.AddRange(new object[] {
            "w"});
            this.cbDisplay.Location = new System.Drawing.Point(81, 68);
            this.cbDisplay.Name = "cbDisplay";
            this.cbDisplay.Size = new System.Drawing.Size(121, 21);
            this.cbDisplay.TabIndex = 9;
            this.cbDisplay.Text = "w";
            // 
            // lbDisplay
            // 
            this.lbDisplay.BackColor = System.Drawing.SystemColors.Control;
            this.lbDisplay.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbDisplay.Location = new System.Drawing.Point(3, 67);
            this.lbDisplay.Name = "lbDisplay";
            this.lbDisplay.Size = new System.Drawing.Size(72, 21);
            this.lbDisplay.TabIndex = 8;
            this.lbDisplay.Text = "Đại lượng";
            this.lbDisplay.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btExit
            // 
            this.btExit.Location = new System.Drawing.Point(366, 3);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(75, 23);
            this.btExit.TabIndex = 7;
            this.btExit.Text = "Thoát";
            this.btExit.UseVisualStyleBackColor = true;
            this.btExit.Click += new System.EventHandler(this.btExit_Click);
            // 
            // lbBaudRate
            // 
            this.lbBaudRate.BackColor = System.Drawing.SystemColors.Control;
            this.lbBaudRate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbBaudRate.Location = new System.Drawing.Point(3, 30);
            this.lbBaudRate.Name = "lbBaudRate";
            this.lbBaudRate.Size = new System.Drawing.Size(72, 21);
            this.lbBaudRate.TabIndex = 6;
            this.lbBaudRate.Text = "BaudRate";
            this.lbBaudRate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbPort
            // 
            this.lbPort.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbPort.Location = new System.Drawing.Point(3, 3);
            this.lbPort.Name = "lbPort";
            this.lbPort.Size = new System.Drawing.Size(72, 21);
            this.lbPort.TabIndex = 5;
            this.lbPort.Text = "Ngõ vào";
            this.lbPort.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pbBar
            // 
            this.pbBar.Location = new System.Drawing.Point(219, 38);
            this.pbBar.Name = "pbBar";
            this.pbBar.Size = new System.Drawing.Size(99, 23);
            this.pbBar.TabIndex = 4;
            // 
            // cbBaudRate
            // 
            this.cbBaudRate.FormattingEnabled = true;
            this.cbBaudRate.Items.AddRange(new object[] {
            "9600",
            "19200",
            "38400",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.cbBaudRate.Location = new System.Drawing.Point(81, 30);
            this.cbBaudRate.Name = "cbBaudRate";
            this.cbBaudRate.Size = new System.Drawing.Size(121, 21);
            this.cbBaudRate.TabIndex = 3;
            this.cbBaudRate.Text = "115200";
            // 
            // btZoom
            // 
            this.btZoom.Enabled = false;
            this.btZoom.Location = new System.Drawing.Point(417, 223);
            this.btZoom.Name = "btZoom";
            this.btZoom.Size = new System.Drawing.Size(75, 23);
            this.btZoom.TabIndex = 7;
            this.btZoom.Text = "Phóng to";
            this.btZoom.UseVisualStyleBackColor = true;
            this.btZoom.Click += new System.EventHandler(this.btZoom_Click);
            // 
            // btScroll
            // 
            this.btScroll.Enabled = false;
            this.btScroll.Location = new System.Drawing.Point(422, 275);
            this.btScroll.Name = "btScroll";
            this.btScroll.Size = new System.Drawing.Size(70, 24);
            this.btScroll.TabIndex = 10;
            this.btScroll.Text = "Thu gọn";
            this.btScroll.UseVisualStyleBackColor = true;
            this.btScroll.Click += new System.EventHandler(this.btScroll_Click);
            // 
            // spCom
            // 
            this.spCom.BaudRate = 115200;
            this.spCom.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.spCom_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // zgW
            // 
            this.zgW.Location = new System.Drawing.Point(351, 397);
            this.zgW.Name = "zgW";
            this.zgW.ScrollGrace = 0D;
            this.zgW.ScrollMaxX = 0D;
            this.zgW.ScrollMaxY = 0D;
            this.zgW.ScrollMaxY2 = 0D;
            this.zgW.ScrollMinX = 0D;
            this.zgW.ScrollMinY = 0D;
            this.zgW.ScrollMinY2 = 0D;
            this.zgW.Size = new System.Drawing.Size(583, 275);
            this.zgW.TabIndex = 12;
            this.zgW.UseExtendedPrintDialog = true;
            // 
            // zgPhaseW
            // 
            this.zgPhaseW.Location = new System.Drawing.Point(951, 328);
            this.zgPhaseW.Name = "zgPhaseW";
            this.zgPhaseW.ScrollGrace = 0D;
            this.zgPhaseW.ScrollMaxX = 0D;
            this.zgPhaseW.ScrollMaxY = 0D;
            this.zgPhaseW.ScrollMaxY2 = 0D;
            this.zgPhaseW.ScrollMinX = 0D;
            this.zgPhaseW.ScrollMinY = 0D;
            this.zgPhaseW.ScrollMinY2 = 0D;
            this.zgPhaseW.Size = new System.Drawing.Size(400, 275);
            this.zgPhaseW.TabIndex = 18;
            this.zgPhaseW.UseExtendedPrintDialog = true;
            // 
            // zgPhaseV
            // 
            this.zgPhaseV.Location = new System.Drawing.Point(951, 24);
            this.zgPhaseV.Name = "zgPhaseV";
            this.zgPhaseV.ScrollGrace = 0D;
            this.zgPhaseV.ScrollMaxX = 0D;
            this.zgPhaseV.ScrollMaxY = 0D;
            this.zgPhaseV.ScrollMaxY2 = 0D;
            this.zgPhaseV.ScrollMinX = 0D;
            this.zgPhaseV.ScrollMinY = 0D;
            this.zgPhaseV.ScrollMinY2 = 0D;
            this.zgPhaseV.Size = new System.Drawing.Size(400, 275);
            this.zgPhaseV.TabIndex = 19;
            this.zgPhaseV.UseExtendedPrintDialog = true;
            // 
            // zgPhaseU
            // 
            this.zgPhaseU.Location = new System.Drawing.Point(534, 24);
            this.zgPhaseU.Name = "zgPhaseU";
            this.zgPhaseU.ScrollGrace = 0D;
            this.zgPhaseU.ScrollMaxX = 0D;
            this.zgPhaseU.ScrollMaxY = 0D;
            this.zgPhaseU.ScrollMaxY2 = 0D;
            this.zgPhaseU.ScrollMinX = 0D;
            this.zgPhaseU.ScrollMinY = 0D;
            this.zgPhaseU.ScrollMinY2 = 0D;
            this.zgPhaseU.Size = new System.Drawing.Size(400, 275);
            this.zgPhaseU.TabIndex = 21;
            this.zgPhaseU.UseExtendedPrintDialog = true;
            // 
            // lbCTI
            // 
            this.lbCTI.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.lbCTI.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbCTI.Location = new System.Drawing.Point(1139, 617);
            this.lbCTI.Name = "lbCTI";
            this.lbCTI.Size = new System.Drawing.Size(166, 55);
            this.lbCTI.TabIndex = 24;
            this.lbCTI.Text = "Trung tâm Nghiên cứu ứng dụng           và Sáng tạo công nghệ -      CTI - ĐHBKHN" +
    "";
            this.lbCTI.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lbCTI.Click += new System.EventHandler(this.lbCTI_Click);
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Location = new System.Drawing.Point(950, 617);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(166, 55);
            this.label1.TabIndex = 25;
            this.label1.Text = "Nguyễn Văn An - 20150013";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1278, 701);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lbCTI);
            this.Controls.Add(this.zgPhaseU);
            this.Controls.Add(this.zgPhaseV);
            this.Controls.Add(this.zgPhaseW);
            this.Controls.Add(this.btScroll);
            this.Controls.Add(this.btZoom);
            this.Controls.Add(this.zgW);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.lvMonitor);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "CTI - SRM Drive";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.ListView lvMonitor;
        private System.Windows.Forms.ComboBox cbComPort;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox cbBaudRate;
        private System.IO.Ports.SerialPort spCom;
        private System.Windows.Forms.ProgressBar pbBar;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lbPort;
        private System.Windows.Forms.Label lbBaudRate;
        private System.Windows.Forms.Button btExit;
        private System.Windows.Forms.ComboBox cbDisplay;
        private System.Windows.Forms.Label lbDisplay;
        private System.Windows.Forms.ColumnHeader MntColumn1;
        private System.Windows.Forms.ColumnHeader MntColumn2;
        private System.Windows.Forms.ColumnHeader MntColumn3;
        private System.Windows.Forms.Button btScroll;
        private System.Windows.Forms.Button btZoom;
        private System.Windows.Forms.Button btClear;
        private System.Windows.Forms.Button btSave;
        private ZedGraph.ZedGraphControl zgW;
        private System.Windows.Forms.Button btRefw;
        private ZedGraph.ZedGraphControl zgPhaseW;
        private ZedGraph.ZedGraphControl zgPhaseV;
        private ZedGraph.ZedGraphControl zgPhaseU;
        private System.Windows.Forms.TextBox tbRefw;
        private System.Windows.Forms.Label lbRefw;
        private System.Windows.Forms.Label lbCTI;
        private System.Windows.Forms.Label label1;
    }
}

