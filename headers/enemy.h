#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <GL/gl.h>
#include "player.h"
#include "gun.h"
#include "wall.h"
#include "utils.h"
#include "aabb.h"

typedef struct _enemy{
	float x;
	float y;
	int width;
	int height;
	int health;
	float *vertices;
	int v_count;
	float speed;
	Gun gun;
	int id;
	struct _enemy *next;
}Enemy;

void enemy_add(Enemy **enemies, Enemy *e);
void enemy_del(Enemy **enemies, int id);
void enemies_free(Enemy *enemies);
void enemies_draw(Enemy *enemies);
void enemies_move(Enemy *enemies, Player *p, Wall *walls, float time);
void enemies_guns_update(Enemy *enemies, float time);
void enemies_bullet_collision(Enemy **enemies, Bullet **bullets);
void enemies_shoot(Enemy *enemies, Player *p, Bullet **bullets);
short enemy_collision(Enemy *e, AABB *rect, float dx, float dy);

#endif
