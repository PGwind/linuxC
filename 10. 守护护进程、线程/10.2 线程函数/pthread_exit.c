#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void func(void)
{
    pthread_exit(NULL);     // 将当前线程退出
    return ;
}

void *tfn(void *arg)
{
    int i = (int)arg;
    sleep(i);

    if (i == 2) {
        // exit(0);        // 表示退出进程
        // return NULL;     // 表示返回到函数调用者
        // func();
        pthread_exit(NULL);
    }

    printf("Num: %dth, thread: pid = %d, tid = %lu\n", i+1, getpid(), pthread_self());
    return NULL;
}

int main()
{
    int i;
    int ret;
    pthread_t tid;

    for (i = 0; i < 5; i++) { 
        ret = pthread_create(&tid, NULL, tfn, (void *)i);   // 按值传递，借助强制转换
        if (ret != 0) {
            sys_err("pthread_create error");
        }
    }

    // sleep(i);
    printf("main: I'm Main, pid = %d, tid = %lu\n", getpid(), pthread_self());

    // return 0;

    pthread_exit((void*)0);
}
