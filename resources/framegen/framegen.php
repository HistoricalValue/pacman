#!/usr/bin/env php
<?php
error_reporting(E_ALL);

if ($argc > 1) if ($argv[1] == '--help') showHelp($exit = true);
if ($argc < 4) showHelp($exit = true);

$dx = intval($argv[1]);
$dy = intval($argv[2]);
$i  = intval($argv[3]);

$x = $y = 0;
while ($i--) {
	echo (' {'.$x.','.$y.',4,4}');
	$x += $dx; $y += $dy;
}


function showHelp($exit) {
	global $argv;
	echo(<<<EOS
Usage:
	$argv[0] dx dy repeats

EOS
	);
	if ($exit)
		exit;
}

?>
