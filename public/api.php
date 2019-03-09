<?php
ini_set("display_errors", true);
header("Content-Type: application/json");

if ($_SERVER["REQUEST_METHOD"] === "GET") {
	if (isset($_GET["in"])) {
		$input = &$_GET["in"];
	} else {
		http_response_code(400);
		print json_encode(
			[
				"status" => "error",
				"message" => "\"in\" parameter required!"
			],
			128
		);
		exit;
	}
} else {
	if (isset($_POST["in"])) {
		$input = &$_POST["in"];
	} else if (isset($_GET["in"])) {
		$input = &$_GET["in"];
	} else {
		http_response_code(400);
		print json_encode(
			[
				"status" => "error",
				"message" => "\"in\" parameter required!"
			],
			128
		);
		exit;
	}
}

if (!is_string($input)) {
	http_response_code(400);
	print json_encode(
		[
			"status" => "error",
			"message" => "\"in\" parameter must be a string!"
		],
		128
	);
	exit;
}

$input = trim(strtolower($input));

if (isset($_GET["name"]) && is_string($_GET["name"])) {
	$name = $_GET["name"];
} else {
	$name = "User";
}

if (isset($_GET["nickname"]) && is_string($_GET["nickname"])) {
	$nickname = $_GET["nickname"];
} else {
	$nickname = "User";
}

$input = escapeshellarg($input);
$name = escapeshellarg($name);
$nickname = escapeshellarg($nickname);
$ext = escapeshellarg(__DIR__."/../ai_gt01.so");
$bin = escapeshellarg(__DIR__."/../bin/gt01.php");
$output = trim(shell_exec("/usr/bin/php -d extension={$ext} {$bin} {$input} {$name} {$nickname}"));
date_default_timezone_set("Asia/Jakarta");
print json_encode(
	[
		"response" => (($output === "") ? null : $output),
		"server_time" => time()
	]
);
