#include <stdio.h>
#include "page.h"
#include "db.h"
#include "map.h"

int main () {
	map results[5];
	char html[2048];

	initPage();

	useTemplate(MAIN);

	db_connect();
	db_query("select * from articles;", results);

	sprintf(html, "<strong>%s</strong>\n \
		<div style=\"text-align: right;\"><em>%s</em></div>\n \
		<br />\n \
		%s \
		<br /><br />\n \
		<div style=\"text-align: right;\"><a href=\"/aboutMe\">%s</a></div>\n \
		",
		map_search(&results[0], "title")->value,
		map_search(&results[0], "date")->value,
		map_search(&results[0], "body")->value,
		map_search(&results[0], "author")->value
	);

	setSlot(BODY, html, HTML_RAW);

	renderPage();

	return 0;
}
