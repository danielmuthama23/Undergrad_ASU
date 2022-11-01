// file: /home/tyler/project_2/producer_consumer.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/slab.h>

#define BUFFER_SIZE 2000

// declare the three semaphores
struct semaphore mutex; // define mutex semaphore
struct semaphore empty; // define empty semaphore
struct semaphore full; // define full semaphore

// declare the four module parameters
static int buffSize = 0; // the buffer size
static int prod = 0; // number of producers (0 or 1)
static int cons = 0; // number of consumers (>0)
static int uuid = 0; // the UID of the user (`id -u <username>`)

// parse all four arguments
module_param(buffSize, int, 0644);
module_param(prod, int, 0644);
module_param(cons, int, 0644);
module_param(uuid, int, 0644);

// declare the two kernel threads
struct task_struct* ts_producer;
struct task_struct* ts_consumer;
struct task_struct* ts_consumer2;

// declare the shared buffer
struct task_struct* BUFFER[BUFFER_SIZE];

// define the in and out variables
int in = 0;
int out = 0;

bool is_running = true;

// variable to hold the sum of all elapsed_time's
unsigned long long total_elapsed_time;

/* convert the difference between nanoseconds to HH:MM:SS */
char* nanoseconds_to_format(unsigned long long ns_diff) {
  // define vars
  long seconds;
  int hours, mins;
  char* formatted = (char*)kmalloc(8 * sizeof(char), GFP_KERNEL);

  // convert to seconds
  seconds = ns_diff / 1000000000;

  // convert to hours
  seconds = seconds % (24 * 3600);
  hours = seconds / 3600;

  // convert to mins
  seconds %= 3600;
  mins = seconds / 60;

  // finalize seconds
  seconds %= 60;

  // make formatted string to return
  sprintf(formatted, "%d:%d:%d", hours, mins, (int)seconds);

  return formatted;
}

static int producer_thread_func(void *arg) {
  struct task_struct* p;
  int item_number = 1;

  for_each_process(p) {
    if (p->cred->uid.val == uuid) {
      // signal down
      if (down_interruptible(&empty)) {
        break;
      }
      if (down_interruptible(&mutex)) {
        break;
      }

      if (!is_running) {
        break;
      }

      // store process in buffer
      BUFFER[in] = p;

      printk(
        "[%s] Produced Item#-%d at buffer index: %d for PID:%d\n",
        ts_producer->comm,
        item_number,
        in,
        p->pid
      );

      item_number++;

      // recalculate in
      in = (in + 1) % buffSize;

      // signal up
      up(&mutex);
      up(&full);
    }
  }

  return 0;
}

static int consumer_thread_func(void *arg) {
  struct task_struct* item;
  int item_number = 1;
  unsigned long long ns_diff;
  char* elapsed_time;

  while (true) {
    // signal down
    if (down_interruptible(&full)) {
      break;
    }
    if (down_interruptible(&mutex)) {
      break;
    }

    if (!is_running) {
      break;
    }

    // grab item from buffer
    item = BUFFER[out];

    ns_diff = ktime_get_ns() - item->start_time;

    total_elapsed_time += ns_diff;

    elapsed_time = nanoseconds_to_format(ns_diff);

    printk(
      "[%s] Consumed Item#-%d on buffer index: %d PID:%d Elapsed Time-%s\n",
      ts_consumer->comm,
      item_number,
      out,
      item->pid,
      elapsed_time
    );

    item_number++;

    // recalculate out
    out = (out + 1) % buffSize;

    // signal up
    up(&mutex);
    up(&empty);
  }

  return 0;
}

/* main module entry point upon load */
int producer_consumer(void) {
  printk("-----Starting Producer Consumer-----\n");

  // initalize all three semaphores
  sema_init(&mutex, 1); // init mutex to 1
  sema_init(&full, 0); // init full to 0
  sema_init(&empty, buffSize); // init empty to buffer size

  if (prod > 0) {
    ts_producer = kthread_run(producer_thread_func, NULL, "prod-thread");
  }

  // handle multiple consumers test case
  if (cons > 0) {
    ts_consumer = kthread_run(consumer_thread_func, NULL, "cons-thread");
  }
  if (cons > 1) {
    ts_consumer2 = kthread_run(consumer_thread_func, NULL, "cons-thread");
  }

  return 0;
}

/* main module exit point upon unload */
void producer_consumer_exit(void) {
  char* elapsed_time = nanoseconds_to_format(total_elapsed_time);

  is_running = false;

  up(&empty);
  up(&mutex);
  up(&full);

  printk(
    "The total elapsed time of all processes for UID %d is %s\n",
    uuid,
    elapsed_time
  );
}

module_init(producer_consumer); // defines module init called at load
module_exit(producer_consumer_exit); // defines module exit called at unload
MODULE_LICENSE("GPL"); // defines the license for the module
