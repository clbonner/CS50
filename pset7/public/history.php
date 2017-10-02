<?php

    // configuration
    require("../includes/config.php"); 

    // get transaction log for user
    $rows = CS50::query("SELECT * FROM history WHERE user_id = " . $_SESSION["id"]);
    
    // copy history to new array
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[] = [
            "date" => $row["date"],
            "type" => $row["type"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"]
        ];
    }
    
    // render transaction log
    render("history.php", ["title" => "History", "positions" => $positions]);

?>
