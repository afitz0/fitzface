#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "page.h"

const size_t MAX_SLOT_SIZE = 4098;
const size_t MAX_LINE_SIZE = 1024;

int initPage() {
	int i;
	for (i = 0; i < NUM_SLOTS; ++i) {
		slots[i].text = (char*)malloc(MAX_SLOT_SIZE);
		strcpy(slots[i].text, "");
	}

	options.jQuery = false;

	return FITZ_SUCCESS;
}

int includejQuery() {
	options.jQuery = true;

	return FITZ_SUCCESS;
}

int printFile(const char * filename) {
	char * line = (char*)malloc(MAX_LINE_SIZE);
	FILE * file = fopen(filename, "r");
	size_t lineSize = MAX_LINE_SIZE;

	while (getline(&line, &lineSize, file) != EOF) {
		printf("%s", line);
	}

	fclose(file);
	free(line);

	return FITZ_SUCCESS;
}

int printStdin() {
	char * line = (char*)malloc(MAX_LINE_SIZE);
	size_t lineSize = MAX_LINE_SIZE;

	while (getline(&line, &lineSize, stderr) != EOF) {
		printf("%s", line);
	}

	free(line);

	return FITZ_SUCCESS;
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
		
		switch (slots[block].type) {
			case HTML_FILE:
				printFile(slots[block].text);
				break;
			case STDIN:
				printStdin();
				break;
			case HTML_RAW:
			case TEXT_RAW:
				printf("%s", slots[block].text);
				break;
			default:
				printf("Unknown block");
		}

		printf("</div> \
				</div> \
			</div>");

		returnCode = FITZ_SUCCESS;
	} else {
		returnCode = FITZ_EMPTY;
	}

	return returnCode;
}

int setSlot(const int slot, const char * value, const int type) {
	int returnCode = FITZ_SUCCESS;

	if ((slot == TITLE) && (type != TEXT_RAW)) {
		returnCode = FITZ_TYPE_ERROR;
	}

	if (strlen(value) > MAX_SLOT_SIZE) {
		slots[slot].text = realloc(slots[slot].text, strlen(value)+1);
	}

	strcpy(slots[slot].text, value);
	slots[slot].type = type;

	return returnCode;
}

int appendSlot(const int slot, const char * value, const int type) {
	int returnCode;
	size_t lenSlot  = strlen(slots[slot].text);
	size_t lenValue = strlen(value);
	size_t newLen = lenSlot + lenValue + 1;
	char * newValue;

	if (newLen > MAX_SLOT_SIZE) {
		returnCode = FITZ_SIZE_ERROR;
	} else {
		newValue = (char*)malloc(newLen);

		sprintf(newValue, "%s %s", slots[slot].text, value);

		returnCode = setSlot(slot, newValue, type);
	}

	return returnCode;
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
			<script type=\"text/javascript\"> \
				var _gaq = _gaq || []; \
				_gaq.push(['_setAccount', 'UA-20321950-1']); \
				_gaq.push(['_trackPageview']); \
				(function() { \
				 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true; \
				 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js'; \
				 var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s); \
				 })(); \
			</script> \
		</head> \
		<body>");

	printBlock(HEAD);
	printBlock(RIGHT_BAR);
	printBlock(BODY);
	printBlock(FOOT);

	printf("</body></html>\n");

	// Free allocated blocks
	for (int i = 0; i < NUM_SLOTS; ++i) {
		free(slots[i].text);
	}

	return FITZ_SUCCESS;
}

int useTemplate(const int temp) {
	switch (temp) {
		case MAIN:
			setSlot(TITLE, 
				"Fitzface.com",
				TEXT_RAW
			);

			setSlot(RIGHT_BAR,
				"<ul> \
					<li><a href=\"/aboutMe\">About Me</a></li> \
					<li><a href=\"/aboutSite\">About Fitzface.com</a></li> \
					<li><a href=\"/resume\">Resume</a></li> \
				</ul>",
				HTML_RAW
			);

			setSlot(HEAD,
				"<strong><a href=\"/\">Fitzface.com</a></strong>",
				HTML_RAW
			);

			break;
		default:
			break;
	}

	return FITZ_SUCCESS;
}
