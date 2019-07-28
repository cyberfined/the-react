#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>
#include "player.h"

typedef struct {
	float cur_time;
	float delay_time;
	float data;
	void (*func)(Player*,float);
	short is_active;
}Timer;

Timer* timer_new(float delay_time, void(*func)(Player*,float), float data);
short timer_update(Timer *t, Player *p, float time);

#endif
