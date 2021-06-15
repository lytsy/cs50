<?php
    require("../includes/config.php");
    $id = get_user_id();

    $user_history = CS50::query("SELECT * FROM history WHERE user_id = ?", $id);
    if (count($user_history)> 0){
        
        $positions = [];
        foreach ($user_history as $row)
        {
            $splitTimeStamp = explode(" ", $row["time"]);
            $positions[] = [
                "action" => $row["action"],
                "symbol" => $row["symbol"],
                "shares" => number_format($row["shares"], 2, '.', ''),
                "price" => number_format($row["price"], 2, '.', ''),
                "date" => $splitTimeStamp[0],
                "time" => $splitTimeStamp[1]
            ];
        }

        render(
            "history.php", 
            [
                "title" => "History", 
                "positions" => $positions
            ]
        );
    }
    render(
        "report.php", 
        [
            "title" => "History", 
            "header" => "History", 
            "message"=> "History is empty."
        ]
    );
?>