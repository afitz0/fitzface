#ifndef FITZFACE_COM_MAP
#define FITZFACE_COM_MAP

#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>

#include "error.h"

typedef struct map_value {
	struct map_value * next;
	struct map_value * prev;
	char * key;
	char * value;
} map_value;

typedef struct map {
	map_value ** values;
	size_t max;
} map;

map map_init(size_t max_size);
int map_hash(map * m, const char * key);
int map_insert(map * m, const char * key, const char * value);
int map_update(map * m, const char * key, const char * value);
int map_delete(map * m, const char * key);
map_value * map_search(map * m, const char * key);
int map_free(map * m);

#endif
