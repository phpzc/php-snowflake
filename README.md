# php-snowflake
php-snowflake extension 只支持Linux

- 默认配置8台机器支持 php-fpm 128个进程 自行修改 snowflake_config.h文件 改变数量

- 各个机器修改 DEVICE_NUMBER宏 代表各机器,在对应机器上编译即可

```
    <?php
    if(!extension_loaded('php_snowflake')){
    	die('php_snowflake not loaded'.PHP_EOL);
    }
    $time=microtime(true);
    for($i=0;$i<1000000;$i++){
      php_snowflake();
    }
    $time2=microtime(true);
    echo $time2 - $time;
    echo PHP_EOL;
 ```

 ```
 [root@phpzc-net php_snowflake]# /usr/local/php/php-5.6.22/bin/php -c /usr/local/php/php-5.6.22/etc/php.ini test.php
 0.24432897567749
 [root@phpzc-net php_snowflake]#
 ```
100w次只需要0.24秒