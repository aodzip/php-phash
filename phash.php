<?php
$hash_1 = phash('/home/aodzip/test/compare/1.jpg');
$hash_2 = phash('/home/aodzip/test/compare/2.jpg');
$hash_a = phash('/home/aodzip/test/compare/a.jpg');
$hash_b = phash('/home/aodzip/test/compare/b.jpg');
echo bin2hex($hash_1) . "   " . decbin($hash_1) . PHP_EOL;
echo bin2hex($hash_2) . "   " . decbin($hash_2) . PHP_EOL;
echo bin2hex($hash_a) . "   " . decbin($hash_a) . PHP_EOL;
echo bin2hex($hash_b) . "   " . decbin($hash_b) . PHP_EOL;
echo hamming_distance($hash_1, $hash_2) . PHP_EOL;
echo hamming_distance($hash_a, $hash_b) . PHP_EOL;
