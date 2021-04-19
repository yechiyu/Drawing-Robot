<?php
error_reporting(E_ALL);
set_time_limit(0);

$service_port = 8080;
$address = "127.0.0.1";

$direction = $_POST['direction'];

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket < 0) {
  echo "socket_create() failed: reason: " . socket_strerror($socket) . "\n";
} else {
  echo "OK.\n";
}

$result = socket_connect($socket, $ip, $port);
if ($result < 0) {
  echo "socket_connect() failed.\nReason: ($result) " . socket_strerror($result) . "\n";
} else {
  echo "connect OK<br>";
}

$out = '';

if (!socket_write($socket, $direction, strlen($direction))) {
  echo "socket_write() failed: reason: " . socket_strerror($socket) . "\n";
} else {
  echo "Message sent to server successful！\n";
  echo "The content to be sent is: fine name = $direction ";
}


while($out = socket_read($socket, 8192)) {
  echo "The receiving server returned the message successfully！<br>";
  echo "The accepted content is:", $out;
}

echo "close SOCKET...<br>";
socket_close($socket);
echo "close OK<br>";

?>