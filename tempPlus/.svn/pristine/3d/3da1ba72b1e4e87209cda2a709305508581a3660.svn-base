using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DetectGUIPlus
{
    public partial class WelcomeHohai : Form
    {
        private int waitSeconds = 0;
        public WelcomeHohai(int seconds)
        {
            this.waitSeconds = seconds;
            InitializeComponent();
            bunifuFormFadeTransition1.ShowAsyc(this);
        }

        private void Welcome_Load(object sender, EventArgs e)
        {
            this.timerwelcom.Start();
            this.timerwelcom.Interval = this.waitSeconds;
        }

        private void timerwelcom_Tick(object sender, EventArgs e)
        {
            this.timerwelcom.Stop();
            this.Close();
        }
    }
}
