#include <stdio.h>
#include <stdlib.h>	//system
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
//#include <linux/delay.h>
#include <sys/ioctl.h>

//#define DEVICE_NAME 238

//#define DEVICE_NAME				"passive_buzzer"

#define MAGIC_NUMBER    'L' 

#define PWM_IOCTL_SET_FREQ	_IO(MAGIC_NUMBER,  1)
#define PWM_IOCTL_STOP		_IO(MAGIC_NUMBER,  0)
#define PWM_IOCTL_INPUT_FREQ		_IO(MAGIC_NUMBER,  2)

int main(int argc, char *argv[])
{
		int i = 0;
		//int j = 0;
		int freq = 0 ;
		int frequence=0;
		float duty_cycle = 0.0;
		float duty = 0.0;
		int degree = 0;
		int val = -1;
		int fd;
		int duration;
		int pwm_freq = 500;
		int NS_IN_1HZ = 1000000000;
		
		char *msg = "Message passed by ioctl\n", c, message[100];
		
		fd = open("/dev/passive_buzzer", 0); 
		if(fd<0)
		{
			perror("can not open device fileL /dev/passive_buzzer\n");
			exit(-1);
		}
	
		while(1)
		{
			printf("please select number to control passive_buzzer\n");
			printf("1:degree  2:for  3:exit : 4:Frequence 5:from_200-5000HZ-> ");
			scanf("%d", &val);	
			//printf("\n");

			switch(val)
				{
				 case 1: 
					printf("1: pleae set degree \n");
					scanf("%d",&degree);
					duty_cycle = (0.05 * pwm_freq) + (0.19 * pwm_freq * degree / 180);
					duty = duty_cycle * 0.01 * (NS_IN_1HZ / pwm_freq);
					freq = (int)duty;
					printf("-----------------------------\n");
					printf("degree = %d,\nduty_cycle = %.2f,\nfreq = %d\n",degree, duty_cycle, freq);
					printf("-----------------------------\n");
					ioctl(fd, PWM_IOCTL_SET_FREQ, freq,0);
					//usleep(200000);					
					break;
				 case 3:
					printf("EXIT\n");
					close(fd);
					return 0;
				 case 2:
					for(i=0;i<=180;i=i+18){
					    duty_cycle = (0.05 * pwm_freq) + (0.19 * pwm_freq * i / 180);
					    duty = duty_cycle * 0.01 * (NS_IN_1HZ / pwm_freq);
					    freq = (int)duty;
						printf("-----------------------------\n");
						printf("degree = %d,\nduty_cycle = %.2f,\nfreq = %d\n", i, duty_cycle, freq);
						printf("-----------------------------\n");
					    ioctl(fd, PWM_IOCTL_SET_FREQ, freq,0);
					    //usleep(200000);
					}
					break;
				case 4:
					printf("4: pleae set frequence \n");
					scanf("%d",&frequence);
					freq = (int)frequence*1000;
					//printf("4: pleae set duration \n");
					//scanf("%d",&duration);
					//duration = (int)duration*100;
					printf("-----------------------------\n");
					printf("freq = %d,duration = %d\n", freq,0);
					printf("-----------------------------\n");
					ioctl(fd, PWM_IOCTL_INPUT_FREQ, freq,0);
					//usleep(200000);
					break;	
				case 5:
					for(i=200;i<=8000;i=i+50){
					   freq = (int)i*1000;
					   printf("-----------------------------\n");
						printf("freq = %d,duration = %d\n", freq,0);
						printf("-----------------------------\n");
						ioctl(fd, PWM_IOCTL_INPUT_FREQ, freq,0);
					    //usleep(200000);
					}
					break;
				default:
					break;

			}

		}
		
		return 0;
}
