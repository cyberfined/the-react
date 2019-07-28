#include "headers/enemy.h"
#define DISTANCE 450

void enemy_add(Enemy **enemies, Enemy *e) {
	Enemy *i;
	if(*enemies == NULL) {
		*enemies = e;
	}else {
		for(i = *enemies; i->next != NULL; i = i->next);
		i->next = e;
		i->next->id = i->id+1;
	}
}

void enemy_del(Enemy **enemies, int id) {
	Enemy *i;
	Enemy *tmp;
	if(id == 0) {
		tmp = (*enemies)->next;
		if(tmp)tmp->id = 0;
		free((*enemies)->vertices);
		free(*enemies);
		*enemies = tmp;
	}else {
		for(i = *enemies; i->next != 0; i=i->next) {
			if(i->next->id == id)
				break;
		}
		tmp = i->next->next;
		free(i->next->vertices);
		free(i->next);
		i->next = tmp;
	}
}

void enemies_free(Enemy *enemies) {
	Enemy *i;
	for(i = enemies; i != NULL; i = i->next) {
		free(i->vertices);
		free(i);
	}
}

void enemies_draw(Enemy *enemies) {
	Enemy *i;
	AABB camera = {-global_x, -global_y, WIN_W, WIN_H};
	for(i = enemies; i != NULL; i = i->next) {
		if(!enemy_collision(i, &camera, 0, 0)) continue;
		glPushMatrix();

		glTranslatef(i->x, i->y, 0.0);
		polygon_draw(i->vertices, i->v_count);

		glPopMatrix();
	}
}

void enemies_guns_update(Enemy *enemies, float time) {
	Enemy *i;
	for(i = enemies; i != NULL; i = i->next) {
		gun_update(&i->gun, time);
	}
}

void enemies_shoot(Enemy *enemies, Player *p, Bullet **bullets) {
	Enemy *i;
	float l; 
	for(i = enemies; i != NULL; i = i->next) {
		l = sqrt((i->x - p->x)*(i->x - p->x) + (i->y - p->y)*(i->y - p->y));
		if(l > DISTANCE) continue;
		i->gun.x = i->x + i->width/2;
		i->gun.y = i->y + i->height/2;
		gun_shot_xy(&i->gun, bullets, p->x, p->y);

	}
}

short enemy_collision(Enemy *e, AABB *rect, float dx, float dy) {
	AABB e_rect = {e->x+dx, e->y+dy, e->width, e->height};
	return aabb_collision(&e_rect, rect);
}

void enemies_bullet_collision(Enemy **enemies, Bullet **bullets) {
	Enemy *i;
	Bullet *j;
	AABB b_rect;
	for(i = *enemies; i != NULL; i = i->next) {
		for(j = *bullets; j != NULL; j = j->next) {
			b_rect = bullet_get_rect(j);
			if(enemy_collision(i, &b_rect, 0, 0)) {
				if(--i->health == 0)
					enemy_del(enemies, i->id);
				bullet_del(bullets, j->id);
			}
		}
	}
}

void enemies_move(Enemy *enemies, Player *p, Wall *walls, float time) {
	float sx;
	float sy;
	float dx = 0;
	float dy = 0;
	float l;
	AABB wall_rect;
	Wall *j;
	Enemy *i;

	for(i = enemies; i != NULL; i = i->next) {
		sx = p->x - i->width/2 - i->x;
		sy = p->y - i->height/2 - i->y;
		l = sqrt(sx*sx + sy*sy);
		if(l > DISTANCE) continue;
		dx = l != 0 ? sx/l : 0;
		dy = l != 0 ? sy/l : 0;
		dx *= i->speed * time;
		dy *= i->speed * time;

		for(j = walls; j != NULL; j = j->next) {
			wall_rect = wall_get_rect(j);
			if(enemy_collision(i, &wall_rect, dx, 0))
				dx = 0;
			if(enemy_collision(i, &wall_rect, 0, dy))
				dy = 0;
		}
		i->x += dx;
		i->y += dy;
	}
}
