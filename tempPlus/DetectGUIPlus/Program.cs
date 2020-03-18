using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DetectGUIPlus
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            //大屏幕 1920*1080
            //Application.Run(new MainWindow());

            //小屏幕 1200*700
            Application.Run(new XMLConfigureSmall());
        }
    }
}
