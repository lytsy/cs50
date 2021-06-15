<?php
require("../includes/config.php");
$id = get_user_id();

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $portfolios = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $id);
    if (count($portfolios) == 0) {
        render(
            "report.php",
            [
                "title" => "Sell",
                "header" => "Empty",
                "message" => "You don't have stocks to sell."
            ]
        );
    }

    $positions = [];
    foreach ($portfolios as $portfolio) {
        $stock = lookup($portfolio["symbol"]);
        if (!$stock) {
            apologize("Symbol not finded.");
        }
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => number_format($portfolio["shares"], 2, '.', ''),
            "symbol" => $portfolio["symbol"]
        ];
    }
    render(
        "sell_form.php",
        [
            "title" => "Sell",
            "positions" => $positions
        ]
    );
} else if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (empty($_POST["symbol"])) {
        apologize("Symbol not selected.");
    }
    $symbol = $_POST["symbol"];

    if (empty($_POST["shares"])) {
        apologize("Shares not selected.");
    }
    $sell_shares = $_POST["shares"];

    if ($sell_shares <= 0) {
        apologize("Shares value invalid.");
    }

    $stock = lookup($symbol);
    if (!$stock) {
        apologize("Symbol not finded.");
    }
    $price = $stock["price"];
    if ($price <= 0) {
        apologize("Price invalid.");
    }

    $portfolio = CS50::query(
        "SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
        $id,
        $symbol
    );
    if (count($portfolio) != 1) {
        apologize("Price invalid.");
    }
    $user = CS50::query("SELECT * FROM users WHERE id = ?", $id);
    if (count($user) != 1) {
        apologize("User is not found.");
    }

    $shares_left = $portfolio[0]["shares"] - $sell_shares;
    if ($shares_left < 0) {
        apologize("You trying sell more shares than have.");
    }

    $cash_gain = $sell_shares * $price;
    $cash = $user[0]["cash"] + $cash_gain;
    $cash_update_result = CS50::query(
        "UPDATE users SET cash = ? WHERE id = ?",
        $cash,
        $id
    );
    if ($cash_update_result == 0) {
        apologize("Transaction failed.");
    }

    if ($shares_left > 0) {
        CS50::query(
            "UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
            $shares_left,
            $id,
            $symbol
        );
    } else {
        CS50::query(
            "DELETE FROM portfolios WHERE user_id = ? AND symbol = ?",
            $id,
            $symbol
        );
    }

    CS50::query(
        "INSERT INTO history (user_id, action, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP())",
        $id,
        "sell",
        strtoupper($symbol),
        $sell_shares,
        $price
    );

    render(
        "sell_report.php",
        [
            "title" => "Index",
            "shares" => $sell_shares,
            "cash_gain" => $cash_gain,
            "cash_updated" => $cash
        ]
    );
}
