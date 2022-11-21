using Providers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;

namespace WebApplication
{
    public partial class _Default : Page
    {
        // handle page load
        protected void Page_Load(object sender, EventArgs e)
        {
            //System.Diagnostics.Debug.WriteLine("here");
            //System.Diagnostics.Debug.WriteLine(User.IsInRole("Member"));

            // display active users count
            ActiveUsers.Text = "Number of active users: " + Application["numofusers"].ToString();

            // get the current role from xml files and add to custom role provider
            if (User.Identity.IsAuthenticated)
            {
                string[] files = { "Member", "Staff" };

                foreach (string file in files)
                {
                    string path = HttpContext.Current.Server.MapPath(@"~/App_Data/" + file + ".xml");

                    System.IO.FileStream stream = new System.IO.FileStream(path, System.IO.FileMode.Open);

                    XmlDocument doc = new XmlDocument();
                    doc.Load(stream);

                    XmlNode root = doc;
                    XmlNodeList users = root.ChildNodes[1].ChildNodes;

                    foreach (XmlNode user in users)
                    {
                        XmlNode info = user.ChildNodes[0];
                        if (info != null && info.InnerText == User.Identity.Name)
                        {
                            System.Diagnostics.Debug.WriteLine(User.Identity.Name);
                            Handler.CurrentRole = file;
                            Handler.CurrentEmail = user.ChildNodes[3].InnerText;
                            Handler.CurrentName = user.ChildNodes[2].InnerText;
                            stream.Close();
                            return;
                        }
                    }

                    // close file
                    stream.Close();
                }
            }
        }
    }
}