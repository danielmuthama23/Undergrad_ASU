using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class OrderProcessing
    {
        public void runOrderProcessing()
        { 

        }

        public static Boolean isValidCard(int cardNo)
        {
            return cardNo >= 3000 && cardNo <= 3999;
        }
    }
}
