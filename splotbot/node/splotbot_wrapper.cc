#include <node.h>
#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>

#include "splotbot_wrapper.h"
#include "../cpp/splotbot.h"

// Javascript interopbility
using namespace v8;
using namespace std;

Persistent<Function> SplotbotWrapper::constructor;
Persistent<String> SplotbotWrapper::callback;
Persistent<Object> SplotbotWrapper::module;

Splotbot *splotbot;

SplotbotWrapper::SplotbotWrapper() {
}

SplotbotWrapper::~SplotbotWrapper() {
}

/**
 * Initialize the component
 */
void SplotbotWrapper::Init(Handle<Object> exports) {

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  tpl->SetClassName(String::NewSymbol("SplotbotWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("runCode"),
      FunctionTemplate::New(runCode)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("runRucolaCode"),
      FunctionTemplate::New(runRucolaCode)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("rucolaDocumentation"),
      FunctionTemplate::New(rucolaDocumentation)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("registerCallback"),
      FunctionTemplate::New(registerCallback)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());

  exports->Set(String::NewSymbol("SplotbotWrapper"), constructor);

  // Reach the function in the .js file (it emits the data over the socket)
  callback = NODE_PSYMBOL("eventCallback");

  module = Persistent<Object>::New(exports);

}

Handle<Value> SplotbotWrapper::New(const Arguments& args) {
  HandleScope scope;


  v8::String::Utf8Value param1(args[0]->ToString());
  string configFile = string(*param1);

  v8::String::Utf8Value param2(args[1]->ToString());
  string mendelSocket = string(*param2);

  // Make the splotbot.
  splotbot = new Splotbot(configFile,mendelSocket);
  splotbot->registerCallback(eventCallback);
  splotbot->run();

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

/**
 * Run instructions
 */
Handle<Value> SplotbotWrapper::runCode(const Arguments& args) {
    HandleScope scope;

    // Accept array of instructions
    Handle<Array> jArr = Handle<Array>::Cast(args[0]);

    // Accept length of instruction array
    int num = jArr->Get(1)->NumberValue();
    uint length = jArr->Length();

    // "cast" the array to a vector
    vector<int> v;
    for(int i=0; i<length; i++) {
        v.push_back(jArr->Get(i)->NumberValue());
    }
    int *arr = &v[0];

    // Perform the instructions
    splotbot->executeInstructions(length,arr);

    // Return 0
    return scope.Close(Number::New(0));
}

/**
 * Run Rucolang Code
 */
Handle<Value> SplotbotWrapper::runRucolaCode(const Arguments& args) {
    HandleScope scope;

    v8::String::Utf8Value param1(args[0]->ToString());

    std::string code = std::string(*param1);

    //execute the rucolangcode
    splotbot->executeRucolaCode(code);

    // Return 0
    return scope.Close(Number::New(0));
}

/**
 * Rucolang documentation
 */
Handle<Value> SplotbotWrapper::rucolaDocumentation(const Arguments& args){
    HandleScope scope;

    string doc = splotbot->rucolaDocumentation();

    return scope.Close(String::New(doc.c_str()));
}


/**
 * Handle callbacks in c
 * TODO: Make this work
 */
Handle<Value> SplotbotWrapper::registerCallback(const Arguments& args){
    HandleScope scope;

    cout << "YES";
    return scope.Close(Number::New(0));
}

/**
 * This is a fallback for the callback method
 * Send http requests to the server
 */
void SplotbotWrapper::eventCallback(string name, string data) {
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,
            ("http://localhost:8000/event/"+name).c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (data.length()+1));
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
