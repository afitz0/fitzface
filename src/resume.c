#include "page.h"

int main () {
	initPage();
	includejQuery();
	useTemplate(MAIN);

  setSlot(TITLE, 
    "Fitzface.com",
		TEXT_RAW
  );

	setSlot(BODY,
		"resumeText.html",
		HTML_FILE
	);

	setSlot(FOOT,
		"This page <a href=\"http://validator.w3.org/check?uri=http%3A%2F%2Ffitzface.com%2Fresume\">validated with W3C</a>",
		HTML_RAW
	);

	renderPage();
}
