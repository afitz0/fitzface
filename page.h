#ifndef FITZFACE_COM_PAGE
#define FITZFACE_COM_PAGE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "errorCodes.h"

const size_t MAX_SLOT_SIZE = 1024;
const size_t MAX_LINE_SIZE = 1024;

enum {
	TITLE = 0,
	HEAD,
	FOOT,
	RIGHT_BAR,
	BODY,
	NUM_SLOTS
} slotKeys;

enum {
	HTML_RAW = 0,
	HTML_FILE,
	TEXT_RAW
} slotTypes;

struct slotValues {
	int type;
	char * text;
};

struct pageOptions {
	bool jQuery;	
};

struct slotValues slots[NUM_SLOTS];
struct pageOptions options;

int initPage() {
	int i;
	for (i = 0; i < NUM_SLOTS; ++i) {
		slots[i].text = (char*)malloc(MAX_SLOT_SIZE);
		strcpy(slots[i].text, "");
	}

	options.jQuery = false;

	return FITZ_RETURN_SUCCESS;
}

int includejQuery() {
	options.jQuery = true;

	return FITZ_RETURN_SUCCESS;
}

int printFile(const char * filename) {
	char * line = (char*)malloc(MAX_LINE_SIZE);
	FILE * file = fopen(filename, "r");
	size_t lineSize = MAX_LINE_SIZE;

	while (getline(&line, &lineSize, file) != EOF) {
		printf("%s", line);
	}

	fclose(file);

	return FITZ_RETURN_SUCCESS;
}

int printBlock(const int block) {
	int returnCode;

	if (strcmp(slots[block].text, "") != 0) {
		switch (block) {
			case RIGHT_BAR:
				printf("<div class=\"rightBar\">");
				break;
			case BODY:
				printf("<div class=\"body\">");
				break;
			case HEAD:
				printf("<div class=\"header\">");
				break;
			case FOOT:
				printf("<div class=\"footer\">");
				break;
			default:
				printf("<div class=\"unknown\">");
		}

		printf("<div class=\"shadow\"> \
			<div class=\"content\">");
		
		if (slots[block].type == HTML_FILE)
			printFile(slots[block].text);
		else if ((slots[block].type == HTML_RAW) || (slots[block].type == TEXT_RAW))
			printf("%s", slots[block].text);

		printf("</div> \
				</div> \
			</div>");

		returnCode = FITZ_RETURN_SUCCESS;
	} else {
		returnCode = FITZ_RETURN_EMPTY;
	}

	return returnCode;
}

int setSlot(const int slot, const char * value, const int type) {
	int returnCode = FITZ_RETURN_SUCCESS;

	if ((slot == TITLE) && (type != TEXT_RAW)) {
		returnCode = FITZ_RETURN_TYPE_ERROR;
	}

	strcpy(slots[slot].text, value);
	slots[slot].type = type;

	return returnCode;
}

int appendSlot(const int slot, char * value) {
	return FITZ_RETURN_SUCCESS;
}

int renderPage() {
	// Headers
	printf("Content-type: text/html\r\n\r\n");

	// Content
	printf("<!doctype html><html><head> \
		<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">");
	printf("<title>%s</title>", slots[TITLE].text);

	if (options.jQuery) {
		printf("<script type=\"text/javascript\" src=\"http://code.jquery.com/jquery-1.4.2.min.js\"></script>");
	}

	printf("<link rel=\"stylesheet\" href=\"/main.css\" type=\"text/css\"> \
		</head> \
		<body>");

	printBlock(HEAD);
	printBlock(RIGHT_BAR);
	printBlock(BODY);
	printBlock(FOOT);

	return FITZ_RETURN_SUCCESS;
}

#endif
