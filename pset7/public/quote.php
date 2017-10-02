<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Stock Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["stock"]))
            apologize("You must provide a valid stock code.");
        
        $s = lookup($_POST["stock"]);
        
        if($s == FALSE)
            apologize("Invalid stock code.");
        
        $_SESSION["price"] = $s["price"];
        $_SESSION["symbol"] = $s["symbol"];
        $_SESSION["name"] = $s["name"];
        
        render("quote.php");
    }

?>
