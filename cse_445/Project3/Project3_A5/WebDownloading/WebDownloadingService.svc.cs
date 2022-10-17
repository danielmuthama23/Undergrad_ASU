using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace WebDownloading
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : WebDownloadingService
    {
        public string WebDownload(string url)
        {
            WebClient myClient = new WebClient(); // create a channel
            byte[] abc = myClient.DownloadData(url); // get download data as byte array
            return System.Text.Encoding.UTF8.GetString(abc); // decode byte array to string and return
        }
    }
}
