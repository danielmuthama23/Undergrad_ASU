using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class TicketAgent
    {
        public static event OrderCreatedEventHandler? orderCreated; // event handler

        // halled from event handler
        public void onPriceCut(string senderId, int newPrice)
        {
            Console.WriteLine("[TicketAgent{0}] is about to send an order.", senderId);
            sendOrder(senderId);
        }

        // main ticket agent function ran from threads
        public void runTicketAgent()
        {
            while (Program.cruiseThreadTerminated == false)
            {
                Thread.Sleep(Program.rand.Next(1000, 3000)); // simulate thread delay
                sendOrder(Thread.CurrentThread.Name);
            }
        }

        // create and send order to multicell
        private void sendOrder(string senderID)
        {
            // randomly generate info
            int cardNo = Program.rand.Next(2000, 4999);
            int quantity = Program.rand.Next(1, 50);
            int unitPrice = Program.rand.Next(20, 200);

            OrderClass order = new OrderClass(senderID, cardNo, quantity, unitPrice);

            Console.WriteLine("[TicketAgent{0}] order has been created.", senderID);

            Program.multiCell.setOneCell(order);
            orderCreated(); // emit order created event
        }

        // order processor callback
        public void onOrderProcessed(string senderId, int cardNo, int quantity, double unitPrice)
        {
            double chargedAmt = OrderProcessing.getChargedAmount(unitPrice, quantity);
            Console.WriteLine(
                "[TicketAgent{0}] order has been processed. Card {1} charged ${2} for {3} tickets at ${4} each.",
                senderId, cardNo, chargedAmt, quantity, unitPrice
            );
        }
    }
}
