$(function (){


    $(".desktop-icon-set").click(function() {
        $("#interface").load($(this).data("send"), function(){
        });
    });


    $("#cancelBt").click(function() {
        $("#sideValue").css("bottom","-200px");
    });
})