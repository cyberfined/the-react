#include "headers/player.h"
#define RAD_TO_DEG 57.2957795131

void player_draw(Player *p) {
	glPushMatrix();

	glTranslatef(p->x, p->y, 0.0f);
	glRotatef(p->angle*RAD_TO_DEG+90, 0.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	circle_draw(p->r);

	glColor3f(1.0f, 1.0f, 1.0f);
	arrow_draw(p->r);

	glPopMatrix();
}

void arrow_draw(float r) {
	glBegin(GL_LINES);
	
	glVertex2f(-r, -r);
	glVertex2f(0.0f, -r*2);

	glVertex2f(0.0f, -r*2);
	glVertex2f(r, -r);

	glEnd();
}

void player_bullet_collision(Player *p, Bullet **bullets) {
	Bullet *i;
	AABB b_rect;
	for(i = *bullets; i != NULL; i = i->next) {
		b_rect = bullet_get_rect(i);
		if(player_collision(p, &b_rect, 0, 0)) {
			bullet_del(bullets, i->id);
			if(--p->health == 0) {
				printf("You were dead\nGame Over :(\n");
				exit(0);
			}
			printf("Your health %i\n", p->health);
		}
	}
}

short player_collision(Player *p, AABB *rect, float dx, float dy) {
	AABB player_rect = {p->x - p->r + dx, p->y - p->r + dy, p->r*2, p->r*2};
	return aabb_collision(&player_rect, rect);
}

void player_walls_collision(Player *p, Wall *walls, float dx, float dy) {
	Wall *i;
	AABB wall_rect;
	for(i = walls; i != NULL; i = i->next) {
		wall_rect = wall_get_rect(i);
		if(player_collision(p, &wall_rect, dx, 0))
			dx = 0;
		if(player_collision(p, &wall_rect, 0, dy))
			dy = 0;
	}
	p->x += dx;
	p->y += dy;
	p->gun.x = p->x;
	p->gun.y = p->y;
	global_x = WIN_W - p->x - p->r - WIN_W/2;
	global_y = WIN_H - p->y - p->r - WIN_H/2;
}

void player_move(Player *p, Wall *walls, float time) {
	float dx = p->speed * time * cos(p->angle);
	float dy = p->speed * time * sin(p->angle);
	player_walls_collision(p, walls, dx, dy);
}

void player_strafe(Player *p, Wall *walls, float time, short dx, short dy) {
	float d = p->speed * time;
	player_walls_collision(p, walls, d * dx, d * dy);
}
