#include "headers/timer.h"

Timer* timer_new(float delay_time, void(*func)(Player*,float), float data) {
	Timer *t = (Timer*)malloc(sizeof(Timer));
	t->cur_time = 0;
	t->delay_time = delay_time;
	t->data = data;
	t->func = func;
	t->is_active = 0;
	return t;
}

short timer_update(Timer *t, Player *p, float time) {
	t->cur_time += time;
	if(t->cur_time >= t->delay_time) {
		t->func(p, t->data);
		return 1;
	}
	return 0;
}
