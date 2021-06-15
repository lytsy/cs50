<?php
    require("../includes/config.php");
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("change_password.php", ["title" => "change password"]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {

        if (empty($_POST["new_password"]))
        {
            apologize("You must provide new password.");
        }
        else if (empty($_POST["old_password"]))
        {
            apologize("You must provide old password.");
        }
        else if ($_POST["new_password"]!=$_POST["confirmation"])
        {
            apologize("Password must be equal to confirmation.");
        }

        $id = get_user_id();
        $rows = CS50::query("SELECT * FROM users WHERE id = ?", $id);
        if (count($rows) == 1)
        {
            $user = $rows[0];
            if (password_verify($_POST["old_password"], $user["hash"]))
            {
                $new_hash = password_hash($_POST["new_password"], PASSWORD_DEFAULT);
                $update_query_result = CS50::query(
                    "UPDATE users SET hash = ? WHERE id = ?", 
                    $new_hash, 
                    $id
                );
                if (count($update_query_result) == 1) {
                    render(
                        "report.php", 
                        [
                            "title" => "Password changed!", 
                            "header" => "Success!", 
                            "message"=> "Password was successfuly changed."
                        ]
                    );
                }
            }
        }
        apologize("Failed to change password.");
    }

?>



