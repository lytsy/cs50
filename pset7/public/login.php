<?php
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("login_form.php", ["title" => "Log In"]);
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

        $rows = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        if (count($rows) == 1)
        {
            $row = $rows[0];

            if (password_verify($_POST["password"], $row["hash"]))
            {
                $_SESSION["id"] = $row["id"];
                redirect("/");
            }
        }

        apologize("Invalid username and/or password.");
    }

?>
