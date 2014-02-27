/**
 * C++11 Thread edition
 */

#include <v8.h>
#include <node.h>
#include <thread>
#include <string.h>
#include <iostream>

using namespace v8;
using namespace std;

// handles required for callback messages
Persistent<String> callback_symbol;
Persistent<Object> module_handle;


// callback that runs the javascript in main thread
static void Callback(int i)
{
    cout << "Callback called";
    HandleScope scope;

    // locate callback from the module context if defined by script
    // texample = require('texample')
    // texample.callback = function( ... ) { ..
    Local<Value> callback_v = module_handle->Get(callback_symbol);
    if (!callback_v->IsFunction()) {
         // callback not defined, ignore
         return;
    }
    Local<Function> callback = Local<Function>::Cast(callback_v);

    Local<Value> argv[1];
    argv[0] = Local<Value>::New(Integer::New(i));

    // call the callback and handle possible exception
    callback->Call(module_handle, 1, argv);
}

// The background thread
static void TheThread()
{
    int i = 0;
    while(true) {
        Callback(i);
        i++;
    }
}

// Start the background thread
Handle<Value> Start(const Arguments &args)
{
    cout << "Start called";
    HandleScope scope;
    
    TheThread();
    //thread(TheThread);

    return True();
}

void Initialize(Handle<Object> target)
{
    cout << "Initialize called";
    HandleScope scope;

    NODE_SET_METHOD(target, "start", Start);

    callback_symbol = NODE_PSYMBOL("callback");
    // store handle for callback context
    module_handle = Persistent<Object>::New(target);
}

extern "C" {
    static void Init(Handle<Object> target)
    {
        Initialize(target);
    }

    NODE_MODULE(texample, Init);
}
