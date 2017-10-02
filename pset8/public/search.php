<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // if geo supplied, perform search on database
    if(!empty($_GET["geo"]))
    {
        // search postal_code for matching rows
        $rows = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name2) AGAINST (?)", $_GET["geo"]);
        
        // copy each row in to places
        if(!empty($rows))
        {
            foreach($rows as $row)
            {
                $places[] = $row;
            }
        }

        
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>