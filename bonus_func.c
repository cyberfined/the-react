#include "headers/bonus_func.h"

void bonus_functions_init(Map **map) {
	map_add_pair(map, "speedup", (void*)speedup);
	map_add_pair(map, "radiusup", (void*)radiusup);
	map_add_pair(map, "healthup", (void*)healthup);
}

void speedup(Player *p, float data) {
	p->speed = (int)data;
}

void radiusup(Player *p, float data) {
	p->r = data;
}

void healthup(Player *p, float data) {
	p->health += data;
	printf("Your health %i\n",p->health);
}
