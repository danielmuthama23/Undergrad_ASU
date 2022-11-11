using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Xml.Schema;
using System.Xml;
using System.Xml.Linq;
using System.Xml.XPath;

namespace WebService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        public string verification(string xmlUrl, string xsdUrl)
        {
            var set = new XmlSchemaSet();

            using (var wc = new WebClient())
            {
                try
                {
                    wc.DownloadString(xmlUrl); // Downloads the XML doc to check that the xml is valid before moving forward
                }
                catch (WebException _e)
                {
                    return "Invalid XML";
                }
            }

            // load xml with try and catch for possible errors
            var xd = new XmlDocument();
            try
            {
                xd.Load(xmlUrl);
            }
            catch (XmlException e)
            {
                return e.ToString();
            }

            try
            {
                set.Add(null, xsdUrl); // Loads the schema into the schema set
            }
            catch
            {
                return "Error with loading one of the supplied urls";
            }

            // grab errors or return "No Error"
            string res = "No Error";
            XDocument.Load(new XmlNodeReader(xd)).Validate(set, (o, e) => // tries to validate the xml document
            {
                res = e.Message;
            });

            return res;
        }

        public string XPathSearch(string xmlUrl, string pathEx)
        {
            // load reader from external url
            XmlTextReader reader = new XmlTextReader(xmlUrl);
            // create xpath document from reader
            XPathDocument dx = new XPathDocument(reader);
            XPathNavigator nav = dx.CreateNavigator();
            XPathNodeIterator iterator = nav.Select(pathEx);

            // iterate through info and then return what is needed
            string res = "";
            while (iterator.MoveNext())
            {
                XPathNodeIterator it = iterator.Current.Select("Name");
                it.MoveNext();
                string data = it.Current.Value;
                res += data + "<br />";
            }

            return res;
        }
    }
}
