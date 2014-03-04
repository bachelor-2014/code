#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "splotbot_wrapper.h"

using namespace v8;

/**
 * Initialize
 */
void InitAll(Handle<Object> exports) {
      SplotbotWrapper::Init(exports);
}

// Expose the addon
NODE_MODULE(addon, InitAll)
