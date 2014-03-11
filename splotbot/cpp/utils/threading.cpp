#include <pthread.h>
#include <iostream>
#include "threading.h"
#include <unistd.h>
#include <semaphore.h>

// Struct containing the necessary parameters to the thread runner function
typedef struct {
    sem_t *sem;
    function<void()> func;
} ThreadParam;

// Runner function for starting a new thread based on the given ThreadParam parameter
void *runner(void *param) {
    ThreadParam tp = *((ThreadParam *) param);

    function<void()> func = tp.func;
    sem_t *sem = tp.sem;

    sem_post(sem);
    func();
    pthread_exit(0);
}

// Runs the giving function in a separate thread
void runAsThread(function<void()> func) {
    sem_t sem;
    sem_init(&sem, 0, 0);

    ThreadParam tp;
    tp.sem = &sem;
    tp.func = func;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t tid;
    pthread_create(&tid, &attr, runner, (void *) &tp);

    sem_wait(&sem);
}
