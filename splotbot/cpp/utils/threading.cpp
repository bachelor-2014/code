#include "threading.h"
#include <pthread.h>

using namespace std;

void *runner(void *param) {
    function<void()> func = *((function<void()> *) param);
    func();
    pthread_exit(0);
}

void runAsThread(function<void()> func) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t tid;
    pthread_create(&tid, &attr, runner, (void *) &func);
}
