using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

using ZedGraph;



namespace GiaoDienSRM
{


    public partial class Form1 : Form
    {
        string serialRefSpeed, serialFbSpeed;
        string serialRefI1, serialFbI1, serialRefI2, serialFbI2, serialRefI3, serialFbI3;
        double refSpeed = 1, fbSpeed = 1;
        double refI1 = 1, fbI1 = 1, refI2 = 1, fbI2 = 1, refI3 = 1, fbI3 = 1;
        double tickStart, time;
        int stt = 0, zoomFlag = 1, lastMode = 0; //stt: báo nhận dữ liệu
                                                 //zoomFlag: báo Tự động căn trục
                                                 //lastMode: ghi nhận Tự động căn trục/Phóng to.
        int intModeScroll = 0;                   //cờ đặt xem Thu gọn/Toàn bộ

        const double constxScaleMax = 20;
        const double constxScaleMin = 0;
        const double constxScaleMinStep = 5;
        const double constxScaleMajStep = 10;
        const double constxExpansion = 10;

        const double constyScaleMax = 100;
        const double constyScaleMin = 0;
        const double constyScaleMinStep = 5;
        const double constyScaleMajStep = 10;

        #region Timer1ms
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (spCom.IsOpen)
            {
                pbBar.Value = 100;
                //   if (refSpeed < 50) { DisplayLView(); }
                // CÓ THỂ SẼ LÀM RẤT NHIỀU CHUYỆN Ở ĐÂY
                DisplayLView();
                Draw();
                Draw(zgPhaseU, refI1, fbI1);
                Draw(zgPhaseV, refI2, fbI2);
                Draw(zgPhaseW, refI2, fbI3);
                //               stt = 0;
            }
            else
            {
                pbBar.Value = 0;
            }
        }
        #endregion

        // tickStart = Environment.TickCount;
        public Form1()
        {
            InitializeComponent();
            InitialDisplayLView();
        }

        #region Form1_Load
        private void Form1_Load(object sender, EventArgs e)
        {
            //cbComPort.DataSource = SerialPort.GetPortNames(); // Lấy nguồn cho comboBox là tên của cổng COM
            //cbComPort.Text = Properties.Settings.Default.ComName; // Lấy ComName đã làm ở bước 5 cho comboBox


            //  Khởi tạo Graph1
            InitGraphW();
            InitGraphPhaseU();
            InitGraphPhaseV();
            InitGraphPhaseW();
        }
        #endregion

        #region InitGraphW
        public void InitGraphW()
        {
            GraphPane plotW = zgW.GraphPane;

            plotW.Title.Text = "Đồ thị vận tốc theo thời gian";
            plotW.XAxis.Title.Text = "Thời gian (s)";
            plotW.YAxis.Title.Text = "Vận tốc v/ph";

            RollingPointPairList list0 = new RollingPointPairList(60000);
            RollingPointPairList list1 = new RollingPointPairList(60000);

            LineItem Curve0 = plotW.AddCurve("Set Value", list0, Color.Red, SymbolType.None);
            LineItem Curve1 = plotW.AddCurve("Feedback Value", list1, Color.Blue, SymbolType.None);

            plotW.XAxis.Scale.Min = constxScaleMin;
            plotW.XAxis.Scale.Max = constxScaleMax;
            plotW.XAxis.Scale.MinorStep = constxScaleMinStep;
            plotW.XAxis.Scale.MajorStep = constxScaleMajStep;

            plotW.AxisChange();  // Vẽ
                                 //  zgW.AxisChange();
        }
        #endregion

        #region InitGraphPhaseU
        public void InitGraphPhaseU()
        {
            GraphPane plotPhaseU = zgPhaseU.GraphPane;

            plotPhaseU.Title.Text = "Đồ thị dòng điện pha U";
            plotPhaseU.XAxis.Title.Text = "Thời gian (s)";
            plotPhaseU.YAxis.Title.Text = "Dòng điện (A)";

            RollingPointPairList listU0 = new RollingPointPairList(60000);
            RollingPointPairList listU1 = new RollingPointPairList(60000);

            LineItem CurveU0 = plotPhaseU.AddCurve("Set Value", listU0, Color.Red, SymbolType.None);
            LineItem CurveU1 = plotPhaseU.AddCurve("Feedback Value", listU1, Color.Blue, SymbolType.None);

            plotPhaseU.XAxis.Scale.Min = constxScaleMin;
            plotPhaseU.XAxis.Scale.Max = constxScaleMax;
            plotPhaseU.XAxis.Scale.MinorStep = constxScaleMinStep;
            plotPhaseU.XAxis.Scale.MajorStep = constxScaleMajStep;

            plotPhaseU.AxisChange(); 
        }
        #endregion

        #region InitGraphPhaseV
        public void InitGraphPhaseV()
        {
            GraphPane plotPhaseV = zgPhaseV.GraphPane;

            plotPhaseV.Title.Text = "Đồ thị dòng điện pha V";
            plotPhaseV.XAxis.Title.Text = "Thời gian (s)";
            plotPhaseV.YAxis.Title.Text = "Dòng điện (A)";

            RollingPointPairList listV0 = new RollingPointPairList(60000);
            RollingPointPairList listV1 = new RollingPointPairList(60000);

            LineItem CurveV0 = plotPhaseV.AddCurve("Set Value", listV0, Color.Red, SymbolType.None);
            LineItem CurveV1 = plotPhaseV.AddCurve("Feedback Value", listV1, Color.Blue, SymbolType.None);

            plotPhaseV.XAxis.Scale.Min = constxScaleMin;
            plotPhaseV.XAxis.Scale.Max = constxScaleMax;
            plotPhaseV.XAxis.Scale.MinorStep = constxScaleMinStep;
            plotPhaseV.XAxis.Scale.MajorStep = constxScaleMajStep;

            plotPhaseV.AxisChange();

        }
        #endregion

        #region InitGraphPhaseW
        public void InitGraphPhaseW()
        {
            GraphPane plotPhaseW = zgPhaseW.GraphPane;

            plotPhaseW.Title.Text = "Đồ thị dòng điện pha W";
            plotPhaseW.XAxis.Title.Text = "Thời gian (s)";
            plotPhaseW.YAxis.Title.Text = "Dòng điện (A)";

            RollingPointPairList listW0 = new RollingPointPairList(60000);
            RollingPointPairList listW1 = new RollingPointPairList(60000);

            LineItem CurveW0 = plotPhaseW.AddCurve("Set Value", listW0, Color.Red, SymbolType.None);
            LineItem CurveW1 = plotPhaseW.AddCurve("Feedback Value", listW1, Color.Blue, SymbolType.None);

            plotPhaseW.XAxis.Scale.Min = constxScaleMin;
            plotPhaseW.XAxis.Scale.Max = constxScaleMax;
            plotPhaseW.XAxis.Scale.MinorStep = constxScaleMinStep;
            plotPhaseW.XAxis.Scale.MajorStep = constxScaleMajStep;

            plotPhaseW.AxisChange();

        }
        #endregion

        #region General Draw
        public void Draw(ZedGraphControl zedgr, double refValue, double fbValue)
        {
            GraphPane plot = zedgr.GraphPane;
            if (plot.CurveList.Count <= 0) //  Trả về nếu lỗi
                return;
            
            LineItem curve0 = plot.CurveList[0] as LineItem;
            LineItem curve1 = plot.CurveList[1] as LineItem;

            if ((curve0 == null) || (curve1 == null))
            {
                return;
            }

            IPointListEdit list0 = curve0.Points as IPointListEdit;
            IPointListEdit list1 = curve1.Points as IPointListEdit;

            if ((list0 == null) || (list1 == null))
            {
                return;
            }

            time = (Environment.TickCount - tickStart) / 1000; // Thêm điểm vào đồ thị
            list0.Add(time, refValue);
            list1.Add(time, fbValue);


            Scale xScale = plot.XAxis.Scale; //    Lấy đối tượng phạm vi đồ thị theo 2 trục
            Scale yScale = plot.YAxis.Scale;
            if (zoomFlag == 1)  //Chế độ tự động căn trục
            {
                if (time > xScale.Max - xScale.MajorStep) //    Tự động điều chỉnh trục X
                {
                    if (intModeScroll == 1)         //Thu gọn
                    {
                        xScale.Max = time + constxScaleMajStep;
                        xScale.Min = xScale.Max - constxScaleMax;
                    }
                    else                            //Mở rộng
                    {
                        xScale.Max = time + constxScaleMajStep;
                        xScale.Min = 0.0;
                    }

                }

                if (Max(refValue, fbValue) > yScale.Max - constyScaleMajStep)   //    Tự động điều chỉnh trục Y
                {
                    yScale.Max = Max(refSpeed, fbSpeed) + constyScaleMajStep;    //   yScale.MajorStep;
                }
                else if (Min(refValue, fbValue) < yScale.Min + constyScaleMajStep)
                {
                    yScale.Min = Min(refValue, fbValue) - constyScaleMajStep;    //   yScale.MajorStep;
                }

                lastMode = 1; // Xác nhận chế độ tự động

            }// Chế độ phóng to. (Trục cố định ) 
            else if (time + 10 > xScale.Max)
            {; }// xScale.Max += constxExpansion; } //   Mở rộng trục X khi ở chế độ Phóng to (tĩnh)
            else if (lastMode == 1) //Lệnh thực thi khi chuyển chế độ từ Tự động sang
            {
                xScale.Min = constxScaleMin;    //Khôi phục lại trục đồ thị theo mặc định, có dự trữ
                                                //Miền giá trị giới hạn hai trục sẽ không thay đổi
                xScale.MinorStep = (int)xScale.MajorStep / 5;
                xScale.MajorStep = (int)(xScale.Max / 4);

                //    yScale.Min = 0;
                //    yScale.Max = 100;
                yScale.MinorStep = Convert.ToInt32(yScale.MajorStep / 3);
                yScale.MajorStep = Convert.ToInt32(yScale.Max / 5);

                lastMode = 0;
            }

            zedgr.AxisChange();
            zedgr.Invalidate();
            zedgr.Refresh();
        }

        private void lvMonitor_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void btRefw_Click(object sender, EventArgs e)
        {
            try
            {
                refSpeed = Convert.ToDouble(tbRefw.Text);
            }
            catch
            {
                MessageBox.Show("Giá trị đặt không hợp lệ. Vui lòng đặt lại ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void lbCTI_Click(object sender, EventArgs e)
        {

        }
        #endregion

        #region Draw
        public void Draw()
        {
            if (zgW.GraphPane.CurveList.Count <= 0) //  Trả về nếu lỗi
                return;


            LineItem curve0 = zgW.GraphPane.CurveList[0] as LineItem;
            LineItem curve1 = zgW.GraphPane.CurveList[1] as LineItem;

            if ((curve0 == null) || (curve1 == null))
            {
                return;
            }

            IPointListEdit list0 = curve0.Points as IPointListEdit;
            IPointListEdit list1 = curve1.Points as IPointListEdit;

            if ((list0 == null) || (list1 == null))
            {
                return;
            }

            time = (Environment.TickCount - tickStart) / 1000; // Thêm điểm vào đồ thị
            list0.Add(time, refSpeed);
            list1.Add(time, fbSpeed);


            Scale xScale = zgW.GraphPane.XAxis.Scale; //    Lấy đối tượng phạm vi đồ thị theo 2 trục
            Scale yScale = zgW.GraphPane.YAxis.Scale;
            if (zoomFlag == 1)  //Chế độ tự động căn trục
            {
                if (time > xScale.Max - xScale.MajorStep) //    Tự động điều chỉnh trục X
                {
                    if (intModeScroll == 1)         //Thu gọn
                    {
                        xScale.Max = time + constxScaleMajStep;
                        xScale.Min = xScale.Max - constxScaleMax;
                    }
                    else                            //Mở rộng
                    {
                        xScale.Max = time + constxScaleMajStep;
                        xScale.Min = 0.0;
                    }

                }

                if (Max(refSpeed, fbSpeed) > yScale.Max - constyScaleMajStep)   //    Tự động điều chỉnh trục Y
                {
                    yScale.Max = Max(refSpeed, fbSpeed) + constyScaleMajStep;    //   yScale.MajorStep;
                }
                else if (Min(refSpeed, fbSpeed) < yScale.Min + constyScaleMajStep)
                {
                    yScale.Min = Min(refSpeed, fbSpeed) - constyScaleMajStep;    //   yScale.MajorStep;
                }

                lastMode = 1; // Xác nhận chế độ tự động

            }// Chế độ phóng to. (Trục cố định ) 
            else if (time + 10 > xScale.Max)
            {; }// xScale.Max += constxExpansion; } //   Mở rộng trục X khi ở chế độ Phóng to (tĩnh)
            else if (lastMode == 1) //Lệnh thực thi khi chuyển chế độ từ Tự động sang
            {
                xScale.Min = constxScaleMin;    //Khôi phục lại trục đồ thị theo mặc định, có dự trữ
                                                //Miền giá trị giới hạn hai trục sẽ không thay đổi
                xScale.MinorStep = (int)xScale.MajorStep / 5;
                xScale.MajorStep = (int)(xScale.Max / 4);

                //    yScale.Min = 0;
                //    yScale.Max = 100;
                yScale.MinorStep = Convert.ToInt32(yScale.MajorStep / 3);
                yScale.MajorStep = Convert.ToInt32(yScale.Max / 5);

                lastMode = 0;
            }

            zgW.AxisChange();
            zgW.Invalidate();
            zgW.Refresh();
        }
        #endregion

        #region btScroll
        private void btScroll_Click(object sender, EventArgs e)
        {
            {
                if (btScroll.Text == "Thu gọn")
                {
                    intModeScroll = 1;
                    btScroll.Text = "Mở rộng";
                }
                else
                {
                    intModeScroll = 0;
                    btScroll.Text = "Thu gọn";
                }
            }
        }
        #endregion

        #region btConnect
        private void btConnect_Click(object sender, EventArgs e)
        {
            if (spCom.IsOpen)
            {
                spCom.Write("2"); //Gửi ký tự "2" qua Serial, tương ứng với state = 2
                spCom.Close();
                btConnect.Text = "Kết nối";
                btExit.Enabled = true;


                btScroll.Enabled = false;
                btZoom.Enabled = false;
                // SaveSetting(); // Lưu cổng COM vào ComName
            }
            else
            {
                try
                {
                    spCom.PortName = cbComPort.Text; // Lấy cổng COM
                    spCom.BaudRate = Convert.ToInt32(cbBaudRate.Text); // Lấy BaudRate // 115200

                    spCom.Open();
                    btConnect.Text = "Ngắt kết nối";
                    btExit.Enabled = false;


                    spCom.Write("1"); // Run
                    tickStart = Environment.TickCount;
                    btScroll.Enabled = true;
                    btZoom.Enabled = true;
                }
                catch
                {
                    MessageBox.Show("Không thể kết nối cổng " + spCom.PortName, "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        #endregion

        #region btZoom
        private void btZoom_Click(object sender, EventArgs e)
        {
            {
                if (btZoom.Text == "Tự động")
                {
                    zoomFlag = 1;
                    btZoom.Text = "Phóng to";
                    btScroll.Enabled = true;
                }
                else
                {
                    zoomFlag = 0;
                    btZoom.Text = "Tự động";
                    btScroll.Enabled = false;
                }
            }
        }
        #endregion

        #region btClear
        private void btClear_Click(object sender, EventArgs e)
        {
            if (spCom.IsOpen)
            {
                spCom.Write("3"); //Gửi bản tin thông báo = 3 nếu reset.
            }
            else
            {
                MessageBox.Show("Thiết bị chưa kết nối", "Thông báo",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
             
            lvMonitor.Items.Clear();    // Xóa dữ liệu tới thời điểm hiện có của cả hai
            ClearZedGraph();            // Dữ liệu mới tiếp tục được nạp vào

        }
        #endregion

        #region btExit
        private void btExit_Click(object sender, EventArgs e)
        {
            DialogResult phanhoi;
            phanhoi = MessageBox.Show("Bạn muốn thoát phần mềm?", "Thoát", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
            if (phanhoi == DialogResult.OK)
            {
                // this.Close(); // Đóng ứng dụng
                Application.Exit();
            }
        }
        #endregion


        #region ReadSerialData
        private void spCom_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                string[] arrData = spCom.ReadLine().Split('|');
                //                SerialRealTime = arrData[0];
                serialRefSpeed = arrData[0];
                serialFbSpeed = arrData[1];
                serialRefI1 = arrData[2];
                serialFbI1 = arrData[3];
                serialRefI2 = arrData[4];
                serialFbI2 = arrData[5];
                serialRefI3 = arrData[6];
                serialFbI3 = arrData[7];

                //                double.TryParse(SerialRealTime, out RealTime);
                double.TryParse(serialRefSpeed, out refSpeed);
                double.TryParse(serialFbSpeed, out fbSpeed);

                double.TryParse(serialRefI1, out refI1);
                double.TryParse(serialFbI1, out fbI1);
                double.TryParse(serialRefI2, out refI2);
                double.TryParse(serialFbI2, out fbI2);
                double.TryParse(serialRefI3, out refI3);
                double.TryParse(serialFbI3, out fbI3);

                time = (Environment.TickCount - tickStart) / 1000;

                stt = 1; // Bật cờ xử lý xong chuỗi, sẵn sàng hiển thị và vẽ
            }
            catch
            {
                return;
            }
        }
        #endregion


        #region InitialDisplayLView
        public void InitialDisplayLView()
        {
            lvMonitor.FullRowSelect = true;
            lvMonitor.GridLines = true;


            this.MntColumn1.Text = "Thời gian (s)";      // Cột thời gian của ListView
            this.MntColumn1.Width = lvMonitor.Size.Width / lvMonitor.Columns.Count; //Độ rộng của cột.

            this.MntColumn2.Text = "Giá trị đặt";        // Cột Giá trị đặt
            this.MntColumn2.Width = lvMonitor.Size.Width / lvMonitor.Columns.Count;

            this.MntColumn3.Text = "Đáp ứng";           // Cột giá trị phản hồi
            this.MntColumn3.Width = lvMonitor.Size.Width / lvMonitor.Columns.Count;
        }
        #endregion


        #region DisplayLView
        public void DisplayLView()
        {
            if (stt == 0) // biến trạng thái - HỦY stt == 0;
            {
                //  MessageBox.Show("stt = 0 ");
                return;
            }
            ListViewItem item = new ListViewItem(time.ToString()); // Biến thời gian vào cột đầu tiên của item
            item.SubItems.Add(refSpeed.ToString());                // Biến refSpeed cột thứ hai
            item.SubItems.Add(fbSpeed.ToString());                // Biến  fbSpeed cột thứ ba

            lvMonitor.Items.Add(item); //Đưa item vào hiển thị trong listview - lvMonitor

            lvMonitor.Items[lvMonitor.Items.Count - 1].EnsureVisible(); //Hiển thị giá trị mới nhất của lvMonitor
            stt = 0;
        }
        #endregion


        #region btSave
        private void btSave_Click(object sender, EventArgs e)
        {
            DialogResult phanhoi;
            phanhoi = MessageBox.Show("Bạn muốn lưu đồ thị", "Lưu dữ liệu", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
            if (phanhoi == DialogResult.OK)
            {
                // Lưu vào tệp Excel
                SaveToExcel();
                MessageBox.Show("Dữ liệu tốc độ w đã lưu", "Lưu",
                MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            }
        }
        #endregion

        #region SaveSetting

        public void SaveSetting()
        {
            Properties.Settings.Default.ComName = cbComPort.Text;
            Properties.Settings.Default.Save();
        }
        #endregion


        #region ClearZedGraph
        public void ClearZedGraph()
        {

            int i = 1;
            foreach (var item in this.Controls.OfType<ZedGraphControl>())
            {

            item.GraphPane.CurveList.Clear(); // Xóa đường
            item.GraphPane.GraphObjList.Clear(); // Xóa đối tượng

            item.AxisChange();
            item.Invalidate();

            if (i == 1)
            {
             item.GraphPane.Title.Text = "Thử chơi tí thôi mà. Gì căng!";
             item.GraphPane.XAxis.Title.Text = "Thời gian";
             item.GraphPane.YAxis.Title.Text = "I, J";

             RollingPointPairList list0 = new RollingPointPairList(60000);
             RollingPointPairList list1 = new RollingPointPairList(60000);

             LineItem Curve0 = zgW.GraphPane.AddCurve("Set Value", list0, Color.Red, SymbolType.None);
             LineItem Curve1 = zgW.GraphPane.AddCurve("Feedback Value", list1, Color.Blue, SymbolType.None);
            }
            i++;

            item.GraphPane.XAxis.Scale.Min = constxScaleMin;
            item.GraphPane.XAxis.Scale.Max = constxScaleMax;
            item.GraphPane.XAxis.Scale.MinorStep = constxScaleMinStep;
            item.GraphPane.XAxis.Scale.MajorStep = constxScaleMajStep;
            item.GraphPane.YAxis.Scale.Min = constyScaleMax;
            item.GraphPane.YAxis.Scale.Max = constyScaleMin;

            item.AxisChange();
            }
        }
        #endregion


        #region SaveExcel
        private void SaveToExcel()
        {
            Microsoft.Office.Interop.Excel.Application xls = new Microsoft.Office.Interop.Excel.Application();
            xls.Visible = true;
            Microsoft.Office.Interop.Excel.Workbook wb = xls.Workbooks.Add(Microsoft.Office.Interop.Excel.XlSheetType.xlWorksheet);
            Microsoft.Office.Interop.Excel.Worksheet ws = (Microsoft.Office.Interop.Excel.Worksheet)xls.ActiveSheet;

            // Đặt tên cho hai ô A1. B1 lần lượt là "Thời gian (s)" và "Dữ liệu", sau đó tự động dãn độ rộng
            Microsoft.Office.Interop.Excel.Range rg = (Microsoft.Office.Interop.Excel.Range)ws.get_Range("A1", "B1");
            ws.Cells[1, 1] = "Thời gian (s)";
            ws.Cells[1, 2] = "wref";
            ws.Cells[1, 3] = "wfb";

            rg.Columns.AutoFit(); //Tự động dãn độ rộng

            // Lưu từ ô đầu tiên của dòng thứ 2, tức ô A2
            int i = 2;
            int j = 1;

            foreach (ListViewItem item in lvMonitor.Items)
            {
                ws.Cells[i, j] = item.Text.ToString();
                foreach (ListViewItem.ListViewSubItem drv in item.SubItems)
                {
                    ws.Cells[i, j] = drv.Text.ToString(); //Lưu các giá trị ở cột thứ 2 trở đi
                    j++;
                }
                j = 1; 
                i++; //đặt lại j. Đẩy i xuống hàng tiếp theo (0 -> ... s)
            }
        }
        #endregion


        #region Hàm so sánh
        public double Max(double x, double y)
        {
            return (x > y) ? x : y;
        }
        public double Min(double x, double y)
        {
            return (x < y) ? x : y;
        }
        #endregion


    }
}
