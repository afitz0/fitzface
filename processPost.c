#include "page.h"
#include <string.h>
#include <stdio.h>

#define MAXINPUT 2048

void unencode(char *src, int length, char *dest) {
	int i;
	for(i = 0; i < length; i++) {
		if (src[i] == '+')
			src[i] = ' ';
		else
			dest[i] = src[i];
	}

	dest[i] = '\0';
}

int main (int argc, char ** argv) {
	char *lenstr;
	char input[MAXINPUT], data[MAXINPUT];
	long len;

	initPage();
	useTemplate(MAIN);

	lenstr = getenv("CONTENT_LENGTH");
	sscanf(lenstr, "%ld", &len);

	fgets(input, len+1, stdin);
	unencode(input, len, data);

	printf("%s\n", data);

	/*
	setSlot(BODY,
		data,
		TEXT_RAW
	);

	renderPage();
	*/
}
