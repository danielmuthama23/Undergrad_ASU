using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApp
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void VerificationButton_Click(object sender, EventArgs e)
        {
            // handle input and response for verification service
            if (xmlUrl.Text != null && xsdUrl.Text != null)
            {
                ServiceReference.IService1 verSer = new ServiceReference.Service1Client();
                string data = verSer.verification(xmlUrl.Text, xsdUrl.Text);
                VerificationInfo.Text = data; // display info
            }
        }

        protected void SearchButton_Click(object sender, EventArgs e)
        {
            // handle input and response for search service
            if (xmlUrl2.Text != null && pathEx.Text != null)
            {
                ServiceReference.IService1 ser = new ServiceReference.Service1Client();
                string data = ser.XPathSearch(xmlUrl2.Text, pathEx.Text);
                SearchInfo.Text = data; // display info
            }
        }
    }
}