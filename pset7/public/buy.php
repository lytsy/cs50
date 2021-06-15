<?php
require("../includes/config.php");
$id = get_user_id();

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    render("buy_form.php", ["title" => "Buy"]);
} else if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (empty($_POST["symbol"])) {
        apologize("Symbol can't be empty.");
    }
    if (empty($_POST["shares"])) {
        apologize("Shares can't be empty.");
    }
    if (!preg_match("/^\d+$/", $_POST["shares"])) {
        apologize("Shares must be positive integer.");
    }

    $cash_query = CS50::query("SELECT cash FROM users WHERE id = ?", $id);
    if (count($cash_query) != 1) {
        apologize("User not finded.");
    }

    $stock = lookup($_POST["symbol"]);
    if (!$stock) {
        apologize("Symbol not finded.");
    }

    $cost = $stock["price"] * $_POST["shares"];
    $cash = $cash_query[0]["cash"] - $cost;

    if ($cash < 0) {
        apologize("You don't have enought money.");
    }

    CS50::query(
        "UPDATE users SET cash = ? WHERE id = ?",
        $cash,
        $id
    );
    CS50::query(
        "INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
        $id,
        strtoupper($_POST["symbol"]),
        $_POST["shares"]
    );

    CS50::query(
        "INSERT INTO history (user_id, action, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP())",
        $id,
        "buy",
        strtoupper($_POST["symbol"]),
        $_POST["shares"],
        $stock["price"]
    );

    $report = [
        "shares" => $_POST["shares"],
        "symbol" => $_POST["symbol"],
        "cost" => $cost,
        "cash" => $cash
    ];
    render(
        "buy_report.php",
        [
            "title" => "Buy report",
            "report" => $report
        ]
    );
}
