#include <linux/types.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
#include <asm/delay.h>
#include <mach/regs-mem.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <linux/gpio.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio.h>


#define BUZZER_ON  1
#define BUZZER_OFF 3
#define BUZZER_TEST 4


#define DEVICE_MAJOR 235
#define DEVICE_NAME "buzzer"

#define PIN		EXYNOS4_GPX0(0) //pin2
#define PIN2	EXYNOS4_GPD0(2) //pin13

#define S3C2443A_FCLK 400000000

//void s3c_gpio_cfgpin(unsigned int pin, unsigned int function);

typedef struct _BUZZER_PARAM{
		unsigned int num;
	}BUZZER_PARAM;

typedef struct _KEY_PARAM{
		unsigned int state;
	}KEY_PARAM;


#define MS_DELAY(s)   Delay(s<<2)

void Delay(int time)
{

	volatile int i, j = 0;
	volatile static int loop = S3C2443A_FCLK/100000; //4000
	
	for(;time > 0;time--)
		for(i=0;i < loop; i++) { 
			j++; 
		}
}

static void buzzer_off(int buzzer_num)
{
	//int gpj2dat,gpj3dat;
	switch(buzzer_num)
	{
		case 1://buzzer1
		    printk("buzzer_off\n");
		    gpio_direction_output(PIN,0);
		    break;
		case 2://buzzer3
			printk("buzzer_off\n");
		    gpio_direction_output(PIN2,0);
			break;
		default:
			break;
	}
}

static void buzzer_on(int buzzer_num)
{

	//int gpj2dat,gpj3dat;
	switch(buzzer_num)
	{
		case 1://buzzer1
		    printk("buzzer_on\n");
            gpio_direction_output(PIN,1);	
		    break;
		case 2://buzzer3
			printk("buzzer_on\n");
            gpio_direction_output(PIN2,1);	
			break;
		default:
			break;
	}
}

static ssize_t buzzer_read2(struct file *filp,char *buf,size_t count,loff_t *l)
{
	return count;
}

static ssize_t buzzer_write(struct file *filp,const char *buf,size_t count,loff_t *f_ops)
{
	return count;
}

static long buzzer_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	int num;
	printk("cmd=%d\n",cmd);
	switch(cmd)
	{
	case BUZZER_ON:
		printk("on\n");
		ret = copy_from_user(&num, (int*)arg, sizeof(int));
		if (ret != 0)
		{
			printk("gpio_ioctl: copy_from_user failed\n");
			return(-EFAULT);
		}
		printk("num = %d\n",num);
		buzzer_on(num);
		break;	
	case BUZZER_OFF:
		printk("of\n");
		ret = copy_from_user(&num, (int *)arg, sizeof(int));//arg = 3-->num = 3
		if (ret != 0)
		{
			printk("gpio_ioctl: copy_from_user failed\n");
			return(-EFAULT);
		}
		printk("num = %d\n",num);
		buzzer_off(num);
		break;	
	}
	return 0;
}

static int buzzer_open(struct inode *inode, struct file *filp)
{	
	int ret;
	
	printk("open in kernel\n");
	/*ªì©l¤Æ GPIO ±µ¸}*/
	
	ret=gpio_request(PIN,DEVICE_NAME);
	ret=gpio_request(PIN2,DEVICE_NAME);
	
	if(ret<0){
		printk(KERN_EMERG "PIN fail !\n");
		printk( KERN_INFO "%s: %s unable to get TRIG gpio\n", DEVICE_NAME, __func__ );
		gpio_free(PIN);
		gpio_free(PIN2);
		return ret;
	}
	
	// Set gpios directions
	//s3c_gpio_cfgpin(PIN, S3C_GPIO_OUTPUT);
	//gpio_set_value(EXYNOS4_GPB(0),1);
	
	if( gpio_direction_output( PIN, 0) < 0 )	// Set pin 2 as output with default value 0
	{
		printk( KERN_INFO "%s: %s unable to set TRIG gpio as output\n", DEVICE_NAME, __func__ );
		ret = -EBUSY;
		return(ret);
	}
	if( gpio_direction_output( PIN2, 0) < 0 )	// Set pin 2 as output with default value 0
	{
		printk( KERN_INFO "%s: %s unable to set TRIG gpio as output\n", DEVICE_NAME, __func__ );
		ret = -EBUSY;
		return(ret);
	}
	return 0;
}

static int buzzer_release(struct inode *inode, struct file *filp)
{
	printk("buzzer release\n");
    return 0;
}

static struct file_operations buzzer_fops = 
{
	owner		:	THIS_MODULE,
	read		:	buzzer_read2,
	write		:	buzzer_write,
	unlocked_ioctl	:	buzzer_ioctl,
	open		:	buzzer_open,
	release		:	buzzer_release,
};

static struct class *buzzer_class;

static int __init buzzer_init(void)
{
	int retval;
	
	retval = register_chrdev(DEVICE_MAJOR,DEVICE_NAME,&buzzer_fops);
	if(retval < 0)
	{
		printk(KERN_INFO "%s: registering device %s with major %d failed with %d\n",
		       __func__, DEVICE_NAME, DEVICE_MAJOR, DEVICE_MAJOR );
		return retval;
	}

	printk("Buzzer driver register success!\n");
	
	buzzer_class = class_create(THIS_MODULE, "buzzer");
        if (IS_ERR(buzzer_class))
	{
		printk(KERN_WARNING "Can't make node %d\n",DEVICE_MAJOR);
                return PTR_ERR(buzzer_class);
	}

    device_create(buzzer_class, NULL, MKDEV(DEVICE_MAJOR, 0),NULL, DEVICE_NAME);
	printk("Buzzer driver make node success!\n"); 
	return 0;
}
static void __exit buzzer_exit(void)
{
    device_destroy(buzzer_class,MKDEV(DEVICE_MAJOR, 0));
    class_destroy(buzzer_class);
	printk("Buzzer driver remove node success!\n");
	gpio_free(PIN);
	gpio_free(PIN2);
	unregister_chrdev(DEVICE_MAJOR,DEVICE_NAME);
	printk("Buzzer driver release success!\n");

}
module_init(buzzer_init);
module_exit(buzzer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DMATEK Co., Ltd <http://www.dmatek.com.tw>");
MODULE_DESCRIPTION("buzzer  driver");


