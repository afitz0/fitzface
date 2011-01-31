#include <stdio.h>
#include <string.h>
#include <time.h>

#include "db.h"
#include "map.h"
#include "error.h"

const char * SIMPLE_BODY  = "Lorem ipsum dolor sit amet, consectetur adipiscing volutpat.";
const char * COMPLEX_BODY = "There's a need for random symbols &!@#$%^&*() and tags <b></b><strong></strong><html></html>";

int main () {
	const int VALUES = 5000;
	map * results;
	int i, j, rows, error, returnCode = EXIT_SUCCESS;

	// --------------------------------------------------------------------------
	printf("> Connect to database... ");
	fflush(stdout);
	if (db_connect() != FITZ_SUCCESS) {
		puts("not ok");
		returnCode = EXIT_FAILURE;
	} else {
		puts("ok");
	}

	// --------------------------------------------------------------------------
	printf("> Insert some innocuous values... ");
	fflush(stdout);
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];
		char author[64];
		char date[64];

		char * body = malloc(strlen(SIMPLE_BODY+1));;
		time_t t = time(NULL);

		sprintf(title, "Title %d", i);
		strcpy(body, SIMPLE_BODY);
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
	fflush(stdout);
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
	fflush(stdout);
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
	printf("> Insert some values, esapcing first... ");
	fflush(stdout);
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];
		char author[64];
		char date[64];

		char * body = malloc(strlen(COMPLEX_BODY+1));;
		time_t t = time(NULL);

		sprintf(title, "Random symbol test '%d'!", i);
		strcpy(title, db_escape(title));

		strcpy(body, COMPLEX_BODY);
		strcpy(body, db_escape(body));

		strcpy(author, "Me");
		strcpy(author, db_escape(author));

		strftime(date, sizeof(date), "%F %T", localtime(&t));
		strcpy(date, db_escape(date));

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
	fflush(stdout);
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];

		sprintf(title, "Random symbol test '%d'!", i);
		strcpy(title, db_escape(title));

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
	fflush(stdout);
	for (i = 0; i < VALUES; ++i) {
		char query[1024];
		char title[64];

		sprintf(title, "Random symbol test '%d'!", i);
		strcpy(title, db_escape(title));

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
	fflush(stdout);
	db_close();
	puts("ok");

	return returnCode;
}
