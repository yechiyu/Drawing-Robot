$(function (){


    $(".desktop-icon-set").click(function() {
        $("#interface").load($(this).data("send"), function(){
        });
    });


    $("#cancelBt").click(function() {
        $("#sideValue").css("bottom","-200px");
    });

    $("#turnUp").click(function(){
        $.ajax({
            type : "post",
            url : "../page/moveCtrl.php",
            dataType: "json",
            data : {
                "direction": "Up"
            },
            success : function (data) {
                alert("returen!");
            },
        });
    });

    $("#turnLeft").click(function(){
        $.ajax({
            type : "post",
            url : "../page/moveCtrl.php",
            dataType: "json",
            data : {
                "direction": "Left"
            },
            success : function (data) {
            },
        });
    });

    $("#turnRight").click(function(){
        $.ajax({
            type : "post",
            url : "../page/moveCtrl.php",
            dataType: "json",
            data : {
                "direction": "Right"
            },
            success : function (data) {
            },
        });
    });

    $("#turnDown").click(function(){
        $.ajax({
            type : "post",
            url : "../page/moveCtrl.php",
            dataType: "json",
            data : {
                "direction": "Down"
            },
            success : function (data) {
            },
        });
    });
})