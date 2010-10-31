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

	renderPage();
}
