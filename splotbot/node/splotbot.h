#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <node.h>

class Splotbot : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  explicit Splotbot(double value = 0);
  ~Splotbot();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> runCode(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;
  double value_;
};

#endif
