using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using RestSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Xml.Linq;

namespace CurrencyConverter
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        Dictionary<string, string> countries;

        //retrieve available countries for cmbo box
        public Dictionary<string, string> GetCountries()
        {
            if (countries == null)
            {
                //create dictionary with value and key pair
                countries = new Dictionary<string, string>();
                string countryResponse = getResponseString($"exchangerates_data/symbols");

                Dictionary<string, object> responseData = JsonConvert.DeserializeObject<Dictionary<string, object>>(countryResponse);
                if ((bool)responseData["success"])
                {
                    var tempSymbols = (JObject)responseData["symbols"];
                    countries = tempSymbols.ToObject<Dictionary<string, string>>();
                }
            }

            return countries;
        }

        //retrieve data from api
        private string getResponseString(string relURI)
        {
            var client = new RestClient("https://api.apilayer.com/");

            var request = new RestRequest(relURI, Method.Get);
            request.AddHeader("apikey", "4Z8UBaRVJZu4V9OJ5caZsWsV20nHcbc5");

            RestResponse response = client.Execute(request);
            return response.Content;
        }

        //convert currencies
        public double Convert(string fromCurrency, string toCurrency, double fromCurrencyAmount)
        {
            //plug in values from application
            string responseContent = getResponseString($"exchangerates_data/convert?to={toCurrency}&from={fromCurrency}&amount={fromCurrencyAmount}");

            //convert data to dictionary
            Dictionary<string, object> responseData = JsonConvert.DeserializeObject<Dictionary<string, object>>(responseContent);

            if ((bool)responseData["success"])
            {
                return (double)responseData["result"];
            }
            else
            {
                return -1;
            }

        }
    }
}
