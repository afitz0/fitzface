#include "page.h"

int main () {
  initPage();

  setSlot(TITLE, 
    "Fitzface.com",
		TEXT_RAW
  );

  setSlot(RIGHT_BAR,
    "<ul> \
      <li><a href=\"/aboutMe\">About Me</a></li> \
      <li><a href=\"/aboutSite\">About Fitzface.com</a></li> \
      <li><a href=\"/resume\">My Resume</a></li> \
    </ul>",
		HTML_RAW
  );

	setSlot(HEAD,
    "<strong><a href=\"/\">Fitzface.com</a></strong>",
		HTML_RAW
	);

  setSlot(BODY,
    "<strong>New site</strong> \
		<div style=\"text-align: right;\"><em>October 30, 2010</em></div> \
		<p> \
			This is a brand-new site. Obviously a work in progress. Check out the \
			links to the right for some more information, especially the <a href=\"/aboutSite\">About \
			Fitzface.com</a> page, which talks some about what this site is. The \
			fun part: its backend is written in C. \
			<br /><br /> \
			For the most part, it's just raw HTML. For now. The C doesn't do much \
			yet, but I plan on extending it to support all kinds of things \
			like forms, templates, articles, and full database interaction. I'll \
			be chroniclng what happens through more posts like this one. \
			<br /><br /> \
			<div style=\"text-align: right;\"><a href=\"/aboutMe\">A. Fitz</a></div> \
		</p>",
		HTML_RAW
  );

  renderPage();

  return 0;
}
