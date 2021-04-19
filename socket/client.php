<?php
error_reporting(E_ALL);
set_time_limit(0);
echo "<h2>TCP/IP Connection</h2>\n";
$port = 8080;
$ip = "127.0.0.1";

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket < 0) {
	echo "socket_create() failed: reason: " . socket_strerror($socket) . "\n";
}else {
	echo "OK.\n";
}

echo "trying connect '$ip' port: '$port'...\n";

$result = socket_connect($socket, $ip, $port);
if ($result < 0) {
	echo "socket_connect() failed.\nReason: ($result) " . socket_strerror($result) . "\n";
}else {
	echo "connect OK\n";
}

$in = "Ho\r\n";

$in .= "first blood\r\n";
$in1 = "12";
$out = '';

$in2 = $in1+1;

if(!socket_write($socket, $in2, strlen($in2))) {
	echo "socket_write() failed: reason: " . socket_strerror($socket) . "\n";
}else {
	echo "Message sent to server successful！\n";
	echo "The content to be sent is:<font color='red'>$in2</font> <br>";
}

if(!socket_write($socket, $in1, strlen($in1))) {
        echo "socket_write() failed: reason: " . socket_strerror($socket) . "\n";
}else {
        echo "Message sent to server successful！\n";
        echo "The content to be sent is:<font color='red'>$in1</font> <br>";
}

while($out = socket_read($socket, 8192)) {
	echo "The receiving server returned the message successfully！\n";
	echo "The accepted content is:",$out;
}
echo "close SOCKET...\n";
socket_close($socket);
echo "close OK\n";
?>

