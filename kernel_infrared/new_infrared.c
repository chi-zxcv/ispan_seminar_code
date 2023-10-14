/*-------------------------------------------------------------------------
 * Filename:      gpio_drv.c
 * Copyright:     Copyright (C) 2006, dmatek
 * Author:        chris_zhang <www.dmatek.com>
 * Description:   gpio driver
 * Created at:     Aug 11 2006
 *-----------------------------------------------------------------------*/

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


#define LED_ON  1
#define LED_OFF 0
#define LED_TEST 3

/* 設定 硬體編號及名稱 */
#define DEVICE_MAJOR 233
#define DEVICE_NAME "infrared"

/* 設定 4412 接腳 */
#define PIN 	EXYNOS4_GPX0(2)  //pin6
#define BLING	EXYNOS4_GPX0(3) //pin8
#define LED		EXYNOS4_GPX0(6)	//LED 	 pin10		


#define EXYNOS4_GPA1CON			(EXYNOS5_GPA1(1) )
#define EXYNOS4_GPA1DAT			(EXYNOS5_GPA1(1) + 0x4)

#define MS_DELAY(s)   Delay(s<<2)
//void s3c_gpio_cfgpin(unsigned int pin, unsigned int function);

/* 全域變數mode是程式讀取硬體資料的模式 */
static int mode = 0;

int data_in(void)
{
	gpio_direction_input(PIN);
	return gpio_get_value(PIN);
}
void gpio_out(int value)   //set gpio is output
{
    gpio_direction_output(PIN,value);
}

//static int buf;
static ssize_t infrared_read(struct file *file, int* value, size_t size, loff_t *off)
{
    /*
		int ret;
		local_irq_disable();
		buf = data_in(); 
		local_irq_disable();
        printk("<1> reading _data = %d\n", gpio_get_value(PIN));
		if(buf == 1){
			printk("<1> Cautious!! Someone's detected !\n");
        }else{
         	printk("<1> Safe now! \n");
			//return -EAGAIN;
		}
		ret = copy_to_user(value,&buf,sizeof(buf)); //copy buf to buffer
		if(ret < 0){
			printk("Copy to user error!!\n");
			return -EAGAIN;
        }else{
         	return 0;
		}

	*/
	size_t ret;
	
	if (mode == 0){ //warming
		int data;
		printk("<1> reading _data = %d\n", gpio_get_value(PIN));
		local_irq_disable();
        data = gpio_get_value(PIN);
		gpio_set_value(LED, gpio_get_value(PIN));
		local_irq_enable();
        ret = copy_to_user(&value, (int *)data, sizeof(data));
		//ret = copy_to_user(value, data, sizeof(data));
		if (ret<0){
			printk("<1> ---ret error---");
		}
	}else if (mode == 1){ //party
		int data;
		printk("<1> reading _data = %d\n", gpio_get_value(PIN));
		local_irq_disable();
        data = gpio_get_value(PIN);
		gpio_set_value(BLING, gpio_get_value(PIN));
		local_irq_enable();
        ret = copy_to_user(&value, (int *)data, sizeof(data));
		//ret = copy_to_user(value, &data, sizeof(data));
		if (ret<0){
			printk("<1> ---ret error---");
		}
	}else{;
		gpio_set_value(LED, 0);
		gpio_set_value(BLING, 0);
	}	
	return 0;
	
}



static int infrared_open(struct inode *inode, struct file *filp)
{	
	/*初始化 GPIO 接腳*/
	int ret;
	printk("open in kernel\n");
	/*初始化 GPIO 接腳*/
	gpio_free (PIN);
	ret=gpio_request(PIN,DEVICE_NAME);
	if(ret<0){
		printk(KERN_EMERG "%d failed !\n",PIN);
		printk( KERN_INFO "%s: %s unable to get TRIG gpio\n", DEVICE_NAME, __func__ );
		gpio_free(PIN);
		return ret;
	}
	// Set gpios directions
	//s3c_gpio_cfgpin(PIN, S3C_GPIO_INPUT); //將PIN腳配置成第二個函數的功能
	gpio_direction_input(PIN);	
	/* ----設 定 ws2812b-8---- */
	printk ("<1>-----BLING open-----\n");
	gpio_free (BLING);
	ret = gpio_request(BLING, "BLING");
	if (ret<0){
		printk("<1> ---ret error---");
		ret = -EBUSY;
		return(ret);
	}
	gpio_direction_output(BLING,0);
	/* ----設 定 L E D---- */
	printk("<1>-----LED open-----\n");
	gpio_free (LED);
	ret = gpio_request(LED, "LED");
	if (ret<0){
		printk("<1> ---ret error---");
		ret = -EBUSY;
		return(ret);
	}
	gpio_direction_output(LED, 0);
	return 0;
}

static long infrared_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	/*
	read模式的mode變化如何進行，
	在ioctl用switch-case的方式定義APP傳來 0 , 1 時直接賦值給 mode，
	除此之外的情形燈號關閉。
	*/
	int ret;
	//int num;
	printk("cmd=%d\n",cmd);
	switch (cmd){
		case 0:
			mode = cmd;
			printk ("<1>----case 0_ warming condition----\n");
				
			break;
		case 1:
			mode = cmd;
			printk ("<1>----case 1_ party condition----\n");
			break;
		default : // APP傳 arg = 3 ---> mode = 3
			ret = copy_from_user(&mode, (int *)arg, sizeof(int)); 
			if (ret != 0){
				printk ("<1>----gpio_ioctl：copy from user failed----\n");
				return (-EFAULT);
			}
			
			break;
	}
	gpio_set_value(LED, 0);
	gpio_set_value(BLING, 0);
	return 0;
}


static int infrared_release(struct inode *inode, struct file *filp)
{
	/* -----關 閉 硬 體----- */
	gpio_free(PIN);
	gpio_free(BLING);
	gpio_free(LED);
	printk("infrared device release\n");
	return 0;
}

static struct file_operations infrared_fops = 
{
	owner		:	THIS_MODULE,
	read		:	infrared_read,
	open		:	infrared_open,
	unlocked_ioctl	:	infrared_ioctl,
	release		:	infrared_release,
};

static struct class *infrared_class; 

static int __init infrared_init(void)
{
	int ret;
	/* 註 冊 DEVICE_MAJOR, DEVICE_NAME */
	ret = register_chrdev(DEVICE_MAJOR,DEVICE_NAME,&infrared_fops);
	if(ret < 0)
	{
		printk(KERN_WARNING "Can't get major %d\n",DEVICE_MAJOR);
		return ret;
	}

	printk("Infrared driver register success!\n");
	
	infrared_class = class_create(THIS_MODULE, "Infrared");
    if (IS_ERR(infrared_class))
	{
		printk(KERN_WARNING "Can't make node %d\n",DEVICE_MAJOR);
        return PTR_ERR(infrared_class);
	}

    device_create(infrared_class, NULL, MKDEV(DEVICE_MAJOR, 0),NULL, DEVICE_NAME);
	printk("Infrared driver makes node successfully!\n");
	return 0;
}
static void __exit infrared_exit(void)
{
    device_destroy(infrared_class,MKDEV(DEVICE_MAJOR, 0));
    class_destroy(infrared_class);
	printk("Infrared driver remove node successfully!\n");
	gpio_free(PIN);
	unregister_chrdev(DEVICE_MAJOR,DEVICE_NAME);
	printk("Infrared driver released successfully!\n");

}
module_init(infrared_init);
module_exit(infrared_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DMATEK Co., Ltd <http://www.dmatek.com.tw>");
MODULE_DESCRIPTION("Infrared sensor driver");


