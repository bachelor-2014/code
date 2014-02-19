#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "splotbot_wrapper.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
      SplotbotWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)
