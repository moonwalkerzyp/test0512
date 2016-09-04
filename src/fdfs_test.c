#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/wait.h>


#include "make_log.h"


int main(int argc,char**argv)
{
    pid_t pid;         
    int pipefd[2]; //0 read   1 write 
    char fdfsid[128] = {0}; 

    pipe(pipefd);

    pid = fork();

    if(pid<0)
    {
        perror("fork error");
        return -1;
    }
    if(pid>0)
    {
        close(pipefd[1]); //关闭写端
        //parent
        wait(NULL);
        read(pipefd[0],fdfsid,sizeof(fdfsid));
        LOG("FDFS_MOUDUAL","FDFS_TEST","fdfs_id[%s]",fdfsid);
        printf("im parent %d\n",getpid());
    }
    else
    {
        //child
        close(pipefd[0]); //子进程写数据 关闭读端

        dup2(pipefd[1],STDOUT_FILENO);

        execlp("fdfs_upload_file","fdfs_upload_file","./conf/client.conf","abcd.txt",NULL);
        //perror("execlp error\n");
        LOG("FDFS_MOUDUAL_TEST","FDFS_TEST","error[%s]","execlp error");
        return -1;
    }


    //printf("hello world\n");
    return 0;
}
