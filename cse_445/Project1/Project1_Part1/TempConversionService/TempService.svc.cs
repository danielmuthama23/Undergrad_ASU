using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace TempConversionService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class TempService : ITempService
    {
        // handle the conversion between celsius and fahrenheit both ways
        public int c2f(int c)
        {
            return (int)(c * 1.8 + 32);
        }

        public int f2c(int f)
        {
            return (int)((f - 32) / 1.8);
        }
    }
}
