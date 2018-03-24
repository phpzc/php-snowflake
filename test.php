<?php
if(!extension_loaded('php_snowflake')){
    die('php_snowflake loaded'.PHP_EOL);
}
$time=microtime(true);
for($i=0;$i<1000000;$i++){
  php_snowflake();
}
$time2=microtime(true);
echo $time2 - $time;
echo PHP_EOL;