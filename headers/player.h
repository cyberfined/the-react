#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "global.h"
#include "utils.h"
#include "gun.h"
#include "wall.h"
#include "aabb.h"

typedef struct {
	float x;
	float y;
	int r;
	int health;
	float angle;
	float speed;
	Gun gun;
}Player;

void player_draw(Player *p);
void player_move(Player *p, Wall *walls, float time);
void player_strafe(Player *p, Wall *walls, float time, short dx, short dy);
void player_bullet_collision(Player *p, Bullet **bullets);
void arrow_draw(float r);
short player_collision(Player *p, AABB *rect, float dx, float dy);
void player_walls_collision(Player *p, Wall *walls, float dx, float dy);

#endif
