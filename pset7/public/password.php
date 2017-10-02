<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password.php", ["title" => "Change Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check old password has been supplied
        if (empty($_POST["oldpw"]))
        {
            apologize("You must provide your password.");
        }
        
        // validate old password
        $hash = CS50::query("SELECT hash FROM users WHERE id = " . $_SESSION["id"]);
        if (password_verify($_POST["oldpw"], $hash[0]["hash"]) == false)
            apologize("Password incorrect.");
        else if ($_POST["newpw"] !== $_POST["confirmation"])
        {
            // passwords don't match
            apologize("The passwords do not match.");
        }
        
        // update hash in users table
        $rows = CS50::query("UPDATE users SET hash = '" . password_hash($_POST["newpw"], PASSWORD_DEFAULT) . "' WHERE id = " . $_SESSION["id"]);

        if ($rows !== 1)
        {
            // insert failed
            apologize("An error occured.");
        }
        else
            render("../views/password.php", ["title" => "Password Change Successfull"]);
    }

?>