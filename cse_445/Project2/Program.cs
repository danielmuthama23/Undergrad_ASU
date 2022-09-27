using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    public delegate void PriceCutEventHandler(string senderId, int priceCut);
    public delegate void OrderProcessedEventHandler(string senderId, int cardNo, int quantity, double unitPrice);
    public delegate void OrderCreatedEventHandler();

    internal class Program
    {
        public static readonly int THREADS_N = 5; // N = 5

        public static bool cruiseThreadTerminated = false; // used to terminate the thread

        public static Thread[] ticketAgentThreads = new Thread[THREADS_N]; // list of all running threads

        // multi cell buffer class that can be called from anywhere
        public static MultiCellBuffer multiCell = new MultiCellBuffer(); 

        // instantiated here rather than redoing it in multiple places
        public static readonly Random rand = new Random();
        public static void Main()
        {
            // create cruise and ticket agent
            Cruise cruise = new();
            TicketAgent ticketAgent = new();

            // start threads
            Thread cruiseThread = new(new ThreadStart(cruise.runCruise));
            cruiseThread.Start();

            // register event handlers
            Cruise.priceCut += new PriceCutEventHandler(ticketAgent.onPriceCut);
            OrderProcessing.orderProcessed += new OrderProcessedEventHandler(ticketAgent.onOrderProcessed);
            TicketAgent.orderCreated += new OrderCreatedEventHandler(cruise.onOrderCreated);

            // create 5 threads
            for (int i = 0; i < THREADS_N; i++)
            {
                ticketAgentThreads[i] = new(new ThreadStart(ticketAgent.runTicketAgent));
                ticketAgentThreads[i].Name = (i + 1).ToString();
                ticketAgentThreads[i].Start();
            }
        }
    }
}
