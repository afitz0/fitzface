#ifndef FITZFACE_COM_PAGE
#define FITZFACE_COM_PAGE

#include <stdlib.h>
#include <stdbool.h>

extern const size_t MAX_SLOT_SIZE;
extern const size_t MAX_LINE_SIZE;

enum {
	MAIN
} templates;

enum {
	TITLE = 0,
	HEAD,
	FOOT,
	RIGHT_BAR,
	BODY,
	NUM_SLOTS
} slotKeys;

enum {
	HTML_RAW,
	HTML_FILE,
	TEXT_RAW,
	STDIN
} slotTypes;

struct slotValues {
	int type;
	char * text;
};

struct pageOptions {
	bool jQuery;	
};

struct slotValues  slots[NUM_SLOTS];
struct pageOptions options;

int initPage      ();
int includejQuery ();
int printFile     (const char * filename);
int printStdin    ();
int printBlock    (const int block);
int setSlot       (const int slot, const char * value, const int type);
int appendSlot    (const int slot, const char * value, const int type);
int renderPage    ();
int useTemplate   (const int temp);

#endif
