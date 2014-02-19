#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "splotbot.h"

using namespace v8;

Persistent<Function> Splotbot::constructor;

Splotbot::Splotbot(double value) : value_(value) {
}

Splotbot::~Splotbot() {
}

void Splotbot::Init(Handle<Object> exports) {

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Splotbot"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("runCode"),
      FunctionTemplate::New(runCode)->GetFunction());
  constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("Splotbot"), constructor);
}

Handle<Value> Splotbot::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    Splotbot* obj = new Splotbot(value);
    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

Handle<Value> Splotbot::runCode(const Arguments& args) {
  HandleScope scope;

  Splotbot* obj = ObjectWrap::Unwrap<Splotbot>(args.This());
  obj->value_ += 1;

  return scope.Close(Number::New(obj->value_));
}
