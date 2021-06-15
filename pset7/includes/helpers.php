<?php
    
    /**
     * helpers.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Helper functions.
     */

    require_once("config.php");
    
    /**
     * Apologizes to user with message.
     */
    function apologize($message)
    {
        render("apology.php", ["message" => $message]);
    }

    /**
     * Facilitates debugging by dumping contents of argument(s)
     * to browser.
     */
    function dump()
    {
        $arguments = func_get_args();
        require("../views/dump.php");
        exit;
    }

    /**
     * Logs out current user, if any.  Based on Example #1 at
     * http://us.php.net/manual/en/function.session-destroy.php.
     */
    function logout()
    {
        // unset any session variables
        $_SESSION = [];

        // expire cookie
        if (!empty($_COOKIE[session_name()]))
        {
            setcookie(session_name(), "", time() - 42000);
        }

        // destroy session
        session_destroy();
    }

    /**
     * Returns a stock by symbol (case-insensitively) else false if not found.
     */
    function lookup($symbol)
    {
        global $ALPHAVANTAGE_API_KEY;
        // reject symbols that start with ^
        if (preg_match("/^\^/", $symbol))
        {
            return false;
        }

        // reject symbols that contain commas
        if (preg_match("/,/", $symbol))
        {
            return false;
        }

        // headers for proxy servers
        $headers = [
            "Accept" => "*/*",
            "Connection" => "Keep-Alive",
            "User-Agent" => sprintf("curl/%s", curl_version()["version"])
        ];

        // open connection to Alphavantage
        $context = stream_context_create([
            "http" => [
                "header" => implode(array_map(function($value, $key) { return sprintf("%s: %s\r\n", $key, $value); }, $headers, array_keys($headers))),
                "method" => "GET"
            ]
        ]);
        
        $handle = @fopen("https://www.alphavantage.co/query?apikey={$ALPHAVANTAGE_API_KEY}&datatype=csv&function=TIME_SERIES_INTRADAY&interval=1min&symbol={$symbol}", "r", false, $context);
        if ($handle === false)
        {
            // trigger (big, orange) error
            trigger_error("Could not connect to Alphavantage!", E_USER_ERROR);
            exit;
        }
        // download second line of CSV file
        for ($i=0; $i < 2; $i++) { 
            $data = fgetcsv($handle);
        }
        
        if ($data === false || count($data) == 1)
        {
            return false;
        }

        // close connection to Alphavantage
        fclose($handle);

        // ensure symbol was found
        if ($data[1] === "0.00")
        {
            return false;
        }

        // return stock as an associative array
        return [
            "symbol" => strtoupper($symbol),
            "name" => $symbol,
            "price" => floatval($data[1])
        ];
    }

    /**
     * Redirects user to location, which can be a URL or
     * a relative path on the local host.
     *
     * http://stackoverflow.com/a/25643550/5156190
     *
     * Because this function outputs an HTTP header, it
     * must be called before caller outputs any HTML.
     */
    function redirect($location)
    {
        if (headers_sent($file, $line))
        {
            trigger_error("HTTP headers already sent at {$file}:{$line}", E_USER_ERROR);
        }
        header("Location: {$location}");
        exit;
    }

    /**
     * Renders view, passing in values.
     */
    function render($view, $values = [])
    {
        // if view exists, render it
        if (file_exists("../views/{$view}"))
        {
            // extract variables into local scope
            extract($values);

            // render view (between header and footer)
            require("../views/header.php");
            require("../views/{$view}");
            require("../views/footer.php");
            exit;
        }

        // else err
        else
        {
            trigger_error("Invalid view: {$view}", E_USER_ERROR);
        }
    }

    function get_user_id()
    {
        if (empty($_SESSION["id"])) {
            apologize("You must log in.");
        }
        return $_SESSION["id"];
    }    

?>
