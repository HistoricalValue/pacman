<?php

if ($argc < 2) { ?>
Converts animation film config file from old type (relative pixels)
to new way (normal pixels).

Argument needed: filename to read.

Prints result to stdout.

<?php
return;} // help

$old_config = file($argv[1]);

// for each line
foreach ($old_config as $line) {
	if (ereg ('^#', $line)) // is comment line, just print
		echo ($line);
	else {
		$toks = split('[[:space:]]', $line);
		$i = 0;
		foreach ($toks as $tok) {
			if (!ereg('^[[:space:]]*$', $tok)) {
			if ($i < 3) { // do-not-care stuff - just print
				echo ($tok.' ');
			} else {
				$nums = split('[{,}]', $tok);
				$n = array();
				foreach ($nums as $num)
					if (!ereg('^[[:space:]]*$', $num))
						$n[] = $num << 3;
				echo ('{'."$n[0],$n[1],$n[2],$n[3]} ");
			}
			$i++;
			}
		}
		echo("\n");
	}
} // foreach line

?>
