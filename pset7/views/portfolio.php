<div>
    <table style="width:100%">
        <tr>
            <th>Symbol</th>
            <th>Company Name</th>
            <th>No. of Shares</th>
            <th>Price</th>
            <th>Value</th>
        </tr>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td>£<?= number_format($position["price"], 2) ?></td>
                <td>£<?= number_format($position["shares"] * $position["price"], 2) ?></td>
            </tr>
        <?php endforeach ?>
    </table>
    <br>
        <table style="width:100%">
            <tr>
                <td>Balance</td>
                <td>£<?= number_format($cash, 2) ?></td>
            </tr>
        </table>
</div>
