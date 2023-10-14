
#include <stdio.h>
#include <stdlib.h>	//system
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_INFRARED "/dev/infrared"     

#define infrared_OPEN 1
#define infrared_STOP 0
static int infraredfd = -1;
static void open_infrared(void);
static void close_infrared(void);

int main(int argc, char *argv[])
{		
		int infret = -1;
		int val,condition;
		int freq = 1200;
		
		open_infrared();
		
		
		while(1)
		{
			printf("please select number for condition\n");
			printf("1:Motion detection 2:situational mode  3:exit : ->");
			scanf("%d", &condition);	
			printf("\n");
			
			switch(condition){
				case 1: 
				 	ioctl(infraredfd,0,infrared_OPEN); 
					break;
				case 2:
				 	ioctl(infraredfd,1,infrared_OPEN); 
					break;
				case 3:
					close_infrared();
				default:
					return 0;
			}
			
			//infraredfd detection
			infret = read(infraredfd, &val, sizeof(val));
			if(infret<0){
				printf("Reading infrared data error!\n");
			}
			if (val == 1){
				printf("Alert ! Someone detected!\n");
				printf("LED ON! \n");
			}else{
				printf("no one!\n");
				printf("Buzzer OFF! \n");
			}
			
			sleep(2);
		}
		
		return 0;
}


static void open_infrared(void){
	infraredfd = open(DEVICE_INFRARED,O_RDONLY); //Open infrared device
	if (infraredfd < 0){
		perror("Open Infrared device failed!!\n");
		exit(1);
	}
	//return infraredfd;
}

static void close_infrared(void){
	if (infraredfd > 0){
		close(infraredfd);
		infraredfd = -1;
	}
}

