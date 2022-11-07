using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using Newtonsoft.Json;

namespace TravelService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        // helper function used in both services to get lat/lon
        public string[] GetLatLon(string zipcode)
        {
            string[] data = new string[2];
            using (var webClient = new System.Net.WebClient())
            {
                try
                {
                    string zipEndpoint = "https://api.geoapify.com/v1/geocode/search?text=" + zipcode + "&lang=en&limit=10&type=postcode&filter=countrycode:us&&format=json&apiKey=d548c5ed24604be6a9dd0d989631f783";
                    var json = webClient.DownloadString(zipEndpoint); // Retrieves JSON
                    dynamic obj = JsonConvert.DeserializeObject<dynamic>(json); // Creates object to deserialize JSON
                    dynamic res = obj["results"][0];
                    data[0] = res["lat"];
                    data[1] = res["lon"];
                    return data; // store and return as 2 length array
                }
                catch
                {
                    return data; // return null array of length 2 if theres an error
                }
            }
        }
        public string[] GetHotels(string zipcode)
        {
            List<string> hotels = new List<string>();

            string[] latlon = GetLatLon(zipcode); // get lon and lat as array
            if (latlon[1] == null)
            {
                hotels.Add("Error grabbing lat and long from zipcode!");
                return hotels.ToArray();
            }

            // setup web client
            using (var webClient = new System.Net.WebClient())
            {
                try
                {
                    string placesEndpoint = "https://api.geoapify.com/v2/place-details?lat=" + latlon[0] + "&lon=" + latlon[1] + "&features=drive_15.hotel&apiKey=d548c5ed24604be6a9dd0d989631f783";
                    var json = webClient.DownloadString(placesEndpoint); // Retrieves JSON
                    dynamic obj = JsonConvert.DeserializeObject<dynamic>(json); // Creates object to deserialize JSON
                    foreach (dynamic f in obj["features"])
                    {
                        dynamic p = f["properties"];
                        hotels.Add((string)p["name"]); // add the name of the hotels to list
                    }
                }
                catch
                {
                    hotels.Add("Error grabbing featured hotels!");
                    return hotels.ToArray();
                }
            }

            // remove the first hotel which is always set to null
            if (hotels.Count > 0)
            {
                hotels.RemoveAt(0);
            }

            return hotels.ToArray();
        }

        public string[] GetRestaurants(string zipcode)
        {
            List<string> hotels = new List<string>();

            string[] latlon = GetLatLon(zipcode); // get lat and lon
            if (latlon[1] == null)
            {
                hotels.Add("Error grabbing lat and long from zipcode!");
                return hotels.ToArray();
            }

            using (var webClient = new System.Net.WebClient())
            {
                try
                {
                    string placesEndpoint = "https://api.geoapify.com/v2/place-details?lat=" + latlon[0] + "&lon=" + latlon[1] + "&features=radius_1000.restaurant&apiKey=d548c5ed24604be6a9dd0d989631f783";
                    var json = webClient.DownloadString(placesEndpoint); // Retrieves JSON
                    dynamic obj = JsonConvert.DeserializeObject<dynamic>(json); // Creates object to deserialize JSON
                    foreach (dynamic f in obj["features"])
                    {
                        dynamic p = f["properties"];
                        hotels.Add((string)p["name"]); // add restaurants to the list
                    }
                }
                catch
                {
                    hotels.Add("Error grabbing featured restaurants!");
                    return hotels.ToArray();
                }
            }

            // remove the first hotel which is always set to null
            if (hotels.Count > 0)
            {
                hotels.RemoveAt(0);
            }

            return hotels.ToArray();
        }
    }
}
