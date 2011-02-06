$(document).ready(function() {
	$("#hideAll").click(hideall);
});

function hideall() {
	if ($("#hideAll").html() == "Hide All") {
		$(".block").slideUp('fast');
		$("#hideAll").html("Show All");
		$(".hideSection").children($("a")).html("Show");
	} else {
		$(".block").slideDown('fast');
		$("#hideAll").html("Hide All");
		$(".hideSection").children($("a")).html("Hide");
	}
}

function hide(section) {
	var id = "#"+section;
	var button = "#hide"+section;

	if ($(button).html() == "Hide") {
		$(id).slideUp('slow');
		$(button).html("Show");
	} else {
		$(id).slideDown('slow');
		$(button).html("Hide");
	}
}
