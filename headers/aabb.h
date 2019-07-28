#ifndef AABB_H
#define AABB_H

typedef struct {
	float x;
	float y;
	int w;
	int h;
}AABB;

short aabb_collision(AABB *rect1, AABB *rect2);

#endif
