#!/usr/bin/env php
<?php
error_reporting(E_ALL);

if ($argc > 1) if ($argv[1] == '--help') showHelp($exit = true);
if ($argc < 6) showHelp($exit = true);

$dx = intval($argv[1]);
$dy = intval($argv[2]);
$times  = intval($argv[3]);
$offx = intval($argv[4]);
$offy = intval($argv[5]);

$x = $y = 0;
$id = 2000;
$op = 1;
switch ($op) {
	case 0 :
		$i = $times;
		while ($i--) {
			echo (' {'.($x + $off).','.$y.',4,4}');
			$x += $dx; $y += $dy;
		}
		break;
	case 1 :
		for ($i = 0; $i < $times; $i++) {
			echo ("$id ".($x + $offx)." ".($y + $offy).
			 " 120 dot\n");
			$x += $dx; $y += $dy; $id++;
		}
}

function showHelp($exit) {
	global $argv;
	echo(<<<EOS
Usage:
	$argv[0] dx dy repeats offset-x offset-y

EOS
	);
	if ($exit)
		exit;
}

?>
