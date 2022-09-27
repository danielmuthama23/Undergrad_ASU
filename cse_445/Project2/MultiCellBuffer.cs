using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project2
{
    internal class MultiCellBuffer
    {
        public OrderClass?[] bufferCells;
        private int n = 2;
        private int count = 0;
        private static Semaphore? readPool = null;
        private static Semaphore? writingPool = null;

        public MultiCellBuffer() //constructor 
        {
            lock (this)
            {
                if (n <= Program.THREADS_N)
                {
                    writingPool = new Semaphore(n, n);
                    readPool = new Semaphore(n, n);
                    bufferCells = new OrderClass[n]; // create n cells

                    for (int i = 0; i < n; i++)
                    {
                        bufferCells[i] = null; // make sure all cells are set to null at the beginning
                    }
                }
            }
        }

        // set cell with OrderClass data
        public void setOneCell(OrderClass data)
        {
            writingPool.WaitOne();

            lock (this)
            {
                while (count == n) // wait if the cells are full
                {
                    Monitor.Wait(this);
                }

                for (int i = 0; i < n; i++)
                {
                    if (bufferCells[i] == null) // makes sure there is no data being overwritten 
                    {
                        bufferCells[i] = data;
                        count++;
                        i = n;
                    }
                }
                writingPool.Release();
                Monitor.Pulse(this);
            }
        }

        // get OrderClass data from cell
        public OrderClass getOneCell()
        {
            readPool.WaitOne();
            OrderClass output = null;

            lock (this)
            {
                while (count == 0) // wait if cells are full
                {
                    Monitor.Wait(this);
                }

                for (int i = 0; i < n; i++)
                {
                    if (bufferCells[i] != null) // makes sure there is valid data
                    {
                        output = bufferCells[i];
                        bufferCells[i] = null;
                        count--;
                        i = n;
                    }
                }
                readPool.Release();
                Monitor.Pulse(this);
            }
            return output;
        }
    }
}
