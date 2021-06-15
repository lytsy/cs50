<div class="container">
    <table  class ="tab"> 
        <tr class="tab-title">
            <td>action</td>
            <td>symbol</td>
            <td>shares</td>
            <td>price</td>
            <td>date</td>
            <td>time</td>
        </tr>

        <?php foreach ($positions as $position): ?> 

        <tr>
            <td><?= htmlspecialchars($position["action"]) ?></td>
            <td><?= htmlspecialchars($position["symbol"]) ?></td>
            <td><?= htmlspecialchars($position["shares"]) ?></td>
            <td><?= htmlspecialchars($position["price"]) ?></td>
            <td><?= htmlspecialchars($position["date"]) ?></td>
            <td><?= htmlspecialchars($position["time"]) ?></td>
        </tr>
            
        <?php endforeach ?> 
    </table>

</div>
