#include <string.h>
#include <stdlib.h>

#include "error.h"

char * errorString(const int code) {
	char * string = malloc(1024);

	switch (code) {
		case FITZ_ERROR:
			strcpy(string, "A generic error has occurred.");
			break;
		case FITZ_TYPE_ERROR:
			strcpy(string, "Type specified is not allowed in the given slot.");
			break;
		case FITZ_SIZE_ERROR:
			strcpy(string, "Given value exceeds specified size limits.");
			break;
		case FITZ_UNIMPLEMENTED:
			strcpy(string, "This feature is not yet implemented.");
			break;
		case FITZ_KEY_EXISTS:
			strcpy(string, "Given key already exists. Use map_update instead.");
			break;
		case FITZ_NOT_FOUND:
			strcpy(string, "Given key does not exist.");
			break;
		case FITZ_EMPTY:
			strcpy(string, "Given block has no contents.");
			break;
		default:
			strcpy(string, "Unknown error code.");
	}

	return string;
}
