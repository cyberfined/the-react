#include "headers/wall.h"

void walls_draw(Wall *walls) {
	Wall *i;
	AABB camera = {-global_x, -global_y, WIN_W, WIN_H};
	AABB wall_rect;

	for(i = walls; i != NULL; i = i->next) {
		wall_rect = wall_get_rect(i);
		if(!aabb_collision(&camera, &wall_rect)) continue;
		glPushMatrix();

		glColor3f(i->color[0], i->color[1], i->color[2]);
		glTranslatef(i->x, i->y, 0.0f);
		glBegin(GL_LINE_LOOP);
		
		glVertex2f(0, 	 0);
		glVertex2f(i->w, 0);
		glVertex2f(i->w, i->h);
		glVertex2f(0, 	 i->h);

		glEnd();

		glPopMatrix();
	}
}
void wall_add(Wall **walls, Wall *w) {
	Wall *i;
	if(*walls == NULL)
		*walls = w;
	else {
		for(i = *walls; i->next != NULL; i = i->next);
		i->next = w;
	}
}

Wall* wall_new(char **args) {
	int i = 0;
	Wall *tmp = (Wall*)malloc(sizeof(Wall));
	tmp->x = atoi(args[1]);
	tmp->y = atoi(args[2]);
	tmp->w = atoi(args[3]);
	tmp->h = atoi(args[4]);
	for(i = 0; i < 3; i++) tmp->color[i] = atof(args[i+5]);
	tmp->next = NULL;
	return tmp;
}

void walls_free(Wall *walls) {
	Wall *i;
	for(i = walls; i != NULL; i = i->next) {
		free(i);
	}
}

AABB wall_get_rect(Wall *w) {
	AABB rect = {w->x, w->y, w->w, w->h};
	return rect;
}
