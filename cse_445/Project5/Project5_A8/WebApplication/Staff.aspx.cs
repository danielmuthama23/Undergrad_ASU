using Providers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Web;
using System.Web.Configuration;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;

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

        // handle add staff button click
        protected void AddStaffButton_Click(object sender, EventArgs e)
        {
            if (
                StaffUsernameInput.Text != "" &&
                StaffPasswordInput.Text != "" &&
                StaffFullNameInput.Text != "" &&
                StaffEmailInput.Text != ""
            )
            {
                string username = StaffUsernameInput.Text;
                string password = StaffPasswordInput.Text;
                string fullName = StaffFullNameInput.Text;
                string email = StaffEmailInput.Text;

                if (!isNewUser(username))
                {
                    StaffAddResponse.Text = "Username already taken!";
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
                    StaffAddResponse.Text = "Invalid password! Please double check the requirements.";
                    return;
                }

                // check if email is valid
                if (
                    email == null ||
                    !(new Regex(@"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$").IsMatch(email))
                )
                {
                    StaffAddResponse.Text = "Invalid email!";
                    return;
                }

                string encryptedPass = Crypt.Crypt.Encrypt(password);
                addToXmlFile(
                    username,
                    encryptedPass,
                    fullName,
                    email
                );
                StaffUsernameInput.Text = "";
                StaffPasswordInput.Text = "";
                StaffFullNameInput.Text = "";
                StaffEmailInput.Text = "";
                StaffAddResponse.Text = "Successfuly added " + username + " as a staff member!";
            }
        }

        // handle the submit button for WeatherService
        protected void GetWeather_Click(object sender, EventArgs e)
        {
            // make sure input isnt blank before sending request
            if (ZipcodeInput.Text != "")
            {
                // send request using inputted data
                WeatherServiceReference.WeatherService service1 = new WeatherServiceReference.WeatherServiceClient();
                string[] data = service1.Weather5Day(ZipcodeInput.Text);
                string formatted = ""; // format the array into readable string
                for (int i = 0; i < data.Length; i++)
                {
                    formatted += data[i] + " <br>";
                }
                Label7.Text = formatted; // display formatted info
            }
        }

        // check if the user is new by search xmls
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

        // add the info to Staff.xml
        private void addToXmlFile(string u, string encryPass, string fn, string em)
        {
            string path = HttpContext.Current.Server.MapPath(@"~/App_Data/Staff.xml");

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