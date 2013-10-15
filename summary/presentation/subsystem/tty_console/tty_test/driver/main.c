#define pr_fmt(fmt)	"[azhe]" fmt

#include <linux/module.h> 
#include <linux/moduleparam.h> 
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/kernel.h>       /* pr_info() */
#include <linux/slab.h>         /* kmalloc() */
#include <linux/fs.h>           /* everything... */
#include <linux/errno.h>        /* error codes */
#include <linux/types.h>        /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>        /* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>    
#include <asm/system.h>         /* cli(), *_flags */
#include <asm/uaccess.h>        /* copy_*_user */
#include <linux/delay.h>

#include <linux/cdev.h>  
#include <linux/tty.h>  
#include <linux/fs.h>  
#include <linux/tty_driver.h>  
#include <linux/tty_flip.h>  
#include <linux/ioport.h>  
#include <linux/serial_reg.h>  
  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("azhe_liu");  
 
#define TTY_azhe_MINORS_NUM    5  
#define TTY_azhe_LINE		0
#define TTY_azhe_MAJOR        202  
static struct tty_driver *tty_azhe_driver;  
  
static int tty_azhe_open(struct tty_struct *tty, struct file *filp);  
static void tty_azhe_close(struct tty_struct *tty, struct file *filp);  
static int tty_azhe_write(struct tty_struct *tty, const unsigned char *buffer, int count);  
static int tty_azhe_write_room(struct tty_struct *tty);  
static void tty_azhe_set_termios(struct tty_struct *tty, struct ktermios * old);  
static int tty_azhe_put_char(struct tty_struct *tty, unsigned char ch);  
  
static struct tty_operations tty_azhe_ops = {  
    .open = tty_azhe_open,  
    .close = tty_azhe_close,  
    .write = tty_azhe_write,  
    .put_char = tty_azhe_put_char,  
    .write_room = tty_azhe_write_room,  
    .set_termios = tty_azhe_set_termios,  
};  
  
  
static int __init tty_azhe_init(void)  
{  
    //int i;  
    int retval;  
      
    tty_azhe_driver = alloc_tty_driver(TTY_azhe_MINORS_NUM); 

    if(!tty_azhe_driver)  
        return -ENOMEM;  
      
    tty_azhe_driver->owner = THIS_MODULE;  
    tty_azhe_driver->driver_name = "tty_azhe";  
    tty_azhe_driver->name = "ttty_azhe";  
    tty_azhe_driver->major = TTY_azhe_MAJOR;  
    tty_azhe_driver->minor_start = 0;      
    tty_azhe_driver->type = TTY_DRIVER_TYPE_SERIAL;  
    tty_azhe_driver->subtype = SERIAL_TYPE_NORMAL;  
    tty_azhe_driver->flags = TTY_DRIVER_REAL_RAW;  
    tty_azhe_driver->init_termios = tty_std_termios;  
    tty_azhe_driver->init_termios.c_cflag = B115200 | CS8 | CREAD | HUPCL | CLOCAL;  
    tty_set_operations(tty_azhe_driver, &tty_azhe_ops);  
  
    retval = tty_register_driver(tty_azhe_driver);  
    if(retval){  
        pr_info("%s:Failed to register tty_azhe_driver!\n", __func__);  
        put_tty_driver(tty_azhe_driver);  
        return retval;  
    }  
 /*
    for(i = 0; i < TTY_azhe_MINORS_NUM; i++)  
        tty_register_device(tty_azhe_driver, i, NULL);  
*/
    pr_info("%s ok!\n", __func__);
    return 0;  
}  
  
static int tty_azhe_open(struct tty_struct *tty, struct file *filp)  
{  
    pr_info("%s:Open OK!\n", __func__);  

    tty->low_latency = 1;   
    return 0;  
}  
  
static void tty_azhe_close(struct tty_struct *tty, struct file *filp)  
{  
    pr_info("%s:ClOSE OK!\n", __func__); 
    return;  
}  
  
static int tty_azhe_write(struct tty_struct *tty, const unsigned char *buffer, int count)  
{  
    int retval = count;   
    pr_info("%s:count :%d\n", __func__, count);  
    pr_info("%s:user write: %s \n", __func__, buffer);  
    tty_insert_flip_string(tty, buffer, count);  
    tty_flip_buffer_push(tty);  
      
    return retval;  
}  
  
static int tty_azhe_put_char(struct tty_struct *tty, unsigned char ch)  
{  
      
    pr_info("%s:put_char :%c\n", __func__, ch);  
    return 0;  
}  
  
  
static int tty_azhe_write_room(struct tty_struct *tty)  
{  
    int room;  
    room = 255;
    pr_info("%s: room =%d\n", __func__, room);
    return room;  
}  
  
static void tty_azhe_set_termios(struct tty_struct *tty, struct ktermios *old)  
{  
    if(tty->termios->c_cflag == old->c_cflag){  
        pr_info("%s:Nothing to change!\n", __func__);  
        return ;  
    }  
    pr_info("%s:There is something to Change............\n", __func__);  
    return ;  
}  
  
static void __exit tty_azhe_exit(void)  
{  
/* 
    int i; 

    for(i = 0; i < TTY_azhe_MINORS_NUM; i++)  
        tty_unregister_device(tty_azhe_driver, i); 
*/ 
    tty_unregister_driver(tty_azhe_driver);  
    pr_info("%s\n", __func__);
}  
  
module_init(tty_azhe_init);  
module_exit(tty_azhe_exit);

