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

#define PWM_IOCTL_SET_FREQ				_IO(MAGIC_NUMBER,  1)
#define PWM_IOCTL_STOP					_IO(MAGIC_NUMBER,  0)
#define PWM_IOCTL_INPUT_FREQ			_IO(MAGIC_NUMBER,  2)
#define PWM_IOCTL_SET_FREQ_TIME			_IO(MAGIC_NUMBER,  3)



#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int main(int argc, char *argv[])
{
		int i = 0;
		int thisNote;
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
		int divider;
		
		char *msg = "Message passed by ioctl\n", c, message[100];
		int melody2[] = {
			// Pink Panther theme
			// Score available at https://musescore.com/benedictsong/the-pink-panther
			// Theme by Masato Nakamura, arranged by Teddy Mason
			
			REST,2, REST,4, REST,8, NOTE_DS4,8, 
			NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
			NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
			NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
			NOTE_E4,2, REST,4, REST,8, NOTE_DS4,4,
			
			NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
			NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,8, NOTE_B4,-8, NOTE_E5,8,
			NOTE_DS5,1,   
			NOTE_D5,2, REST,4, REST,8, NOTE_DS4,8, 
			NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
			NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
			
			NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
			NOTE_E4,-4, REST,4,
			REST,4, NOTE_E5,-8, NOTE_D5,8, NOTE_B4,-8, NOTE_A4,8, NOTE_G4,-8, NOTE_E4,-8,
			NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8,   
			NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, NOTE_E4,16, NOTE_E4,16, NOTE_E4,2,
			
		};
		
		int melody[] = {
			// HAPPY BIRTHDAY SONG
			// https://github.com/hibit-dev/buzzer/blob/master/src/other/happy_birthday/happy_birthday.ino
			
			NOTE_C4,4, NOTE_C4,8, NOTE_D4,4, NOTE_C4,4, 
			NOTE_F4,4, NOTE_E4,2, NOTE_C4,4, NOTE_C4,8, 
			NOTE_D4,4, NOTE_C4,4,NOTE_G4,4, NOTE_F4,2, 
			NOTE_C4,4, NOTE_C4,8, NOTE_C5,4, NOTE_A4,4, NOTE_F4,4, NOTE_E4,4,   
			NOTE_D4,4, REST,1, NOTE_AS4,4, NOTE_AS4,8, NOTE_A4,4, NOTE_F4,4, 
			NOTE_G4,4, NOTE_F4,2, 
			
		};
		int notes = sizeof(melody) / sizeof(melody[0]) / 2;
		fd = open("/dev/passive_buzzer", 0); 
		if(fd<0)
		{
			perror("can not open device fileL /dev/passive_buzzer\n");
			exit(-1);
		}
	
		while(1)
		{
			printf("please select number to control passive_buzzer\n");
			printf("1:Set Frequence 2:Echo from 200-5000HZ  3:sing a song  4:exit -> ");
			scanf("%d", &val);	
			//printf("\n");

			switch(val)
				{
				case 4:
					printf("EXIT\n");
					close(fd);
					return 0;
				case 1:
					printf("1: pleae set frequence \n");
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
				case 2:
					for(i=200;i<=8000;i=i+50){
					   freq = (int)i*1000;
					   printf("-----------------------------\n");
						printf("freq = %d,duration = %d\n", freq,0);
						printf("-----------------------------\n");
						ioctl(fd, PWM_IOCTL_INPUT_FREQ, freq,0);
					    //usleep(200000);
					}
					break;
					
				case 3:
					for (thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
						int tempo = 120;// change this to make the song slower or faster
						int wholenote = (60000 * 4) / tempo;
						int noteDuration;
						
						// calculates the duration of each note
						divider = melody[thisNote + 1];
						if (divider > 0) {
							// regular note, just proceed
							noteDuration = wholenote / divider;
						} else if (divider < 0) {
							// dotted notes are represented with negative durations!!
							noteDuration = wholenote / abs(divider);
							noteDuration *= 1.5; // increases the duration in half for dotted notes
						}
						
						//for frequence
						i=melody[thisNote];
						freq = (int)i*1000;
					    //print word
						printf("-----------------------------\n");
						printf("freq = %d,duration = %d\n", freq,noteDuration);
						printf("-----------------------------\n");
						//ioctl(fd, PWM_IOCTL_SET_FREQ_TIME, freq,noteDuration);
						ioctl(fd, PWM_IOCTL_INPUT_FREQ, freq,0);
						usleep(noteDuration*400);
					}
				default:
					break;
			}

		}
		
		return 0;
}
