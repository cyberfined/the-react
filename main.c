#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "headers/global.h"
#include "headers/player.h"
#include "headers/wall.h"
#include "headers/enemy.h"
#include "headers/bonus.h"
#include "headers/parser.h"

SDL_Window *window;
const Uint8 *keys; 
short mouse_down = 0;
short is_run = 1;
float cycle_time = 0;
int WIN_W=500, WIN_H=500;
float global_x = 0, global_y = 0;
AABB exit_place;
Map *functions = NULL;

Player p = {0, 0, 10, 10, -90, 5.0f, {100, 100, 7, 2, 10, 0}};
Bullet *p_bullets = NULL;
Bullet *e_bullets = NULL;
Wall *walls = NULL;
Bonus *bonuses = NULL;
Enemy *faggots = NULL;


int init(void) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("The Reactor", 100, 100, WIN_W, WIN_H, SDL_WINDOW_OPENGL);
	if(!window) {
		fprintf(stderr, "Failed to initialize window: %s\n", SDL_GetError());
		return 0;
	}

	SDL_GL_CreateContext(window);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	keys = SDL_GetKeyboardState(NULL);

	global_x = WIN_W - p.x - p.r - WIN_W/2;
	global_y = WIN_H - p.y - p.r - WIN_H/2;

	return 1;
}

void event_handler(SDL_Event *event) {
	switch(event->type) {
	case SDL_QUIT:
		is_run = 0;
		break;
	case SDL_KEYDOWN:
		keys = SDL_GetKeyboardState(NULL);
		break;
	case SDL_KEYUP:
		keys = SDL_GetKeyboardState(NULL);
		break;
	case SDL_MOUSEMOTION:
		p.angle = atan2(event->motion.y - p.y - global_y, event->motion.x - p.x - global_x);
		break;
	case SDL_MOUSEBUTTONDOWN:
		mouse_down = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		mouse_down = 0;
		break;
	}
}

void update(void) {
	/*Handle Keyboard*/
	if(keys[SDL_SCANCODE_W]) {
		player_move(&p, walls, cycle_time);

		if(player_collision(&p, &exit_place, 0, 0) && !faggots) {
			printf("You Win\nGame Over :)\n");
			exit(0);
		}
	}
	if(keys[SDL_SCANCODE_S]) {
		player_strafe(&p, walls, cycle_time, 0, 1);
	}
	if(keys[SDL_SCANCODE_A]) {
		player_strafe(&p, walls, cycle_time, -1, 0);
	}
	if(keys[SDL_SCANCODE_D]) {
		player_strafe(&p, walls, cycle_time, 1, 0);
	}
	if(mouse_down) {
		gun_shot_angle(&p.gun, &p_bullets, p.angle);
	}
	/*update*/
	gun_update(&p.gun, cycle_time);	
	enemies_guns_update(faggots, cycle_time);
	bullets_move(&p_bullets, walls, cycle_time);
	bullets_move(&e_bullets, walls, cycle_time);
	player_bullet_collision(&p, &e_bullets);
	enemies_bullet_collision(&faggots, &p_bullets);
	enemies_move(faggots, &p, walls, cycle_time);
	enemies_shoot(faggots, &p, &e_bullets);
	bonuses_update(&bonuses, &p, cycle_time);
	/*OpenGL update*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-global_x, WIN_W-global_x, WIN_H-global_y, -global_y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	bullets_draw(p_bullets);
	bullets_draw(e_bullets);
	walls_draw(walls);
	bonuses_draw(bonuses);
	enemies_draw(faggots);
	player_draw(&p);
	SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[]) {
	SDL_Event event;
	float previous_time = 0;
	float current_time = 0;

	if(argc == 3) {
		WIN_W = atoi(argv[1]);
		WIN_H = atoi(argv[2]);
	}

	bonus_functions_init(&functions);
	parse_level("map1.map", &walls, &bonuses, &faggots, &exit_place, &p);
	if(!init())
		return 1;

	while(is_run) {
		current_time = SDL_GetTicks();/*Do not play more than 49 days XD*/
		cycle_time = current_time - previous_time;
		cycle_time /= 10;
		while(SDL_PollEvent(&event)){
			event_handler(&event);
		}
		update();
		render();
		previous_time = current_time;
	}

	/*Clean Up*/
	bullets_free(p_bullets);
	bullets_free(e_bullets);
	enemies_free(faggots);
	walls_free(walls);
	bonuses_free(bonuses);
	map_free(functions);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
