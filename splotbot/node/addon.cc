#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "splotbot.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
      Splotbot::Init(exports);
}

NODE_MODULE(addon, InitAll)
