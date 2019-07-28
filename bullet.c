#include "headers/bullet.h"

Bullet* bullet_new(float x, float y, float dx, float dy, float speed, float r) {
	Bullet *b = (Bullet *)malloc(sizeof(Bullet));
	b->x = x;
	b->y = y;
	b->dx = dx;
	b->dy = dy;
	b->speed = speed;
	b->r = r;
	b->next = NULL;
	b->id = 0;
	return b;
}

void bullet_add(Bullet **bullets, Bullet *b) {
	Bullet *i;
	if(*bullets == NULL)
		*bullets = b;
	else {
		for(i = *bullets; i->next != NULL; i = i->next);
		i->next = b;
		i->next->id = i->id+1;
	}
}

void bullet_del(Bullet **bullets, int id) {
	Bullet *i;
	Bullet *tmp;
	if(id == 0) {
		tmp = (*bullets)->next;
		if(tmp)tmp->id = 0;
		free(*bullets);
		*bullets = tmp;
	}else {
		for(i = *bullets; i->next != 0; i=i->next) {
			if(i->next->id == id)
				break;
		}
		tmp = i->next->next;
		free(i->next);
		i->next = tmp;
	}
}

void bullets_free(Bullet *bullets) {
	Bullet *i;
	for(i = bullets; i != NULL; i = i->next) {
		free(i);
	}
}

void bullets_move(Bullet **bullets, Wall *walls, float time) {
	Bullet *i;
	Wall *j;
	AABB wall_rect;
	AABB bullet_rect;
	for(i = *bullets; i != NULL; i = i->next) {
		i->x += i->dx * time * i->speed;
		i->y += i->dy * time * i->speed;	
		bullet_rect = bullet_get_rect(i);
		for(j = walls; j != NULL; j = j->next) {
			wall_rect = wall_get_rect(j);
			if(aabb_collision(&bullet_rect, &wall_rect)) {
				bullet_del(bullets, i->id);
				break;
			}
		}
	}
}

void bullets_draw(Bullet *bullets) {
	Bullet *i;
	AABB camera = {-global_x, -global_y, WIN_W, WIN_H};
	AABB bullet_rect;
	for(i = bullets; i != NULL; i = i->next) {
		bullet_rect = bullet_get_rect(i);
		if(!aabb_collision(&bullet_rect, &camera)) continue;
		glPushMatrix();

		glTranslatef(i->x, i->y, 0.0f);
		circle_draw(i->r);

		glPopMatrix();
	}
}

AABB bullet_get_rect(Bullet *b) {
	AABB rect = {b->x - b->r, b->y - b->r, b->r*2, b->r*2};
	return rect;
}
