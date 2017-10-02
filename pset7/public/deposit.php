<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("deposit_funds.php", ["title" => "Deposit Funds"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (is_numeric($_POST["funds"]) == false)
            apologize("You must enter a number.");
        
        $rows = CS50::query("UPDATE users SET cash = cash + " . $_POST["funds"] . " WHERE id = " . $_SESSION["id"]);
        
        if ($rows !== 1)
        {
            // insert failed
            apologize("An error occured.");
        }
        
        $rows = CS50::query("INSERT INTO history (type, price, user_id) VALUES('DEPOSIT', " . $_POST["funds"] . ", " . $_SESSION["id"] . ")");
        
        render("../views/deposit.php", ["title" => "Funds Desposited", "funds" => $_POST["funds"]]);
    }

?>