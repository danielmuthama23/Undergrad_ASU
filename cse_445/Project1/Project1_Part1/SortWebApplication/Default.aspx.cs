using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SortWebApplication
{
    public partial class _Default : Page
    {
        // handle the 'Sort' button and call internal services
        protected void Button1_Click(object sender, EventArgs e)
        {
            SortService.ISortService sortService = new SortService.SortServiceClient();
            Label1.Text = "Sorted: " + sortService.sort(TextBox1.Text);
        }
    }
}