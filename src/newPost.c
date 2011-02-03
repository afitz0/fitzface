#include <stdio.h>
#include <string.h>
#include <time.h>

#include "page.h"
#include "map.h"
#include "db.h"

#define MAXINPUT 2048

#define DEBUG 0

const char * DEBUG_INPUT = "title=hello&body=+h%26+&submit=Submit";

map    tokenize(char *input);
char * unencode(char *src);

int main (int argc, char ** argv) {
	char * conLen;

	initPage();
	useTemplate(MAIN);

	if (DEBUG)
		conLen = malloc(1); // just needs to be !NULL
	else
		conLen = getenv("CONTENT_LENGTH");

	if (conLen == NULL) {
		setSlot(TITLE,
			"New Article",
			TEXT_RAW
		);

		setSlot(BODY,
			"<form name=\"register\" action=\"\" method=\"post\">\n \
				<strong>Title:</strong>\n \
				<input type=\"text\" name=\"title\" style=\"width: 50%;\" />\n \
				<br />\n \
				<textarea maxlength=\"1000\" rows=20 style=\"width: 100%;\" name=\"body\" class=\"limited\"></textarea>\n \
				<br />\n \
				<input type=\"submit\" name=\"submit\" value=\"Submit\"/>\n \
			</form>\n \
			",
			HTML_RAW
		);
	} else {
		char input[MAXINPUT], author[MAXINPUT], date[MAXINPUT];
		char *title, *body, *query;
		long int len;
		int error, rows;
		time_t t = time(NULL);
		map formValues = map_init(10);

		if (DEBUG) {
			strcpy(input, DEBUG_INPUT);
			len = strlen(input)+1;
		} else {
			sscanf(conLen, "%ld", &len);
			fgets(input, len+1, stdin);
		}

		formValues = tokenize(input);

		db_connect();

		title = db_escape(map_search(&formValues, "title")->value);
		body  = db_escape(map_search(&formValues, "body")->value);
		strcpy(author, "A Fitz");
		strftime(date, sizeof(date), "%F %T", localtime(&t));

		query = malloc(strlen(title)
			+ strlen(body)
			+ strlen(author)
			+ strlen(date)
			+ strlen("insert into articles (title,body) values ('','','','')") + 1);
		sprintf(query, "insert into articles (title,body,author,date) values ('%s','%s','%s','%s')",
			title, body, author, date);

		db_query(query, &rows, &error);
		if (error != FITZ_SUCCESS) {
			setSlot(BODY,
				query,
				TEXT_RAW
			);
		} else {
			setSlot(BODY,
				"<h1>Thanks for posting!</h1>",
				TEXT_RAW
			);
		}

		free(query);
	}

	renderPage();

	return EXIT_SUCCESS;
}

map tokenize(char *input) {
	int i, j;
	char * token;
	char key[MAXINPUT], value[MAXINPUT];
	map output = map_init(10);

	token = strtok(input, "&");
	while (token != NULL) {
		for (i = 0; i < strlen(token); i++) {
			if (token[i] == '=')
				break;
			else
				key[i] = token[i];
		}
		key[i] = '\0';

		i++;

		for (j = 0; j < strlen(token); j++)
			value[j] = token[i+j];
		value[j] = '\0';

		map_insert(&output, key, unencode(value));
		token = strtok(NULL, "&");
	}

	return output;
}

char * unencode(char *src) {
	char * in = src;
	char * out = malloc(strlen(src));
	int i;

	for (i = 0; *in != '\0'; i++) {
		if (*in == '+') {
			out[i] = ' ';
		} else if (*in == '%') {
			char hex[2];
			hex[0] = *(++in);
			hex[1] = *(++in);

			out[i] = (char)strtol(hex, NULL, 16);
		} else {
			out[i] = *in;
		}

		in++;
	}

	out[i] = '\0';
	return out;
}
