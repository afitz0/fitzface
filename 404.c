#include "page.h"

int main () {
	initPage();

	setSlot(HEAD, 
		"<title>Fitzface.com</title> \
		<link rel=\"stylesheet\" href=\"/main.css\" type=\"text/css\">",
		HTML_RAW
	);

	setSlot(BODY,
		"<br /> \
		<strong>Oops. That page doesn't exist!</strong> \
		<br /><br />",
		HTML_RAW
	);

	renderPage();
}
