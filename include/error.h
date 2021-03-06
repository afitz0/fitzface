#ifndef FITZFACE_COM_ERROR
#define FITZFACE_COM_ERROR

enum {
	FITZ_SUCCESS = 0,
	FITZ_ERROR,
	FITZ_TYPE_ERROR,
	FITZ_SIZE_ERROR,
	FITZ_UNIMPLEMENTED,
	FITZ_KEY_EXISTS,
	FITZ_NOT_FOUND,
	FITZ_NULL_VALUE,
	FITZ_MEMORY_ERROR,
	FITZ_EMPTY
} FITZ_RETURNS;

char * errorString(const int code);

#endif
