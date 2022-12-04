// file: /home/tyler/project_4/proc_filesys.c
#include <linux/kernel.h>   
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/hrtimer.h>
#include <linux/sched/mm.h>
#include <linux/ktime.h>

#define BUFFER_SIZE 1000

// declare the module paramter
static int uuid = 1;

// parse all arguments
module_param(uuid, int, 0644);

// create the proc entries as defined in the doc
static struct proc_dir_entry *proc_dir;
static struct proc_dir_entry *identity;
static struct proc_dir_entry *statistics;

// used for the message payload
char message[BUFFER_SIZE];

// define values
unsigned long rss = 1688;
unsigned long swap = 0;
unsigned long wss = 1688;

// variable to hold the sum of all elapsed_time's
unsigned long long total_elapsed_time;

// convert the difference between nanoseconds to HH:MM:SS
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

void count_pages(struct task_struct *ltask) {
    if (ltask != NULL) {
        const struct vm_area_struct *vma = ltask->mm->mmap;
        while (vma != NULL) {
            unsigned long address;
            for (address = vma->vm_start; address < vma->vm_end; address += PAGE_SIZE) {
                if (ptep_test_and_clear_young(vma, address, pte_by_address(ltask->mm, address)) == 1) {
                    wss = wss + 1;
                }
            }
            vma = vma->vm_next;
        }
    }
}

unsigned long timer_interval_ns = 10e9;
static struct hrtimer hr_timer;
enum hrtimer_restart timer_callback(struct hrtimer *timer_for_restart) {
    ktime_t currtime, interval;
    currtime = ktime_get();
    interval = ktime_set(0, timer_interval_ns);
    hrtimer_forward(timer_for_restart, currtime, interval);
    
    count_pages(task);
    rss = rss * PAGE_SIZE;
    rss = rss / 1024;
    wss = wss * PAGE_SIZE;

    wss = wss / 1024;
    swap = swap * PAGE_SIZE;
    swap = swap / 1024;

    rss = 0;
    wss = 0;
    swap = 0;
    return HRTIMER_RESTART;
}

/*
    file: This is the File Object, pointing to the file from where the data is to be read
    ubuf:  The User space buffer where the data is to be written to
    count: The length of the buffer
    ppos:  The requested position of the data
*/
static ssize_t read_fn(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) {
    char buff[BUFFER_SIZE];
    ssize_t len = 0;

    // catch out of bound err
    if(*ppos > 0 || count < BUFFER_SIZE) {
        return 0;
    }

    // check the incoming message
    if(strcmp(message, "whoami") == 0) {
        // send output as specified in doc
        len += sprintf(buff, "[CSE330][Fall2022][Project-4][ASUID:1218959911][Tyler Fichiera]\n");
    } else {
        pid_t pid; 
        int bytes = sscanf(message, "%d", &pid); // get pid from message
        if(bytes < 0) {
            len += sprintf(buff, "Could not get the process id\n");
        } else {
            char* elapsed = nanoseconds_to_format(total_elapsed_time);
            len += sprintf(
                buff,
                "[PID:%d]-[RSS:%ldKB]-[SWAP:%ldKB]-[WSS=%ldKB]-[ELAPSED TIME=%s]\n",
                pid,
                rss,
                swap,
                wss,
                elapsed
            );
        }
    }

    // send to userspace
    if(copy_to_user(ubuf, buff, len)) {
        return -EFAULT; // send memory address invalid error
    }
    *ppos = len;

    return len;
}

/*
    file: This is the File Object, pointing to the file from where the data is to be written to
    ubuf:  The User space buffer containing the write data
    count: The length of the buffer
    ppos:  The requested position to write the data to
*/
static ssize_t write_fn(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
    char buff[BUFFER_SIZE];
    ssize_t len = 0;

    // catch out of bound err
    if(*ppos > 0 || count > BUFFER_SIZE) {
        return -EFAULT;
    }

    // send to userspace
    if(copy_from_user(buff, ubuf, count)) {
        return -EFAULT; // send memory address invalid error
    }

    sscanf(buff, "%s", message);

    len += strlen(buff); // add bytes count
    *ppos = len;

    return len;
}

// invoke the function pointers defined above and to be used in the creation
static struct proc_ops test_proc_fs = {
    .proc_read = read_fn,
    .proc_write = write_fn,
};

/* main module entry point upon load */
static int proc_filesys_init(void) {
    // create proc directory and entries
    proc_dir = proc_mkdir("cse330", NULL);
    identity = proc_create("identity", 0666, proc_dir, &test_proc_fs);
    statistics = proc_create("statistics", 0666, proc_dir, &test_proc_fs);

	printk(KERN_ALERT "Proc dir and entries created!\n");
	return 0;
}

/* main module exit point upon unload */
static void proc_filesys_exit(void) {
    // remove them in reverse order
    remove_proc_entry("statistics", proc_dir);
    remove_proc_entry("identity", proc_dir);
    proc_remove(proc_dir);

	printk(KERN_WARNING "Proc dir and entries removed!\n");
}

module_init(proc_filesys_init); // defines module init called at load
module_exit(proc_filesys_exit); // defines module exit called at unload
MODULE_LICENSE("GPL"); // defines the license for the module
