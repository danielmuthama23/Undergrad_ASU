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

namespace TextTranslator
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        //retrive list of lanuages to populate combobox
        public string[] GetLanguages()
        {

            string languageResponse = getResponseStringLa($"language_translation/languages");

            JObject responseData = JsonConvert.DeserializeObject<JObject>(languageResponse);

            //only retrieve language values
            JToken tempLanguages = responseData["languages"];
            string[] langs = new string[46];
            for (int i = 0; i < 46; i++)
            {
                string l = (string)tempLanguages[i]["language"];
                langs[i] = l;
            }
            return langs;

        }

        //client and request variables to interact with api
        private string getResponseStringLa(string relURI)
        {
            var client = new RestClient("https://api.apilayer.com/");

            var request = new RestRequest(relURI, Method.Get);
            request.AddHeader("apikey", "4Z8UBaRVJZu4V9OJ5caZsWsV20nHcbc5");

            RestResponse response = client.Execute(request);
            return response.Content;
        }

        //translate text
        public string Translate(string target, string body)
        {
            //plug in target language from application into api
            var client = new RestClient("https://api.apilayer.com/language_translation/translate?target=" + target);

            //post rather than get method
            var request = new RestRequest()
            {
                Method = Method.Post
            };

            request.AddHeader("apikey", "4Z8UBaRVJZu4V9OJ5caZsWsV20nHcbc5");

            request.AddParameter("text/plain", body, ParameterType.RequestBody);

            RestResponse response = client.Execute(request);

            string languageResponse = response.Content;

            dynamic responseData = JsonConvert.DeserializeObject<dynamic>(languageResponse);


            string translatedText;
            try
            {
                translatedText = responseData["translations"][0]["translation"];
            } catch
            {
                translatedText = "Unable to get a translation for the input.";
            }

            return translatedText;
        }
    }
}

