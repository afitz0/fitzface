#include <stdio.h>
#include "page.h"
#include "db.h"
#include "map.h"
#include "errorCodes.h"

int main () {
	map results = map_init(10);
	char html[2048];

	initPage();

	useTemplate(MAIN);

	db_connect();
	if (db_query("select * from articles", &results) != FITZ_SUCCESS) {
		printf("db_query failed!\n");
	}

	sprintf(html, "<strong>%s</strong>\n \
		<div style=\"text-align: right;\"><em>%s</em></div>\n \
		<br />\n \
		%s \
		<br /><br />\n \
		<div style=\"text-align: right;\"><a href=\"/aboutMe\">%s</a></div>\n \
		",
		map_search(&results, "title")->value,
		map_search(&results, "date")->value,
		map_search(&results, "body")->value,
		map_search(&results, "author")->value
	);

	setSlot(BODY, html, HTML_RAW);

	renderPage();

	return 0;
}
