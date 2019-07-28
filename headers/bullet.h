#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <GL/gl.h>
#include "global.h"
#include "utils.h"
#include "wall.h"
#include "aabb.h"

typedef struct _bullet {
	float x;
	float y;
	float dx;
	float dy;
	float speed;
	float r;
	int id;
	struct _bullet *next;
}Bullet;

Bullet* bullet_new(float x, float y, float dx, float dy, float speed, float r);
void bullet_add(Bullet **bullets, Bullet *b);
void bullet_del(Bullet **bullets, int id);
void bullets_free(Bullet *bullets);
void bullets_move(Bullet **bulltes, Wall *walls, float time);
void bullets_draw(Bullet *bullets);
AABB bullet_get_rect(Bullet *b);

#endif
