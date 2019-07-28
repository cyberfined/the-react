#include "headers/parser.h"
#define BUF_SIZE 1024

char* file_to_buf(char *filename, int *len) {
	FILE *file = fopen(filename, "r");
	if(!file) {
		fprintf(stderr, "Failed to open %s\n", filename);
		return NULL;
	}
	char *buf;
	fseek(file, 0, SEEK_END);
	*len = ftell(file);
	buf = (char*)malloc(*len + 1);
	fseek(file, 0, SEEK_SET);
	fread(buf, sizeof(char), *len, file);
	buf[*len] = '\0';
	fclose(file);
	return buf;
}

char** str_split(char *str, int len, char delim, int *count) {
	char **tokens;
	int i;
	int j = 0;
	int s = 0;
	*count = 1;
	for(i = 0; i < len; i++) {
		if(str[i] == delim) *count = *count + 1;
	}
	tokens = malloc(sizeof(char*) * (*count));
	for(i = 0; i < *count; i++) {
		tokens[i] = malloc(BUF_SIZE + 1);
	}
	for(i = 0; i < len; i++) {
		tokens[j][s] = str[i];
		s++;
		if(str[i] == delim) {
			tokens[j][s-1] = '\0';
			j++;
			s=0;
		}
	}
	tokens[j][s] = '\0';
	return tokens;
}

void parse_level(char *filename, Wall **walls, Bonus **bonuses, Enemy **enemies, AABB *exit_place, Player *p) {
	int len;
	int obj_count;
	int fields_count;
	char *file = file_to_buf(filename, &len);
	char **obj = str_split(file, len, ';', &obj_count);
	char **fields;
	int i;
	int j;

	for(i = 0; i < obj_count; i++) {
		fields = str_split(obj[i], strlen(obj[i]), ',', &fields_count);
		if(!strcmp(fields[0], "w")) {
			wall_add(walls, wall_new(fields));
		}else if(!strcmp(fields[0], "e")) {
			enemy_add(enemies, parse_enemy(fields));
		}else if(!strcmp(fields[0], "b")) {
			bonus_add(bonuses, parse_bonus(fields));
		}else if(!strcmp(fields[0],"f")) {
			exit_place->x = atoi(fields[1]);
			exit_place->y = atoi(fields[2]);
			exit_place->w = atoi(fields[3]);
			exit_place->h = atoi(fields[4]);
		}else if(!strcmp(fields[0], "p")) {
			p->x = atof(fields[1]);
			p->y = atof(fields[2]);
		}
		for(j = 0; j < fields_count; j++) {
			free(fields[j]);
		}
		free(fields);
		free(obj[i]);
	}

	free(obj);
	free(file);
}

Enemy* parse_enemy(char **args) {
	int len;
	int obj_count;
	int fields_count;
	char *file = file_to_buf(args[3], &len);
	char **obj = str_split(file, len, ';', &obj_count);
	char **fields;
	Enemy *e = (Enemy*)malloc(sizeof(Enemy));
	int i,j;

	e->x = atof(args[1]);
	e->y = atof(args[2]);
	e->gun.x = 0;
	e->gun.y = 0;
	e->gun.cur_time = 0;
	e->id = 0;
	e->next = NULL;

	for(i = 0; i < obj_count; i++) {
		fields = str_split(obj[i], strlen(obj[i]), ',', &fields_count);
		if(!strcmp(fields[0], "v")) {
			e->v_count = (fields_count - 1)/5;
			e->vertices = vertices_create(fields, fields_count);
		}else if(!strcmp(fields[0], "w")) {
			e->width = atoi(fields[1]);
		}else if(!strcmp(fields[0], "h")) {
			e->height = atoi(fields[1]);
		}else if(!strcmp(fields[0], "l")) {
			e->health = atoi(fields[1]);
		}else if(!strcmp(fields[0], "s")) {
			e->speed = atof(fields[1]);
		}else if(!strcmp(fields[0], "r")) {
			e->gun.radius = atof(fields[1]);
		}else if(!strcmp(fields[0], "g")) {
			e->gun.speed = atof(fields[1]);
		}else if(!strcmp(fields[0], "d")) {
			e->gun.delay_time = atof(fields[1]);
		}
		for(j = 0; j < fields_count; j++) {
			free(fields[j]);
		}
		free(fields);
		free(obj[i]);
	}

	free(obj);
	free(file);
	return e;
}

Bonus* parse_bonus(char **args) {
	int len;
	int obj_count;
	int fields_count;
	char *file = file_to_buf(args[3], &len);
	char **obj = str_split(file, len, ';', &obj_count);
	char **fields;
	Bonus *b = (Bonus*)malloc(sizeof(Bonus));
	int i,j;

	b->x = atof(args[1]);
	b->y = atof(args[2]);
	b->timer = (Timer*)malloc(sizeof(Timer)); 
	b->timer->cur_time = 0;
	b->timer->is_active = 0;
	b->id = 0;
	b->next = NULL;

	for(i = 0; i < obj_count; i++) {
		fields = str_split(obj[i], strlen(obj[i]), ',', &fields_count);
		if(!strcmp(fields[0], "v")) {
			b->v_count = (fields_count - 1)/5;
			b->vertices = vertices_create(fields, fields_count);
		}else if(!strcmp(fields[0], "w")) {
			b->width = atoi(fields[1]);
		}else if(!strcmp(fields[0], "h")) {
			b->height = atoi(fields[1]);
		}else if(!strcmp(fields[0], "f")) {
			void(*tmp)(Player*,float) = map_get_value(functions, fields[1]);
			if(!functions) puts("doubleNULL");
			if(!tmp) puts("NULL");
			b->func = tmp;
			b->timer->func = tmp;
		}else if(!strcmp(fields[0], "d")) {
			b->timer->delay_time = atof(fields[1]);
		}else if(!strcmp(fields[0], "a1")) {
			b->data = atof(fields[1]);
		}else if(!strcmp(fields[0], "a2")) {
			b->timer->data = atof(fields[1]);
		}
		for(j = 0; j < fields_count; j++) {
			free(fields[j]);
		}
		free(fields);
		free(obj[i]);
	}

	free(obj);
	free(file);
	return b;
}

float* vertices_create(char **args, int args_count) {
	float *vertices = (float*)malloc(sizeof(float)*(args_count-1));
	int i;

	for(i = 1; i < args_count; i++) {
		vertices[i-1] = atof(args[i]);
	}

	return vertices;
}
