#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "wall.h"
#include "enemy.h"
#include "bonus.h"
#include "aabb.h"
#include "map.h"
#include "bonus_func.h"

char* file_to_buf(char *filename, int *len);
char** str_split(char *str, int len, char delim, int *count);
void parse_level(char *filename, Wall **walls, Bonus **bonuses, Enemy **enemies, AABB *exit_place, Player *p);
Enemy* parse_enemy(char **args);
Bonus* parse_bonus(char **args);
float* vertices_create(char **args, int args_count);
short player_exit(Player *p);

#endif
