<?php
error_reporting(E_ALL);
set_time_limit(0);

$port = 8080;
$ip = "127.0.0.1";

move_uploaded_file($file, $path . $fileName);

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket < 0) {
  echo "socket_create() failed: reason: " . socket_strerror($socket) . "\n";
}

$result = socket_connect($socket, $ip, $port);
if ($result < 0) {
  echo "socket_connect() failed.\nReason: ($result) " . socket_strerror($result) . "\n";
}

$out = '';

$fileName = 'get cpu temp';

if (!socket_write($socket, $fileName, strlen($fileName))) {
  echo "socket_write() failed: reason: " . socket_strerror($socket) . "\n";
}

while($out = socket_read($socket, 8192)) {
  echo "CPU:", $out;
}

socket_close($socket);


?>