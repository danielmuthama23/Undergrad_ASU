using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Web;
using System.Web.Optimization;
using System.Web.Routing;
using System.Web.Security;
using System.Web.SessionState;
using System.Xml;
using Providers;

namespace WebApplication
{
    public class Global : HttpApplication
    {
        void Application_Start(object sender, EventArgs e)
        {
            // Code that runs on application startup
            RouteConfig.RegisterRoutes(RouteTable.Routes);
            BundleConfig.RegisterBundles(BundleTable.Bundles);
            Application["numofusers"] = 0;
        }

        // add +1 to for all application users
        // done by ethan robinson
        void Session_Start(object sender, EventArgs e)
        {
            Application["numofusers"] = (int)Application["numofusers"] + 1;
        }
    }
}