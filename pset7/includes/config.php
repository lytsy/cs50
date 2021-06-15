<?php

    /**
     * config.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Configures app.
     */
    
    // display errors, warnings, and notices
    
    ini_set("display_errors", true);
    error_reporting(E_ALL);
    $ALPHAVANTAGE_API_KEY="MYMJH87UF4LSBY0L";
    /* get your free API_KEY: https://www.alphavantage.co/support/#api-key */
    
    // requirements
    require("helpers.php");


    // CS50 Library
    require("../vendor/library50-php-5/CS50/CS50.php");
    CS50::init(__DIR__ . "/../config.json");

    // enable sessions
    session_start();

    // require authentication for all pages except /login.php, /logout.php, and /register.php
    if (!in_array($_SERVER["PHP_SELF"], ["/login.php", "/logout.php", "/register.php", "/restore_password.php"]))
    {
        if (empty($_SESSION["id"]))
        {
            redirect("login.php");
        }
    }

?>
