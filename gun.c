#include "headers/gun.h"

void gun_shot_angle(Gun *g, Bullet **bullets, float angle) {
	Bullet *b;
	if(g->cur_time <= g->delay_time) return;
	g->cur_time = 0;
	b = bullet_new(g->x, g->y, 
		 		   cos(angle),
				   sin(angle),
				   g->speed,
				   g->radius);
	bullet_add(bullets, b);
}

void gun_shot_xy(Gun *g, Bullet **bullets, float x, float y/*, int count*/) {
/*If you get into this function variable inbstead count, segmentation fault will happen*/
	float sx, sy;
	float dx, dy;
	float l;
	/*float k = 0;*/
	Bullet *b;
	/*int i;*/

	if(g->cur_time <= g->delay_time) return;
		g->cur_time = 0;
	/*for(i = 0; i < count; i++) {
		k = i%2 == 0 ? 20 : -20;*/
		sx = x - g->x /*+ k*i*/;
		sy = y - g->y;
		l = sqrt(sx*sx + sy*sy);
		dx = sx/l;
		dy = sy/l;
		b = bullet_new(g->x, g->y,
					   dx, dy,
				       g->speed,
				       g->radius);
		bullet_add(bullets, b);
	/*}*/
}

void gun_update(Gun *g, float time) {
	g->cur_time += time;
}
