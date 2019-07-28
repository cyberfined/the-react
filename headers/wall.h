#ifndef WALL_H
#define WALL_H

#include <stdlib.h>
#include <GL/gl.h>
#include "global.h"
#include "aabb.h"

typedef struct _wall {
	int x;
	int y;
	int w;
	int h;
	float color[3];
	struct _wall *next;
}Wall;

void walls_draw(Wall *walls);
void wall_add(Wall **walls, Wall *w);
Wall* wall_new(char **args);
void walls_free(Wall *wals);
AABB wall_get_rect(Wall *w);

#endif
