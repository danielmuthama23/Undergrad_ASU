using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WebBroswerWindowsFormsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // handle the 'Go' button
        private void button1_Click(object sender, EventArgs e)
        {
            webBrowser1.Navigate(textBox1.Text);
        }

        // handle the 'Refresh' button
        private void button2_Click(object sender, EventArgs e)
        {
            webBrowser1.Refresh();
        }

        // handle the 'Home' button
        private void button3_Click(object sender, EventArgs e)
        {
            webBrowser1.GoHome();
        }

        // handle the 'Back' button
        private void button4_Click(object sender, EventArgs e)
        {
            webBrowser1.GoBack();
        }

        // handle the 'Forward' button
        private void button5_Click(object sender, EventArgs e)
        {
            webBrowser1.GoForward();
        }

        //  handle the 'Caclulate' button
        private void button6_Click(object sender, EventArgs e)
        {
            // convert strings to doubles
            double num1 = Convert.ToDouble(textBox2.Text);
            double num2 = Convert.ToDouble(textBox3.Text);

            // check for combo box value / operand
            if (comboBox1.Text == "+")
            {
                label2.Text = "= " + (num1 + num2);
            }
            else if (comboBox1.Text == "-")
            {
                label2.Text = "= " + (num1 - num2);
            }
            else if (comboBox1.Text == "*")
            {
                label2.Text = "= " + (num1 * num2);
            }
            else if (comboBox1.Text == "/")
            {
                label2.Text = "= " + (num1 / num2);
            }
        }

        // handle 'Get Quote' button
        private void button7_Click(object sender, EventArgs e)
        {
            // reference external stock service
            StockQuoteService.IService stockService = new StockQuoteService.ServiceClient();
            string quote = stockService.getStockquote(textBox4.Text);
            label5.Text = "Quote: " + quote;
        }
    }
}