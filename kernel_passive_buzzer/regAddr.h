#ifndef __REG_ADDR_H__
#define __REG_ADDR_H_

#define GPD0CON    ((unsigned long)0x114000A0)
#define GPD0DAT    ((unsigned long)0x114000A4)

//Base Address: 0x139D_0000 (PWM)
//Base Address: 0x1216_0000 (PWM_ISP)

//linux/arch/arm/mach-exynos/include/mach/map-exynos4.h
//#define TIMER_BASE ((unsigned long)0x139D0000)

#define TCFG0      ((unsigned long)0x139D0000)
#define TCFG1      ((unsigned long)0x139D0004)
#define TCON       ((unsigned long)0x139D0008)

#define TCNTB0     ((unsigned long)0x139D000C)
#define TCMPB0     ((unsigned long)0x139D0010)
#define TCNTO0     ((unsigned long)0x139D0014)

#define TCNTB1     ((unsigned long)0x139D0018)
#define TCMPB1     ((unsigned long)0x139D001C)
#define TCNTO1     ((unsigned long)0x139D0020)

#define TCNTB2     ((unsigned long)0x139D0024)
#define TCMPB2     ((unsigned long)0x139D0028)
#define TCNTO2     ((unsigned long)0x139D002C)

#define TCNTB3     ((unsigned long)0x139D0030)
#define TCMPB3     ((unsigned long)0x139D0034)
#define TCNTO3     ((unsigned long)0x139D0038)

#define TCNTB4     ((unsigned long)0x139D003C)
#define TCNTO4     ((unsigned long)0x139D0040)

#define TINT_CSTAT ((unsigned long)0x139D002C)
 
#endif