#include <node.h>
#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>

#include "splotbot_wrapper.h"
#include "../cpp/splotbot.h"

using namespace v8;
using namespace std;

Persistent<Function> SplotbotWrapper::constructor;
Persistent<String> SplotbotWrapper::callback;
Persistent<Object> SplotbotWrapper::module;

Splotbot splotbot;

SplotbotWrapper::SplotbotWrapper() {
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

  tpl->PrototypeTemplate()->Set(String::NewSymbol("registerCallback"),
      FunctionTemplate::New(registerCallback)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());

  exports->Set(String::NewSymbol("SplotbotWrapper"), constructor);
  
  callback = NODE_PSYMBOL("eventCallback");

  module = Persistent<Object>::New(exports);

  splotbot.registerCallback(eventCallback);
}

Handle<Value> SplotbotWrapper::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    // double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    Local<Value> funcval = Local<Value>::New(args[0]);
    Local<Function> func = Local<Function>::Cast(funcval);
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

    //int num = jArr->Get(1)->NumberValue();
    uint length = jArr->Length();

    vector<int> v;
    for(uint i=0; i<length; i++) {
        v.push_back(jArr->Get(i)->NumberValue());
    }
    int *arr = &v[0];

    splotbot.executeInstructions(length,arr);

    return scope.Close(Number::New(0));
}

Handle<Value> SplotbotWrapper::registerCallback(const Arguments& args){
    HandleScope scope;
    //Local<Function> callback = Local<Function>::Cast(args[0]);
    //eventCallback = Persistent<Function>::New(callback);

    //function<void(string,string)> func = [](string name, string data) -> void {
    //    HandleScope funcscope;
    //    Local<Value> argv[2] = {
    //        Local<Value>::New(String::New(name.c_str())),
    //        Local<Value>::New(String::New(data.c_str()))
    //    };

    //    //callback->Call(Context::GetCurrent()->Global(), 0, NULL);
    //};


    cout << "YES";
    return scope.Close(Number::New(0));
}

void SplotbotWrapper::eventCallback(string name, string data) {
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,
            ("http://localhost:8080/event/"+name).c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (data.length()+1));
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
