#include "page.h"

int main (int argc, char ** argv) {
	initPage();
	useTemplate(MAIN);

	setSlot(TITLE,
		"New Article",
		TEXT_RAW
	);

	setSlot(BODY,
		"<form name=\"register\" action=\"processPost\" method=\"post\">\n \
			<table id=\"form\">\n \
				<tr>\n \
					<td class=\"label\"><strong>Title:</strong></td>\n \
					<td><input type=\"text\" name=\"title\" style=\"width: 350px\" /></td>\n \
				</tr>\n \
			</table>\n \
			<strong>Article:</strong>\n \
			<br />\n \
			<textarea maxlength=\"1000\" rows=20 cols=100 name=\"area\" class=\"limited\"></textarea>\n \
			<br />\n \
			<input type=\"submit\" name=\"submit\" value=\"Register\"/>\n \
		</form>\n \
		",
		HTML_RAW
	);

	renderPage();
}
