#include <stdio.h>
#include <string.h>
#include <time.h>

#include "page.h"
#include "map.h"
#include "db.h"

#define MAXINPUT 2048

#define DEBUG 0

void unencode(char *src, int length, char *dest);
map  tokenize(char *input);

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
		char input[MAXINPUT], data[MAXINPUT], author[MAXINPUT], date[MAXINPUT];
		char *title, *body, *query;
		long int len;
		int error, rows;
		time_t t = time(NULL);
		map formValues = map_init(10);

		if (DEBUG) {
			strcpy(input, "title=this is a title&body=hello&author=a. b.");
			len = strlen(input)+1;
		}
		else {
			sscanf(conLen, "%ld", &len);
			fgets(input, len+1, stdin);
		}

		unencode(input, len, data);

		formValues = tokenize(data);

		db_connect();

		title = db_escape(map_search(&formValues, "title")->value);
		body = db_escape(map_search(&formValues, "body")->value);
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
	}

	renderPage();

	return EXIT_SUCCESS;
}

void unencode(char *src, int length, char *dest) {
	int i;
	for(i = 0; i < length; i++) {
		if (src[i] == '+')
			dest[i] = ' ';
		else
			dest[i] = src[i];
	}

	dest[i] = '\0';
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

		map_insert(&output, key, value);
		token = strtok(NULL, "&");
	}

	return output;
}
