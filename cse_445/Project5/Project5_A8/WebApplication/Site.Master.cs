using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Security;
using Providers;

namespace WebApplication
{
    public partial class SiteMaster : MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void LogButton_Click(object sender, EventArgs e)
        {
            if (HttpContext.Current.User.Identity.IsAuthenticated)
            {
                Handler.CurrentRole = null;
                FormsAuthentication.SignOut();
                Response.Redirect("~/");
            } else
            {
                FormsAuthentication.RedirectToLoginPage();
            }
        }
    }
}