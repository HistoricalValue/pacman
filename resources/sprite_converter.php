<?php

if ($argc < 4) { ?>
Converts the sprites configuration file so that the dot sprites are
shifted by 2 pixels (x and y).

Requires three(3) arguments : the file to be read, the dot starting id
(included) and the dot last id (not included)

Prints result in stdout.
<?php return; } // help

$old_config = file ($argv[1]);
$id_base = intval($argv[2]);
$id_top  = intval($argv[3]);

foreach ($old_config as $line) {
	if (ereg('^#', $line)) { // comment line
		// just print
		echo ($line);
	} else {
		$toks = split('[[:space:]]', $line);
		$id	= $toks[0];
		$x 	= $toks[1];
		$y	= $toks[2];
		$z	= $toks[3];
		$fid	= $toks[4];
		$reps	= $toks[5];
		if ($id >= $id_base && $id < $id_top) { // is dot
			$x += 2;
			$y += 2;
		}
		echo ("$id $x $y $z $fid $reps\n");
	}
}

?>
