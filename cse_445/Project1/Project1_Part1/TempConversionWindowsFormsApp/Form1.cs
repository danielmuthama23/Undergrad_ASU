using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TempConversionWindowsFormsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // handle the 'Convert' button
        private void button1_Click(object sender, EventArgs e)
        {
            // reference internal service 'TempConversionService'
            TempService.ITempService tempService = new TempService.TempServiceClient();
            int inputTemp = Int32.Parse(textBox1.Text); // convert string to int
            if (radioButton1.Checked)
            {
                label2.Text = "Conversion: " + tempService.f2c(inputTemp);
            }
            else
            {
                label2.Text = "Conversion: " + tempService.c2f(inputTemp);
            }
        }
    }
}
