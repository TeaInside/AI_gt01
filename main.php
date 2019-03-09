<?php

if (!function_exists("tea_gt01")) {
	unset($argv[0]);
	foreach ($argv as &$v) {
		$v = escapeshellarg($v);
	}
	unset($v);
	$ext = escapeshellarg(__DIR__."/ai_gt01.so");
	$file = escapeshellarg(__FILE__);
	$argv = implode($argv, " ");
	proc_close(proc_open(
		"php -d extension={$ext} {$file} {$argv}",
		[
			["pipe", "r"],
			["file", "php://stdout", "w"],
			["file", "php://stderr", "w"]
		],
		$pipes
	));
	unset($pipes);
	exit;
}

print tea_gt01(
	$argv[1],
	$argv[2] ?? "User",
	$argv[3] ?? "User"
);
