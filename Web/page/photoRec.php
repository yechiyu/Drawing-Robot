<?php
    if(isset($_FILES['photo']['tmp_name'])){
        $photo = $_FILES['photo']['tmp_name'];
        $fileName = $_FILES['photo']['name'];
        $path = "D:\apache\Apache24\htdocs\RTEP\storeImg";
        echo $path.$fileName;
        move_uploaded_file($photo, $path.$fileName);

        echo "<script>alert('提交成功!');location.href='".$_SERVER["HTTP_REFERER"]."';</script>";
    }
?>