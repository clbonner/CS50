<?php

    // configuration
    require("../includes/config.php"); 

    // get stocks
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = " . $_SESSION["id"]);
    
    // copy stocks in to new array
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    // get cash balance
    $rows = CS50::query("SELECT cash FROM users WHERE id =" . $_SESSION["id"]);
    
    // get account balance
    $cash = $rows[0]["cash"];
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>
