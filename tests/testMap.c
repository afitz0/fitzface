#include "map.h"
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
