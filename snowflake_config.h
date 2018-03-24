//
// Created by 张成 on 2018/3/23.
//

#ifndef PHP_SNOWFLAKE_SNOWFLAKE_CONFIG_H
#define PHP_SNOWFLAKE_SNOWFLAKE_CONFIG_H

// 定义机器号  3位 机器号    支持8台
//
// 7位进程号取模值 计算 加起来总计10位   限制8台机器 进程数不超过128
// 根据机器数量作取舍
#define DEVICE_PID_NUMBER 7
#define DEVICE_NUMBER 0x000

#endif //PHP_SNOWFLAKE_SNOWFLAKE_CONFIG_H
