<div class="container">
    <form action="sell.php" method="post">
       <select class="form-item" name="symbol">
            <option disabled>Choose symbol</option>
            <?php foreach ($positions as $position): ?> 
                <option value="<?= htmlspecialchars($position["symbol"]) ?>">
                    <?= htmlspecialchars($position["name"])." (".htmlspecialchars($position["shares"])."x".htmlspecialchars($position["price"])."$)" ?>
                </option>
            <?php endforeach ?> 
        </select>
        <input  class="form-item" type="number" name="shares"  min="0"value="0">
        <input class="form-item" type="submit" value="Sell">
    </form>
</div>