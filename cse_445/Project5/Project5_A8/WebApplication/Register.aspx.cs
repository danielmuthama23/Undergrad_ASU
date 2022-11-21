using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Xml;
using System.Web.UI.WebControls;
using System.Text.RegularExpressions;
using System.Web.Security;
using Crypt;
using Providers;

namespace WebApplication
{
    public partial class Register : Page
    {
        // load captcha at page load
        protected void Page_Load(object sender, EventArgs e)
        {
            string VERIFIER_API_LINK = "https://venus.sod.asu.edu/WSRepository/Services/ImageVerifier/Service.svc/GetImage/";

            VerifierImage.ImageUrl = VERIFIER_API_LINK + Handler.VerifyImageCode;
        }

        // handle register button click
        protected void RegisterButton_Click(object sender, EventArgs e)
        {
            if (
                UsernameInput.Text != "" &&
                PasswordInput.Text != "" &&
                FullNameInput.Text != "" &&
                EmailInput.Text != "" &&
                ImageVerifyText.Text != ""
            )
            {
                if (ImageVerifyText.Text != Handler.VerifyImageCode)
                {
                    //Handler.VerifyImageCode = Handler.getVerifyCode();
                    RegisterResLabel.Text = "Invalid image verifier text!";
                    return;
                }

                string username = UsernameInput.Text;
                string password = PasswordInput.Text;
                string fullName = FullNameInput.Text;
                string email = EmailInput.Text;

                if (!isNewUser(username))
                {
                    RegisterResLabel.Text = "Username already taken!";
                    return;
                }

                // check if valid password
                if (
                    password == null ||
                    !(new Regex(@"[0-9]+").IsMatch(password)) ||
                    !(new Regex(@"[A-Z]+").IsMatch(password)) ||
                    password.Length < 8
                )
                {
                    RegisterResLabel.Text = "Invalid password! Please double check the requirements.";
                    return;    
                }

                // check if email is valid
                if (
                    email == null ||
                    !(new Regex(@"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$").IsMatch(email))
                )
                {
                    RegisterResLabel.Text = "Invalid email!";
                    return;
                }

                string encryptedPass = Crypt.Crypt.Encrypt(password);
                addToXmlFile(
                    UsernameInput.Text,
                    encryptedPass,
                    FullNameInput.Text,
                    EmailInput.Text
                );
                FormsAuthentication.RedirectFromLoginPage(username, true);
            }
        }

        // checks if a username alread exists in either Member.xml or Staff.xml
        private bool isNewUser(string username)
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
                    if (info != null && info.InnerText == username)
                    {
                        stream.Close();
                        return false;
                    }
                }

                stream.Close();
            }

            return true;
        }

        // add the info to Member.xml
        private void addToXmlFile(string u, string encryPass, string fn, string em)
        {
            string path = HttpContext.Current.Server.MapPath(@"~/App_Data/Member.xml");

            System.IO.FileStream stream = new System.IO.FileStream(path, System.IO.FileMode.Open);

            XmlDocument doc = new XmlDocument();
            doc.Load(stream);

            XmlNode username = doc.CreateElement("Username");
            username.InnerText = u;
            XmlNode pass = doc.CreateElement("EncryptedPass");
            pass.InnerText = encryPass;
            XmlNode fullName = doc.CreateElement("FullName");
            fullName.InnerText = fn;
            XmlNode email = doc.CreateElement("Email");
            email.InnerText = em;

            XmlNode user = doc.CreateElement("Member");
            user.AppendChild(username);
            user.AppendChild(pass);
            user.AppendChild(fullName);
            user.AppendChild(email);

            doc.DocumentElement.AppendChild(user);

            stream.Position = 0;
            doc.Save(stream);

            stream.Close();
        }
    }
}