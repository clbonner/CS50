<div>
    <b>Stock Symbol:</b> <?php echo($_SESSION["symbol"]); ?><br>
    <b>Name:</b> <?php echo($_SESSION["name"]); ?><br>
    <b>Price:</b> £<?php echo(number_format($_SESSION["price"], 2)); ?><br>
</div>