using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace TryIt
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        // handle the register button click with all four inputs
        protected void RegisterButton_Click(object sender, EventArgs e)
        {
            if (
                UsernameInput.Text != "" &&
                PasswordInput.Text != "" &&
                FullNameInput.Text != "" &&
                EmailInput.Text != ""
            )
            {
                AuthServiceReference.IService1 authService = new AuthServiceReference.Service1Client();
                string res = authService.Register(UsernameInput.Text, PasswordInput.Text, FullNameInput.Text, EmailInput.Text);
                RegisterResLabel.Text = res;

                // save to cookie
                HttpCookie cookie = new HttpCookie("current_username");
                // Assigning value to the created cookie  
                cookie.Value = UsernameInput.Text;
                cookie.Expires.Add(new TimeSpan(0, 1, 0));
                // Adding Cookie to the response instance  
                Response.Cookies.Add(cookie);

                // clear the inputs
                UsernameInput.Text = "";
                PasswordInput.Text = "";
                FullNameInput.Text = "";
                EmailInput.Text = "";
            }
        }

        // handle the login functionality with both inputs
        protected void LoginButton_Click(object sender, EventArgs e)
        {
            if (UsernameLoginInput.Text != "" && PasswordLoginInput.Text != "")
            {
            AuthServiceReference.IService1 authService = new AuthServiceReference.Service1Client();
            string res = authService.Login(UsernameLoginInput.Text, PasswordLoginInput.Text);
            LoginResLabel.Text = res;

            // save to cookie
            HttpCookie cookie = new HttpCookie("current_username");
            // Assigning value to the created cookie  
            cookie.Value = UsernameInput.Text;
            cookie.Expires.Add(new TimeSpan(0, 1, 0));
            // Adding Cookie to the response instance  
            Response.Cookies.Add(cookie);

            // clear the inputs
            UsernameLoginInput.Text = "";
            PasswordLoginInput.Text = "";
        }
    }

        // get user that is currently stored in cookies and display their account info
        protected void GetUserButton_Click(object sender, EventArgs e)
        {
            string cookie = Request.Cookies["current_username"].Value; // get curr user from cookies
            if (cookie == null || cookie == "")
            {
                AccountInfoLabel.Text = "No user is currently signed in!";
            } else
            {
                AuthServiceReference.IService1 authService = new AuthServiceReference.Service1Client();
                string res = authService.GetUser(cookie);
                AccountInfoLabel.Text = res;
            }
        }

        // get hotels from zipcode and display each on their own line
        protected void GetHotels_Click(object sender, EventArgs e)
        {
            if (HotelZipcodeInput.Text != null)
            {
                string text = "";
                TravelServiceReference.IService1 travelService = new TravelServiceReference.Service1Client();
                string[] res = travelService.GetHotels(HotelZipcodeInput.Text);
                for (int i = 0; i < res.Length; i++) // iterate through all hotels (max 100)
                {
                    text += res[i] + "<br>";
                }
                HotelsLabel.Text = text;
            }
        }

        // get restaurants and display each on their own line
        protected void GetRestaurants_Click(object sender, EventArgs e)
        {
            if (RestaurantZipcodeInput.Text != null)
            {
                string text = "";
                TravelServiceReference.IService1 travelService = new TravelServiceReference.Service1Client();
                string[] res = travelService.GetRestaurants(RestaurantZipcodeInput.Text);
                for (int i = 0; i < res.Length; i++) // iterate through all restaurants (max 100)
                {
                    text += res[i] + "<br>";
                }
                RestaurantsLabel.Text = text;
            }
        }
    }
}