#include <iostream>
#include <pthread.h>
#include <mutex>

using namespace std;

mutex mtx;

void *runner(void *param) {
    int i = *((int*) param);
    for (int j = 0; j < 5; j++) {
        mtx.lock();
        cout << "Thread " << (i) << ": " << j << endl;
        mtx.unlock();
    }

    pthread_exit(0);
}

int main(int argc, char** argv) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t tids[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&tids[i], &attr, runner, ids+i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}
