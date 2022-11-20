using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Configuration;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    public partial class Contact : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            // grab the admins stored in appSettings in Web.config
            string[] admins = WebConfigurationManager.AppSettings["ADMINS"].Split(',');
            if (!admins.Contains(User.Identity.Name))
            {
                StaffUsernameInput.Enabled = false;
                StaffPasswordInput.Enabled  = false;
                StaffFullNameInput.Enabled= false;
                StaffEmailInput.Enabled = false;
                AddStaffButton.Enabled = false;
                return;
            }
        }

        protected void AddStaffButton_Click(object sender, EventArgs e)
        {

        }
    }
}