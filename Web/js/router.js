$(function (){


    $(".desktop-icon-set").click(function() {
        $("#interface").load($(this).data("send"), function(){
        });
    });

    $(".desktop-icon-set1").click(function() {
        $("#interface").load($(this).data("send"), function(){
        });
        $.ajax({
            type:"post",
            url:"../page/profile.php",
            dataType:"html",
            success:function(data){
                $("#profile-sys-cpu").html(data);
            }
        })
    });

    $("#cancelBt").click(function() {
        $("#sideValue").css("bottom","-200px");
    });
})