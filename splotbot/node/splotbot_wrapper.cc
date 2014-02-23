#include <node.h>
#include <vector>

#include "splotbot_wrapper.h"
#include "../cpp/splotbot.h"

using namespace v8;
using namespace std;

Persistent<Function> SplotbotWrapper::constructor;

SplotbotWrapper::SplotbotWrapper(){
}

SplotbotWrapper::~SplotbotWrapper() {
}

void SplotbotWrapper::Init(Handle<Object> exports) {

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  tpl->SetClassName(String::NewSymbol("SplotbotWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("runCode"),
      FunctionTemplate::New(runCode)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("sendImage"),
      FunctionTemplate::New(sendImage)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());

  exports->Set(String::NewSymbol("SplotbotWrapper"), constructor);
}

Handle<Value> SplotbotWrapper::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    SplotbotWrapper* obj = new SplotbotWrapper();
    obj->Wrap(args.This());
    return args.This();
  } else {
// Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 0;
    Local<Value> argv[argc] = {};
    return scope.Close(constructor->NewInstance(0, argv));
  }
}

Handle<Value> SplotbotWrapper::runCode(const Arguments& args) {
  HandleScope scope;

    Handle<Array> jArr = Handle<Array>::Cast(args[0]); //Array::New(length);

    int num = jArr->Get(1)->NumberValue();
    uint length = jArr->Length();

    vector<int> v;
    for(int i=0; i<length; i++) {
        v.push_back(jArr->Get(i)->NumberValue());
    }
    int *arr = &v[0];

    //Splotbot->runCode(length,arr);

  return scope.Close(Number::New(0));
}

Handle<Value> SplotbotWrapper::sendImage(const Arguments& args){
    HandleScope scope;

    return scope.Close(Number::New(0));
}
