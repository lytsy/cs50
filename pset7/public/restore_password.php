<?php
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("restore_password.php", ["title" => "Settings"]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }

        if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }

        $user = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
        if (count($user) != 1)
        {
            apologize("Username invalid.");
        }

        $user_email = $user[0]["email"];
        if ($user_email !== $_POST["email"]) 
        {
            apologize("Email invalid.");
        }

        if (empty($user_email) || $user_email == NULL)
        {
            apologize("Your account dont have email for restore.");
        }

        $pwd = bin2hex(openssl_random_pseudo_bytes(4));
        $pwd_hash = password_hash($pwd, PASSWORD_DEFAULT);
        
        $subject = "Password reseted!";
        $message = "Your password was reseted. New password: {$pwd}";
        $is_mail_delivered = mail($user_email, $subject, $message);
        if (!$is_mail_delivered )
        {
            apologize("Failed to deliver mail.");
        }

        CS50::query(
            "UPDATE users SET hash = ? WHERE id = ?", 
            $pwd_hash, 
            $user[0]["id"]
        );

        render(
            "report.php", 
            [
                "title" => "Password reseted!", 
                "header" => "Password reseted!", 
                "message"=> "Password was reseted, new password sent to your email."
            ]
        );
    }
?>