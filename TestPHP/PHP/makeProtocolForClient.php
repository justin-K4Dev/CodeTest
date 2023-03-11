<?php
    include_once './Common/ErrorCode.php';
    include_once './Common/Protocol.php';
    include_once './Common/Define.php';
    
    $now = date('Y-m-d H:i:s', time());
    echo "//Update Date : $now\n"; 
?>

<pre>

// Command
public class COMMAND {
    <?php
    $reflKey = new ReflectionClass('Command');
    $defkeys = $reflKey->getConstants();
    foreach ($defkeys as $key => $val) {
        echo "\tpublic const string $key = \"$val\";\n";
    }
    ?>        
}

// Key
public class KEY {
    <?php
    $reflKey = new ReflectionClass('Key');
    $defkeys = $reflKey->getConstants();
    foreach ($defkeys as $key => $val) {
        echo "\tpublic const string $key = \"$val\";\n";
    }
    ?>
}

// Error
public class ERROR {
    <?php
    $reflKey = new ReflectionClass('ERROR_CODE');
    $defkeys = $reflKey->getConstants();
    foreach ($defkeys as $key => $val) {
        echo "\tpublic const int $key = $val;\n";
    }
    ?>
}

</pre>
