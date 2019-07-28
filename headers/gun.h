#ifndef GUN_H
#define GUN_H

#include <math.h>
#include <GL/gl.h>
#include "bullet.h"

typedef struct {
	float x;
	float y;
	float speed;
	float radius;
	float delay_time;
	float cur_time;
}Gun;

void gun_shot_angle(Gun *g, Bullet **bullets, float angle);
void gun_shot_xy(Gun *g, Bullet **bullets, float x, float y/*, int count*/); /*If you get into this function variable inbstead count, segmentation fault will happen*/
void gun_update(Gun *g, float time);

#endif
