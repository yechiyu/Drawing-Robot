<?php
    $imgname = $_FILES['myfile']['name'];
    $tmp = $_FILES['myfile']['tmp_name'];
    $filepath = '../storeImg';
    echo $imgname;
    if(move_uploaded_file($tmp,$filepath.$imgname)){
        echo "上传成功";
    }else{
        echo "上传失败";
    }
?>