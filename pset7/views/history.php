<div>
    <table style="width:100%">
        <tr>
            <th>Date</th>
            <th>Type</th>
            <th>Stock</th>
            <th>No. of shares</th>
            <th>Price</th>
        </tr>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["date"] ?></td>
                <td><?= $position["type"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td>£<?= number_format($position["price"], 2) ?></td>
            </tr>
        <?php endforeach ?>
    </table>
</div>
