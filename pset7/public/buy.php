<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy Shares"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check shares input is valid
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
            apologize("Number of shares must be a positive whole number.");
        
        // convert symbol to upercase
        $symbol = strtoupper($_POST["symbol"]);
        
        // get current share price
        $s = lookup($symbol);
        if (empty($s))
            apologize("Invalid stock code.");
        
        // calculate sale price
        $sale = $s["price"] * $_POST["shares"];
        
        // get cash balance
        $rows = CS50::query("SELECT cash FROM users WHERE id =" . $_SESSION["id"]);
        
        // check they can afford to buy
        if ($sale > $rows[0]["cash"])
            apologize("You cannot afford to buy the requested shares.");
            
        // update users cash balance
        $update = CS50::query("UPDATE users SET cash = cash - " . $sale . " WHERE id = " . $_SESSION["id"]);
        
        // update users portfolio
        $update = CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(" . $_SESSION["id"] . ", '" . $symbol . "', " . $_POST["shares"] . ") ON DUPLICATE KEY UPDATE shares = shares + " . $_POST["shares"]);
        
        // update transaction log
        $update = CS50::query("INSERT INTO history (type, symbol, shares, price, user_id) VALUES('BUY','" . $symbol . "'," . $_POST["shares"] . "," . $sale . "," . $_SESSION["id"] . ")");
        
        render("../views/buy.php", ["sale" => $sale, "name" => $s["name"], "shares" => $_POST["shares"]]);
    }

?>
