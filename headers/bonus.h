#ifndef BONUS_H
#define BONUS_H

#include <stdlib.h>
#include <GL/gl.h>
#include "global.h"
#include "utils.h"
#include "player.h"
#include "timer.h"
#include "aabb.h"

typedef struct _bonus {
	float x;
	float y;
	int width;
	int height;
	float *vertices;
	int v_count;
	float data;
	void(*func)(Player*, float);
	int id;
	Timer *timer;
	struct _bonus *next;
}Bonus;

void bonus_add(Bonus **bonuses, Bonus *b);
void bonus_del(Bonus **bonuses, int id);
void bonuses_update(Bonus **bonuses, Player *p, float time);
void bonuses_free(Bonus *bonuses);
void bonuses_draw(Bonus *bonuses);
AABB bonus_get_rect(Bonus *b);

#endif
