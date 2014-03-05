#ifndef _THREADING_H_
#define _THREADING_H_

#include <iostream>

using namespace std;

void runAsThread(function<void()> func);

#endif
