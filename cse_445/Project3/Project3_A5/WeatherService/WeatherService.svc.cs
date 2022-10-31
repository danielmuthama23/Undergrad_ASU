using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Security.Policy;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using Newtonsoft.Json;

namespace WeatherService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : WeatherService
    {
        public string[] Weather5Day(string zipcode)
        {
            // build endpoint with zipcode
            string endpoint = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/" + zipcode + "/?key=NWBJ7784YXHV3GCDQ3ZA6ZJVC";
            
            // store results here
            string[] result = new string[5];

            using (var webClient = new System.Net.WebClient())
            {
                try
                {
                    var json = webClient.DownloadString(endpoint); // Retrieves JSON
                    dynamic obj = JsonConvert.DeserializeObject<dynamic>(json); // Creates object to deserialize JSON 

                    for (int i = 0; i < 5; i++)
                    {
                        string tempStr = ""; // hold temp info

                        // get desired data
                        tempStr += "Date: " + (string)obj["days"][i]["datetime"] + "<br>";
                        tempStr += "Current Temperature: " + (string)obj["days"][i]["temp"] + "<br>";
                        tempStr += "Min Temperature: " + (string)obj["days"][i]["tempmin"] + "<br>";
                        tempStr += "Max Temperature: " + (string)obj["days"][i]["tempmax"] + "<br>";
                        tempStr += "Max Temperature: " + (string)obj["days"][i]["tempmax"] + "<br>";
                        tempStr += "Conditions: " + (string)obj["days"][i]["conditions"] + "<br>";

                        result[i] = tempStr; // store in array
                    }
                }
                catch
                {
                    // display errors
                    string[] err = new string[1];
                    err[0] = "Error retrieving info for zipcode " + zipcode;
                    return err;
                }
            }

            return result;
        }
    }
}
