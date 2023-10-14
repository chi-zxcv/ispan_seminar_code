#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__


#include <asm/delay.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/fb.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/of.h>
//#include <linux/pinctrl/consumer.h>
#include <linux/platform_device.h>
#include <linux/poll.h>
#include <linux/pwm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/types.h>
#include <mach/gpio.h>
#include <mach/hardware.h>
#include <mach/hardware.h>
#include <mach/regs-gpio.h>
#include <mach/regs-mem.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>



typedef struct _SERVO_PARAM{
	unsigned int num;
	//unsigned int state;
}SERVO_PARAM;

typedef struct _KEY_PARAM{
	unsigned int state;
}KEY_PARAM;

#endif
