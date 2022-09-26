using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class OrderClass
    {
        private string senderId;
        private int cardNo;
        private int quantity;
        private double unitPrice;

        // constructor with 4 args
        public OrderClass(string senderId, int cardNo, int quantity, double unitPrice)
        {
            this.senderId = senderId;
            this.cardNo = cardNo;
            this.quantity = quantity;
            this.unitPrice = unitPrice;
        }

        // getters
        public string getSenderId() { return senderId; }
        public int getCardNo() { return cardNo; }
        public int getQuantity() { return quantity; } 
        public double getUnitPrice() { return unitPrice; } 

    }
}
