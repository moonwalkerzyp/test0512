#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "redis_op.h"
#include "make_log.h"

#define TEST_LOG_MOUDUAL  "test"
#define TEST_LOG_PROC "main_test"

int main(void)
{
    redisContext * conn = NULL;
    redisReply *reply;
    

//    RVALUES value; 

    char buf[10][1024] = {{0}}; 
    RVALUES value = buf;

    int ret = 0;
    int num = 0;
    int i = 0;
     
    char * ip_str = "127.0.0.1";
    char * port   = "6379";

    char *key = "mylistkey1";
    char *value1 = "listvalue1";
    char *value2 = "listvalue2";
 
    

    conn = rop_connectdb_nopwd(ip_str,port);

    if(conn==NULL)
    {
        LOG(TEST_LOG_MOUDUAL,TEST_LOG_PROC,"[error]rop_connectdb_nopwd");
        goto END;
    }

    reply = redisCommand(conn,"subscribe %s","chanal2");
    while(1)
    {
        if(conn->obuf!=NULL)
        {
            sleep(1);
            printf("%s\n",conn->obuf);
        }
    }

    ret = rop_list_push(conn, key, value1);
    if(ret!=0)
    {
        printf("rop_list_push error\n");
        LOG(TEST_LOG_MOUDUAL,TEST_LOG_PROC,"[error]list_push");
        goto END;
    }

    ret = rop_list_push(conn, key, value2);
    if(ret!=0)
    {
        printf("rop_list_push error\n");
        LOG(TEST_LOG_MOUDUAL,TEST_LOG_PROC,"[error]list_push");
        goto END;
    }

    ret = rop_range_list(conn,key,0,1,value,&num);
    if(ret!=0)
    {
        printf("rop_range_list error\n");
        LOG(TEST_LOG_MOUDUAL,TEST_LOG_PROC,"[error]list_range");
        goto END;
    
    }

    ret = rop_string_set(conn,"stringkey","strvalue1");
    if(ret!=0)
    {
        printf("rop_string_set error\n");
        LOG(TEST_LOG_MOUDUAL,TEST_LOG_PROC,"[error]string_set");
        goto END;
    }

    printf("%d\n",num);
    for(i=0;i<num;i++)
    {
        printf("%s\n",value[i]);
    }

END:
    rop_disconnect(conn);
    return ret;
}

