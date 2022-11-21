using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using Crypt;
using Providers;

namespace WebApplication
{
    public partial class Login : Page
    {
        private string role = null;

        // load captcha image on page load
        protected void Page_Load(object sender, EventArgs e)
        {
            string VERIFIER_API_LINK = "https://venus.sod.asu.edu/WSRepository/Services/ImageVerifier/Service.svc/GetImage/";

            VerifierImage.ImageUrl = VERIFIER_API_LINK + Handler.VerifyImageCode;
        }

        // handle login button click
        protected void LoginButton_Click(object sender, EventArgs e)
        {
            if (
                UsernameLoginInput.Text != "" &&
                PasswordLoginInput.Text != "" &&
                ImageVerifyText.Text != ""
            )
            {
                System.Diagnostics.Debug.WriteLine(ImageVerifyText.Text);
                System.Diagnostics.Debug.WriteLine("here: " + Handler.VerifyImageCode);
                if (ImageVerifyText.Text != Handler.VerifyImageCode)
                {
                    //Handler.VerifyImageCode = Handler.getVerifyCode();
                    LoginResMessage.Text = "Invalid image verifier text!";
                    return;
                }

                string username = UsernameLoginInput.Text;
                string password = PasswordLoginInput.Text;

                XmlNodeList info = getValidUserNode(username, password);
                if (info != null)
                {
                    System.Diagnostics.Debug.WriteLine(role);
                    FormsAuthentication.RedirectFromLoginPage(username, RememberMe.Checked);
                    //Roles.AddUserToRole(username, role);
                }
                else
                {
                    LoginResMessage.Text = "Not valid login!";
                }
            }
        }

        private XmlNodeList getValidUserNode(string username, string password)
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
                    XmlNodeList info = user.ChildNodes;
                    //System.Diagnostics.Debug.WriteLine(Crypt.Crypt.Decrypt(info[1].InnerText));
                    if (
                        info[0] != null &&
                        info[0].InnerText == username &&
                        info[1] != null &&
                        Crypt.Crypt.Decrypt(info[1].InnerText) == password
                    )
                    {
                        Handler.CurrentRole = file;
                        stream.Close();
                        return info;
                    }
                }

                stream.Close();
            }

            return null;
        }
    }
}