<div class="container">
    <h1>Bought</h1>
    <p><?= "You successfully bought ".htmlspecialchars($report["shares"])." shares of ".htmlspecialchars($report["symbol"])."." ?></p>
    <p><?= "Cash spended: ".htmlspecialchars($report["cost"])."$." ?></p>
    <p><?= "Current balance: ".htmlspecialchars($report["cash"])."$." ?></p>
</div>
