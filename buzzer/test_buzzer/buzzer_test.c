
#include <stdio.h>
#include <stdlib.h>	//system
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
//#include <linux/delay.h>
#include <sys/ioctl.h>

#include "buzzer.h"
#define LED_TEST 3

#define DEVICE_BLTEST "/dev/buzzer"      ///devπù¸c‘O∂®

int main(int argc, char *argv[])
{
		int fd;
		int val = -1;
		int num = 1;
		
		fd= open(DEVICE_BLTEST,O_RDONLY); //opendev‘OÇ‰
		if(fd<0)
		{
			perror("can not open device");
			exit(1);
		}
	
		while(1)
		{
			printf("please select number to control buzzer\n");
			printf("1:buzzer:D608 2:buzzer :D609  3:exit : ->");
			scanf("%d", &val);	
			printf("\n");
			if(val !=3){
				printf("select led on or off: 1:ON  3:OFF: ->");
				scanf("%d", &num);
				printf("\n");
				}
			switch(val)
				{
				 case 1: 
				 	if(num == BUZZER_ON)
						ioctl(fd,BUZZER_ON,&val);
					else if(num == BUZZER_OFF)
						ioctl(fd,BUZZER_OFF,&val);

					break;
				 case 2:
				 	if(num == BUZZER_ON)
						ioctl(fd,BUZZER_ON,&val);
					else if(num == BUZZER_OFF)
						ioctl(fd,BUZZER_OFF,&val);
					break;

				 case 3:
					close(fd);
				default:
					return 0;

			}

		}
		//close(fd);
		
		return 0;
}
