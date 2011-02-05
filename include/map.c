#include <stdio.h>

#include "map.h"

map map_init(size_t max_size) {
	map m;
	int i;

	m.max = max_size;
	m.values = (map_value**)malloc(max_size * sizeof(map_value*));
	if (m.values == NULL) {
		fprintf(stderr, "Malloc'ing values failed!\n");
	} else {
		for (i = 0; i < (int)max_size; ++i) {
			m.values[i] = NULL;
		}
	}

	return m;
}

// hash -- returns index based on given string
int map_hash(map * m, const char * key) {
	int hash = 0, i;
	unsigned char * buf;

	buf = malloc(SHA_DIGEST_LENGTH);
	if (buf == NULL) {
		fprintf(stderr, "Allocation of buffer for hash failed!\n");
		return FITZ_MEMORY_ERROR;
	}

	if (SHA1((const unsigned char *)key, strlen(key), buf) == NULL) {
		fprintf(stderr, "Calculation of SHA1 failed!\n");
		free(buf);
		return FITZ_ERROR;
	}

	for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
		hash += (int)buf[i];
	}

	free(buf);
	return (hash % m->max);
}

// insert
int map_insert(map * m, const char * key, const char * value) {
	int index = map_hash(m, key);

	map_value * v = malloc(sizeof(map_value));
	if (v == NULL) {
		fprintf(stderr, "Allocation of new value failed!\n");
		return FITZ_MEMORY_ERROR;
	}

	v->next  = NULL;
	v->prev  = NULL;
	v->key   = malloc(strlen(key)+1);
	if (v->key == NULL) {
		fprintf(stderr, "Allocation of new value's key failed!\n");
		free(v);
		return FITZ_MEMORY_ERROR;
	}

	v->value = malloc(strlen(value)+1);
	if (v->value== NULL) {
		fprintf(stderr, "Allocation of new value's text failed!\n");
		free(v->key);
		free(v);
		return FITZ_MEMORY_ERROR;
	}

	strcpy(v->key, key);
	strcpy(v->value, value);

	if (m->values[index] == NULL) {
		m->values[index] = v;
	} else {
		map_value * n = m->values[index];

		if (strcmp(n->key, key) == 0) {
			free(v->key);
			free(v->value);
			free(v);
			return FITZ_KEY_EXISTS;
		}

		while (n->next != NULL) {
			n = n->next;

			if (strcmp(n->key, key) == 0) {
				free(v->key);
				free(v->value);
				free(v);
				return FITZ_KEY_EXISTS;
			}
		}

		n->next = v;
		v->prev = n;
	}

	return FITZ_SUCCESS;
}

// update
int map_update(map * m, const char * key, const char * new_value) {
	map_value * v = map_search(m, key);

	if (v == NULL) {
		return FITZ_NOT_FOUND;
	} else {
		strcpy(v->value, new_value);
		return FITZ_SUCCESS;
	}
}

// delete
int map_delete(map * m, const char * key) {
	map_value * v = map_search(m, key);
	int index = map_hash(m, key);

	if (v == NULL) {
		return FITZ_NOT_FOUND;
	} else {
		if (v->prev != NULL && v->next != NULL) {
			v->prev->next = v->next;
			v->next->prev = v->prev;
		} else if (v->prev != NULL && v->next == NULL) {
			v->prev->next = NULL;
		} else if (v->prev == NULL && v->next != NULL) {
			m->values[index] = v->next;
			v->next->prev = NULL;
		} else if (v->prev == NULL && v->next == NULL) {
			m->values[index] = NULL;
		}

		free(v->key);
		free(v->value);
		free(v);
	}

	return FITZ_SUCCESS;
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

int map_free(map * m) {
	int i;

	for (i = 0; i < m->max; i++) {
		if (m->values[i] != NULL) {
			map_value * n = m->values[i];
			map_value * p;

			while (n->next != NULL) {
				n = n->next;
			}

			p = n->prev;
			free(n);
			n = p;

			while (p != NULL) {
				p = n->prev;
				free(n);
				n = p;
			}
		}
	}

	free(m->values);

	return FITZ_SUCCESS;
}


