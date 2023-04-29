#include "pthread.h"
#include "stdio.h"

void *th(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        printf("thread called %d\n", i);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thr;
    int ret;

    ret = pthread_create(&thr, NULL, th, NULL);

    if (ret != 0)
    {
        printf("error");
        return 2;
    }
    pthread_detach(thr);
    return 0;
}