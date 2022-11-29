using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;

namespace Providers
{
    public static class Handler
    {
        // vars to store per session
        public static string CurrentRole = null;
        public static string CurrentName = null;
        public static string CurrentEmail = null;
        public static string VerifyImageCode = getVerifyCode();

        // verify code gen for 5 char code
        public static string getVerifyCode()
        {
            string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

            var random = new Random();

            string res = "";

            // verify using 5 characters
            for (int i = 0; i < 5; i++)
            {
                res += chars[random.Next(chars.Length)];
                //System.Diagnostics.Debug.WriteLine(verifyImgText);
            }

            return res;
        }
    }

    // handler to use with formsauth that refs xml files
    public class CustomRoleProvider : RoleProvider
    {

        public override string ApplicationName { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public override void AddUsersToRoles(string[] usernames, string[] roleNames)
        {
            throw new NotImplementedException();
        }

        public override void CreateRole(string roleName)
        {
            throw new NotImplementedException();
        }

        public override bool DeleteRole(string roleName, bool throwOnPopulatedRole)
        {
            throw new NotImplementedException();
        }

        public override string[] FindUsersInRole(string roleName, string usernameToMatch)
        {
            throw new NotImplementedException();
        }

        public override string[] GetAllRoles()
        {
            throw new NotImplementedException();
        }

        public override string[] GetRolesForUser(string username)
        {
            //System.Diagnostics.Debug.WriteLine("here2");
            if (Handler.CurrentRole != null)
            {
                return new string[] { Handler.CurrentRole };
            }
            return new string[] { }; 
        }

        public override string[] GetUsersInRole(string roleName)
        {
            throw new NotImplementedException();
        }

        public override bool IsUserInRole(string username, string roleName)
        {
            //System.Diagnostics.Debug.WriteLine("here1");
            return Handler.CurrentRole != null;
        }

        public override void RemoveUsersFromRoles(string[] usernames, string[] roleNames)
        {
            throw new NotImplementedException();
        }

        public override bool RoleExists(string roleName)
        {
            throw new NotImplementedException();
        }
    }
}