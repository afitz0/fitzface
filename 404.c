#include "page.h"

int main () {
	initPage();
	useTemplate(MAIN);

	setSlot(TITLE,
		"Error 404",
		TEXT_RAW
	);

	setSlot(BODY,
		"<br /> \
		<strong>Oops. That page doesn't exist!</strong> \
		<br /><br />",
		HTML_RAW
	);

	renderPage();
}
