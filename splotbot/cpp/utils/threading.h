#ifndef _THREADING_H_
#define _THREADING_H_

#include <functional>
#include <iostream>
#include <semaphore.h>

using namespace std;

void runAsThread(function<void()> func);

#endif
