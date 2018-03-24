#include "snowflake.h"
#include "snowflake_config.h"

struct globle g_info;

int php_snowflake_workid;

#define   sequenceMask  (-1L ^ (-1L << 12L))

int pow_int(int n,int m)
{
    if( m == 1)
    {
        return n;
    }else{
        return n * pow_int(n, m -1);
    }
}


//only run once
void set_workid()
{
    //机器号搭配进程号
    pid_t pid = getpid();

    int val = (int)pid % pow_int(2,DEVICE_PID_NUMBER)  ;// 取模 需要进程数 不超过2的DEVICE_PID_NUMBER次方

    // 自定义机器号 拼接 进程取模值  当作机器唯一标识
    php_snowflake_workid =  ((DEVICE_NUMBER &0x3ff) << DEVICE_PID_NUMBER ) |  (val&0x3ff);


}

uint64_t get_curr_ms()
{
    struct timeval time_now;
    gettimeofday(&time_now,NULL);
    uint64_t ms_time =time_now.tv_sec*1000+time_now.tv_usec/1000;
    return ms_time;
}

uint64_t wait_next_ms(uint64_t lastStamp)
{
    uint64_t cur = 0;
    do {
        cur = get_curr_ms();
    } while (cur <= lastStamp);
    return cur;
}
int atomic_incr(int id)
{
    __sync_add_and_fetch( &id, 1 );
    return id;
}
uint64_t get_unique_id()
{

    uint64_t  uniqueId=0;
    uint64_t nowtime = get_curr_ms();
    uniqueId = nowtime<<22;
    uniqueId |=(php_snowflake_workid&0x3ff)<<12;


    if (nowtime <g_info.last_stamp)
    {
        perror("error");
        exit(-1);
    }
    if (nowtime == g_info.last_stamp)
    {
        g_info.seqid = atomic_incr(g_info.seqid)& sequenceMask;
        if (g_info.seqid ==0)
        {
            nowtime = wait_next_ms(g_info.last_stamp);
        }
    }
    else
    {
        g_info.seqid  = 0;
    }
    g_info.last_stamp = nowtime;
    uniqueId |=g_info.seqid;

    return uniqueId;
}
