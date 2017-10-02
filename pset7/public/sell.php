<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell Shares"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // convert symbol to upercase
        $symbol = strtoupper($_POST["symbol"]);
        
        // get current share price
        $s = lookup($symbol);
        if (empty($s))
            apologize("Invalid stock code.");
            
        // check user has shares in company
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = " . $_SESSION["id"] . " AND symbol = '" . $symbol . "'");
        if (empty($rows))
            apologize("You don't have any shares in this company to sell.");
            
        // calculate sale price    
        $sale = $s["price"] * $rows[0]["shares"];
        
        // update portfolio and cash balance
        $update = CS50::query("DELETE FROM portfolios WHERE user_id = " . $_SESSION["id"] . " AND symbol = '" . $symbol . "'");
        $update = CS50::query("UPDATE users SET cash = cash + ". $sale ." WHERE id = ". $_SESSION["id"]);
        
        // update transaction log
        $update = CS50::query("INSERT INTO history (type, symbol, shares, price, user_id) VALUES('SELL', '" . $symbol . "'," . $rows[0]["shares"] . "," . $sale . "," . $_SESSION["id"] . ")");
        
        render("../views/sell.php", ["sale" => $sale, "name" => $s["name"]]);
    }

?>
