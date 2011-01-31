#include <stdio.h>
#include <string.h>
#include <time.h>

#include "db.h"
#include "map.h"
#include "error.h"

int main () {
	const int VALUES = 5000;
	map * results;
	int i, j, rows, error, returnCode = EXIT_SUCCESS;

	// --------------------------------------------------------------------------
	printf("> Connect to database... ");
	if (db_connect() != FITZ_SUCCESS) {
		puts("not ok");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	// --------------------------------------------------------------------------
	printf("> Insert some values... ");
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];
		char body[64];
		char author[64];
		char date[64];
		time_t t = time(NULL);

		sprintf(title, "Title %d", i);
		strcpy(body, "Lorem ipsum dolor sit amet, consectetur adipiscing volutpat.");
		strcpy(author, "Me");
		strftime(date, sizeof(date), "%F %T", localtime(&t));

		sprintf(query, "insert into articles (title,body,author,date) values ('%s','%s','%s','%s')",
			title, body, author, date);

		results = db_query(query, &rows, &error);
		if (error != FITZ_SUCCESS) {
			puts("not ok");
			returnCode = EXIT_FAILURE;
			break;
		}
	}
	if (i == VALUES) {
		puts("ok");
	}

	// --------------------------------------------------------------------------
	printf("> Retrieve those values... ");
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];

		sprintf(title, "Title %d", i);
		sprintf(query, "select * from articles where title = '%s'", title);

		results = db_query(query, &rows, &error);
		if (error != FITZ_SUCCESS || results == NULL) {
			puts("not ok");
			returnCode = EXIT_FAILURE;
			break;
		}

		for (j = 0; j < rows; ++j) {
			fprintf(stderr, "got values:\n \ttitle(%s)\n \tbody(%s)\n \tauthor(%s)\n \tdate(%s)\n",
				map_search(&results[j], "title")->value,
				map_search(&results[j], "body")->value,
				map_search(&results[j], "author")->value,
				map_search(&results[j], "date")->value
			);
		}
	}
	if (i == VALUES) {
		puts("ok");
	}

	// --------------------------------------------------------------------------
	printf("> Delete those values... ");
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];

		sprintf(title, "Title %d", i);
		sprintf(query, "delete from articles where title = '%s'", title);

		results = db_query(query, &rows, &error);
		if (error != FITZ_SUCCESS) {
			puts("not ok");
			returnCode = EXIT_FAILURE;
			break;
		}
	}
	if (i == VALUES) {
		puts("ok");
	}

	// --------------------------------------------------------------------------
	printf("> Close DB connection... ");
	db_close();
	puts("ok");

	return returnCode;
}
