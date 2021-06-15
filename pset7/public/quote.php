<?php
require("../includes/config.php"); 

if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    render("quote_form.php", ["title" => "Search symbol"]);
}

else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    if (empty($_POST["symbol"]))
    {
        apologize("You must provide symbol.");
    }

    $stock = lookup($_POST["symbol"]);
    if (!$stock) {
        apologize("Symbol not finded.");
    }

    $price = number_format($stock["price"], 2, '.', '');
    render(
        "quote.php", 
        [
            "title" => "Symbol information", 
            "name" => $stock["name"], 
            "price" =>$price
        ]
    );
   
}

?>
