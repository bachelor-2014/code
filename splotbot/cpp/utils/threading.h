#ifndef _THREADING_H_
#define _THREADING_H_

#include <iostream>

void runAsThread(std::function<void()> func);

#endif
