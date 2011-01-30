#include "map.h"
#include <stdio.h>

int main() {
	map m;
	map_value * result;
	int code = 0, i, returnCode = EXIT_SUCCESS;
	char a[8], b[8];
	const int SIZE = 150000;

	printf("> Init maps... ");
	m = map_init(SIZE);
	if (m.values == NULL) {
		puts("not ok");
		puts("ERROR: map init failed. Critical; cannot continue.");
		exit(EXIT_FAILURE);
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	strcpy(b, "world");
	printf("> Insert '%s' => '%s'... ", a, b);
	code = map_insert(&m, a, b);
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		puts("ERROR: insert failed.");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	printf("> Retrieve key '%s'... ", a);
	result = map_search(&m, a);
	if (result == NULL) {
		puts("not ok");
		puts("ERROR: did not find entry.");
		returnCode = EXIT_FAILURE;
	} else if (strcmp(result->value, b) != 0){
		puts("not ok");
		printf("ERROR: got back '%s' => '%s'. Expected value '%s'", result->key, result->value, b);
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	strcpy(b, "mundo");
	printf("> Change key '%s' to value '%s'... ", a, b);
	code = map_update(&m, a, b);
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		puts("ERROR: update failed.");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	printf("> Retrieve key '%s'... ", a);
	result = map_search(&m, a);
	if (result == NULL) {
		puts("not ok");
		puts("ERROR: did not find entry.");
		returnCode = EXIT_FAILURE;
	} else if (strcmp(result->value, b) != 0){
		puts("not ok");
		printf("ERROR: got back '%s' => '%s'. Expected value '%s'", result->key, result->value, b);
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	printf("> Delete key '%s'... ", a);
	code = map_delete(&m, a);
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		puts("ERROR: delete failed.");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	strcpy(a, "hello");
	printf("> Retrieve key '%s'... ", a);
	result = map_search(&m, a);
	if (result != NULL) {
		puts("not ok");
		printf("ERROR: expected NULL, got '%s' => '%s'.\n", result->key, result->value);
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	printf("> Inserting %d different key,value pairs... ", SIZE);
	for (i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);
		sprintf(b, "value%d", i);

		code = map_insert(&m, a, b);
		if (code != FITZ_SUCCESS) {
			puts("not ok");
			printf("ERROR: insertion of key %d failed\n", i);
			returnCode = EXIT_FAILURE;
			break;
		}
	}
	if (i == SIZE) {
		puts("ok");
	}

	strcpy(a, "key100");
	printf("> Delete %s... ", a);
	code = map_delete(&m, a);
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		printf("ERROR: deletion of %s failed.\n", a);
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	printf("> Retrieve key0..key%d... ", SIZE-1);
	for (i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);
		sprintf(b, "value%d", i);

		result = map_search(&m, a);
		if (result == NULL) {
			if (i != 100) {
				puts("not ok");
				printf("ERROR: could not find key%d.\n", i);
				returnCode = EXIT_FAILURE;
				break;
			}
		} else if (strcmp(result->key, a) != 0) {
			puts("not ok");
			printf("ERROR: retrieved key does not match. Expected '%s' got '%s' instead.\n", a, result->key);
			returnCode = EXIT_FAILURE;
			break;
		} else if (strcmp(result->value, b) != 0) {
			puts("not ok");
			printf("ERROR: retrieved value does not match. Expected '%s' got '%s' instead.\n", b, result->value);
			returnCode = EXIT_FAILURE;
			break;
		}
	}
	if (i == SIZE) {
		puts("ok");
	}

	printf("> Reinsert key100... ");
	code = map_insert(&m, "key100", "value100");
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		puts("ERROR: insert failed.");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	printf("> Draw map... ");
	for (i = 0; i < SIZE; i++) {
		fprintf(stderr, "[%d]: ", i);
		if (m.values[i] == NULL) {
			fprintf(stderr, "NULL\n");
		} else {
			map_value * n = m.values[i];

			while (n != NULL) {
				fprintf(stderr, "'%s'=>'%s' ", n->key, n->value);
				n = n->next;
			}

			fprintf(stderr, "\n");
		}
	}
	if (i == SIZE) {
		puts("ok");
	}

	printf("> Delete key0..key%d... ", SIZE-1);
	for (i = 0; i < SIZE; i++) {
		sprintf(a, "key%d", i);

		code = map_delete(&m, a);
		if (code != FITZ_SUCCESS) {
			puts("not ok");
			printf("ERROR: delete of key '%s' failed!\n", a);
			returnCode = EXIT_FAILURE;
			break;
		}
	}
	if (i == SIZE) {
		puts("ok");
	}

	printf("> Free map... ");
	code = map_free(&m);
	if (code != FITZ_SUCCESS) {
		puts("not ok");
		puts("ERROR: map_free failed.");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	return returnCode;
}
