#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
    HandleScope scope;

    // Callback handling
    const unsigned argc = 1;
    Local<Function> cb = Local<Function>::Cast(args[argc]);
    Local<Value> argv[argc] = { Local<Value>::New(String::New("Callback argument")) };
    cb->Call(Context::GetCurrent()->Global(), argc, argv);

    return scope.Close(String::New("method1"));
}

Handle<Value> Method2(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New("method2"));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("mCallbacks"), FunctionTemplate::New(Method)->GetFunction());
    exports->Set(String::NewSymbol("mReturns"), FunctionTemplate::New(Method2)->GetFunction());
}

NODE_MODULE(hello, init)
