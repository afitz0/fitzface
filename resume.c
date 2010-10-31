#include "page.h"

int main () {
	initPage();

  setSlot(TITLE, 
    "Fitzface.com",
		TEXT_RAW
  );

	setSlot(HEAD,
    "<strong>Fitzface.com</strong>",
		HTML_RAW
	);

	setSlot(BODY,
		"resumeText.html",
		HTML_FILE
	);

	renderPage();
}
