using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class Cruise
    {
        private static readonly Random rand = new Random();

        private int price;

        public Cruise()
        {
            price = pricingModel();
        }

        public void runCruise()
        {

        }

        public int pricingModel()
        {
            return rand.Next(40, 200);
        }
    }
}
