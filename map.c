#include "headers/map.h"

void map_add_pair(Map **map, char *key, void *value) {
	Map *tmp = (Map*)malloc(sizeof(Map));
	Map *i;
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	if(*map == NULL) {
		*map = tmp;
	}else {
		for(i = *map; i->next != NULL; i = i->next);
		i->next =  tmp;
	}
}

void map_del_pair(Map **map, char *key) {
	Map *i;
	Map *tmp;
	if(*map && !strcmp((*map)->key, key)) {
		tmp = (*map)->next;
		free(*map);
		*map = tmp;
	}else {
		for( i = *map; i->next != NULL; i=i->next) {
			if(i->next && !strcmp(key, i->next->key))
				break;
		}
		tmp = i->next->next;
		free(i->next);
		i->next = tmp;
	}
}

void map_free(Map *map) {
	Map *i;
	for(i = map; i != NULL; i = i->next) {
		free(i);
	}
}

void* map_get_value(Map *map, char *key) {
	Map *i;
	for(i = map; i != NULL; i = i->next) {
		if(!strcmp(i->key, key))
			return i->value;
	}
	return NULL;
}
