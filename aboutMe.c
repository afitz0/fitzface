#include "page.h"

int main () {
  initPage();

  setSlot(TITLE, 
    "About this site",
		TEXT_RAW
  );

	setSlot(HEAD,
    "<strong><a href=\"/\">Fitzface.com</a></strong>",
		HTML_RAW
	);

  setSlot(BODY,
    "<p> \
      This is me. \
    </p>",
		HTML_RAW
  );

  setSlot(RIGHT_BAR,
    "<ul> \
      <li><a href=\"/aboutMe\">About Me</a></li> \
      <li><a href=\"/aboutSite\">About Fitzface.com</a></li> \
      <li><a href=\"/resume\">My Resume</a></li> \
    </ul>",
		HTML_RAW
  );

  renderPage();
}
