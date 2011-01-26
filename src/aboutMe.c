#include "page.h"

int main () {
  initPage();

	useTemplate(MAIN);

  setSlot(TITLE, 
    "About this site",
		TEXT_RAW
  );

  setSlot(BODY,
    "<p> \
      This is me. \
    </p>",
		HTML_RAW
  );

  renderPage();
}
