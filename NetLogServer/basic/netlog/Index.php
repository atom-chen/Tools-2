<?php

// 启动文件，空文件，方便启动调试服务器
// header("location: http://127.0.0.1/webroot/index.html");
// exit;

$content = file_get_contents('index.html');

echo $content;

