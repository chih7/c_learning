//producer_consumer.cpp
//chih
//20141021

#define PRODUCER_NUM   5  //生产者数
#define CONSUMER_NUM   4  //消费者数
#define DELAY_TIME     10  //生产(或消费)任务之间的最大时间间隔

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


const int BUFFER_LENGTH = 5;
int buffer[BUFFER_LENGTH];
int front = 0, rear = -1; // 缓冲区的前端和尾端
int size = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//编译时初始化锁为解锁状态
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;


void *producer(void *arg);
void *consumer(void *arg);

int main(int argc, char **argv)
{
    srand(getpid());  //初始化随机函数发生器

    pthread_t aThrd[CONSUMER_NUM+PRODUCER_NUM];
    int dwThrdIdx;
    for(dwThrdIdx = 0; dwThrdIdx < CONSUMER_NUM; dwThrdIdx++)
    {  //创建CONSUMER_NUM个消费者线程，传入(void*)dwThrdIdx作为ConsumerThread的参数
        pthread_create(&aThrd[dwThrdIdx], NULL, consumer, (void*)dwThrdIdx);
    }
    sleep(1);
    for(dwThrdIdx = 0; dwThrdIdx < PRODUCER_NUM; dwThrdIdx++)
    {
        pthread_create(&aThrd[dwThrdIdx], NULL, producer, (void*)dwThrdIdx);
    }
    while(1);
    return 0;
}

void *producer(void *arg)
{
    pthread_detach(pthread_self());//获取自身线程ID
    int dwThrdNo = (int)arg;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (size == BUFFER_LENGTH) // 如果缓冲区已满，等待; 否则，添加新产品
        {
            printf("buffer is full. producer is waiting...\n");
            pthread_cond_wait(&full_cond, &mutex);
        }
        // 往尾端添加一个产品
        rear = (rear + 1) % BUFFER_LENGTH;
        buffer[rear] = rand() % BUFFER_LENGTH;
        printf("producer produces the item %d: %d, Current Product Num: %d\n", rear, buffer[rear],size+1);
        ++size;
        if (size == 1) // 如果当前size=1, 说明以前size=0, 消费者在等待，则给消费者发信号
        {
            pthread_cond_broadcast(&empty_cond);
        }
        pthread_mutex_unlock(&mutex);
        sleep(rand()%DELAY_TIME + 1);
    }
}

void *consumer(void *arg)
{
    pthread_detach(pthread_self());//将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源
    int dwThrdNo = (int)arg;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        while (size == 0) // 如果缓冲区已空，等待; 否则，消费产品
        {
            printf("buffer is empty. consumer is waiting...\n");
            pthread_cond_wait(&empty_cond, &mutex);
        }
        // 从前端消费一个产品
        printf("consumer consumes an item%d: %d, Current Product Num: %d\n", front, buffer[front],size-1);
        front = (front + 1) % BUFFER_LENGTH;
        --size;
        if (size == BUFFER_LENGTH-1) // 由满变为非满时,如果当前size=BUFFER_LENGTH-1，说明以前生产者在等待，则给生产者发信号
        {
            pthread_cond_broadcast(&full_cond);
        }
        pthread_mutex_unlock(&mutex);
        sleep(rand()%DELAY_TIME + 1);
    }
}
