using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class OrderProcessing
    {
        public static event OrderProcessedEventHandler orderProcessed; // event handler
        
        private const double TAX = 0.11; // 11% tax
        
        // process order emit
        public static void processOrder(OrderClass order, int price)
        { 
            if (!isValidCard(order.getCardNo()))
            {
                Console.WriteLine("[TicketAgent{0}] {1} is not a valid credit card number.", order.getSenderId(), order.getCardNo());
                return;
            }
            double chargeAmt = getChargedAmount(order.getUnitPrice(), order.getQuantity());
            orderProcessed(order.getSenderId(), order.getCardNo(), order.getQuantity(), order.getUnitPrice());
        }

        // helper for calculating total price including tax
        public static double getChargedAmount(double unitPrice, int quantity)
        {
            return (1 + TAX) * unitPrice * quantity;
        }

        // check if card is in the range of [3000, 4000)
        public static bool isValidCard(int cardNo)
        {
            return cardNo >= 3000 && cardNo <= 3999;
        }
    }
}
