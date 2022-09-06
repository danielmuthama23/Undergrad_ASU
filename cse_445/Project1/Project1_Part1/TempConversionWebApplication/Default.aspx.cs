using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace TempConversionWebApplication
{
    public partial class _Default : Page
    {
        // handle the 'Convert' button
        protected void Button1_Click(object sender, EventArgs e)
        {
            // reference internal service
            TempService.ITempService tempService = new TempService.TempServiceClient();
            int inputTemp = Int32.Parse(TextBox1.Text);
            if (DropDownList1.SelectedValue == "Celsius")
            {
                // call operations from within service
                Label2.Text = "Conversion: " + tempService.f2c(inputTemp);
            }
            else
            {
                Label2.Text = "Conversion: " + tempService.c2f(inputTemp);
            }
        }
    }
}