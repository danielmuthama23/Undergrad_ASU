using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class Program
    {
        private static readonly int THREADS_N = 5;

        public static Thread[] ticketAgentThreads = new Thread[THREADS_N];
        public static void Main()
        {
            Cruise cruise = new();
            TicketAgent ticketAgent = new();

            Thread cruiseThread = new(new ThreadStart(cruise.runCruise));
            cruiseThread.Start();

            for (int i = 0; i < THREADS_N; i++)
            {
                ticketAgentThreads[i] = new(new ThreadStart(ticketAgent.runTicketAgent));
                ticketAgentThreads[i].Name = (i + 1).ToString();
                ticketAgentThreads[i].Start();
            }
        }
    }
}
