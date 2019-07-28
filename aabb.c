#include "headers/aabb.h"

short aabb_collision(AABB *rect1, AABB *rect2) {
	if (rect1->x < rect2->x + rect2->w &&
   		rect1->x + rect1->w > rect2->x &&
   		rect1->y < rect2->y + rect2->h &&
   		rect1->h + rect1->y > rect2->y) {
    		return 1;
		}
	return 0;
}
