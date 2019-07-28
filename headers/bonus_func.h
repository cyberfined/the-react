#ifndef BONUS_FUNC_H
#define BONUS_FUNC_H

#include <stdio.h>
#include "player.h"
#include "map.h"

extern Map *functions;
void bonus_functions_init(Map **map);
void speedup(Player *p, float data);
void radiusup(Player *p, float data);
void healthup(Player *p, float data);

#endif
