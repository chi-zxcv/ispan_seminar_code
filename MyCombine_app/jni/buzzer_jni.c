#include <string.h>
#include <jni.h>
//#include "tw_com_dmatek_buzzer_Linux_buzzer.h"
#include <stdio.h>
#include <stdlib.h>	//system
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/delay.h>
#include <sys/ioctl.h>

#include "buzzer_jni.h"
#define BUZZER_TEST 3

#define DEVICE_BLTEST "/dev/buzzer"  
int fd;
JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1buzzer_openbuzzer
  (JNIEnv* env, jclass thiz)
  {
     fd= open(DEVICE_BLTEST,O_RDONLY); 
     return fd;  
  }
 JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1buzzer_closebuzzer
  (JNIEnv* env, jclass thiz)
  {
      close(fd);
      return 0;   
  }
  
  
  
  JNIEXPORT jint JNICALL Java_tw_com_dmatek_buzzer_Linux_1buzzer_send
  (JNIEnv* env, jclass thiz, jint buzzer_num, jint on_off)
  {  
      ioctl(fd,on_off,&buzzer_num);
      return  0;   
  }