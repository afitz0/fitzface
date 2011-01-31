#include <stdio.h>

#include "page.h"
#include "db.h"
#include "map.h"
#include "error.h"

int main () {
	map * results;
	char html[2048];
	int rows, error;

	initPage();

	useTemplate(MAIN);

	db_connect();
	results = db_query("select * from articles order by date desc", &rows, &error);

	if (error != FITZ_SUCCESS) {
		sprintf(html, "<strong>Error</strong>\n \
			Could not fetch entries from database! \
		");
	} else {
		if (rows == 0) {
			sprintf(html, "<strong>Empty</strong>\n \
				There was nothing in the database!\n \
			");
		} else {
			for (int i = 0; i < rows; i++) {
				sprintf(html, "<strong>%s</strong>\n \
					<div style=\"text-align: right;\"><em>%s</em></div>\n \
					<br />\n \
					%s \
					<br /><br />\n \
					<div style=\"text-align: right;\"><a href=\"/aboutMe\">%s</a></div>\n \
					<br />\n \
					<hr />\n \
					<br />\n \
					",
					map_search(&results[i], "title")->value,
					map_search(&results[i], "date")->value,
					map_search(&results[i], "body")->value,
					map_search(&results[i], "author")->value
				);

				appendSlot(BODY, html, HTML_RAW);
			}
		}
	}

	setSlot(FOOT,
		"This page <a href=\"http://validator.w3.org/check?uri=http%3A%2F%2Ffitzface.com\">validated with W3C</a>",
		HTML_RAW
	);

	renderPage();

	return 0;
}
