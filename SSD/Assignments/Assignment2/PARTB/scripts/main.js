$(document).ready(function()
{
    $('#header').load("header.html");
    $('#footer').load("footer.html");
    console.log($(".menuitem").log);
    console.log($(".menuitem").log);
});
$(".menuitem")
.click(function() {
    $(".menuitem").removeClass("active");
    $(this).addClass("active");
 });