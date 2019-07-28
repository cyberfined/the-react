#include "headers/bonus.h"

void bonus_add(Bonus **bonuses, Bonus *b) {
	Bonus *i;
	if(*bonuses == NULL)
		*bonuses = b;
	else {
		for(i = *bonuses; i->next != NULL; i = i->next);
		i->next = b;
		i->next->id = i->id+1;
	}
}

void bonus_del(Bonus **bonuses, int id) {
	Bonus *i;
	Bonus *tmp;
	if(id == 0) {
		tmp = (*bonuses)->next;
		if(tmp)tmp->id = 0;
		free((*bonuses)->timer);
		free((*bonuses)->vertices);
		free(*bonuses);
		*bonuses = tmp;
	}else {
		for(i = *bonuses; i->next != 0; i=i->next) {
			if(i->next->id == id)
				break;
		}
		tmp = i->next->next;
		free(i->next->timer);
		free(i->next->vertices);
		free(i->next);
		i->next = tmp;
	}
}

void bonuses_update(Bonus **bonuses, Player *p, float time) {
	Bonus *i;
	AABB bonus_rect;
	for(i = *bonuses; i != NULL; i = i->next) {
		if(!i->timer->is_active) {
			bonus_rect = bonus_get_rect(i);
			if(player_collision(p, &bonus_rect, 0, 0)) {
				i->timer->is_active = 1;
				i->func(p, i->data);
			}
		}else if(timer_update(i->timer, p, time)) {
			bonus_del(bonuses, i->id);
		}
	}
}

void bonuses_free(Bonus *bonuses) {
	Bonus *i;
	for(i = bonuses; i != NULL; i = i->next) {
		free(i->timer);
		free(i->vertices);
		free(i);
	}
}

void bonuses_draw(Bonus *bonuses) {
	Bonus *i;
	AABB camera = {-global_x, -global_y, WIN_W, WIN_H};
	AABB bonus_rect;
	for(i = bonuses; i != NULL; i = i->next) {
		bonus_rect = bonus_get_rect(i);
		if(!aabb_collision(&camera, &bonus_rect) || i->timer->is_active) continue;

		glPushMatrix();

		glTranslatef(i->x, i->y, 0.0f);
		polygon_draw(i->vertices, i->v_count);

		glPopMatrix();
	}
}

AABB bonus_get_rect(Bonus *b) {
	AABB rect = {b->x, b->y, b->width, b->height};
	return rect;
}
