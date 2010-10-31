#include "page.h"

int main () {
  initPage();

  setSlot(TITLE, 
    "About this site",
		TEXT_RAW
  );

	setSlot(HEAD,
    "<strong>Fitzface.com</strong>",
		HTML_RAW
	);

  setSlot(BODY,
    "<p> \
      This is Fitzface.com, web home for Andrew Fitz Gibbon. The site is not \
      made with Word Press, Drupal, or anything like that. Similarly, on the \
      backend, I don't use anything like Cake, or Django (though I might use \
      some jQuery here and there). The backend is a custom-built framework \
      written in C. Yes, that's right, I'm using a low-level compiled language \
      as a web programming framework. \
      <br /> \
      <br /> \
      Why? \
      <br /> \
      <br /> \
      Why not. I don't like PHP, and I'm getting increasingly frustrated with \
      interpreted languages with little-to-no typing. <em>Why don't you use \
      something like Java or Python?</em> you ask? With my work in HPC, I'm \
      more familiar with C than anything else. Perl-CGI might work, but Perl \
      doesn't have a strong enough type system for my tastes. \
      <br /> \
      That's Fitzface.com. A personal, modern web site built using C. Among \
      other things, I plan on chronicling its development here. \
    </p>",
		HTML_RAW
  );

  setSlot(RIGHT_BAR,
    "<ul> \
      <li><a href=\"/me\">About Me</a></li> \
      <li><a href=\"/site\">About Fitzface.com</a></li> \
      <li><a href=\"/resume\">My Resume</a></li> \
    </ul>",
		HTML_RAW
  );

  renderPage();
}
