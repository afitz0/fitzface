#include "page.h"

int main () {
  initPage();

	useTemplate(MAIN);

  setSlot(BODY,
    "<strong>New site</strong>\n \
		<div style=\"text-align: right;\"><em>October 30, 2010</em></div>\n \
			<br />\n \
			This is a brand-new site. Obviously a work in progress. Check out the\n \
			links to the right for some more information, especially the <a href=\"/aboutSite\">About\n \
			Fitzface.com</a> page, which talks some about what this site is. The\n \
			fun part: its backend is written in C.\n \
			<br /><br />\n \
			For the most part, it's just raw HTML. For now. The C doesn't do much\n \
			yet, but I plan on extending it to support all kinds of things\n \
			like forms, templates, articles, and full database interaction. I'll\n \
			be chroniclng what happens through more posts like this one.\n \
			<br /><br />\n \
			<div style=\"text-align: right;\"><a href=\"/aboutMe\">A. Fitz</a></div>\n \
	  ",
		HTML_RAW
  );

  renderPage();

  return 0;
}
