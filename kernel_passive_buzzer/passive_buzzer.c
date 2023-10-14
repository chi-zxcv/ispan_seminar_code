#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/err.h>
#include <linux/pwm.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>	
#include <linux/delay.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#define DEVICE_MAJOR 238

#define DEVICE_NAME				"passive_buzzer"

#define MAGIC_NUMBER    'L' 

#define PWM_IOCTL_SET_FREQ				_IO(MAGIC_NUMBER,  1)
#define PWM_IOCTL_STOP					_IO(MAGIC_NUMBER,  0)
#define PWM_IOCTL_INPUT_FREQ			_IO(MAGIC_NUMBER,  2)
#define PWM_IOCTL_SET_FREQ_TIME			_IO(MAGIC_NUMBER,  3)
 


#define NS_IN_1HZ			1000000000
#define PWM_IN_FREQ         NS_IN_1HZ / 500

//#define MOTOR_PWM_ID		3

#define MOTOR_PWM_GPIO	 	EXYNOS4_GPD0(3) //pin15


static long passive_buzzer_ioctl(struct file *file, unsigned int cmd, unsigned long arg,unsigned long duration)
{
	int delay1_us,sing_time;
	int q;
	int ret = 0;

	switch (cmd) {
		case PWM_IOCTL_SET_FREQ:
			if (arg == 0)
				return -EINVAL;
			
			printk("<1>passive_buzzer_CTL\n");
			delay1_us = (int)arg;
			printk("cmd = %d\n freq = %d\n", cmd, delay1_us);
			
			for(q=50;q>0;q--){
				gpio_direction_output(MOTOR_PWM_GPIO, 1);
				udelay(delay1_us);
				gpio_direction_output(MOTOR_PWM_GPIO, 0);
				udelay(PWM_IN_FREQ - delay1_us);
			}
			break;

		case PWM_IOCTL_STOP:

		case PWM_IOCTL_INPUT_FREQ:
			if (arg == 0)
				return -EINVAL;
			
			printk("<1>passive_buzzer_CTL\n");
			delay1_us = (int)arg;
			printk("cmd = %d\n freq = %d\n", cmd, delay1_us);
			
			for(q=10;q>0;q--){
				gpio_direction_output(MOTOR_PWM_GPIO, 1);
				ndelay(delay1_us);
				gpio_direction_output(MOTOR_PWM_GPIO, 0);
				udelay(PWM_IN_FREQ - delay1_us);
			}

			break;
		case PWM_IOCTL_SET_FREQ_TIME:
						
			printk("<1>passive_buzzer_SET\n");
			delay1_us = (int)arg;
			int ret;
			ret = copy_from_user(&sing_time, (int*)duration, sizeof(int));
			printk("sing_time = %d\n",sing_time);
			printk("cmd = %d\n freq = %d\nduration = %d\n", cmd, delay1_us,sing_time);
			
			for(q=sing_time;q>0;q--){
				gpio_direction_output(MOTOR_PWM_GPIO, 1);
				ndelay(delay1_us);
				gpio_direction_output(MOTOR_PWM_GPIO, 0);
				udelay(PWM_IN_FREQ - delay1_us);
			}

			break;
		default:
			break;
	}

	return 0;

}

static int passive_buzzer_open(struct inode *inode, struct file *filp)
{	/*ªì©l¤Æ GPIO ±µ¸}*/

	int ret1 = -1;
	int ret2 = -1;
	ret1 = gpio_request( MOTOR_PWM_GPIO, DEVICE_NAME);
	if( ret1 < 0 )	// request pin 2
	{
		printk( KERN_INFO "%s: %s unable to get TRIG gpio\n", DEVICE_NAME, __func__ );
		ret1 = -EBUSY;
		gpio_free(MOTOR_PWM_GPIO);
		return(ret1);
	}
	
	ret2 = gpio_direction_output( MOTOR_PWM_GPIO, 0);
	if( ret2 < 0 )	// Set pin 2 as output with default value 0
	{
		printk( KERN_INFO "%s: %s unable to set TRIG gpio as output\n", DEVICE_NAME, __func__ );
		ret2 = -EBUSY;
		return(ret2);
	}

	s3c_gpio_cfgpin(MOTOR_PWM_GPIO, S3C_GPIO_OUTPUT);
	
	
	return 0;
}


static int passive_buzzer_release(struct inode *inode, struct file *filp)
{
	gpio_free(MOTOR_PWM_GPIO);
	return 0;
}

static struct file_operations passive_buzzer_fops = 
{
	owner		    :	THIS_MODULE,
	unlocked_ioctl	:	passive_buzzer_ioctl,
	open		    :	passive_buzzer_open,
	release		    :	passive_buzzer_release,
};

static struct class *passive_buzzer_class;

static int __init passive_buzzer_init(void)
{
	int retval;
	//int ret;
	
	retval = register_chrdev(DEVICE_MAJOR,DEVICE_NAME,&passive_buzzer_fops);
	if(retval < 0)
	{
		printk(KERN_WARNING "Can't get major %d\n",DEVICE_MAJOR);
		return retval;
	}

	printk("passive_buzzer driver register success!\n");
	
	passive_buzzer_class = class_create(THIS_MODULE,"passive_buzzer");
        if (IS_ERR(passive_buzzer_class))
	{
		printk(KERN_WARNING "Can't make node %d\n",DEVICE_MAJOR);
                return PTR_ERR(passive_buzzer_class);
	}

    device_create(passive_buzzer_class, NULL, MKDEV(DEVICE_MAJOR, 0),NULL, DEVICE_NAME);
	printk("passive_buzzer driver make node success!\n");
	
	return 0;
}
static void __exit passive_buzzer_exit(void)
{
	gpio_free(MOTOR_PWM_GPIO);
    device_destroy(passive_buzzer_class,MKDEV(DEVICE_MAJOR, 0));
    class_destroy(passive_buzzer_class);
	printk("passive_buzzer driver remove node success!\n");
	unregister_chrdev(DEVICE_MAJOR,DEVICE_NAME);
	printk("passive_buzzer driver release success!\n");

}
module_init(passive_buzzer_init);
module_exit(passive_buzzer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("michael199584566@gmail.com");
MODULE_DESCRIPTION("passive_buzzer  driver");
