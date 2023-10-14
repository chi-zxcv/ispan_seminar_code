#ifndef BUZZER_DRV_H
#define BUZZER_DRV_H


#define BUZZER_ON 1
#define BUZZER_OFF 3

typedef struct _BUZZER_PARAM{
	unsigned int num;
	//unsigned int state;
}BUZZER_PARAM;

typedef struct _KEY_PARAM{
	unsigned int state;
}KEY_PARAM;

#endif
