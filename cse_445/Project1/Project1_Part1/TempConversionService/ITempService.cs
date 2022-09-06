using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace TempConversionService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface ITempService
    {
        // include two operation contracts for the two conversions
        [OperationContract]
        int c2f(int c);

        [OperationContract]
        int f2c(int f);
    }
}
