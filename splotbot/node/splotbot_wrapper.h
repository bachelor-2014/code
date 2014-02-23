#ifndef SPLOTBOT_WRAPPER_H
#define SPLOTBOT_WRAPPER_H

#include <node.h>

class SplotbotWrapper : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  explicit SplotbotWrapper();
  ~SplotbotWrapper();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> runCode(const v8::Arguments& args);
  static v8::Handle<v8::Value> sendImage(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;
  double value_;
};

#endif
