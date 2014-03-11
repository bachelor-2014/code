#include <pthread.h>
#include <iostream>
#include "threading.h"
#include <unistd.h>
#include <semaphore.h>

sem_t sem; //TODO Could be better

void *runner(void *param) {
    function<void()> func = *((function<void()> *) param);
    sem_post(&sem);
    func();
    pthread_exit(0);
}

void runAsThread(function<void()> func) {
    sem_init(&sem, 0, 0);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t tid;
    pthread_create(&tid, &attr, runner, (void *) &func);
    sem_wait(&sem);
}
