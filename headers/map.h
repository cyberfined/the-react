#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>

typedef struct _map {
	char *key;
	void *value;
	struct _map *next;
}Map;

void map_add_pair(Map **map, char *key, void *value);
void map_del_pair(Map **map, char *key);
void map_free(Map *map);
void* map_get_value(Map *map, char *key);

#endif
