#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "page.h"

const size_t LINE_LENGTH = 512;

int initPage() {
	int i;
	for (i = 0; i < NUM_SLOTS; ++i) {
		slots[i].text = malloc(1);
		if (slots[i].text != NULL) {
			slots[i].text[0] = '\0';
		} else {
			perror("Allocation of slot failed");
		}
	}

	options.jQuery = false;

	return FITZ_SUCCESS;
}

int includejQuery() {
	options.jQuery = true;

	return FITZ_SUCCESS;
}

int printFile(const char * filename) {
	FILE * file;
	char * line;

	file = fopen(filename, "r");
	if (file == NULL) {
		perror("Could not open file");
		return FITZ_ERROR;
	}

	line = malloc(LINE_LENGTH);
	if (line == NULL) {
		perror("Allocation of line buffer failed");
		return FITZ_ERROR;
	}

	while (fgets(line, (int)LINE_LENGTH, file) != NULL) {
		printf("%s", line);
	}

	if (fclose(file) != 0) {
		perror("Warning: could not close file");
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

		printf("<div class=\"content\">");
		
		switch (slots[block].type) {
			case HTML_FILE:
				if (printFile(slots[block].text) != FITZ_SUCCESS) {
					fprintf(stderr, "Printing file %s failed!\n", slots[block].text);
				}
				break;
			case HTML_RAW:
			case TEXT_RAW:
				printf("%s", slots[block].text);
				break;
			default:
				printf("Unknown block");
		}

		printf("</div></div>");

		returnCode = FITZ_SUCCESS;
	} else {
		returnCode = FITZ_EMPTY;
	}

	return returnCode;
}

int setSlot(const int slot, const char * value, const int type) {
	slots[slot].text = realloc(slots[slot].text, strlen(value)+1);
	if (slots[slot].text == NULL) {
		fprintf(stderr, "Resize of slots[%d] faild!\n", slot);
		return FITZ_MEMORY_ERROR;
	}

	if ((slot == TITLE) && (type != TEXT_RAW))
		return FITZ_TYPE_ERROR;

	if (value == NULL)
		return FITZ_NULL_VALUE;

	strcpy(slots[slot].text, value);
	slots[slot].type = type;
	return FITZ_SUCCESS;
}

int appendSlot(const int slot, const char * value, const int type) {
	size_t slotLen  = strlen(slots[slot].text);
	size_t newLen   = slotLen + strlen(value) + 1;
	char * newValue = malloc(newLen);
	int ret;

	if (newValue == NULL) {
		perror("Allocation of value for appending failed");
		return FITZ_MEMORY_ERROR;
	}

	if (slotLen == 0)
		strcpy(newValue, value);
	else
		(void)snprintf(newValue, newLen, "%s%s", slots[slot].text, value);

	newValue[newLen-1] = '\0';
	ret = setSlot(slot, newValue, type);
	free(newValue);

	return ret;
}

int renderPage() {
	int i;

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

	if (printBlock(HEAD) != FITZ_SUCCESS)
		fprintf(stderr, "Printing block HEAD failed!");
	if (printBlock(RIGHT_BAR) != FITZ_SUCCESS)
		fprintf(stderr, "Printing block RIGHT_BAR failed!");
	if (puts("<div class=\"main\">") == EOF)
		fprintf(stderr, "Printing start div failed!");
	if (printBlock(BODY) != FITZ_SUCCESS)
		fprintf(stderr, "Printing block BODY failed!");
	if (printBlock(FOOT) != FITZ_SUCCESS)
		fprintf(stderr, "Printing block FOOT failed!");
	if (puts("</div>") == EOF)
		fprintf(stderr, "Printing end div failed!");


	printf("</body></html>\n");

	// Free allocated blocks
	for (i = 0; i < NUM_SLOTS; ++i) {
		free(slots[i].text);
	}

	return FITZ_SUCCESS;
}

int useTemplate(const int temp) {
	int code;

	switch (temp) {
		case MAIN:
			code = setSlot(TITLE,
				"Fitzface.com",
				TEXT_RAW
			);
			if (code != FITZ_SUCCESS)
				fprintf(stderr, "Setting slot TITLE failed!\n");

			code = setSlot(RIGHT_BAR,
				"<ul> \
					<li><a href=\"/aboutMe\">About Me</a></li> \
					<li><a href=\"/aboutSite\">About Fitzface.com</a></li> \
					<li><a href=\"/resume\">Resume</a></li> \
				</ul>",
				HTML_RAW
			);
			if (code != FITZ_SUCCESS)
				fprintf(stderr, "Setting slot RIGHT_BAR failed!\n");

			code = setSlot(HEAD,
				"<strong><a href=\"/\">Fitzface.com</a></strong>",
				HTML_RAW
			);
			if (code != FITZ_SUCCESS)
				fprintf(stderr, "Setting slot HEAD failed!\n");

			break;
		default:
			break;
	}

	return FITZ_SUCCESS;
}
