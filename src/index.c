#include "page.h"

int main () {
  initPage();

	useTemplate(MAIN);

  setSlot(BODY,
    "<strong>On github</strong>\n \
			<div style=\"text-align: right;\"><em>January 25, 2011</em></div>\n \
			<br /> \n \
			I've put the site's code up on github for all to see.\n \
			<a href=\"https://github.com/afitz0/fitzface\">Here's the link.</a>\n \
			<div style=\"text-align: right;\"><a href=\"/aboutMe\">A. Fitz</a></div>\n \
\
		<br />\n \
		<hr />\n \
		<br />\n \
\
    <strong>Downtime</strong>\n \
			<div style=\"text-align: right;\"><em>January 21, 2011</em></div>\n \
			<br /> \n \
			After a long period of downtime caused by a power outage, my site is back up\n \
			and I can start working on the site again.\n \
			<br />\
			<br />\
			A lot has happened since my last post. I'll say more later.\n \
			<div style=\"text-align: right;\"><a href=\"/aboutMe\">A. Fitz</a></div>\n \
\
		<br />\n \
		<hr />\n \
		<br />\n \
\
		<strong>Update</strong>\n \
			<div style=\"text-align: right;\"><em>December 6, 2010</em></div>\n \
			<br /> \n \
			It's obviously been over a month since my last (and first) update, but I have been working \
			on the site. I started working on a good interface for creating new posts here \
			and as part of that process began working on the database API. It's probably \
			not surprising to hear that I quickly ran into the desire to have something \
			akin to an associative array. So I made one. From scratch. Fortunately it wasn't \
			difficult as hash tables are the quintessential A&amp;DS project. Implementing it was \
			a friendly reminder of what's involved. \
			<br /><br /> \
			So now that I have a working associative array, I need to devise a structure \
			for holding results from database queries, connect the form interface to the DBI, \
			create an API for sanitising form input, and any number of other things. \
			<br /><br /> \
			Outside of the site itself, it's now only 9 days from when I'll be living in London. \
			I fly out next Wednesday and then begins my 5-month (or so) stay in England. I plan \
			on using this site to chronicle that stay, through blog posts and photos. \
			<div style=\"text-align: right;\"><a href=\"/aboutMe\">A. Fitz</a></div>\n \
\
		<br />\n \
		<hr />\n \
		<br />\n \
\
		<strong>New site</strong>\n \
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

	setSlot(FOOT,
		"This page <a href=\"http://validator.w3.org/check?uri=http%3A%2F%2Ffitzface.com\">validated with W3C</a>",
		HTML_RAW
	);

  renderPage();

  return 0;
}
