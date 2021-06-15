<div class="container">

    <table  class ="tab">   
    <tr class="tab-title">
        <td>symbol</td>
        <td>shares</td>
        <td>price</td>
    </tr>
    <?php foreach ($positions as $position): ?> 

    <tr>
        <td><?= htmlspecialchars($position["symbol"]) ?></td>
        <td><?= htmlspecialchars($position["shares"]) ?></td>
        <td><?= htmlspecialchars($position["price"])."$" ?></td>
    </tr>

    <?php endforeach ?> 
    <tr> 
        <td>cash:</td>
        <td colspan="2" class="al-right"> <?= htmlspecialchars($cash)."$"?></td>
    </tr>
    <tr> 
        <td>total:</td>
        <td colspan="2" class="al-right"> <?= htmlspecialchars($total)."$"?></td>
    </tr>
    </table>
        
   
    </div>
