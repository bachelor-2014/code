#ifndef SPLOTBOT_WRAPPER_H
#define SPLOTBOT_WRAPPER_H

#include <node.h>
#include <string>

class SplotbotWrapper : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  explicit SplotbotWrapper();
  ~SplotbotWrapper();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> runCode(const v8::Arguments& args);
  static v8::Handle<v8::Value> runRucolaCode(const v8::Arguments& args);
  static v8::Handle<v8::Value> registerCallback(const v8::Arguments& args);
  static void eventCallback(std::string name, std::string data);
  static v8::Persistent<v8::Function> constructor;
  double value_;
  static v8::Persistent<v8::String> callback;
  static v8::Persistent<v8::Object> module;

};

#endif
