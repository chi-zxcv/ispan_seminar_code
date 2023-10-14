#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>	//system
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
//#include <linux/delay.h>
#include <sys/ioctl.h>

#define DEVICE_BLTEST "/dev/infrared"  
#define infrared_OPEN 1
#define infrared_STOP 0
static int infraredfd = -1;

int fd,infret,val;

JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1infrared_openinfrared
  (JNIEnv * env, jclass thiz)
  {
     fd= open(DEVICE_BLTEST,O_RDONLY); 
     return fd;  
  }
JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1infrared_closeinfrared
  (JNIEnv * env, jclass thiz)
 {
      printf("EXIT\n");
      close(fd);
      return 0;   
  }
  
JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1infrared_ioctl_1infrared
  (JNIEnv * env, jclass thiz, jint condition_num)  

  {  
      ioctl(fd,condition_num,infrared_OPEN);
      return  0;   
  }
  
JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1infrared_read_1infrared
  (JNIEnv * env, jclass thiz)
  {  
      infret = read(fd, &val, sizeof(val));
      return  val;   
  }
