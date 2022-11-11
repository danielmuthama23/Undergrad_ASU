using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.NetworkInformation;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Web;
using System.Text.RegularExpressions;

namespace AuthService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        private const string DATA_FILENAME = "userinfo.txt"; // constant file for all data writing/reading

        public string Register(string username, string password, string fullName, string email)
        {
            string fLocation = Path.Combine(HttpRuntime.AppDomainAppPath, @"App_Data"); // Get path from server root to current
            fLocation = Path.Combine(fLocation, DATA_FILENAME); // From current to App_Data

            string userInfoLine = username + "|" + password + "|" + fullName + "|" + email;

            // check if user already exists
            using (StreamReader sr = File.OpenText(fLocation))
            {
                while (!sr.EndOfStream)
                {
                    string line = sr.ReadLine();
                    string[] spl = line.Split('|'); // split and user info as defined in Register
                    if (username == spl[0]) // check username match
                        return "A user with username " + username + " already exists!";
                    if (username == spl[3]) // check email match
                        return "A user with email " + email + " already exists!";
                }
            }

            // check if valid password
            if (
                password == null ||
                !(new Regex(@"[0-9]+").IsMatch(password)) ||
                !(new Regex(@"[A-Z]+").IsMatch(password)) ||
                password.Length < 8
            )
            {
                return "Invalid password! Please double check the requirements.";
            }

            // check if email is valid
            if (
                email == null ||
                !(new Regex(@"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$").IsMatch(email))
            )
            {
                return "Invalid email!";
            }

            // write to file
            using (StreamWriter sw = File.CreateText(fLocation))
            {
                sw.WriteLine(userInfoLine);
            }

            return "Successfully created account for " + username + "!";
        }

        public string Login(string username, string password)
        {
            string fLocation = Path.Combine(HttpRuntime.AppDomainAppPath, @"App_Data"); // From server root to current
            fLocation = Path.Combine(fLocation, DATA_FILENAME); // From current to App_Data

            using (StreamReader sr = File.OpenText(fLocation))
            {
                while (!sr.EndOfStream) // read all lines in the file
                {
                    string line = sr.ReadLine();
                    string[] spl = line.Split('|'); // split and user info as defined in Register
                    if (username == spl[0] && password == spl[1])
                    {
                        return "Successfuly logged in user " + username + "!";
                    }
                }
            }
            return "Unsuccessful login attempt!";
        }

        // get user info to display on client without the password visable
        public string GetUser(string username)
        {
            string fLocation = Path.Combine(HttpRuntime.AppDomainAppPath, @"App_Data"); // From server root to current
            fLocation = Path.Combine(fLocation, DATA_FILENAME); // From current to App_Data

            using (StreamReader sr = File.OpenText(fLocation))
            {
                while (!sr.EndOfStream) // read all lines
                {
                    string line = sr.ReadLine();
                    string[] spl = line.Split('|'); // split and user info as defined in Register
                    if (username == spl[0])
                    {
                        string formatted = "Username: " + spl[0] + "<br>" +
                            "Password: " + new string('*', spl[1].Length) + "<br>" + // ex/ "Password1" = "*********"
                            "Name: " + spl[2] + "<br>" +
                            "Email: " + spl[3];
                        return formatted;
                    }
                }
            }
            return "Could not find user with username " + username + "!";
        }
    }
}
