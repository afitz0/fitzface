#include "map.h"

/*
#include <stdio.h>

int main() {
	map m;
	map_value * result;
	int code = 0;
	char a[8], b[8];
	const int SIZE = 150;

	printf("---> Init map with %d indexes\n", SIZE);
	m = map_init(SIZE);
	if (m.values == NULL) {
		puts("ERROR: map init failed. Critical, cannot continue.");
		exit(1);
	}

	strcpy(a, "hello");
	strcpy(b, "world");
	printf("---> Insert '%s' => '%s'\n", a, b);
	code = map_insert(&m, a, b);
	if (code != FITZ_SUCCESS) {
		puts("ERROR: insert failed.");
	}

	strcpy(a, "hello");
	printf("---> Retrieve key '%s'\n", a);
	result = map_search(&m, a);
	if (result == NULL) {
		puts("ERROR: did not find entry.");
	} else {
		printf("Got back key '%s', value '%s'\n", result->key, result->value);
	}

	strcpy(a, "hello");
	strcpy(b, "mundo");
	printf("---> Change key '%s' value from 'world' to '%s'\n", a, b);
	code = map_update(&m, a, b);
	if (code != FITZ_SUCCESS) {
		puts("ERROR: update failed.");
	}

	strcpy(a, "hello");
	printf("---> Retrieve key '%s'\n", a);
	result = map_search(&m, a);
	if (result == NULL) {
		puts("ERROR: did not find entry.");
	} else {
		printf("Got back key '%s', value '%s'\n", result->key, result->value);
	}

	strcpy(a, "hello");
	printf("---> Delete key '%s'\n", a);
	code = map_delete(&m, a);
	if (code != FITZ_SUCCESS) {
		puts("ERROR: delete failed.");
	}

	strcpy(a, "hello");
	printf("---> Retrieve key '%s'\n", a);
	result = map_search(&m, a);
	if (result != NULL) {
		printf("ERROR: should have gotten NULL, got '%s' => '%s' instead.\n", result->key, result->value);
	}

	printf("---> Inserting %d different key,value pairs\n", SIZE);
	for (int i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);
		sprintf(b, "value%d", i);

		code = map_insert(&m, a, b);
		if (code != FITZ_SUCCESS) {
			printf("ERROR: insertion of key %d failed\n", i);
		}
	}

	strcpy(a, "key100");
	printf("---> Delete %s\n", a);
	code = map_delete(&m, a);
	if (code != FITZ_SUCCESS) {
		printf("ERROR: deletion of %s failed.\n", a);
	}

	printf("---> Retrieve key0..key%d\n", SIZE-1);
	for (int i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);
		sprintf(b, "value%d", i);

		result = map_search(&m, a);
		if (result == NULL) {
			if (i != 100) {
				printf("ERROR: could not find key%d.\n", i);
			}
		} else if (strcmp(result->key, a) != 0) {
			printf("ERROR: retrieved key does not match. Expected '%s' got '%s' instead.\n", a, result->key);
		} else if (strcmp(result->value, b) != 0) {
			printf("ERROR: retrieved value does not match. Expected '%s' got '%s' instead.\n", b, result->value);
		}
	}

	puts("---> Reinsert key100.");
	code = map_insert(&m, "key100", "value100");
	if (code != FITZ_SUCCESS) {
		puts("ERROR: insert failed.");
	}

	puts("---> Draw map");
	for (int i = 0; i < SIZE; i++) {
		printf("[%d]: ", i);
		if (m.values[i] == NULL) {
			printf("NULL\n");
		} else {
			map_value * n = m.values[i];

			while (n != NULL) {
				printf("'%s'=>'%s' ", n->key, n->value);
				n = n->next;
			}

			printf("\n");
		}
	}

	printf("---> Delete key0..key%d\n", SIZE-1);
	for (int i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);

		code = map_delete(&m, a);
		if (code != FITZ_SUCCESS) {
			printf("ERROR: delete of key '%s' failed!\n", a);
		}
	}

	puts("---> Free map");
	code = map_free(&m);
	if (code != FITZ_SUCCESS) {
		puts("ERROR: map_free failed.");
	}

	return 0;
}
*/

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
	for (int i = 0; i < m->max; i++) {
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


