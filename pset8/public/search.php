<?php
/* Search matches in db for autocomplete location */

require(__DIR__ . "/../includes/config.php");
$query_limit = 20;

function send_search_result($places = [])
{
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));
    exit;
}

if (!isset($_GET['geo'], $_GET['geo'])) {
    http_response_code(400);
    exit;
}

/* First, we look for a match of a key with one field. If nothing is found, we expand the search, looking for less exact matches. */

$key = trim($_GET['geo']);
$rows = CS50::query(
    "SELECT * FROM places WHERE 
    country_code=? OR postal_code=? OR place_name LIKE ? OR admin_name1 LIKE ?  OR admin_code1=?
    LIMIT {$query_limit};",
    $key,
    $key,
    $key . "%",
    $key . "%",
    $key
);
if (count($rows) > 0) {
    send_search_result($rows);
}

$key = trim(str_replace(", ", "*, ", $_GET["geo"])) . "*";
$rows = CS50::query(
    "SELECT * FROM places WHERE 
    MATCH(country_code, postal_code, place_name, admin_name1, admin_code1) 
    AGAINST(? IN BOOLEAN MODE) 
    LIMIT {$query_limit};", 
    $key
);
send_search_result($rows);