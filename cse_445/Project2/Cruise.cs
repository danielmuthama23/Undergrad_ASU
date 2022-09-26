using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Project2.TicketAgent;

namespace Project2
{
    internal class Cruise
    {
        public static event PriceCutEventHandler? priceCut; // event handler

        private int price;
        private int priceCutCounter = 0;
        private int cur = 0; // index of thread #
        private const int T = 10; // max number of price cuts before terminating

        public Cruise() // constructor
        {
            price = pricingModel();
        }

        // main cruise method called from thread
        public void runCruise()
        {
            while (priceCutCounter < T) // run until the price cut counter reaches the max
            {
                Thread.Sleep(Program.rand.Next(1000, 3000));
                changePrice(pricingModel());
            }
            // Console.WriteLine("\nProcess killed... max price counts ({0}) reached!\n", T);    
            Program.cruiseThreadTerminated = true;
        }

        // change price based on random input
        public void changePrice(int newPrice)
        {
            if (cur == Program.ticketAgentThreads.Length)
            {
                cur = 0;
            }

            if (priceCut != null)
            {
                // compare the new and the old price
                if (newPrice < price)
                {
                    priceCut(Program.ticketAgentThreads[cur].Name, newPrice);
                    priceCutCounter++;
                    cur++;
                }

                // set price if there is a change
                if (price != newPrice)
                    price = newPrice;
            }
        }

        // get random price
        public int pricingModel() { return Program.rand.Next(40, 200); }

        // get from multi cell and start thread
        public void onOrderCreated()
        {
            OrderClass order = Program.multiCell.getOneCell();
            Thread thread = new Thread(() => OrderProcessing.processOrder(order, price));
            thread.Start();
        }
    }
}
