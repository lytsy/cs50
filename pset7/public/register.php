<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("register_form.php", ["title" => "Register"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if ($_POST["password"]!=$_POST["confirmation"])
        {
            apologize("Password must be equal to confirmation.");
        }

        //email must be empty or valid
        if (!empty($_POST["email"]) && !filter_var($_POST["email"], FILTER_VALIDATE_EMAIL)) {
            apologize("Invalid email.");
        }

        $insert_query_result = CS50::query(
            "INSERT IGNORE INTO users (username, hash, cash, email) VALUES(?, ?, 10000.0000, ?)", 
            $_POST["username"], 
            password_hash($_POST["password"], PASSWORD_DEFAULT), 
            $_POST["email"]
        );

        if($insert_query_result == 0){
            apologize("Username already exists");
        }

        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        if (count($rows) == 1){
            $_SESSION["id"] = $rows[0]["id"];
            redirect("index.php");
        }
    }
?>