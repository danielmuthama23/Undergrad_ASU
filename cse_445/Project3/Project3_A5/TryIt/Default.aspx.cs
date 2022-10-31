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

        // handle the submit button for WebDownloading
        protected void UrlSubmit_Click(object sender, EventArgs e)
        {
            // make sure input isnt blank before sending request
            if (UrlInput.Text != "")
            {
                // send request using inputted data
                WebDownloadingService.WebDownloadingService service1 = new WebDownloadingService.WebDownloadingServiceClient();
                string data = service1.WebDownload(UrlInput.Text);
                Label4.Text = data; // display data
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
                Label5.Text = formatted; // display formatted info
            }
        }
    }
}