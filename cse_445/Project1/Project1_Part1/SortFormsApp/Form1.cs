using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SortFormsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // handle the 'Sort' button and call internal service
        private void button1_Click(object sender, EventArgs e)
        {
            SortService.ISortService sortService = new SortService.SortServiceClient();
            label3.Text = "Sorted: " + sortService.sort(textBox1.Text);
        }
    }
}
