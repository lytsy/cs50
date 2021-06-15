<?php
    require("../includes/config.php"); 
    $id = get_user_id();

    $user_cash = CS50::query("SELECT cash FROM users WHERE id = ?", $id);
    if (count($user_cash) == 0){
        apologize("User not finded.");
    }
    $cash = number_format($user_cash[0]["cash"], 2, '.', '');

    $portfolios = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $id);
    if (count($portfolios) == 0){
        render(
            "report.php", 
            [
                "title" => "Portfolio", 
                "header" => "Portfolio", 
                "message"=> "Your portfolio is empty. Current balance: {$cash}$"
            ]
        );
    }
    $total=0;
    $positions = [];
    foreach ($portfolios as $portfolio)
    {
        $stock = lookup($portfolio["symbol"]);
        if (!$stock)
        {
            apologize("Symbol not finded.");
        }
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $portfolio["shares"],
            "symbol" => $portfolio["symbol"]
        ];
        $total+=$stock["price"]*$portfolio["shares"];
        
    }

    $total+=$cash;
    render(
        "portfolio.php", 
        [
            "positions" => $positions, 
            "title" => "Portfolio", 
            "cash"=>$cash,
            "total"=>$total
        ]
    );

?>
