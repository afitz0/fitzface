#ifndef FITZFACE_COM_MAP
#define FITZFACE_COM_MAP

#include "errorCodes.h"
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>

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

// init
map map_init(size_t max_size) {
	map m;

	m.max = max_size;
	m.values = (map_value**)malloc(max_size * sizeof(map_value*));

	return m;
}

// hash -- returns index based on given string
int map_hash(map * m, const char * key) {
	int hash = 0;
	unsigned char buf[20];

	SHA1(key, strlen(key), buf);

	for (int i = 0; i < 20; i++) {
		hash += buf[i];
	}

	return (hash % m->max);
}

// insert
int map_insert(map * m, const char * key, const char * value) {
	int index = map_hash(m, key);

	map_value * v = (map_value*)malloc(sizeof(map_value));
	v->next = NULL;
	v->prev = NULL;
	v->key = (char*)malloc(strlen(key)+1);
	v->value = (char*)malloc(strlen(value)+1);

	strcpy(v->key, key);
	strcpy(v->value, value);

	if (m->values[index] == NULL) {
		m->values[index] = v;
	} else {
		map_value * n = m->values[index];

		if (strcmp(n->key, key) == 0)
			return FITZ_KEY_EXISTS;

		while (n->next != NULL) {
			n = n->next;

			if (strcmp(n->key, key) == 0)
				return FITZ_KEY_EXISTS;
		}

		n->next = v;
		v->prev = n;
	}

	return FITZ_SUCCESS;
}

// update
int map_update(map * m, const char * key, const char * value) {
	map_value * v = map_search(m, key);

	if (v == NULL) {
		return FITZ_NOT_FOUND;
	} else {
		strcpy(v->value, value);
		return FITZ_SUCCESS;
	}
}

// delete
int map_delete(map * m, const char * key) {
	map_value * v = map_search(m, key);

	if (v == NULL) {
		return FITZ_NOT_FOUND;
	} else {
		
	}
}

// search (fetch/get)
// returns value struct associated with key, or NULL if not found
map_value * map_search(map * m, const char * key) {
	int index = map_hash(m, key);

	if (m->values[index] != NULL) {
		map_value * n = m->values[index];

		if (strcmp(n->key, key) == 0)
			return n;

		while (n->next != NULL) {
			n = n->next;

			if (strcmp(n->key, key) == 0)
				return n;
		}
	}

	return NULL;
}

// 

#endif
